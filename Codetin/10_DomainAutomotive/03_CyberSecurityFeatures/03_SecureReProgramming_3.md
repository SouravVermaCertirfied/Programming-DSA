These topics separate engineers who have "implemented flashing" from engineers who can actually defend a secure flashing architecture in a cybersecurity review.

---

# 1. Primary Bootloader vs Boot Manager (Deep Understanding)

Many engineers incorrectly think they are the same thing.

They solve different problems.

---

## Boot Sequence Example

```text
Power On
   |
   v
ROM Code
   |
   v
Primary Bootloader (PBL)
   |
   v
Boot Manager
   |
   +----> App A
   |
   +----> App B
   |
   +----> Recovery Mode
```

---

## Primary Bootloader (PBL)

Primary Bootloader is part of the security architecture.

Its job is:

### 1. Establish Root of Trust

The first executable code after reset.

```text
Hardware Root Key
      |
      v
PBL
```

The PBL is trusted because:

* Stored in ROM or protected flash
* Cannot be modified in field

---

### 2. Verify Next Stage

Example:

```text
PBL
  |
Verify Signature
  |
  v
Boot Manager
```

If verification fails:

```text
Do not continue boot
```

---

### 3. Minimal Initialization

Typically:

* Clock
* RAM
* Flash controller

Nothing more.

---

### What PBL DOES NOT Do

Usually:

* No UDS
* No CAN flashing
* No Ethernet flashing
* No application management

Keep it tiny.

Reason:

Smaller attack surface.

---

# Boot Manager

Boot Manager is an update management component.

Its purpose is:

> Decide which image should run.

---

## Typical Responsibilities

### Check Image Validity

```text
App A Valid ?
App B Valid ?
```

---

### Rollback Decisions

```text
New image failed
```

Boot Manager decides:

```text
Go back to previous image
```

---

### Update Activation

Example:

```text
Current Active = A
New Software = B
```

After successful verification:

```text
Switch Active Slot = B
```

---

### Recovery Decisions

Example:

```text
Application crashes
```

Boot Manager:

```text
Boot Recovery Image
```

---

## Security View

PBL answers:

```text
Can I trust the next stage?
```

Boot Manager answers:

```text
Which trusted image should run?
```

---

# Interview Answer

Primary Bootloader establishes cryptographic trust and verifies the next boot stage. Boot Manager is responsible for image selection, rollback handling, update activation, and recovery decisions. PBL focuses on security; Boot Manager focuses on update orchestration.

---

# 2. A/B Partitioning (Deep Dive)

Most modern ADAS and ASIL-B/C/D ECUs use some variation of this.

---

## Memory Layout

```text
+--------------------+
| Bootloader         |
+--------------------+
| Application A      |
+--------------------+
| Application B      |
+--------------------+
| NVM Flags          |
+--------------------+
```

---

Assume:

```text
Application A = Running
Application B = Empty
```

---

# Step 1: Download New Software

UDS flashing starts.

New image goes into:

```text
Application B
```

NOT A.

---

Result:

```text
A = Working
B = New Download
```

---

# Step 2: Verify Download

Compute:

```text
SHA256(B)
```

Verify:

```text
RSA3072 Signature
```

---

If verification fails:

```text
Delete B
Continue using A
```

Vehicle still works.

---

# Step 3: Mark Candidate

Boot Manager stores:

```c
candidate = B;
```

Not active yet.

---

NVM example:

```c
struct BootInfo
{
   uint8 active_slot;
   uint8 candidate_slot;
};
```

---

Current:

```text
Active=A
Candidate=B
```

---

# Step 4: First Boot Validation

Boot Manager boots B.

```text
Boot B once
```

---

Application performs self-tests:

* RAM
* Flash
* Sensors
* Communication

---

Application reports:

```text
Healthy
```

---

# Step 5: Commit

Only now:

```text
Active=B
```

---

Result:

```text
A = Backup
B = Active
```

---

# Why This Is Powerful

Suppose power loss occurs during flashing.

```text
Writing B
Power Lost
```

A remains untouched.

Vehicle boots.

---

Suppose B crashes.

```text
Boot B
Crash
```

Watchdog resets.

Boot Manager detects:

```text
Boot Failure Count > Threshold
```

Rollback:

```text
Boot A
```

---

# Real Automotive Variant

Sometimes:

```text
Factory Image
Current Image
Candidate Image
```

Three-image architecture.

Common in ASIL-D ECUs.

---

# 3. If ECU Has No Space for A/B Partition

This is extremely common in low-cost body ECUs.

Examples:

* Window ECU
* Door ECU
* Seat ECU

Flash size is limited.

---

# Method 1: Bootloader + Recovery Partition

Memory:

```text
+----------------+
| Bootloader     |
+----------------+
| Recovery Image |
+----------------+
| Application    |
+----------------+
```

---

Recovery image is small.

Maybe:

```text
40 KB
```

---

Purpose:

```text
Always able to flash
```

---

Flow

Power loss occurs.

Application corrupted.

---

Bootloader checks:

```text
Application Valid ?
```

No.

---

Jump to:

```text
Recovery Image
```

Recovery image supports:

* CAN
* UDS
* Flashing

Nothing else.

---

Advantage

Needs much less memory than A/B.

---

# Method 2: Streaming Verification Before Programming

This is increasingly used.

---

Normal Approach

```text
Download
Store
Verify
Activate
```

Needs extra storage.

---

Streaming Approach

Verify while receiving.

---

For every TransferData block:

```text
Receive Block
Update SHA256 Context
Program Flash
```

---

At end:

```text
Final SHA256
```

Verify signature.

---

Advantage

No second partition.

---

Limitation

Power loss during programming remains dangerous.

Need recovery bootloader.

---

# Method 3: Sector-by-Sector Swap

Used in memory-constrained MCUs.

---

Memory

```text
Application Area

Sector1
Sector2
Sector3
Sector4
```

---

Temporary buffer:

```text
Scratch Sector
```

---

Update Process

```text
Copy Sector1 → Scratch
Erase Sector1
Write New Sector1
Verify
```

Repeat.

---

Example

```text
Old Sector1
      |
      v
Scratch
      |
      v
New Sector1
```

---

Power-loss recovery metadata maintained.

---

Metadata

```c
CurrentSector=3
ProgrammingState=IN_PROGRESS
```

Stored in EEPROM.

---

After reset:

```text
Resume from Sector3
```

---

This is called:

### Journaling Flash Update

Similar to database transactions.

---

# Method 4: Delta Updates

Instead of:

```text
20 MB Firmware
```

Send:

```text
200 KB Patch
```

---

Patch example:

```text
Replace bytes
0x1200-0x1500
```

---

Benefits:

* Less bandwidth
* Less storage

Common in OTA systems.

---

Still requires recovery strategy.

---

# 4. UDS Request Download (0x34) Deep Explanation

Most engineers know the frame.

Few understand why it exists.

---

# Purpose

Tell ECU:

```text
I am about to send software.
```

---

Think of it as:

```text
File Open()
```

before writing.

---

# Typical Flow

```text
10 02
27 xx

34
36
36
36
37
```

---

# Request Download Structure

General format:

```text
34
DataFormatIdentifier
AddressAndLengthFormatIdentifier
MemoryAddress
MemorySize
```

---

Example

```text
34 00 44 00 10 00 00 00 20 00 00
```

Meaning:

```text
Address = 0x00100000
Size    = 0x00020000
```

---

# ECU Actions Internally

Upon receiving 0x34:

---

## Step 1

Validate Session

```text
Programming Session?
```

If not:

```text
NRC 7F 34 7E
```

---

## Step 2

Validate Security Access

```text
Unlocked?
```

If not:

```text
NRC 33
```

---

## Step 3

Validate Address

Example:

```text
0x00100000
```

Must belong to valid flash area.

---

Prevent:

```text
Overwrite Bootloader
```

---

## Step 4

Validate Size

Example:

```text
Requested Size = 20MB
Flash = 4MB
```

Reject.

---

## Step 5

Reserve Download Context

Create structure:

```c
typedef struct
{
   uint32 targetAddress;
   uint32 totalSize;
   uint32 bytesReceived;
} DownloadContext;
```

---

## Step 6

Initialize Cryptography

For secure flashing:

```c
SHA256_Init();
```

---

Bootloader prepares:

```text
Streaming hash context
```

---

## Step 7

Respond

Example:

```text
74 xx
```

Positive response.

---

May contain:

```text
MaxNumberOfBlockLength
```

Example:

```text
4096 bytes
```

---

Meaning:

```text
Each TransferData block
<= 4096 bytes
```

---

# TransferData (0x36)

For every block:

```text
Receive Data
Program Flash
Update SHA256
Increment Counter
```

---

Example:

```c
SHA256_Update(data);
Flash_Write(data);
```

---

# Transfer Exit (0x37)

Bootloader receives:

```text
Download Finished
```

---

Now:

```text
Finalize SHA256
```

---

Then:

```text
Verify RSA3072 Signature
```

---

Then:

```text
Mark Image Valid
```

or

```text
Reject Image
```

---

# What Happens If Power Is Lost During 0x36?

A robust design stores state information in non-volatile memory:

```c
struct RecoveryInfo
{
   uint32 LastWrittenAddress;
   uint32 DownloadState;
};
```

Example:

```text
LastWrittenAddress=0x10034000
```

After reboot:

```text
Programming Interrupted
```

Bootloader can:

1. Resume download (rare)
2. Restart download (common)
3. Roll back to old image (best with A/B)

---

# Security-Relevant Validation During Download

A production secure bootloader should validate:

### Before 0x34

* Session
* Security access
* Vehicle state

### During 0x36

* Sequence counter
* Address overflow
* Block length
* Memory range
* Download size exceeded

### After 0x37

* SHA256 integrity
* RSA3072 signature
* ECU compatibility
* Software version
* Anti-rollback counter

Only after all checks pass should the Boot Manager activate the image.

A cybersecurity assessor will typically evaluate the design against three questions:

1. Can an attacker install unauthorized software? (RSA-3072 signature verification)
2. Can a power loss brick the ECU? (A/B partitioning, recovery image, journaling)
3. Can an attacker force an older vulnerable version? (anti-rollback protection)

If you can explain the complete interaction between PBL, Boot Manager, secure boot, UDS download services, signature verification, rollback, and power-loss recovery, you are operating at the level expected of a senior automotive firmware/security engineer.