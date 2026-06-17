## Understanding SecOC: Secure Onboard Communication in Automotive Systems

In the modern automotive landscape, vehicles are no longer just mechanical machines; they are "computers on wheels." With the rise of autonomous driving and over-the-air (OTA) updates, the internal communication network (CAN, CAN FD, Ethernet) has become a target for cyberattacks.

**SecOC (Secure Onboard Communication)** is an AUTOSAR module designed to ensure that the data exchanged between Electronic Control Units (ECUs) is authentic and has not been tampered with.

---

## The SecOC Module
The primary goal of SecOC is to provide **integrity** and **authenticity**. It prevents common attacks like "Message Injection" (sending fake commands) and "Replay Attacks" (re-sending a valid old command, like "unlock doors").

### Key Components of a Secured I-PDU:
When SecOC is active, it wraps a standard Data PDU (Protocol Data Unit) into a **Secured I-PDU**, which includes:
1.  **Authentic PDU:** The original data being sent.
2.  **Freshness Value (FV):** A unique, non-repeating number that ensures the message is "new."
3.  **Message Authentication Code (MAC):** A cryptographic checksum generated using the Data, the Freshness Value, and a Secret Key.



---

## The FVM Module (Freshness Value Manager)
The **Freshness Value Manager (FVM)** is a separate functional entity that works alongside SecOC. Its sole job is to manage the "Freshness" of communication to prevent replay attacks.

If a hacker captures a valid "Open Trunk" message and plays it back later, the SecOC module will check the FVM. Since the Freshness Value in the captured message is "old" compared to the current FVM state, the message is rejected.

### How Freshness is Managed:
*   **Trip Counters:** Incremented every time the vehicle starts.
*   **Reset Counters:** Incremented periodically.
*   **Message Counters:** Incremented for every message sent.
*   **Synchronization:** The FVM ensures that both the Sender and Receiver ECUs are "in sync" regarding what the current counter value should be.

---

## Technical Walkthrough: Sending a Secured Message
Let’s look at an example where the **Body Control Module (BCM)** sends a "Lock Doors" command to the **Door Control Unit (DCU)**.

### 1. The Sending Process (BCM side)
*   **Data Preparation:** The BCM prepares the command (e.g., `0x01` for Lock).
*   **FV Retrieval:** SecOC asks the FVM for the current Freshness Value (e.g., `505`).
*   **MAC Generation:** A cryptographic algorithm (like AES-128 CMAC) takes the **Data** + **FV** + **Secret Key** to produce a MAC.
*   **Truncation:** To save bandwidth, the full FV and MAC might be shortened (truncated) before being sent over the CAN bus.
*   **Transmission:** The Secured I-PDU is sent.

### 2. The Receiving Process (DCU side)
*   **Reception:** The DCU receives the Secured I-PDU.
*   **FV Construction:** The DCU's FVM provides the local Freshness Value. It combines the received "truncated" FV with its internal "most significant bits" to reconstruct the full value.
*   **Verification:** The DCU calculates its own MAC using the received Data + reconstructed FV + Secret Key.
*   **Comparison:** If **Calculated MAC == Received MAC**, the message is authentic. The doors lock. If they don't match, the message is dropped.

---

## Operational Flow Diagram
Below is a notepad-style representation of the logical flow between the modules.

```text
SENDER ECU (e.g., BCM)                RECEIVER ECU (e.g., DCU)
======================                ========================

[ Application Layer ]                 [ Application Layer ]
         |                                     ^
         v                                     | (Valid Data)
[   SecOC Module    ]                 [   SecOC Module    ]
         |      ^                              |      ^
         |      | (Get FV)                     |      | (Verify FV)
         |      v                              |      v
[    FVM Module     ]                 [    FVM Module     ]
         |                                     ^
         | (Create MAC)                        | (Reconstruct FV)
         v                                     |
[  Crypto Stack/CSM ]                 [  Crypto Stack/CSM ]
         |                                     ^
         +--------------[ CAN BUS ]------------+
                 (Data + MAC + FV bits)
```

### Why this matters
Without SecOC, a malicious device plugged into the OBD-II port could flood the vehicle network with "Deploy Airbag" or "Stop Engine" commands. With SecOC and FVM, the vehicle effectively ignores any command that doesn't have the "secret handshake" and the "correct timestamp."

# SecOc Module

To configure SecOC (Secure Onboard Communication) in an AUTOSAR environment, you aren't just clicking a checkbox; you are building a cryptographic pipeline. The SecOC module sits between the **PduR (PDU Router)** and the lower-level communication drivers (like CanIf).

The configuration is centered around defining the **Secured I-PDU**, which is a "wrapper" that contains your original data plus security metadata.

---

## 1. Core SecOC Configuration Parameters
The configuration is typically handled in an AUTOSAR tool (like DaVinci Configurator or EB Tresos) within the `SecOC` module.

### A. SecOCGeneral
This container holds global settings for the module.
*   **SecOCMainFunctionPeriod:** The task cycle time (e.g., 0.01s). This determines how often the module processes security queues.
*   **SecOCIpduDevelopmentErrorDetect:** Enables development error tracing (DET).

### B. SecOCPduConfig
This is the heart of the configuration. You must define a `SecOCPduConfig` for every message that needs protection.
*   **SecOCAuthenticLayerPdu:** This links to the original, unprotected PDU (the "Data").
*   **SecOCSecuredLayerPdu:** This links to the new, larger PDU that will actually be sent over the bus.
*   **SecOCFreshnessValueId:** A unique ID used to map this PDU to a specific counter in the FVM.
*   **SecOCDataId:** A unique identifier for the PDU itself, often used as part of the MAC calculation to ensure a MAC for PDU "A" can't be used for PDU "B".

---

## 2. Cryptographic Configuration (MAC & Truncation)
In SecOC, you rarely send the full 128-bit MAC or the full 64-bit Freshness Value because CAN/CAN-FD bandwidth is precious. You must configure **Truncation**.

| Parameter | Description | Typical Value |
| :--- | :--- | :--- |
| **SecOCAuthInfoTxLength** | Number of bits of the MAC to actually transmit. | 24–64 bits |
| **SecOCFreshnessValueTxLength** | Number of bits of the Freshness Value to transmit. | 4–8 bits |
| **SecOCAlgorithm** | The algorithm used (defined in CSM). | AES-128 CMAC |

> **Note:** If you transmit only 8 bits of a 64-bit Freshness Value, the receiver must "reconstruct" the other 56 bits using its local FVM state.

---

## 3. Integration with CSM (Crypto Service Manager)
SecOC does not perform the math itself. It calls the **CSM module**.
*   **Configuration:** You must configure a **CSM Job**. This job links SecOC to a specific cryptographic primitive (like AES-128) and a **Key Slot** (where the secret key is stored in the HSM or Secure Storage).
*   **Interface:** SecOC calls `Csm_MacGenerate` or `Csm_MacVerify`.

---

## 4. The Flow Walkthrough: A Practical Example
Imagine an ECU sending a "Speed" signal of `60 km/h`.

1.  **PduR** receives the "Speed" PDU and routes it to **SecOC**.
2.  **SecOC** fetches the current **Freshness Value** (e.g., `1005`) from the **FVM**.
3.  **SecOC** sends the Data (`60`) + FV (`1005`) + DataID to the **CSM**.
4.  **CSM** uses the **Secret Key** to generate a 128-bit MAC.
5.  **SecOC** truncates the MAC to 24 bits and the FV to 8 bits.
6.  **SecOC** bundles them: `[ Data(60) | FV_low(05) | MAC_trunc(ABC) ]`.
7.  The final **Secured I-PDU** is sent to **CanIf**.

---

## 5. Logical Flow Diagram (Notepad Style)

```text
+--------------------------------------------------------------+
|                    SecOC CONFIGURATION FLOW                  |
+--------------------------------------------------------------+
|                                                              |
| [ PduR ] --> (Routes Authentic PDU)                          |
|    |                                                         |
|    v                                                         |
| [ SecOC Module ] <------------------+ [ FVM Module ]         |
|    | (Step 1: Get Freshness Value)  | (Maintains Counters)   |
|    | (Step 2: Add DataID)           +------------------------+
|    |                                                         |
|    v                                                         |
| [ CSM (Crypto Service Manager) ]                             |
|    | (Step 3: Perform AES-128 CMAC)                          |
|    | (Step 4: Use Key from HSM/Storage)                      |
|    v                                                         |
| [ SecOC Module ]                                             |
|    | (Step 5: Truncate MAC/FV)                               |
|    | (Step 6: Assemble Secured I-PDU)                        |
|    v                                                         |
| [ CanIf / EthIf ] --> (Physical Bus)                         |
|                                                              |
+--------------------------------------------------------------+
| CONFIG CHECKLIST:                                            |
| 1. Define PduId mapping (Authentic <-> Secured)              |
| 2. Set MAC Truncation length (e.g., 28 bits)                 |
| 3. Set FV Truncation length (e.g., 4 bits)                   |
| 4. Link CSM Job ID and Key ID                                |
+--------------------------------------------------------------+
```

