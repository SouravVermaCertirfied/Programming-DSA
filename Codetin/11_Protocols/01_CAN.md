# CAN Protocol
- Controller Area Network
- **Multi-Master**: Any node can initiate communication.
- **Message-Oriented**: Nodes communicate by sending messages (frames) rather than direct addresses.
- **Broadcast Communication**: All nodes receive messages, but only those interested will process them.
- **Error Detection**: Built-in mechanisms to detect and manage errors.
- **Priority Handling**: Message IDs determine priority—lower ID = higher priority.
- **Robustness**: Handles harsh environments, noise-resistant.

## CAN Message Types

- Data Frame: Transmits data.
- Remote Frame: Requests data from another node.
- Error Frame: Sent when an error is detected.
- Overload Frame: Requests extra delay between frames.

**CAN Message Format (11-bit)**
```c
| SOF 1b | Identifier 11b | RTR 1b | IDE 1b | DLC 4b | Data 0–8B | CRC 16b | ACK 2b | EOF 7b |                                      
```
**CAN Message Format (29-bit)**
```c
| SOF | Identifier (Base ID) | SRR | IDE | Identifier (Ext ID) | RTR | r1 | r0 | DLC | Data | CRC | ACK | EOF |
  1b        11b                 1b    1b        18b                 1b    1b   1b   4b   0–8B   16b   2b    7b

```

---
<div style="display: flex; justify-content: space-between;">
    <span></span>
    <a href="02_I2C.md">02_I2C.md →</a>
</div>