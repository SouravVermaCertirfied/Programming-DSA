The **STRIDE** method, originally developed by Microsoft, is a cornerstone of threat modeling in automotive cybersecurity. Given the shift toward Software-Defined Vehicles (SDVs), OTA updates, and V2X connectivity, applying STRIDE helps engineers identify vulnerabilities before they reach the assembly line.

---

## What is STRIDE?
STRIDE is an acronym representing six categories of security threats. In an automotive context, these apply to the **CAN bus, ECUs, infotainment systems, and cloud backends.**

| Threat | Security Property | Automotive Example |
| :--- | :--- | :--- |
| **S**poofing | Authenticity | An attacker sends fake messages to the CAN bus pretending to be the Brake Control Module. |
| **T**ampering | Integrity | Modifying the firmware of an ECU or altering sensor data (e.g., GPS coordinates) during transmission. |
| **R**epudiation | Non-repudiability | A malicious actor triggers a remote command but deletes logs so the system cannot prove who did it. |
| **I**nformation Disclosure | Confidentiality | Eavesdropping on a driver’s private location data or stealing cryptographic keys from vehicle memory. |
| **D**enial of Service | Availability | Flooding the vehicle's gateway with traffic to prevent critical safety messages from being delivered. |
| **E**levation of Privilege | Authorization | A user gaining "Root" access to the infotainment system to bypass safety restrictions or access the drivetrain. |

---

## Applying STRIDE to a Vehicle System
To use STRIDE effectively, automotive engineers typically follow these four steps:

### 1. Decompose the System
Create a **Data Flow Diagram (DFD)** of the feature (e.g., Remote Keyless Entry). Identify:
*   **External Entities:** The user, the key fob, the cloud.
*   **Processes:** The authentication logic, the door lock command.
*   **Data Stores:** The key database, the log files.
*   **Data Flows:** The RF signals, the internal bus messages.

### 2. Identify Threats
Map each STRIDE category to the components of the DFD. 
*   *Is the RF signal between the fob and the car susceptible to **Spoofing** (Relay Attack)?*
*   *Can the internal logs be **Tampered** with to hide a forced entry?*

### 3. Address the Threats
Once identified, you must decide how to handle the risk:
*   **Mitigate:** Use AES-128 encryption or Message Authentication Codes (MACs).
*   **Transfer:** Use a third-party cybersecurity service to monitor the backend.
*   **Eliminate:** Remove the risky feature (e.g., disabling a debug port in production).
*   **Accept:** If the risk is extremely low and the cost to fix it is too high.

### 4. Verify
Ensure the mitigations actually work through **Penetration Testing** and **Fuzzing**.

---

## Why it Matters: ISO/SAE 21434
In the modern automotive industry, STRIDE is often used to satisfy the requirements of **ISO/SAE 21434**. This standard mandates a formal **TARA (Threat Analysis and Risk Assessment)**. While ISO 21434 doesn't force you to use STRIDE, it is the most common "brainstorming" framework used to populate the TARA.

> **Pro-Tip:** When modeling for vehicles, pay extra attention to **Denial of Service (DoS)**. In a PC, a DoS is an annoyance; in a vehicle traveling at 70 mph, a DoS on the braking sub-network is a life-safety critical event.

Are you looking to apply STRIDE to a specific automotive component, like the Infotainment (IVI) or the Gateway ECU?

---
---

Applying the **STRIDE** methodology to an **Electronic Power Steering (EPS)** system is a critical exercise because the EPS is a safety-relevant component (usually rated at ASIL D, the highest integrity level). A compromise here doesn't just mean a data breach; it means a physical loss of vehicle control.

---

## 1. System Decomposition (The DFD)
To analyze the EPS, we first look at its primary interfaces:
*   **Sensors:** Torque sensor (driver input) and Steering Angle sensor.
*   **Communication:** High-speed CAN or CAN-FD bus connecting the EPS to the Engine Control Module (ECM) and ADAS (for lane-keep assist).
*   **Actuator:** The electric motor that provides steering assistance.
*   **Power:** The 12V/48V battery system.



---

## 2. STRIDE Threat Analysis for EPS

### **Spoofing (S)**
*   **Threat:** An attacker injects a spoofed message onto the CAN bus appearing to come from the ADAS module.
*   **Impact:** The EPS "thinks" the Lane Keep Assist is requesting a sharp turn, causing the car to veer off the road (Command Injection).

### **Tampering (T)**
*   **Threat:** A technician or malicious actor modifies the EPS calibration files stored in the NVM (Non-Volatile Memory).
*   **Impact:** The steering feel becomes erratic, or the "end-stop" software limits are removed, potentially damaging the steering rack hardware during a full turn.

### **Repudiation (R)**
*   **Threat:** A firmware update fails or a malicious command is sent, but the EPS diagnostic logs are cleared or overwritten.
*   **Impact:** During a crash investigation, forensic experts cannot prove whether the steering failure was due to a cyberattack or a mechanical fault.

### **Information Disclosure (I)**
*   **Threat:** Reading the real-time torque and angle data via the OBD-II port without authorization.
*   **Impact:** While less critical than control, this data can be used to profile a driver’s behavior or "fingerprint" the vehicle for more advanced subsequent attacks.

### **Denial of Service (D)**
*   **Threat:** Flooding the CAN bus with high-priority traffic (Bus Off attack) so the EPS cannot receive the vehicle speed signal.
*   **Impact:** The EPS fails into a "Safe State." This usually means a loss of power assistance, making the steering extremely heavy and difficult for the driver to maneuver.

### **Elevation of Privilege (E)**
*   **Threat:** Using a vulnerability in the Infotainment system to pivot to the Gateway and eventually gain "Superuser" access to the EPS bootloader.
*   **Impact:** The attacker can reflash the EPS with malicious firmware that ignores all safety inhibits.

---

## 3. Mitigation Strategies
Following the **ISO 26262** (Functional Safety) and **ISO/SAE 21434** (Cybersecurity) standards, the following controls are typically implemented:

*   **Secure Hardware (HSM):** Using a Hardware Security Module to store cryptographic keys.
*   **SecOC (Secure Onboard Communication):** Implementing Message Authentication Codes (MACs) and Freshness Values on CAN messages to prevent **Spoofing** and **Replay** attacks.
*   **Secure Boot:** Ensures the EPS only executes firmware signed by the manufacturer, preventing **Tampering**.
*   **Diagnostic Authentication:** Requiring a "Challenge-Response" (seed/key) mechanism before allowing any changes to EPS parameters via a scan tool (**Elevation of Privilege**).
*   **Internal Plausibility Checks:** The EPS should compare the "Requested Torque" from ADAS against other vehicle sensors (like lateral acceleration). If the request is physically impossible or suspicious, the EPS should ignore it.

---

### **Summary Table for EPS TARA**
| STRIDE Category | Primary Vulnerability | Typical Mitigation |
| :--- | :--- | :--- |
| **Spoofing** | Fake ADAS Commands | SecOC (MAC Authentication) |
| **Tampering** | Malicious Firmware | Secure Boot / Hardware Root of Trust |
| **DoS** | CAN Bus Flooding | Intrusion Detection System (IDS) / Gateway Filtering |

Would you like to dive deeper into the **SecOC** protocols used to prevent the spoofing threats mentioned above?