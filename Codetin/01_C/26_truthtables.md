# Truth Tables Cheat Sheet

## 1. The Core Operators
In interviews, inputs are usually represented as A and B.
* **1 / T** = True
* **0 / F** = False

| Operator | Notation / Code | Definition |
| :--- | :--- | :--- |
| **NOT** (Inverter) | ¬A, !A | Flips the input. |
| **AND** (Conjunction) | A && B | **Only 1** if *both* inputs are 1. |
| **OR** (Disjunction) | A || B | **1** if *at least one* input is 1. |
| **XOR** (Exclusive OR) | A ^ B | **1** if inputs are *different*. |

> | **XOR** (Exclusive OR) | A ^ B | **1** if inputs are *different*. |

### The Master Table

| A | B | NOT A (!A) | A AND B | A OR B | A XOR B |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **0** | **0** | 1 | 0 | 0 | **0** |
| **0** | **1** | 1 | 0 | 1 | **1** |
| **1** | **0** | 0 | 0 | 1 | **1** |
| **1** | **1** | 0 | 1 | 1 | **0** |

---

## 2. Advanced / Conditional Operators

| Operator | Notation | Quick Rule |
| :--- | :--- | :--- |
| **NAND** | !(A && B) | 0 only if both are 1 (Inverse of AND). |
| **NOR** | !(A || B) | 1 only if both are 0 (Inverse of OR). |
| **XNOR** | !(A ^ B) | 1 if inputs are the *same* (Equality check). |
| **Implication** | A -> B | Only 0 if A is true and B is false ("If A, then B"). |

### The Advanced Master Table

| A | B | A NAND B | A NOR B | A XNOR B | A -> B |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **0** | **0** | 1 | 1 | **1** | 1 |
| **0** | **1** | 1 | 0 | **0** | 1 |
| **1** | **0** | 1 | 0 | **0** | **0** |
| **1** | **1** | 0 | 0 | **1** | 1 |

> 💡 **Interview Tip on Implication (A -> B):** A false premise (A = 0) always logically results in a true implication, regardless of B. It’s only busted if the premise is true but the conclusion is false.

---

## 3. High-Yield Laws for Code Optimization

Interviewers love to ask you to "simplify this `if` statement." Use these laws to crush those questions.

* **De Morgan's Laws** (Crucial for refactoring messy conditionals):
  * `!(A && B)` is equivalent to `!A || !B`
  * `!(A || B)` is equivalent to `!A && !B`
* **Idempotence:** 
  * `A && A` simplifies to `A`
  * `A || A` simplifies to `A`
* **Identity & Annihilation:**
  * `A && 1` simplifies to `A` | `A || 0` simplifies to `A` (Identity)
  * `A && 0` simplifies to `0` | `A || 1` simplifies to `1` (Annihilation)
* **Absorption:**
  * `A || (A && B)` simplifies to `A`
  * `A && (A || B)` simplifies to `A`

---

## 4. Quick Interview Checklist

* **How many rows?** If a problem has $n$ variables, your truth table will have 2^n rows. (e.g., 3 variables = 8 rows).
* **Short-Circuit Evaluation:** Remember that in languages like Python, JS, C++, and Java, `A && B` won't even look at `B` if `A` is false. `A || B` won't look at `B` if `A` is true. 
* **XOR Bit Trick:** `A ^ A = 0` and `A ^ 0 = A`. This is the secret sauce for finding the single non-duplicate element in an array in O(N) time and O(1) space!