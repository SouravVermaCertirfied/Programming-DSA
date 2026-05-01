## Deep Dive: PDUs in the AUTOSAR CAN Stack

In AUTOSAR, data isn't just "sent"; it is encapsulated into **Protocol Data Units (PDUs)**. Understanding the transformation of a PDU as it travels through the stack is the key to mastering automotive communication.

---

### 1. The Different Flavors of PDUs
A PDU consists of **SDU (Service Data Unit)** + **PCI (Protocol Control Information)**. Depending on which layer is processing the data, the PDU changes its name and structure:

*   **I-PDU (Interaction Layer PDU):** 
    Used by the **COM** module. It contains signals (like engine speed or temp) packed together. It is "pure" data from the application's perspective.
*   **N-PDU (Network Layer PDU):** 
    Used by the **CanTp** (Transport Protocol) module. If an I-PDU is too large for a single CAN frame (e.g., > 8 bytes for classic CAN), CanTp breaks it into multiple N-PDUs with flow control.
*   **L-PDU (Data Link Layer PDU):** 
    Used by **CanIf**. This adds the CAN ID and DLC (Data Length Code). This is the final package ready for the hardware mailbox.

---

### 2. The PDU Routing Table (The "Post Office")
The **PduR (PDU Router)** acts as the central hub. It doesn't modify the data; it simply looks at its **Routing Table** to decide where a PDU goes.

**Critical Configuration Elements in a PDU Routing Table:**
1.  **Source PDU ID:** The unique identifier assigned by the sending module.
2.  **Destination Module:** (e.g., CanIf, CanTp, COM, or DCM).
3.  **Routing Path:** Defines if the communication is **1:1** (Unicast) or **1:N** (Gateway/Multicast).
4.  **PDU Direction:** RX (Receive) or TX (Transmit).

| Source Module | Target Module | PDU Type | Use Case |
| :--- | :--- | :--- | :--- |
| COM | PduR | TX I-PDU | Normal Application Data Transmission |
| CanIf | PduR | RX L-PDU | Reception of standard CAN messages |
| CanTp | PduR | RX/TX N-PDU | Large data (Diagnostics/Flashing) |
| DCM | PduR | TX/RX PDU | Diagnostic Requests/Responses |

---

### 3. PDU Transformation Flow (ASCII)

This diagram shows how data evolves from a "Signal" into a physical "Frame."

```text
    LAYER           ENTITY                      DATA STRUCTURE
    =====           ======                      ==============

 [ Application ]  (SW-C)                     [ Signal A ][ Signal B ]
                    |                               |
                    v                               v
 [ Services ]     (COM)                      +-------+-------+-------+
                    |                        |     I - PDU           |
                    v                        +-------+-------+-------+
 [ Services ]     (PduR)                             |
                    |                 (Routes I-PDU based on ID)
          +---------+---------+                      |
          |                   |                      v
          |          [ Transport Prot. ]     +-------+-------+-------+
          |            (CanTp)               |  PCI  |   N - PDU     |
          |          (Segmentation)          +-------+-------+-------+
          |                   |                      |
          +---------+---------+                      |
                    |                                v
 [ Hardware ]     (CanIf)                    +-------+-------+-------+
 [ Abstraction ]    |                        | CANID |   L - PDU     |
                    v                        +-------+-------+-------+
                                                     |
 [ Micro-      ]  (CanDrv)                   [ HW Register Write ]
 [ controller  ]                                     |
                                                     v
 [ Physical    ]  (CAN Bus)                  [SOF][ID][CTRL][DATA][CRC]
```

---

### 4. Critical Configuration Checklist for PDUs

*   **PduId References:** Every layer must point to the same PDU ID. If `CanIfRxPduId` in CanIf doesn't match the `PduRSourcePduHandleId` in PduR, the data "drops into a black hole."
*   **Data Provisioning:** 
    *   **Direct:** Data is copied immediately.
    *   **Trigger Transmit:** The PduR asks the upper layer for data only when the lower layer is ready (common in LIN or FlexRay, rare in standard CAN).
*   **PduLength:** Ensure the PDU length matches across all modules. A mismatch between COM (8 bytes) and CanIf (64 bytes for CAN-FD) will cause runtime errors.

> **Trainer's Note:** Remember that **PduR is static**. You cannot change routing paths during runtime. Everything must be defined in your configuration tool during the design phase. If you're losing messages, check the **CanIfRxPduCanIdMask**—it’s often the reason why valid PDUs are filtered out before reaching the PduR.