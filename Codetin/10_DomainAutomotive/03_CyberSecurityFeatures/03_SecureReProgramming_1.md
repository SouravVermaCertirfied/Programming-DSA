# Secure Flashing in Automotive ECUs (RSA-3072 Based) — Advanced Training for a Senior Software Engineer

Assumption:

* ECU firmware updates are performed using UDS (ISO 14229).
* Secure flashing uses RSA-3072 signatures.
* Firmware is distributed in VBF (Volvo Binary Format).
* ECU contains secure boot capability.
* Architecture includes Boot Manager, Bootloader(s), Application.
* Target audience already understands UDS fundamentals.

---

# 1. Why Secure Flashing Exists

Historically, flashing only checked:

* Correct ECU
* Correct software version
* Correct checksum/CRC

This protects against accidental corruption but not malicious modification.

Secure flashing adds:

1. Authenticity

   * Was this software produced by OEM?

2. Integrity

   * Has it been modified?

3. Anti-tampering

   * Prevent installation of modified firmware.

4. Chain of Trust

   * Trust extends from ROM → Bootloader → Application.

---

# 2. ECU Software Architecture

Typical modern ECU:

```text
+-----------------------------------+
| ROM / Hardware Root of Trust      |
+-----------------------------------+
                |
                v
+-----------------------------------+
| Boot Manager                      |
+-----------------------------------+
                |
                v
+-----------------------------------+
| Primary Bootloader                |
+-----------------------------------+
                |
                v
+-----------------------------------+
| Secondary Bootloader              |
+-----------------------------------+
                |
                v
+-----------------------------------+
| Application                       |
+-----------------------------------+
```

---

# 3. Boot Manager vs Bootloader

This is a favorite interview question.

## Boot Manager

Purpose:

Controls boot decision.

Responsibilities:

* Startup decision making
* Select image A or B
* Recovery mode decision
* Rollback decision
* Determine whether update is pending

Example:

```text
If UpdatePending == TRUE
      Boot Secondary Bootloader
Else
      Boot Application
```

Think of it as:

> "Traffic controller"

It decides where execution should go.

---

## Bootloader

Purpose:

Program and validate software.

Responsibilities:

* UDS flashing
* Erase flash
* Write flash
* Verify signature
* Verify checksum
* Start application

Think of it as:

> "Software installer"

---

## Summary

| Boot Manager         | Bootloader        |
| -------------------- | ----------------- |
| Decides what to boot | Programs software |
| Small                | Larger            |
| Startup logic        | Flashing logic    |
| Recovery decisions   | Memory operations |

---

# 4. Primary Bootloader vs Secondary Bootloader

Another common question.

---

## Primary Bootloader (PBL)

Usually:

* Stored in protected flash
* Sometimes ROM
* Never updated in field

Responsibilities:

* Initialize minimal hardware
* Establish root of trust
* Verify Secondary Bootloader

```text
PBL verifies SBL signature
```

If invalid:

```text
Stop boot
Recovery mode
```

---

## Secondary Bootloader (SBL)

Responsibilities:

* UDS flashing
* Signature verification
* Firmware installation
* Diagnostic services

```text
SBL verifies Application
```

---

## Chain of Trust

```text
ROM
 |
 v
Primary Bootloader
 |
 v
Secondary Bootloader
 |
 v
Application
```

Each stage verifies next stage.

This is the essence of secure boot.

---

# 5. Firmware Package Structure

Firmware image is not just raw code.

Typical structure:

```text
+----------------------+
| Header               |
+----------------------+
| Application Binary   |
+----------------------+
| Signature            |
+----------------------+
```

---

# 6. Header Structure

Example:

```c
struct FW_Header
{
   uint32 Magic;
   uint32 HeaderVersion;

   uint32 ECU_ID;
   uint32 SW_Version;

   uint32 ImageSize;

   uint8  SHA256[32];

   uint32 SignatureOffset;
   uint32 SignatureLength;

   uint32 CompatibilityID;

   uint32 AntiRollbackVersion;
};
```

---

## Utility of Header Fields

### Magic Number

Example:

```text
0xDEADBEEF
```

Purpose:

Identify valid image.

Without it:

Random memory could be interpreted as firmware.

---

### ECU ID

Example:

```text
ABS ECU
```

Prevents:

```text
ABS software flashed into BCM
```

---

### Software Version

Used for:

* Version control
* Traceability

---

### Image Size

Used for:

* Boundary checking
* Memory allocation

---

### SHA256 Hash

Represents:

```text
Hash(Firmware Binary)
```

Used for integrity validation.

---

### Signature Offset

Location of RSA signature.

---

### Anti-Rollback Version

Prevents:

```text
Install v2.0
Downgrade to vulnerable v1.0
```

---

# 7. RSA-3072 Signing Process

OEM side.

---

## Step 1: Build Firmware

Compiler produces:

```text
application.bin
```

---

## Step 2: Calculate Hash

```text
SHA256(application.bin)
```

Result:

```text
32 bytes
```

Example:

```text
ABCD1234...
```

---

## Step 3: Sign Hash

Using OEM private key.

```text
Signature =
RSA3072_PrivateKey(Sign(Hash))
```

Result:

```text
384 bytes
```

(3072 bits)

---

## Step 4: Generate Package

```text
+ Header
+ Firmware
+ Signature
```

---

## Step 5: Convert to VBF

Example:

```text
firmware.vbf
```

Contains:

* Metadata
* Memory addresses
* Data blocks

---

# 8. VBF (Volvo Binary Format)

VBF is a container format.

Conceptually:

```text
vbf
 ├─ Header
 ├─ ECU Information
 ├─ Version
 ├─ Data Blocks
 ├─ Signature
 └─ Metadata
```

Example:

```text
:header
sw_part_number
sw_version
ecu_type

:data
0x10000
<binary bytes>

:signature
<RSA signature>
```

---

## Why Use VBF?

Benefits:

* Human readable metadata
* Supports multiple memory segments
* Easy tooling integration
* Supports secure flashing workflows

---

# 9. UDS Reprogramming Flow

Candidate already knows UDS.

Focus on secure aspects.

---

## Step 1

### Diagnostic Session Control (0x10)

```text
10 02
```

Programming session.

---

## Step 2

### Security Access (0x27)

```text
27 xx
```

Unlock programming level.

Purpose:

Prevent unauthorized flashing.

---

## Step 3

### Communication Control (0x28)

Optional.

Reduce network traffic.

---

## Step 4

### Control DTC Setting (0x85)

Optional.

Avoid DTC flooding.

---

## Step 5

### Request Download (0x34)

Contains:

```text
Address
Size
```

ECU prepares flash operation.

---

## Step 6

### Transfer Data (0x36)

```text
Chunk 1
Chunk 2
Chunk 3
...
```

Firmware transferred.

---

## Step 7

### Transfer Exit (0x37)

End transfer.

---

## Step 8

### Routine Control (0x31)

Common routines:

```text
Erase memory
Verify checksum
Verify signature
Install image
```

Examples:

```text
31 01 FF00
Erase

31 01 FF01
Verify Signature
```

OEM-specific.

---

## Step 9

### ECU Reset (0x11)

Reboot ECU.

---

# 10. Verification Process Inside ECU

Most important section.

---

## During Flashing

ECU stores firmware.

```text
Inactive Partition
```

Not active application.

---

## After Download

ECU computes:

```text
CalculatedHash
```

```text
SHA256(received image)
```

---

## Read Signature

From package.

```text
ReceivedSignature
```

---

## Verify

Using OEM public key.

```text
RSA3072_Verify(
    PublicKey,
    CalculatedHash,
    ReceivedSignature
)
```

If:

```text
PASS
```

Image authentic.

---

If:

```text
FAIL
```

Reject image.

---

# 11. Complete Flow from Signing to Verification

Interview-level answer.

---

## OEM Side

```text
Build firmware
     |
     v
SHA256 Hash
     |
     v
RSA3072 Sign
     |
     v
Create Header
     |
     v
Generate VBF
     |
     v
Release Package
```

---

## Vehicle Side

```text
Receive VBF
     |
     v
Parse Header
     |
     v
Check ECU ID
     |
     v
Check Version
     |
     v
Store Image
     |
     v
Calculate SHA256
     |
     v
RSA3072 Verify
     |
     v
Install Image
     |
     v
Set Boot Flag
     |
     v
Reset ECU
```

---

# 12. Preventing ECU Bricking

Critical topic.

---

## Problem

Battery disconnected during flashing.

```text
50% image written
Power lost
```

What now?

---

## Unsafe Design

```text
Erase App
Write App
Boot App
```

Result:

Corrupted application.

ECU dead.

---

## Safe Design (A/B Partition)

```text
Partition A = Active
Partition B = Inactive
```

Example:

```text
A running
B updated
```

---

Flow:

```text
Download to B
Verify B
Mark B Valid
Switch Boot Flag
```

Only after success:

```text
Boot B
```

---

If power loss:

```text
A remains intact
```

System survives.

---

## Boot Flag Example

```text
ACTIVE_SLOT=A
```

After validation:

```text
ACTIVE_SLOT=B
```

Atomic update.

---

# 13. Additional Recovery Mechanisms

## Recovery Bootloader

Minimal bootloader never erased.

Can always enter:

```text
Programming Session
```

Even if application damaged.

---

## Watchdog Validation

New application boots.

Must signal:

```text
Application Healthy
```

within timeout.

Otherwise:

```text
Rollback
```

---

# 14. Invalid Binary Received

Important edge case.

---

## Scenario

Attacker modifies one byte.

---

Original:

```text
Hash A
```

Modified:

```text
Hash B
```

---

Verification:

```text
Hash B != Signed Hash A
```

RSA verification fails.

---

Response:

```text
NRC
Verification Failed
```

Image rejected.

---

## ECU Action

```text
Do NOT activate image
Keep existing image
Log event
```

---

# 15. Anti-Rollback Protection

Attack:

```text
Install old vulnerable firmware
```

---

Header:

```text
Version = 10
```

ECU stored:

```text
CurrentVersion = 15
```

Check:

```text
10 < 15
```

Reject.

---

# 16. How to Defend the Security of This Reprogramming Method

This is often asked in security reviews.

### Authentication

Only OEM owns RSA3072 private key.

Attackers do not.

---

### Integrity

SHA256 detects modification.

---

### Authenticity

RSA3072 signature proves origin.

---

### Secure Boot

Bootloader verifies application before execution.

---

### Security Access

UDS Security Access prevents unauthorized programming.

---

### Anti-Rollback

Old vulnerable software rejected.

---

### Recovery

A/B partition prevents bricking.

---

### Chain of Trust

```text
ROM
 -> PBL
 -> SBL
 -> APP
```

Every stage verified.

---

# 17. Typical Failure Scenarios and ECU Response

| Failure                        | Response          |
| ------------------------------ | ----------------- |
| Wrong ECU ID                   | Reject package    |
| Invalid header                 | Reject package    |
| Bad CRC                        | Reject package    |
| Invalid SHA256                 | Reject package    |
| Invalid RSA signature          | Reject package    |
| Downgrade attempt              | Reject package    |
| Power loss during transfer     | Stay on old image |
| Power loss during verification | Stay on old image |
| New image crashes              | Rollback          |
| Missing signature              | Reject package    |
| Corrupted VBF                  | Reject package    |

---

# 18. Questions the Candidate Should Be Able to Answer

### Difference between Boot Manager and Bootloader

Boot Manager decides what image to boot; Bootloader programs and verifies software.

---

### Difference between Primary and Secondary Bootloader

Primary Bootloader establishes root of trust and verifies Secondary Bootloader. Secondary Bootloader performs diagnostics, flashing, and application verification.

---

### Complete Signing to Verification Flow

Build → SHA256 → RSA3072 Sign → Package/VBF → Download via UDS → Store in inactive partition → SHA256 verify → RSA3072 verify → Activate → Boot.

---

### How Battery Disconnect Is Handled

Using A/B partitioning, boot flags, recovery bootloader, and atomic activation. Existing image remains executable until new image is fully verified.

---

### Why Is Reprogramming Secure?

Because only firmware signed by the OEM private key can pass RSA3072 verification. Integrity, authenticity, anti-rollback, secure boot, and security access together create a chain of trust.

---

### Header Structure Utility

Provides identity, compatibility, versioning, integrity metadata, signature location, anti-rollback information, and parsing information required for secure flashing.

---

### What Happens When Invalid Binary Is Received?

Hash mismatch or signature verification failure occurs. ECU rejects activation, keeps previous image, records diagnostics, and remains recoverable.

---

# Architecture Used in High-ASIL Production ECUs

A production-grade secure flashing architecture typically looks like:

```text
ROM Root of Trust
        |
        v
Primary Bootloader (Immutable)
        |
 RSA3072 Verify
        |
        v
Secondary Bootloader
        |
 RSA3072 Verify
        |
        v
Application A/B Partitions
        |
 SHA256 + Version Check
        |
        v
Boot Manager Activation Logic
        |
        v
Vehicle Functionality
```

This architecture provides authenticity, integrity, anti-rollback protection, power-loss resilience, recovery capability, and a complete cryptographic chain of trust from reset vector to application execution.