A **TARA (Threat Analysis and Risk Assessment)** is a formal document required by the **ISO/SAE 21434** standard. While STRIDE is a *method* used to brainstorm threats, the TARA is the *comprehensive engineering work product* that legally and technically justifies the security of a vehicle system.

If STRIDE is the "how," the TARA is the "proof."

---

## The TARA Workflow
The TARA document follows a strict, repeatable process defined in **Clause 15** of ISO/SAE 21434. It is often described as the cybersecurity equivalent of the **HARA** (Hazard Analysis and Risk Assessment) used in functional safety (ISO 26262).

### 1. Item Definition & Asset Identification
Before analyzing threats, you must define the "Item" (e.g., the Electronic Power Steering).
*   **Assets:** Identify what needs protection. For EPS, assets include the **Steering Control Logic (Integrity)** and **Diagnostic Keys (Confidentiality)**.
*   **Cybersecurity Properties:** Define which property (CIA + Authenticity) is vital for each asset.

### 2. Damage Scenarios
You describe what happens to the *user* or the *vehicle* if an asset is compromised.
*   **Example:** "Loss of steering assistance while driving at high speed."
*   **Impact Rating:** Each scenario is rated across four categories (Safety, Financial, Operational, and Privacy) on a scale from **Negligible** to **Severe/Catastrophic**.

### 3. Threat Scenarios & Attack Path Analysis
This is where **STRIDE** fits in. You identify how an attacker could realize a damage scenario.
*   **Attack Path:** A step-by-step map of how an attacker gets from an entry point (e.g., the OBD-II port) to the target asset (e.g., the EPS motor controller).
*   **Attack Feasibility:** Instead of just "likelihood," automotive TARA uses "Feasibility" based on factors like:
    *   **Time spent** on the attack.
    *   **Specialized expertise** required.
    *   **Knowledge of the system** (Is it public or proprietary?).
    *   **Equipment** (Do they need a laptop or a million-dollar lab?).

### 4. Risk Determination
The TARA calculates a **Risk Value (1 to 5)** by combining the **Impact** of the damage and the **Feasibility** of the attack.
*   **Risk 1:** Negligible (may be accepted).
*   **Risk 5:** Critical (must be mitigated immediately).

---

## TARA Document Structure
A professional TARA report typically includes the following sections to satisfy auditors:

| Section | Content Description |
| :--- | :--- |
| **Item Definition** | System architecture, boundaries, and internal/external interfaces. |
| **Asset Inventory** | List of all hardware, software, and data assets with their security properties. |
| **Impact Assessment** | Detailed breakdown of S.F.O.P. (Safety, Financial, Operational, Privacy) ratings. |
| **Threat Catalog** | Every identified threat (S-T-R-I-D-E) mapped to specific assets. |
| **Attack Feasibility** | The "difficulty score" for each attack path. |
| **Risk Matrix** | The final risk scores (Impact × Feasibility). |
| **Cybersecurity Goals** | High-level requirements (e.g., "The EPS shall only execute signed code"). |

---

## TARA vs. STRIDE: The Key Difference


*   **STRIDE** is a **threat discovery tool**. It helps you think of "what could go wrong" (e.g., *Spoofing* the torque sensor).
*   **TARA** is a **risk management framework**. It takes that "spoofing" threat, calculates how hard it is to pull off (Feasibility), how much it hurts if it happens (Impact), and dictates whether you need to spend money to fix it (Risk Treatment).

> **Important:** In an audit, saying "We used STRIDE" is not enough. You must show the **Attack Path Analysis** and the **Impact Rating** in your TARA document to prove compliance with UN R155/R156 regulations.

Would you like to see a specific example of an **Attack Path** for the EPS system using the **Attack Potential** scoring method?