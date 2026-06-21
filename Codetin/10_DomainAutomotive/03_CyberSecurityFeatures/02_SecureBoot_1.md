
# Module 1: Foundational Automotive Security Concepts

### 1.1 The Threat Landscape in Automotive Firmware


The primary objectives of Secure Boot are:

* **Authenticity:** Ensuring the firmware originated from an authorized source (e.g., the OEM or Tier-1 supplier).
* **Integrity:** Ensuring the firmware has not been corrupted or maliciously modified.
* **Anti-Rollback:** Preventing an attacker from flashing an older, genuine firmware version that contains a known, exploitable security vulnerability.

### 1.2 The Chain of Trust (CoT)

Secure Boot relies on an unbroken Chain of Trust. Security is transitive: if Block A is trusted, and Block A verifies Block B before executing it, then Block B can be trusted.

The chain must start somewhere immutable. This is the **Root of Trust (RoT)**. In the RH850, the RoT is bound to the hardware:

1. **Hardware Core (Power-On Reset):** The MCU releases the internal Hardware Security Module (ICU-M) from reset first.
2. **ICU-M ROM/Firmware:** Executes immutable internal code that initializes the cryptographic engine and fetches the Root Public Key or Master Symmetric Key from protected fuses/Data Flash.
3. **Bootloader Verification:** The ICU-M verifies the Primary Bootloader (PBL) stored in Code Flash.
4. **Application Verification:** The verified PBL (or the ICU-M itself) verifies the Application software components.

### 1.3 Cryptographic Primitives: Symmetric vs. Asymmetric

When implementing Secure Boot, you will choose between two primary architectures:

| Feature | Symmetric (AES-CMAC) | Asymmetric (ECDSA / RSA) |
| --- | --- | --- |
| **Algorithm** | AES-128 or AES-256 in CMAC mode. | RSA-2048/3072 or ECC (Ed25519/NIST P-256). |
| **Key Management** | Same key used for signing (OEM) and verification (ECU). | Private key signs (OEM); Public key verifies (ECU). |
| **Security Risk** | High if compromised. If a hacker extracts the key from one ECU, they can sign firmware for all ECUs sharing that key. | Low if extracted. Compromising the public key in the ECU only allows an attacker to verify, not forge signatures. |
| **Execution Speed** | Extremely fast (microseconds via hardware accelerator). | Slower (milliseconds), computationally intensive. |
| **Signature Size** | Small (typically 16 bytes for MAC). | Large (64 bytes for ECC, 256–384 bytes for RSA). |

*Architectural Choice:* In modern automotive engineering, asymmetric verification is preferred for the Root of Trust (PBL verification) because it eliminates the risk of a leaked global symmetric key. However, symmetric verification (AES-CMAC) is frequently used for downstream application blocks due to stringent boot-time requirements (e.g., meeting the "early CAN frame" requirement within 50–100ms of clamping terminal 15/Ignition).

---

# Module 2: RH850 Hardware Security Architecture

### 2.1 The Intelligent Cryptographic Unit Master (ICU-M)

The RH850 protects keys and execution via an isolated hardware subsystem called the **ICU-M**. Think of it as a microcontroller within a microcontroller.

* **Processor Isolation:** The ICU-M features its own dedicated processor core, internal ROM, and internal RAM, completely isolated from the Main RH850 CPU cores (e.g., G3KH or G3M cores).
* **Hardware Accelerators:** It contains dedicated hardware logic for AES, true random number generation (TRNG), and public-key cryptography (PKI accelerator for RSA/ECC).
* **The Firewall:** The Main CPU cannot access the ICU-M's internal memory or key slots. Communication happens strictly through a command/response mailbox interface via dedicated hardware registers (e.g., `ICUM_MBX_CTRL`).

### 2.2 Memory Architecture & Partitioning

To implement Secure Boot, you must configure the RH850's Flash memory mapping correctly. The RH850 Code Flash is generally divided into:

* **User Boot Area (UBA):** A dedicated area of flash where the primary bootloader or boot-assist code resides. The MCU can be configured via option bytes to boot directly from this area.
* **User Area:** Where your main application, OS (e.g., AUTOSAR Classic), and communication stacks live.

The ICU-M has a dedicated, secured storage region within the non-volatile memory (often localized in specific sectors of Data Flash or dedicated OTP/fuses) called the **Secure Key Storage Region**. This area cannot be read by the main CPU via standard debugger or software instructions; read access is physically blocked at the hardware bus level.

---

# Module 3: Key Management & Storage on RH850

### 3.1 Root of Trust (RoT) Injection & Key Slots

The ICU-M contains predefined **Key Slots**. To establish your Root of Trust, keys must be provisioned during production. This is done in a secure manufacturing environment (End-of-Line or EOL programming).

1. **The Master Key:** This is the administrative key. Once a Master Key is written to the designated master key slot, any future key updates must be cryptographically authenticated using this key.
2. **Boot Verification Key Slots:** Dedicated slots that hold either the AES-CMAC key or the Public Key hash used to verify the boot image.

### 3.2 Key Attributes & Permissions

When you program a key into an ICU-M slot, you must write its associated **Key Attribute Configuration Word**. This configuration specifies:

* **Write Protection:** Making the slot permanent (One-Time Programmable / OTP emulation).
* **Usage Constraints:** Restricting a key so it can *only* be used by the verification engine, ensuring it can never be exported or used for general data decryption.

---

# Module 4: Secure Boot Flavors & Implementation Strategies

On the RH850, we design Secure Boot using one of three execution flows. Your choice depends directly on your OEM's boot time requirements.

### 4.1 Full Secure Boot (Hardware-Enforced / Sequential)

This is the most secure method. The Main CPU is held in a hardware reset state while the ICU-M wakes up, reads the bootloader image from Code Flash, verifies its signature against the stored key, and—only upon successful verification—releases the Main CPU reset line.

```
[Power On] 
    │
    ▼
[ICU-M Wakes Up] ──► [Fetches Verification Key]
    │
    ▼
[ICU-M Computes & Verifies Hash/Signature of PBL]
    │
    ├───► [Verification Fails] ──► [System Halts / Safe State]
    │
    └───► [Verification Passes]
                │
                ▼
      [Release Main CPU Reset] ──► [Main CPU Executes Bootloader]

```

### 4.2 Parallel / Background Boot Verification

If your vehicle network architecture requires the ECU to respond to CAN messages within 30ms of power-on, you cannot wait 40ms for an asymmetric signature check. You must implement a parallel boot.

1. On power-on, both the Main CPU and the ICU-M release from reset simultaneously.
2. The Main CPU immediately executes basic initialization and begins sending network management frames.
3. Simultaneously, the ICU-M hashes the application image in the background.
4. **The TOCTOU Risk:** This introduces a *Time-of-Check to Time-of-Use* vulnerability. The Main CPU is executing code that has not yet been proven authentic.
5. **Mitigation:** The Main CPU must be software-constrained from performing critical, safety-relevant actions (like activating actuators or enabling full communication) until it polls the ICU-M mailbox and receives a positive `BOOT_VALIDATED` status token.

### 4.3 Sequential Software-Assisted Secure Boot

In this model, the Main CPU boots first into an immutable **Boot ROM** or highly protected **Primary Bootloader (PBL)**. The PBL then handles the execution flow:

1. The PBL configures a DMA channel to stream the application image from Code Flash into the ICU-M's input mailbox.
2. The PBL issues an `ICU_VERIFY_SIGNATURE` command.
3. The PBL waits for the hardware response register to indicate success before jumping to the application entry point.

---

# Module 5: Firmware Image Structure & Metadata

To make your firmware verifiable, you cannot just output a raw binary from your compiler/linker toolchain. You must wrap it in a specific container structure via a post-build signing script (typically written in Python using libraries like `cryptography` or `PyCryptodome`).

### 5.1 Designing the Secure Boot Header

Your application binary must be generated with a structured header appended at a fixed memory offset (e.g., the first 256 bytes of the image block).

```
+-------------------------------------------------------+
|                 Secure Boot Header                    |
+-------------------------------------------------------+
| Magic Number (e.g., 0x53454342 - "SECB") [4 Bytes]    |
+-------------------------------------------------------+
| Target Execution Address (Entry Point)   [4 Bytes]    |
+-------------------------------------------------------+
| Image Size (Bytes to be verified)        [4 Bytes]    |
+-------------------------------------------------------+
| Software Version / Anti-Rollback Counter [4 Bytes]    |
+-------------------------------------------------------+
| Reserved / Padding Flags                 [12 Bytes]   |
+-------------------------------------------------------+
| Cryptographic Signature / MAC Tag       [64/256 Bytes]|
+-------------------------------------------------------+
|                                                       |
|             Actual Firmware Binary Payload            |
|             (Code Flash Executable Code)              |
|                                                       |
+-------------------------------------------------------+

```

### 5.2 Anti-Rollback Implementation

An attacker could capture a completely valid, OEM-signed firmware image from three years ago that contains a stack overflow vulnerability, flash it onto the ECU, and then exploit that vulnerability.

To prevent this, we map the software version inside the Secure Boot header to an internal counter:

* The RH850 provides **Monotonic Counters** inside its NVRAM/Data Flash managed by the ICU-M.
* During boot, the ICU-M checks if $Version_{Header} \ge Counter_{Hardware}$.
* If true, the boot continues. If false, execution is blocked.
* During an official OTA update, the update agent explicitly calls an ICU-M command to increment the hardware monotonic counter to match the new version number.

---

# Module 6: Error Handling, Recovery, and Debug Policies

### 6.1 Failure Containment Strategies

What happens when the cryptographic verification fails? As a firmware architect, your design must balance security with functional safety. If a vehicle is traveling down a highway and the ECU undergoes a transient reset, bricking the ECU due to a failed boot check could be fatal.

* **The "Golden Image" Fallback:** The RH850 Code Flash is divided into dual banks (Bank 0 and Bank 1). If Bank 0 fails verification, the Bootloader catches the failure status from the ICU-M and forces a remap/execution jump to Bank 1, which contains a validated, recovery-mode firmware image ("Golden Image") capable of minimal vehicle communication and diagnostic recovery.
* **Safe State Suppression:** If no fallback exists, the ECU must enter a safe state: disable all high-power outputs, pull down H-bridge drivers controlling actuators, and transmit a specific diagnostic trouble code (DTC) over the CAN/Automotive Ethernet network to notify the central gateway.

### 6.2 Lifecycle Management & Debug Disabling

During development, you need an open JTAG/LPD debug interface to step through code. In a production vehicle, that same interface could be used to extract keys or dump memory.

The RH850 manages this through **Hardware Lifecycle States**:

```
[CMIC / DBGINIT] ────► [DBGALLOW] ────► [AUTHDBG] ────► [DBGDISABLE]
  (Factory Raw)       (Development)    (Field Return)   (Production Fleet)

```

1. **DBGALLOW (Development):** Full JTAG access. ICU-M registers can be observed via specific debugger scripts using authentication keys.
2. **AUTHDBG (Authenticated Debug):** JTAG is locked. To connect a debugger to a field-returned ECU, you must issue a challenge-response sequence. The ECU provides a random token; you must sign it with an OEM internal private key to unlock debug capabilities for that single power cycle.
3. **DBGDISABLE (Production):** The JTAG/LPD fuse is physically or logically blown. The hardware debug port is permanently deactivated. No debugger can connect under any circumstance.

---

# Low-Level Code Walkthrough: Interfacing with the ICU-M

Let's look at how you will actually write the C code on the Main Core to interact with the ICU-M hardware mailbox for parallel or software-assisted verification.

```c
#include "rh850_regs.h"

// Define ICU-M Mailbox Status and Command Registers
#define ICUM_MBX_CMD       (*(volatile uint32_t*)(0xFFFEE000))
#define ICUM_MBX_STATUS    (*(volatile uint32_t*)(0xFFFEE004))
#define ICUM_MBX_DATAPTR   (*(volatile uint32_t*)(0xFFFEE008))

// Command Definitions
#define ICUM_CMD_VERIFY_SIGNATURE  0x000000A5
#define ICUM_STATUS_BUSY           0x00000001
#define ICUM_STATUS_SUCCESS        0x00000002
#define ICUM_STATUS_FAIL           0x00000004

typedef struct {
    uint32_t magic;
    uint32_t entry_point;
    uint32_t image_size;
    uint32_t version;
    uint8_t  signature[64]; // Using ECC-256 signature
} __attribute__((packed)) SecureHeader_t;

/**
 * @brief Verifies the application image using the ICU-M co-processor
 * @param header_addr Pointer to the start of the application metadata header in flash
 * @return 1 if verification passes, 0 if it fails
 */
uint8_t Verify_Application_Image(uint32_t header_addr) {
    SecureHeader_t* header = (SecureHeader_t*)header_addr;
    
    // 1. Verify Magic Number first to avoid obvious junk data processing
    if (header->magic != 0x53454342) { 
        return 0; 
    }
    
    // 2. Wait until the ICU-M Mailbox is free
    while (ICUM_STATUS & ICUM_STATUS_BUSY) {
        // Service hardware watchdog here to prevent reset during polling
        __asm__("nop");
    }
    
    // 3. Pass the address of the header/metadata descriptor to the ICU-M
    // The ICU-M will read the image size and signature directly from this pointer
    ICUM_MBX_DATAPTR = header_addr;
    
    // 4. Trigger the verification command
    ICUM_MBX_CMD = ICUM_CMD_VERIFY_SIGNATURE;
    
    // 5. Poll for completion (In a parallel boot, you would do other tasks here)
    while (ICUM_STATUS & ICUM_STATUS_BUSY) {
        // Wait for execution to finish
    }
    
    // 6. Evaluate the hardware response
    if (ICUM_STATUS & ICUM_STATUS_SUCCESS) {
        return 1; // Signature matches, integrity verified!
    } else {
        return 0; // Cryptographic validation failed or counter mismatch
    }
}

void Main_Root_Entry(void) {
    uint32_t app_header_address = 0x00020000; // Example offset for App block
    
    if (Verify_Application_Image(app_header_address)) {
        // Verification passed. Extract entry point and jump to application
        SecureHeader_t* header = (SecureHeader_t*)app_header_address;
        void (*app_entry)(void) = (void (*)(void))header->entry_point;
        
        app_entry(); // Jump to App
    } else {
        // Containment strategy: Fallback or Enter Safe State
        Execute_Safe_State_Halt();
    }
}

void Execute_Safe_State_Halt(void) {
    // Disable interrupts globally
    __asm__("di");
    
    // Put critical peripheral outputs into low power / safe state
    PORT_P0_OUT = 0x0000; 
    
    // Force a local infinite loop while the external watchdog barks
    while(1) {
        // Intentionally do not kick the watchdog here; let the system reset 
        // or enter a fallback state if configured.
    }
}

```

---

This framework covers the end-to-end design requirements for implementing Secure Boot on the RH850 platform. If you have questions about specific register names, options bytes configuring the boot areas, or how to write the linker command file (`.ld`) to accurately position your headers, we can address those immediately.