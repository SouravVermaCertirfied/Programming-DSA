# DCM

<details><summary>FlowChart</summary>

```javascript

[ EXTERNAL DIAGNOSTIC TESTER ]
           |
           | (1) CAN Frame (Request)
           v
+---------------------------------------+
|          CAN INTERFACE (CanIf)        |
+---------------------------------------+
           |
           | (2) PDU Interaction
           v
+---------------------------------------+
|          PDU ROUTER (PduR)            |
+---------------------------------------+
           |
           | (3) Route to DCM
           v
=========================================
||        DCM (AUTOSAR LAYER)          ||
||                                     ||
||  +-------------------------------+  ||
||  |  DSL (Session Layer)          |  ||
||  |  - Start P2 Timers            |  ||
||  |  - Manage Session/Security    |  ||
||  +---------------|---------------+  ||
||                  |                  ||
||  +---------------v---------------+  ||
||  |  DSD (Service Dispatcher)     |  ||
||  |  - Verify Service ID (SID)    |  ||
||  |  - Check Session/Sec Access   |  ||
||  +---------------|---------------+  ||
||                  |                  ||
||  +---------------v---------------+  ||
||  |  DSP (Service Processor)      |  ||
||  |  - Parse Data Parameters      |  ||---(4)--> [ RTE / SW-C ]
||  |  - Execute Service Logic      |  ||<--(5)--- [ DEM / BswM ]
||  +---------------|---------------+  ||
||                  |                  ||
||  +---------------v---------------+  ||
||  |  DSD (Response Assembly)      |  ||
||  |  - Add SID + 0x40 (Positive)  |  ||
||  +---------------|---------------+  ||
||                  |                  ||
||  +---------------v---------------+  ||
||  |  DSL (Transmission Control)   |  ||
||  |  - Finalize P2/S3 Timers      |  ||
||  +-------------------------------+  ||
||                  |                  ||
====================|====================
                    |
                    | (6) Response PDU
                    v
+---------------------------------------+
|          PDU ROUTER (PduR)            |
+---------------------------------------+
                    |
                    | (7) Route to CanIf
                    v
+---------------------------------------+
|          CAN INTERFACE (CanIf)        |
+---------------------------------------+
                    |
                    | (8) CAN Frame (Response)
                    v
[ EXTERNAL DIAGNOSTIC TESTER ]

```
</details>