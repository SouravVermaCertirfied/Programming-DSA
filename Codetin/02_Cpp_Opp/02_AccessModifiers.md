# Access modifiers

Access modifiers are keywords used to set the **visibility** and **accessibility** of classes, methods, and variables. They are the primary tool for implementing **Encapsulation**.

## Common Access Modifiers
In most object-oriented languages (like Java, C#, or C++), there are four main levels:

*   **Public:** The member is accessible from **anywhere** in the program.
*   **Private:** The member is accessible **only within the class** where it is defined. It is hidden from all other classes.
*   **Protected:** The member is accessible within its own class and by **subclasses** (inheritance), but not by unrelated classes.



## Inheritance Access Matrix

This table shows how the access level of a member in the **Parent Class** is transformed when it reaches the **Child Class**, based on the type of inheritance:

| Parent Member | **Public Inheritance** | **Protected Inheritance** | **Private Inheritance** |
| :--- | :--- | :--- | :--- |
| **Public** | Stays **Public** | Becomes **Protected** | Becomes **Private** |
| **Protected** | Stays **Protected** | Stays **Protected** | Becomes **Private** |
| **Private** | **Inaccessible** | **Inaccessible** | **Inaccessible** |

---

### Key Takeaways

*   **Public Inheritance (`is-a`):** The most common form. It preserves the original access levels. If it was public in the parent, the rest of the world can see it in the child.
*   **Protected Inheritance:** Rarely used. It "hides" the parent's public interface from the outside world but keeps it available for future generations (grandchild classes).
*   **Private Inheritance (`implemented-in-terms-of`):** The most restrictive. It turns all inherited public/protected members into private members of the child. This effectively "stops" the inheritance chain; the grandchild class will have no access to the original parent's members.
*   **The "Private" Rule:** Regardless of the inheritance type, **Private** members of a parent are **never** directly accessible to a child class. They are inherited (they exist in memory), but the child cannot "see" them.

---
<div style="display: flex; justify-content: space-between;">
    <a href="01_Pillars.md">← 01_Pillars.md</a>
    <a href="03_ScopeResolutionOperator.md">03_ScopeResolutionOperator.md →</a>
</div>