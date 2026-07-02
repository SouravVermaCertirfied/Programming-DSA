Designing a secure communication framework for Controller Area Network (CAN) and CAN Flexible Data-Rate (CAN-FD) requires addressing a core architectural vulnerability: **CAN is inherently a broadcast bus with zero native encryption, authentication, or source verification.** Any node spliced into the twisted-pair wiring can spoof frames, inject malicious payloads, or replay past valid transmissions.

To solve this at scale, the automotive industry (via AUTOSAR) standardized **SecOC (Secure Onboard Communication)**.

---

## 1. The SecOC Protocol Architecture

SecOC adds an authentication layer to standard CAN/CAN-FD data payloads using symmetric cryptography. It relies on two pillars to verify authenticity and freshness:

1. **Message Authentication Code (MAC):** Proves the authenticity and integrity of the data payload.
2. **Freshness Value (FV):** Defeats replay attacks by ensuring every transmitted frame is cryptographically unique, even if the underlying data payload (e.g., vehicle speed = 0) remains identical.

### The Symmetric Edge

Why symmetric cryptography ($AES-128\ CMAC$) instead of asymmetric ($ECDSA$)?

* **Latency Constraints:** A typical CAN frame requires an end-to-end processing budget of $<2\text{ ms}$. Asymmetric validation takes orders of magnitude longer on automotive microcontrollers.
* **Payload Overhead:** A classic CAN frame has only an 8-byte payload. CAN-FD extends this to 64 bytes. Asymmetric signatures (e.g., 64-byte $ECDSA\ P-256$) would completely consume or overflow a CAN-FD frame without even leaving space for the actual signal data.

---

## 2. Payload Construction & Wire Format

To optimize bus bandwidth, SecOC does not always transmit the full Freshness Value or the full MAC over the wire. Instead, it uses **truncation**.

### The SecOC Broadcast Frame:

* **Authentic Data:** The original signal data (e.g., steering angle, brake pressure).
* **Truncated Freshness Value ($\text{FV}_{\text{Tx}}$):** Only the lowest significant bits (LSBs) of the freshness counter are sent to allow the receiver to synchronize its internal counter.
* **Truncated MAC ($\text{MAC}_{\text{Tx}}$):** The generated MAC is truncated (typically to 4–8 bytes) to fit the remaining CAN-FD payload allocation while maintaining an acceptable security margin against brute-force blind injection.

---

## 3. The Cryptographic Flow Matrix

### A. Transmission (Tx) Logic

When an ECU (e.g., Powertrain Control Module) needs to broadcast a secured message:

1. **Construct PDU:** The ECU compiles the raw functional data signals.
2. **Fetch Full FV:** The SecOC module fetches the current, full-length Freshness Value (e.g., a 64-bit counter) from its internal Freshness Value Management (FVM) driver.
3. **Concatenate Payload:** The engine concatenates the Data, the Data ID (a unique 16-bit identifier for that specific message type to prevent type-substitution attacks), and the **Full FV**:

$$\text{Payload}_{\text{MAC}} = \text{Data} \parallel \text{Data ID} \parallel \text{Full FV}$$


4. **Generate CMAC:** The hardware HSM executes an $AES-128\ CMAC$ operation over $\text{Payload}_{\text{MAC}}$ using a pre-shared Secret Key:

$$\text{Full MAC} = \text{AES-128-CMAC}(K_{\text{SecOC}}, \text{Payload}_{\text{MAC}})$$


5. **Truncate and Transmit:** The full MAC and full FV are truncated. The final PDU ($\text{Data} \parallel \text{Truncated FV} \parallel \text{Truncated MAC}$) is pushed to the CAN controller Tx mailbox.

### B. Reception (Rx) Logic

When a receiving ECU catches the frame on the bus:

1. **Parse Payload:** It splits the frame into Data, $\text{Truncated FV}$, and $\text{Truncated MAC}$.
2. **Reconstruct Full FV:** The receiver takes its *own* internally maintained high-order bits of the Freshness Value and appends the received $\text{Truncated FV}$ (LSBs) to reconstruct what it believes is the **Full FV**.
3. **Locate Symmetric Key:** The HSM pulls the corresponding $K_{\text{SecOC}}$ symmetric key assigned to that specific Message Data ID.
4. **Local CMAC Verification:** The receiver calculates its own local verification MAC over the reconstructed data assembly:

$$\text{Local MAC} = \text{AES-128-CMAC}(K_{\text{SecOC}}, \text{Data} \parallel \text{Data ID} \parallel \text{Reconstructed Full FV})$$


5. **Bitwise Compare:** The receiver truncates its $\text{Local MAC}$ to match the wire-length of the received $\text{Truncated MAC}$. It performs a constant-time comparison. If they match, the message is accepted and passed to the functional application layers; if they mismatch, the frame is dropped, and an error counter increments.

---

## 4. Scaling the Freshness Engine: The FVM Architecture

Managing monotonic freshness counters synchronously across 80+ ECUs over a lossy CAN bus is the hardest part of a production SecOC design. If one ECU's counter drifts or desynchronizes, it will fail to reconstruct the Full FV, resulting in dropped frames (e.g., the ABS module ignoring messages from the Steering column).

To solve this at scale, a centralized **Freshness Value Manager (FVM)** architecture is deployed, typically hosted on the Central Gateway ECU.

### The Triple-Counter Structure (64-bit Full FV)

To minimize bus chatter while maintaining multi-year monotonic tracking, the 64-bit FV is segmented:

* **Trip Counter (High Bits):** Incremented by the Gateway master node every time the vehicle ignition cycles or a fresh "Trip" starts. This value is saved persistently in non-volatile memory (EEPROM/Flash).
* **Reset Counter (Middle Bits):** Incremented cyclically by the Gateway (e.g., every 1000ms) or when the lower message counter overflows.
* **Message Counter (Low Bits):** Incremented locally by individual Tx ECUs every single time a specific CAN frame is transmitted. This is the value truncated onto the wire.

### Synchronization Synchronization Loop

1. The FVM Master periodically broadcasts a **Synchronization Frame** containing the current global **Trip Counter** and **Reset Counter** alongside an authentication MAC.
2. All slave ECUs catch this frame, verify its authenticity, and overwrite their internal high-order and middle-order tracking bits.
3. This keeps the network synchronized, preventing long-term counter drift caused by local clock skew or dropped packets.

---

## 5. Security Architecture & Key Management

SecOC is only as secure as the storage of its symmetric keys ($K_{\text{SecOC}}$). If an attacker extracts a single key from one low-priority ECU (e.g., a smart seat motor), they can spoof messages to drive-critical components sharing that key layer.

### A. Key Isolation & Separation

* **Never Use Global Network Keys:** Do not use one master symmetric key for the whole vehicle. Keys must be strictly isolated per communication cluster or clustered by functional pairing (e.g., $K_{\text{Engine\_to\_Transmission}}$).
* **Symmetric Key Custody:** Symmetric keys must reside strictly within the secure RAM/registers of the **Evita HSM / Secure Enclave** of the microcontroller. The host application core (running the AUTOSAR OS or a POSIX RTOS) should never have read access to these key registers; it can only invoke cryptographic operations by passing a pointer to the hardware slot index.

### B. Dynamic Key Derivation (Sym-Agility)

Instead of hardcoding static SecOC keys during factory assembly, keys should be dynamically updated or rotated using a symmetric Key Derivation Function (KDF):

1. During vehicle startup, the Master Gateway handles an initial asymmetric challenge-handshake with peripheral nodes using the PKI infrastructure (**LDevIDs**).
2. Once authenticated, a **Master Session Key** is established, from which sub-keys for SecOC channels are derived using an $HKDF-SHA256$ derivation primitive based on the current system state or epoch token. This eliminates the risk of permanent extraction of static factory keys via hardware side-channel attacks (e.g., differential power analysis or fault injection).