# Mastering the Air-Gapped Smart Lock: Synchronized Offline OTP Architectures


### 1. The Core Engineering Challenge: The "Cloud Crutch" vs. Power Budget



In consumer smart-lock firmware, however, we face a brutal operational constraint: the Wi-Fi power trap.

A continuous Wi-Fi connection drains standard AA batteries in weeks. To achieve an operating life of 12 to 18 months, the MCU must spend 99.9% of its life in a deep-sleep state micro Ampere range, waking only via a hardware GPIO interrupt from a keypad press.

```
+-----------------------------------------------------------------------+
|                         THE SYSTEM DILEMMA                            |
|                                                                       |
|  [ Cloud-Connected Model ]           [ Air-Gapped Model ]            |
|  - Continuous Wi-Fi telemetry        - MCU in deep sleep             |
|  - Heavy network stack power drain    - Wakes up ONLY on keypress     |
|  - Battery Life: Weeks               - Battery Life: 1+ Year         |
|                                                                       |
|  CRITICAL QUESTION: How do we securely authorize a remote guest      |
|  without a network connection to receive the validation key?         |
+-----------------------------------------------------------------------+
```

Our objective today is to trace how the system passes complex configuration parameters (activation time, duration, and access rights) wrapped inside a simple, human-typable 6-digit decimal token, utilizing nothing but synchronized math.

---

### 2. High-Level Architecture & Data Flow

The system achieves this trick by operating as an asymmetric, synchronized time-based state machine. The phone application acts as the "Heavy Compute Engine," while the lock firmware operates as a "Deterministic State Validator."

#### System Component Interactions

```
+--------------------------+                 +--------------------------+
|        PHONE APP         |                 |    LOCK HARDWARE/FW      |
|  - Network Time (NTP)    |                 |  - Low-Power RTC Crystal |
|  - Cryptographic Key (K) |                 |  - Cryptographic Key (K) |
+------------+-------------+                 +------------+-------------+
             |                                            |
   Generates | 6-Digit Code                               | Validates via
             v                                            v Local Math
   +--------------------+   Shared via SMS/Text   +--------------------+
   |   Guest Handset    |------------------------>|    Physical Lock   |
   | (Displays 583910)  |                         |   Keypad Input     |
   +--------------------+                         +--------------------+
```

---

### The Micro-Payload Construction

Instead of hashing just the current time (like standard Google Authenticator 2FA), the app compresses the entry parameters into a compact 32-bit Micro-Payload Struct ($M$).

```
+------------------ 32-Bit Micro-Payload Struct (M) -------------------+
|  Start Epoch (16 bits)   |  Duration (4 bits)  |  Guest Index (4 bits) |
|  e.g., 1:00 AM Slot      |  e.g., "2 Hours"    |  e.g., Guest #1       |
+-----------------------------------------------------------------------+
```

Start Epoch: The time domain is split into coarse chunks (e.g., 30-minute or 1-hour blocks).
Duration Enum: Pre-defined windows mapped to bit combinations (e.g., 01 = 1 hour, 10 = 2 hours).
Guest Index / Salt Nonce: Multi-guest collision handling.

---

### 3. The Cryptographic Sequence (App to Keypad)

The following sequence diagram outlines how this 32-bit structure is transformed into a 6-digit decimal code and evaluated at the door.

```
[Phone App Engine]           [Guest]              [Lock Firmware]
         |                       |                        |
1. Pack parameters into M        |                        |
2. Compute Hash = HMAC(K, M)     |                        |
3. Truncate & Modulo Hash        |                        |
   to 6-Digit Decimal String     |                        |
         |                       |                        |
         |-- Send 6-digit OTP -->|                        |
         |   (e.g., "482019")    |                        |
         |                       |                        |
         |                       |-- Types "482019" ----->| 1. Wake up from sleep via GPIO
         |                       |   on physical keypad   | 2. Read local RTC time
         |                       |                        | 3. Execute search loop:
         |                       |                        |    Reconstruct M_local for
         |                       |                        |    possible time/guest shifts.
         |                       |                        | 4. Compute local HMACs
         |                       |                        | 5. Match found?
         |                       |                        |<-- [YES] Actuate solenoid
         |                       |                        |    [NO] Increment error counter
```

---

### 4. Execution Walkthrough: The Dual-Guest Scenario

Let’s ground this logic by analyzing a concrete edge case. You have two separate delivery drivers arriving at 1:00 PM.

Guest A needs a 1-hour entry window.
Guest B needs a 2-hour entry window.

#### Step 1: App Side Synthesis

The app initializes two separate payload definitions using the shared master key ($K$).

**[Guest A Struct Generation]**

* Start Time: 1:00 PM (Epoch ID: 4820)
* Duration: 1 Hour (Enum: 01)
* Guest Index: 00 (Default)

Payload M_A = [4820 || 01 || 00] → HMAC-SHA256 → Truncate/Mod → Code A: 123456

**[Guest B Struct Generation]**

* Start Time: 1:00 PM (Epoch ID: 4820)
* Duration: 2 Hours (Enum: 10)
* Guest Index: 00 (Default)

Payload M_B = [4820 || 10 || 00] → HMAC-SHA256 → Truncate/Mod → Code B: 789012

Result: Because the duration configuration changes the underlying bits of the text string being hashed, the two guests receive entirely different codes, despite arriving at the exact same minute.

---

### Step 2: Lock Side Evaluation Loop

Guest B arrives at the door at 2:15 PM and types 789012. The lock wakes up.

```
[Lock Evaluates Code 789012]
        |
        v
Read Local RTC Time
(Time reads: 2:15 PM)
        |
        v
Generate Search Boundaries
(Look back 2 hours to capture valid open codes)
        |
        v
+-------------------------------------------------------+
| Iteration Loop: Generate expected OTPs for:          |
| - Time slots: 12:30 PM, 1:00 PM, 1:30 PM, 2:00 PM    |
| - Durations: 30m, 1hr, 2hr, 24hr                     |
+-------------------------------------------------------+
        |
        v
Does Generated == 789012?
(Match found on: 1:00 PM slot + 2-hour duration)
        |
        v
Verify safety logic:
Is 2:15 PM inside the 1:00 PM + 2hr window?
        |
   +--------+--------+
 [YES] v           [NO] v
Unlock solenoid     Reject code
```

---

### 5. Handling Advanced Operational Edge Cases

#### Case A: Two Guests, Same Arrival Time, SAME Duration

What happens if both Guest A and Guest B arrive at 1:00 PM and both require a 1-hour window? If the payload parameters are perfectly identical, the resulting hash output will be identical. Sending the same 6-digit code to two different individuals introduces a security risk.

The system breaks this symmetry using the Guest Index / Salt Nonce slot inside the payload:

Guest 1 Struct: [Start Time: 1:00 PM] + [Duration: 1 hr] + [Guest Index: 00] → OTP: 456123
Guest 2 Struct: [Start Time: 1:00 PM] + [Duration: 1 hr] + [Guest Index: 01] → OTP: 987321

Firmware Impact: To support this, the local verification search loop simply expands its iterations slightly. On every keypress evaluation, it checks Guest Index = 00, then 01, up to a predefined hardware limit (typically a maximum of 4 active simultaneous guest tokens per time step).

---

#### Case B: The Time-Drift Trap

Because the lock lacks access to an NTP server, its low-power internal RTC crystal will slowly drift out of phase with real-world time due to temperature fluctuations and battery degradation.

If the lock's clock slips 20 minutes behind the phone's clock, the validation boundaries shift out of alignment, causing valid guest codes to be falsely rejected.

```
[Real World / Phone App Time]               [Lock Hardware Clock]
          1:00 PM                                  12:40 PM (Drifted Behind)
             |                                               |
    Generates 1:00 PM code                                  |
             |                                               |
             v                                               v
    Guest types code at door ------[Lock reads clock]------->|
                                                          Evaluates code for 12:40 PM
                                                          [REJECTED: Too Early]
```

#### The Passive Sync Solution

To maintain alignment without a Wi-Fi link, the system utilizes a passive synchronization mechanism via its secondary radio interface (Bluetooth Low Energy).

Every time a primary user (the homeowner) interacts with the lock using the smartphone app locally via Bluetooth, the app executes a silent, background time calibration command. The phone pushes its cellular-synchronized network timestamp to the lock's registers, resetting the internal RTC drift error to zero.

---

### 6. Training Review: Key Design Takeaways

**Zero-Knowledge Decoding:** The lock never truly "decodes" or parses the entry text. It runs a localized, bounded simulation of what the app should have generated, matching inputs against generated expectations.

**Deterministic Boundaries:** To keep Worst-Case Execution Time (WCET) bounded and protect the battery from processor-heavy search loops, variables like duration and look-ahead windows are constrained to highly quantized, predefined step configurations.

**The Power-Security Trade-Off:** The math guarantees that we can maintain a completely air-gapped security perimeter, exchanging high power consumption for brief, localized computational bursts.

---
