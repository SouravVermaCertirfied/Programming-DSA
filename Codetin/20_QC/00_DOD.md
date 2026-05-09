To truly test your **Definition of Done**, you need to move past definitions and into application. These questions are designed to mimic the Qualcomm interview style, which often bridges the gap between high-level software and low-level hardware.

---

## 1. Coding & Bit Manipulation (The C Core)

* **The Bit Flip:** Write a function to count the number of bits set to 1 in a 32-bit integer. Now, optimize it (search for "Brian Kernighan’s Algorithm").
* **Endianness:** Write a C program to determine if a machine is Little Endian or Big Endian.
* **Memory Alignment:** Given a struct with a `char`, an `int`, and a `double`, what is the `sizeof()` that struct on a 32-bit system? How would you use `#pragma pack`?
* **Reverse a Linked List:** Do it iteratively and explain the time/space complexity.
* **The `volatile` Keyword:** Why is `volatile` necessary when writing code that interacts with hardware registers or shared memory in a multi-threaded environment?

---

## 2. Operating Systems & Multithreading

* **The Deadlock:** What are the four necessary conditions for a deadlock to occur? How would you debug one in a real-time system?
* **Priority Inversion:** Explain what happens when a low-priority task holds a mutex needed by a high-priority task while a medium-priority task is running. How does **Priority Inheritance** fix this?
* **Stack vs. Heap:** If a function has a large local array, where is it stored? What happens if that array exceeds the allocated space?
* **Context Switching:** Walk me through exactly what the CPU saves and restores when switching from Process A to Process B.
* **Semaphores vs. Mutexes:** Can a semaphore be released by a different thread than the one that acquired it? Why or why not?

---

## 3. Computer Architecture

* **Cache Locality:** Why is traversing a 2D array row-by-row faster than column-by-column? Explain in terms of cache lines.
* **The Pipeline:** What is a "branch misprediction," and how does it affect the performance of a deep pipeline?
* **Virtual Memory:** How does a **TLB (Translation Lookaside Buffer)** speed up the translation from virtual addresses to physical addresses?
* **DMA (Direct Memory Access):** Why would a system use DMA instead of having the CPU move data from a peripheral (like a modem) to RAM?
* **Interrupt Latency:** What factors contribute to the time it takes for a system to respond to a hardware interrupt?

---

## 4. Qualcomm Specific / System Scenarios

* **The Boot Process:** Generally, what happens from the moment power is applied to a mobile SoC until the Kernel starts?
* **Power Management:** In a battery-constrained device, how do "Sleep States" or "Clock Gating" work to save power?
* **Shared Memory:** If two DSP cores need to communicate with the main Application Processor, how would you design a circular buffer in shared memory to ensure data integrity?
* **Watchdog Timers:** How does a Watchdog Timer prevent a smartphone from staying "frozen" forever?
* **Race Conditions:** You have two threads incrementing a global variable `counter++`. Show how this fails at the assembly level (Load-Modify-Store).

---

### How to Score Yourself

* **If you can answer 15/20 comfortably:** You are over-prepared. **Apply today.**
* **If you struggle with the "Why":** Focus your review on the *reasons* behind the concepts (e.g., why we use DMA, not just what DMA is).
* **If you get stuck on the C/Pointer questions:** Spend 48 hours refreshing your C fundamentals, then **apply.**

**Which of these four sections felt the most difficult for you just now?**