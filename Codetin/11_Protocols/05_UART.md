# UART

- Since this is asynchronous communication so here there are many things that we need to do in configuration, for instance, we should configure both devices at the BAUD RATE because the clock signal is absent.
- This is also makes it advantageous as CLK is not required.

![UART Diagram](./img/UART_FrameFormat.png)

![UART Diagram](./img/UART_FrameFormat_withParity.png)

## UART Technical Specification & Architecture

**UART (Universal Asynchronous Receiver-Transmitter)** is a physical-layer communication protocol used for **asynchronous, serial communication**. Unlike I2C or SPI, UART does not use a shared clock signal; instead, it relies on predefined timing parameters to synchronize data.

---

### 1. Physical Layer (PHY)

UART is a point-to-point interface requiring only two signal wires for full-duplex communication.

* **TX (Transmit):** The data output line.
* **RX (Receive):** The data input line.
* **GND (Ground):** A common reference point is strictly required for voltage level detection.

---

### 2. The Asynchronous Mechanism

Because there is no SCLK line, the Controller and Target must agree on a **Baud Rate** (bits per second) before communication begins.

* **Sampling:** The receiver samples the incoming RX line at a frequency much higher than the baud rate (usually 16x oversampling) to locate the center of each bit and minimize errors.
* **Idle State:** The UART line idles at a **Logic High (1)** state.

---

### 3. Data Frame Structure

Communication is packet-based. A standard UART frame consists of the following components:

1. **Start Bit:** The line transitions from High to Low for one bit period. This signals the receiver to start its internal timer.
2. **Data Frame:** Typically 5 to 9 bits (8 bits is the industry standard). Transmitted LSB (Least Significant Bit) first.
3. **Parity Bit:** An optional bit used for basic error detection (Even or Odd).
4. **Stop Bit(s):** The line returns to a High state for 1, 1.5, or 2 bit periods to signal the end of the packet.

---

### 4. Configuration Parameters (The "N-8-1" Rule)

To ensure compatibility, both devices must be configured identically. The most common configuration is **8N1**:

* **8**: Data bits.
* **N**: No parity bit.
* **1**: One stop bit.

---

### 5. Flow Control

To prevent buffer overflows (when data is sent faster than it can be processed), UART utilizes two types of flow control:

* **Hardware Flow Control:** Uses two additional wires: **RTS** (Request to Send) and **CTS** (Clear to Send).
* **Software Flow Control:** Uses special characters (XON/XOFF) within the data stream to pause and resume transmission.

---

### 6. Technical Comparison: UART vs. I2C vs. SPI

| Feature | UART | I2C | SPI |
| --- | --- | --- | --- |
| **Clocking** | Asynchronous (No clock wire) | Synchronous | Synchronous |
| **Topology** | Point-to-Point (1-to-1) | Multi-target | Multi-target |
| **Max Distance** | Moderate (up to 15m+) | Short (cm) | Short (cm) |
| **Efficiency** | High overhead (Start/Stop bits) | Moderate | Very High |
| **Wires** | 2 (+GND) | 2 (+GND) | 3-4 (+GND) |

---

### 7. Critical Design Constraints

* **Baud Rate Mismatch:** If the internal oscillators of the two devices differ by more than **3%**, the data will become corrupted.
* **Logic Levels:** UART is a protocol, not a voltage standard. While microcontrollers use TTL levels (0V/3.3V or 0V/5V), RS-232 uses negative/positive swings (-12V/+12V). Connecting TTL to RS-232 directly will destroy the hardware.
* **Half-Duplex vs. Full-Duplex:** Standard UART is full-duplex, but RS-485 (a common UART-based industrial standard) is often half-duplex.
