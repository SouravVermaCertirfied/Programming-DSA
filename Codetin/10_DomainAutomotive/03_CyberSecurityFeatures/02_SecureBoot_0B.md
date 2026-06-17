# The Boot Up Process

To truly understand the "first spark" to application execution on an automotive microcontroller like the Renesas RH850, we have to look at the process through three distinct lenses running in parallel: **Analog/Silicon Initialization**, **Hardware Cryptographic Isolation**, and **Software Chain of Trust**.

Here is the microscopic breakdown of the boot timeline, divided into logical phases.

---

## Phase 1: The Silicon Spark (Hardware & Analog Reset)

Before a single line of code executes, the microcontroller must transition from an unstable chunk of silicon to a stable computing environment.

### 1.1 Power Supply Sequencing & Internal Low-Dropouts (LDOs)

* **The Spark:** The ECU receives Power (typically $12\text{V}$ from Clamping Terminal 30 or 15).
* On-board Power Management ICs (PMICs) step this down to supply the RH850's external pins (usually $5.0\text{V}$ or $3.3\text{V}$ for I/O).
* Internal regulators on the RH850 drop this down further to supply the core digital logic ($1.2\text{V}$).

### 1.2 Power-On Reset (POR) & Voltage Monitors

* Internal analog circuits called **Voltage Monitors (VDM)** supervise the core and I/O voltages.
* As long as the voltage is below the operational threshold, the internal **Power-On Reset (POR)** signal is held active (Low). This physically forces all internal flip-flops and registers into a predefined, deterministic state.
* Once voltages stabilize, the POR signal is released (goes High).

### 1.3 Clock Stabilization

* The internal High-Speed On-Chip Oscillator (8 MHz HOCO) starts up immediately because it requires no external components.
* The main external crystal oscillator (X1/X2) begins to vibrate. Because quartz crystals take time to mechanically stabilize, the hardware triggers an internal **Oscillation Stabilization Time (OST)** counter.
* During this OST window, the MCU runs strictly off the internal HOCO to ensure safety-critical logic can begin initializing without waiting for the external crystal.

---

## Phase 2: The Hardware Root of Trust Wakes Up (Option Bytes & ICU-M)

Once clocks are safe, the RH850 does *not* branch to your application code. It routes directly to internal hardware configuration.

### 2.1 Option Byte Fetch

* The hardware flash memory controller automatically reads a dedicated, immutable segment of flash called **Option Bytes** (located in the Extra Area of flash).
* These bytes dictate critical hardware rules before any CPU core is released:
* Is the JTAG/Debug port enabled or disabled?
* What is the hardware allocation for the boot flash memory split?
* **Crucial for Security:** Is the **ICU-M (Intelligent Cryptographic Unit)** enabled for hardware-enforced secure boot?



### 2.2 ICU-M Autonomous Execution

If Hardware-Enforced Secure Boot is active via the Option Bytes:

1. The **Main CPU Core (G3KH/G3M) is held in a hardware reset state** by the internal reset controller.
2. The **ICU-M Coprocessor is released from reset**.
3. The ICU-M boots from its own internal, factory-programmed, immutable Read-Only Memory (ROM).

---

## Phase 3: Cryptographic Verification (The Shield)

With the ICU-M active and the Main CPU frozen, the cryptographic verification of the Primary Bootloader (PBL) begins.

```text
+-------------------------------------------------------------------------+
|                           ICU-M SECURE RUNTIME                          |
+-------------------------------------------------------------------------+
       │
       ▼
1. Fetch Root Public Key Hash ──► From Protected OTP Fuses / Data Flash
       │
       ▼
2. Read PBL Header            ──► From User Boot Area (UBA) Flash
       │
       ▼
3. Compute Hardware Hash      ──► Streams PBL Code Flash through SHA-256 Engine
       │
       ▼
4. Verify Signature           ──► Validates computed hash against Header Signature 
                                  using stored Root Key

```

### 3.1 The Anti-Rollback Check

If the signature is mathematically valid, the ICU-M extracts the **Software Version Counter** from the PBL header. It compares this value against an internal hardware **Monotonic Counter** stored in secure, non-volatile fuses.

* If $Version_{Header} < Counter_{Hardware}$, the execution halts immediately (Downgrade attack detected).
* If valid, the ICU-M updates its internal status registers to `ICUM_STATUS_SUCCESS`.

### 3.2 Main CPU Release

The ICU-M signals the internal reset controller to release the reset line of the primary Main CPU Core (Core 0).

---

## Phase 4: Primary Bootloader Execution (Software Handshake)

The Main CPU finally wakes up. Its hardware instruction pointer is automatically loaded with the **Reset Vector** dictated by the configuration area (typically pointing to the start of the User Boot Area in Flash).

### 4.1 Low-Level C Initialization (`cstart.asm`)

Before C code can execute, basic assembly routines must prepare the environment:

* **Register Initialization:** Clear the general-purpose registers (r1 to r31) to prevent residual startup noise from causing unpredictable branch behavior.
* **Stack Pointer Setup:** Initialize the Stack Pointer register (`sp` / `r3`) to point to a valid, cleared region of internal Retention RAM.
* **RAM Clearing & Initialization:** * The `.bss` section (uninitialized global variables) is explicitly zeroed out.
* The `.data` section (initialized variables) copies its default values from Code Flash into the target internal RAM addresses.


* **ECC Error Initialization:** The RH850 utilizes Error Correction Code (ECC) RAM. To prevent false RAM parity/ECC traps, the bootloader performs a hardware write-fill across the entire RAM layout to establish correct initial ECC checksums for every memory address.

### 4.2 Branch to PBL `main()`

The assembly layer executes a jump instruction (`jmp`) to the entry point of your Primary Bootloader's C code.

---

## Phase 5: The Downstream Chain & Application Launch

The Primary Bootloader's sole job is to verify the massive Main Application (which contains the AUTOSAR stack, OS, and control loops) and jump to it.

### 5.1 Application Verification

The PBL interacts with the ICU-M via the hardware mailbox mechanism to verify the Application image residing in the standard Application Flash banks:

1. The PBL writes the memory address of the Application Header to `ICUM_MBX_DATAPTR`.
2. It writes the verification command to `ICUM_MBX_CMD`.
3. The Main CPU polls `ICUM_MBX_STATUS` while kicking the internal Hardware Watchdog to ensure the system doesn't reset while waiting for the cryptographic engine to finish processing megabytes of application code.

### 5.2 The Final Jump

Once the mailbox returns a success status, the Primary Bootloader de-initializes any peripherals it used (e.g., stopping timers, disabling local interrupts) to clean the state of the MCU.

It reads the exact destination execution address from the validated Application Header and executes a final, destructive software branch:

```c
// Clear the instruction cache before jumping to ensure fresh pipeline state
__synchronize_cache();

// Define a function pointer to the Application's Reset Vector
void (*app_reset_vector)(void) = (void (*)(void))(ApplicationHeader->entry_point);

// Jump out of the Bootloader forever
app_reset_vector();

```

---

## Phase 6: Application Runtime

The Application begins executing its own local `cstart.asm`, resetting the stack pointer to the application's assigned RAM zone, initializing the AUTOSAR OS or Real-Time Operating System (RTOS) vectors, starting the cyclic task schedulers, and finally executing your vehicle control algorithms.

The Chain of Trust is complete; the system is running fully authenticated code from "first spark" to functional application.