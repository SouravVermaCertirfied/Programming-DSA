# 1. Mutex
- Used to protect shared data.
- Mutex are very simple.
- they are locks used for mutual inclusion.
- They enforce strict ownership, only the thread/process that locks can unlock.
- Due to this their main use if mutual exclusion, and not used for signalling.

### Pros of Mutex:
- very simple, lock before using critical section and release after critical section.

### Cons of Mutex:
- Since only the thread that locks can unlock, if the thread that locked goes to sleep no thread can unlock it, this will cause **starvation**.
- Mutex can lead to busy-wait, which burn CPU cycles.

# 2. Semaphores
- There are two types  Binary Semaphores AND Counting Semaphores.
- They are non-negative numbers that are shared between many threads.
- **They work in singalling mechanism**.
- Lesser restrictive control mechanism, any thread can invoke `signal()` and any can singal `wait()`.


### Pros of Semaphores
- Only one thread can access the critical section but, many threads are allowed.
- Flexible resounce management.

### Cons of Semaphores
- It can lead to **priority inversion**.
- 

# 3. Condition Variables
### Mutex with Conditional Variables
- Using mutex alone causes following problems:
    - Wastes CPU
    - Not scalable
- Mutex alone cannot solve the proble - **"Thread should sleep until some condition becomes true"**.
> A condition variable allows a thread to atomically release a mutex and sleep until another thread signals that a condition may be true.

| Feature              | Condition Variable | Semaphore |
| -------------------- | ------------------ | --------- |
| Needs mutex          | Yes                | No        |
| Spurious wakeups     | Yes                | No        |
| Expressiveness       | Higher             | Lower     |

---
<p align="left"><a href="22_Semaphores.md">← 22_Semaphores.md</a></p>
<p align="right" style="margin-top:-2.4em;"><a href="25_SpuriousAwake.md">25_SpuriousAwake.md →</a></p>