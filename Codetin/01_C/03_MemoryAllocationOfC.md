# Memory allocation of C program

There are 4 areas of memory for a c program.
```c

+----------------------------------------------------------+
|                  Task Stack(s) (RAM)                     |  <-- Each RTOS task has its own stack
|     (Local vars, return addresses, CPU registers)        |
|                   [Grows downward]                       |
+----------------------------------------------------------+
|                     Heap (RAM)                           |  <-- Dynamic memory (malloc/free)
|                   [Grows upward]                         |
+----------------------------------------------------------+
|            Unnitializd .bss Segment (RAM)                |  <-- Zero-initialized/uninitialized globals/statics
+----------------------------------------------------------+
|           Initialized .data Segment (RAM)                |  <-- Globals/statics with explicit init values
+----------------------------------------------------------+
|           Code/Text Segment (Flash/ROM)                  |  <-- Program instructions, ISRs (read-only)
+----------------------------------------------------------+
|        Memory-Mapped I/O (Peripheral Registers)          |  <-- Special memory addresses mapped to hardware
+----------------------------------------------------------+
|              RTOS Kernel Memory (RAM)                    |  <-- Task control blocks, semaphores, queues
+----------------------------------------------------------+
|            Optional Interrupt Stack (RAM)                |  <-- Dedicated interrupt stack (if used)
+----------------------------------------------------------+

```
<hr>

## Code Example
```c
#include <stdio.h>
#include <stdlib.h>

// --- Initialized Data Segment ---
// Global variable with an explicit initializer
int global_initialized = 42;

// --- BSS Segment ---
// Global variable without explicit initialization (zero-initialized)
int global_uninitialized;

// Simulate Memory-Mapped I/O by defining a pointer to a special address
#define PERIPHERAL_REG (*(volatile unsigned int*)0x40000000)

// Function prototype
void task_function(int param);

int main(void) {
    // --- Code/Text Segment ---
    // All instructions including main and task_function reside here.

    // --- Stack ---
    // Local variables inside functions live on the stack.
    int local_variable = 10;

    // --- Heap ---
    // Dynamically allocate memory during runtime
    int *dynamic_array = (int *)malloc(5 * sizeof(int));
    if (!dynamic_array) {
        printf("Heap allocation failed!\n");
        return -1;
    }
    for (int i = 0; i < 5; i++) {
        dynamic_array[i] = i * 2;  // Store values on the heap
    }

    // Modify global variables
    global_initialized += 5;
    global_uninitialized = 100;

    // Simulate a write to Memory-Mapped I/O register
    PERIPHERAL_REG = 0xABCD1234;  // Write to peripheral register

    // Call a function (creates new stack frame)
    task_function(local_variable);

    // Print values to verify
    printf("Global Initialized: %d\n", global_initialized);
    printf("Global Uninitialized: %d\n", global_uninitialized);
    printf("Heap Data: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", dynamic_array[i]);
    }
    printf("\n");

    free(dynamic_array);  // Free heap memory

    return 0;
}

void task_function(int param) {
    // Local variable on the stack
    int stack_var = param * 3;

    printf("Inside task_function, stack_var = %d\n", stack_var);
}

```
<hr>

| Memory Area           | Example in Code                                   | Notes (RTOS perspective)                                                                                        |
| --------------------- | ------------------------------------------------- | --------------------------------------------------------------------------------------------------------------- |
| **Code/Text Segment** | `main()`, `task_function()` instructions          | Stored in Flash/ROM, shared by all tasks.                                                                       |
| **Initialized Data**  | `int global_initialized = 42;`                    | Stored in RAM, initialized by startup code. Shared by all tasks — use synchronization if modified concurrently. |
| **BSS Segment**       | `int global_uninitialized;`                       | Stored in RAM, zeroed at startup. Shared like initialized data.                                                 |
| **Heap**              | `malloc()` / `free()` dynamic allocation          | Managed by runtime/RTOS allocator. Use with care in real-time systems due to fragmentation and timing.          |
| **Stack**             | `local_variable`, `stack_var`                     | Each task/thread has its own stack for locals, parameters, return addresses.                                    |
| **Memory-Mapped I/O** | `PERIPHERAL_REG` macro simulating hardware access | Accesses special peripheral register; volatile prevents optimization. Requires careful handling in RTOS.        |
