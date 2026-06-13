Design patterns are essentially "proven recipes" for solving common software design problems. In Object-Oriented Programming (OOP), these are usually categorized into three main buckets: **Creational**, **Structural**, and **Behavioral**.

Here are the heavy hitters that every developer should have in their toolkit:

---

## 1. Creational Patterns (How objects are born)
These patterns deal with object creation mechanisms, trying to create objects in a manner suitable to the situation.

*   **Singleton:** Ensures a class has only one instance and provides a global point of access to it. Think of a single database connection pool or a logging service.
*   **Factory Method:** Defines an interface for creating an object but lets subclasses decide which class to instantiate. It keeps your code decoupled from the specific classes it needs to create.
    
*   **Builder:** Separates the construction of a complex object from its representation. It’s perfect when an object needs many optional parameters (the "anti-telescoping constructor" solution).

---

## 2. Structural Patterns (How objects fit together)
These patterns explain how to assemble objects and classes into larger structures while keeping these structures flexible and efficient.

*   **Adapter:** Acts as a bridge between two incompatible interfaces. It’s like a power plug adapter for your laptop when traveling abroad.
    
*   **Decorator:** Allows behavior to be added to an individual object, dynamically, without affecting the behavior of other objects from the same class. It's a flexible alternative to subclassing.
*   **Facade:** Provides a simplified interface to a complex library, framework, or any other complex set of classes. It’s the "easy button" for a messy subsystem.

---

## 3. Behavioral Patterns (How objects talk)
These patterns are specifically concerned with communication between objects.

*   **Observer:** A subscription mechanism to notify multiple objects about any events that happen to the object they’re observing. This is the backbone of "event-driven" programming.
    
*   **Strategy:** Defines a family of algorithms, encapsulates each one, and makes them interchangeable. It lets the algorithm vary independently from the clients that use it (e.g., choosing between different payment methods like PayPal vs. Credit Card at checkout).
*   **State:** Allows an object to alter its behavior when its internal state changes. The object will appear to change its class.

---


Mastering the **Singleton**, **Factory**, and **Observer** patterns first.  
They appear in almost every modern framework (like React, Spring, or .NET) and provide the quickest "aha!" moments for understanding why patterns matter.

---
<div style="display: flex; justify-content: space-between;">
    <span></span>
    <a href="02_Singleton.md">02_Singleton.md →</a>
</div>