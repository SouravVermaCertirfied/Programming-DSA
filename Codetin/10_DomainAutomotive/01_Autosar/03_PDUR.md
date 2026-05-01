## The PduR (PDU Router): The Central Switchboard

In the AUTOSAR COM stack, the **PduR (PDU Router)** acts as the "Grand Central Station." Its primary job is to route Protocol Data Units (PDUs) between different modules. It is essentially a bridge that decouples upper-layer modules (like COM or DCM) from lower-layer modules (like CanIf, FrIf, or LinIf).

Crucially, the PduR does **not** modify the data payload. It simply looks at the incoming PDU ID and consults its internal "lookup table" to decide where the data needs to go next.

---

### 1. Primary Use Cases of PduR

*   **Local Routing:** Passing data from the Communication layer (COM) down to the Interface layer (CanIf) for transmission, or vice versa for reception.
*   **Transport Protocol (TP) Gateway:** Routing large diagnostic data between different transport protocols (e.g., routing a diagnostic request from CAN-TP to FlexRay-TP).
*   **PDU Fan-out:** Taking one incoming PDU and sending it to multiple destination modules (e.g., sending an engine signal to both the COM module for application logic and a Gateway for another bus).
*   **Gateway Functionality:** Routing data directly between two lower-layer modules (e.g., CAN-to-CAN or CAN-to-LIN) without involving the application layer.



---

### 2. Critical Configurations in PduR

To make the PduR function, you must configure a series of "Routing Paths." If even one ID is mismatched, the entire communication chain breaks.

#### A. PduRRoutingPath
This is the top-level container for a single routing instruction. It links a **Source** to one or more **Destinations**.

#### B. PduRSourcePdu
*   **PduRSourcePduHandleId:** This is the ID that the *sending* module uses to identify the data.
*   **PduRSourcePduRef:** A symbolic reference to the actual PDU defined in the source module (e.g., a reference to an I-PDU in the COM module).

#### C. PduRDestPdu
*   **PduRDestPduHandleId:** The ID that the *receiving* module expects to see.
*   **PduRDestPduRef:** A reference to the PDU in the destination module (e.g., a reference to an L-PDU in CanIf).
*   **PduRTransmissionConfirmation:** A boolean flag. If true, the PduR will notify the upper layer once the lower layer confirms the message was physically sent on the bus.

#### D. PduRConfiguration (Routing Tables)
*   **PduRMaxPduIdCount:** Defines the total number of PDUs the router can handle.
*   **PduRRoutingTable:** A collection of all routing paths. In complex ECUs, this table can contain hundreds of entries.

---

### 3. PduR Interaction Flow (ASCII Diagram)

This diagram shows how PduR handles both **Standard Data (COM)** and **Diagnostic Data (DCM/TP)**.

```text
      [ Upper Layer Modules ]          [ PDU Router (PduR) ]         [ Lower Layer Modules ]
      =======================          =====================         =======================

      +-----------------+                                             +-----------------+
      |   COM Module    |----(PduR_ComTransmit)----|                  |   CAN Interface |
      | (App Signals)   |                          |                  |     (CanIf)     |
      +-----------------+                          |                  +-----------------+
                                                   |                           ^
                                           [ ROUTING TABLE ]                   |
      +-----------------+                          |            (CanIf_Transmit / RxIndication)
      |   DCM Module    |----(PduR_DcmTransmit)----|                           |
      |  (Diagnostics)  |                          |                           v
      +-----------------+                          |                  +-----------------+
                                                   |                  |  CAN Transport  |
                                                   |                  |      (CanTp)    |
                                                   |                  +-----------------+
                                                   |                           |
                                                   |---------------------------|
```

---

### 4. Important Operational Rules

1.  **Static Routing:** PduR is entirely static. You cannot "discover" new routes at runtime. If it isn't in the configuration code, the packet is dropped.
2.  **Zero-Copy (Mostly):** PduR usually passes pointers to data buffers rather than copying the data itself, which keeps it extremely fast.
3.  **Buffer Management:** When acting as a Gateway for Transport Protocols (CanTp), the PduR may provide "PduR Buffers" to hold segments of data during the transfer.

**Trainer's Checklist:**
> When a signal isn't reaching your Application, check the **PduRSourcePduHandleId**. A common mistake is using the *CAN ID* instead of the *PDU Handle ID*. Remember: CanIf cares about CAN IDs; PduR only cares about Handle IDs assigned during configuration.