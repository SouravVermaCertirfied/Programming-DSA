## JTAG (Joint Test Action Group) Technical Specification

**JTAG** (IEEE 1149.1) is a standard industry protocol used for **boundary-scan testing**, on-chip debugging, and flash programming. It allows developers to manipulate and observe the internal state of an Integrated Circuit (IC) without physical probe access to every pin.

---

### 1. Physical Layer (The Test Access Port - TAP)

JTAG typically requires 4 mandatory signals and 1 optional signal. It is a **synchronous, daisy-chainable** interface.

* **TCK (Test Clock):** Synchronizes the internal state machine.
* **TMS (Test Mode Select):** Sampled on the rising edge of TCK to determine the next state of the TAP controller.
* **TDI (Test Data In):** Serial input for data or instructions.
* **TDO (Test Data Out):** Serial output for data or instructions.
* **TRST (Test Reset):** *Optional.* Asynchronous reset of the TAP controller.

---

### 2. Boundary Scan Architecture

The core innovation of JTAG is the **Boundary Scan Cell**. These cells are placed between the device's internal logic and its physical pins.

* **Normal Mode:** The cells are transparent; internal logic connects directly to the pins.
* **Test Mode:** The cells disconnect the internal logic and allow the JTAG interface to "drive" or "sample" the pins directly.
* **Daisy Chaining:** Multiple ICs on a board can be connected in series ($TDO \rightarrow TDI$), allowing a single JTAG header to control every chip on the PCB.

---

### 3. The TAP Controller (State Machine)

The TAP controller is a 16-state finite state machine controlled by the **TMS** line. It is divided into two main paths:

1. **Instruction Register (IR) Path:** Used to load a command into the JTAG logic (e.g., `EXTEST`, `BYPASS`, `IDCODE`).
2. **Data Register (DR) Path:** Used to shift data in/out based on the current instruction (e.g., reading a chip ID or toggling a GPIO).

---

### 4. Key JTAG Instructions

* **BYPASS:** Shortens the path through a chip to a single bit. Essential for quickly reaching the next chip in a daisy chain.
* **IDCODE:** Connects the Device Identification Register to the DR path to identify the manufacturer and part number.
* **EXTEST:** Allows the user to set and read the state of physical pins (Boundary Scan).
* **SAMPLE/PRELOAD:** Takes a "snapshot" of pin values during normal operation.

---

### 5. JTAG for Debugging (On-Chip Debug - OCD)

Modern processors (ARM, RISC-V, etc.) extend JTAG to provide real-time debugging capabilities:

* **Run Control:** Haling, stepping, and resuming the CPU.
* **Breakpoints:** Setting hardware registers to trigger a halt on specific memory addresses.
* **Memory Access:** Directly reading/writing RAM and Peripheral registers while the CPU is halted.

---

### 6. Technical Comparison: JTAG vs. SWD

| Feature | JTAG (IEEE 1149.1) | SWD (Serial Wire Debug) |
| --- | --- | --- |
| **Pins** | 4 or 5 | 2 (SWDIO, SWCLK) |
| **Daisy Chaining** | Native support | Not natively supported |
| **Origin** | Boundary Scan Testing | ARM-specific Debugging |
| **Topologies** | Multi-device chains | Point-to-point |

---

### 7. Senior Interview Question: "The Broken Chain"

> **"You have a JTAG chain with 4 devices. You can read the IDCODE of the first two, but the last two return all 0s or all 1s. How do you isolate the fault using only the TAP state machine logic, and what are the most likely electrical causes?"**

**Expert Troubleshooting Steps:**

1. **Check the BYPASS register:** Force the first two devices into BYPASS mode (length = 1 bit). If you still can't reach the 3rd device, the issue is between $TDO_{2}$ and $TDI_{3}$.
2. **Check TCK/TMS Integrity:** Since these are shared across all devices, a reflection or signal integrity issue at the end of the long trace often causes the later devices to lose synchronization.
3. **The "High-Z" Trap:** If the $TDO$ of a device is stuck in High-Impedance, the line will float, leading to constant 1s or 0s.

---
<p align="left"><a href="06_DMA.md">← 06_DMA.md</a></p>
<p align="right" style="margin-top:-2.4em;"><a href="08_Ethernet.md">08_Ethernet.md →</a></p>