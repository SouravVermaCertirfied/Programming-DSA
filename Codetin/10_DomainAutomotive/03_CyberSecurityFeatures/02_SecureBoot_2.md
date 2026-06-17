```text

==================================================================================================
                      RH850 SECURE BOOT HARDWARE & SOFTWARE INTERACTION FLOW
==================================================================================================

    +-------------------------------------------------+
    |               POWER-ON RESET (POR)              |
    |  - Option Bytes dictate Hardware Boot Area      |
    |  - Main CPU executes from Immutable Boot ROM/PBL|
    +-------------------------------------------------+
                            │
                            ▼
    +-------------------------------------------------+
    |         MAIN CPU: INITIALIZE PERIPHERALS        |
    |  - Configure Watchdog Timer (WDT) window        |
    |  - Locate Application Header in Code Flash      |
    +-------------------------------------------------+
                            │
                            ▼
    +-------------------------------------------------+
    |       MAIN CPU: CHECK HEADER SANITY             |
    |  - Read Flash at App Header Offset              |
    |  - Check Magic Number (e.g., 0x53454342)        |
    +-------------------------------------------------+
                            │
            ┌───────────────┴───────────────┐
    [Magic Valid?]                  [Magic Invalid?]
            │                               │
            ▼ (Yes)                         ▼ (No)
    +-------------------------------+   +-----------------------------------+
    |    POLL ICU-M MAILBOX STATUS  |   |    FATAL ERROR: BYPASS TO SAFE    |
    |  Read: ICUM_MBX_STATUS        |   |  - Go to Execute_Safe_State_Halt()|
    +-------------------------------+   +-----------------------------------+
            │                                               ▲
    ┌───────┴───────┐                                       │
[ICUM_STATUS_BUSY?]                                         │
    │               │                                       │
    ▼ (Yes)         ▼ (No)                                  │
[Service WDT]  +------------------------------------+       │
    │          |   PROVISION ICU-M MAILBOX REGISTERS|       │
    └───────►  | - ICUM_MBX_DATAPTR = Header Address|       │
               | - ICUM_MBX_CMD = 0x000000A5        |       │
               +------------------------------------+       │
                                │                           │
                                ▼                           │
               +------------------------------------+       │
               |     ICU-M ACCELERATOR WAKES UP     |       │
               | - Reads Key from secure hardware   |       │
               | - Streams Flash Payload into Engine|       │
               | - Computes Asymmetric Signature    |       │
               +------------------------------------+       │
                                │                           │
                                ▼                           │
               +------------------------------------+       │
               |    MAIN CPU: POLL FOR COMPLETION   |       │
               | - Check ICUM_MBX_STATUS            |       │
               | - Service Hardware Watchdog        |       │
               +------------------------------------+       │
                                │                           │
         ┌──────────────────────┴──────────────────────┐    │
[ICUM_STATUS_SUCCESS?]                        [ICUM_STATUS_FAIL?]
         │                                             │    │
         ▼ (Yes: Signature & Anti-Rollback Match)      ▼ (No: Cryptographic Mismatch)
    +------------------------------------+       +-----------------------------------+
    |    SUCCESSFUL CHAIN OF TRUST       |       |       CRITICAL SECURITY AUDIT     |
    | - Extract Header->entry_point      |       | - Log failure to SecOC/Dem        |
    | - Clear/Reconfigure Boot Watchdog  |       | - Isolate Communication Channels  |
    +------------------------------------+       +-----------------------------------+
                     │                                             │
                     ▼                                             ▼
    +------------------------------------+       +-----------------------------------+
    |      BRANCH TO APPLICATION         |       |      EXECUTE SAFE STATE HALT     |
    | - Inline assembly: "jmp [reg]"     |       | - Disable interrupts globally     |
    | - Main Application starts running  |       | - Allow Watchdog to reset system  |
    +------------------------------------+       | - Or switch to Golden Image bank  |
                                                 +-----------------------------------+

```