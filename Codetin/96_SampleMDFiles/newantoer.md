# Topic 1: C Programming

Explanation of the code:

## Code Snippet from `demo1.c`

### this is something i have been trying to do 
but lets make sure htat you are getting it
'writting first article is usally though `src` folders are grea _if you are doing all good_ make sure to *highlisht the new text* ~letss see if t works~ 

# Comparison of Multiprogramming, Multiprocessing, and Multithreading

## Table of Differences

| **Feature**               | **Multiprogramming**                                    | **Multiprocessing**                                      | **Multithreading**                                      |
|---------------------------|---------------------------------------------------------|---------------------------------------------------------|--------------------------------------------------------|
| **Defination**             | Multiple programs are loaded into memory and executed sequentially by switching the CPU between them. | Multiple processors work on multiple processes at the same time. | Multiple threads run within a single process, sharing the same memory. |
| **Execution**              | One process runs at a time but the CPU switches between processes to simulate simultaneous execution. | Multiple processes run at the same time on different CPUs. | Multiple threads of the same process run concurrently. |
| **CPU Usage**              | CPU is kept busy by switching between processes. | CPU power is used by multiple processors working simultaneously. | CPU power is shared between threads, usually within a single core or multiple cores. |
| **Goal**                   | Maximize CPU utilization by switching between processes. | Improve performance by using multiple processors. | Improve efficiency within a single process, managing concurrent tasks. |
| **Memory**                 | Each process runs independently with its own memory. | Each process has its own memory space. | Threads share the same memory space within a process. |
| **Resource Sharing**       | No resource sharing between processes. | Processes may communicate using inter-process communication (IPC). | Threads share resources such as memory and file handles. |
| **Overhead**               | Less overhead than multiprocessing but higher than multithreading. | High overhead due to multiple processes running on separate CPUs. | Lower overhead, as threads share memory space and resources. |
| **Example**                | Running a word processor and a browser at the same time. | A multi-core server processing multiple requests simultaneously. | A web browser handling user input, rendering a page, and downloading images in parallel. |
| **Scheduling**             | Managed by the OS; the CPU alternates between processes. | Managed by the OS across multiple processors. | Managed by the OS within a single process, scheduling threads. |
| **Resource Sharing**       | No resource sharing between processes. | Processes may communicate using inter-process communication (IPC). | Threads share resources such as memory and file handles. |
| **Overhead**               | Less overhead than multiprocessing but higher than multithreading. | High overhead due to multiple processes running on separate CPUs. | Lower overhead, as threads share memory space and resources. |
| **Example**                | Running a word processor and a browser at the same time. | A multi-core server processing multiple requests simultaneously. | A web browser handling user input, rendering a page, and downloading images in parallel. |
| **Scheduling**             | Managed by the OS; the CPU alternates between processes. | Managed by the OS across multiple processors. | Managed by the OS within a single process, scheduling threads. |



## Explanation of Demo Code:

# Colored Text Example

<span style="color: blue;">
<strong>Multiprogramming</strong>: The demo simply prints two messages, simulating two programs being "run" one after the other.
</span>

<span style="color: green;">
**Multiprocessing**: The code demonstrates how to use `fork()` to create a child process. Both the parent and child processes print a message, simulating how they can run independently.
</span>

<span style="color: red;">
**Multithreading**: This example uses the `pthread` library to create two threads. Each thread prints a message, and they run concurrently within the same process.
</span>

<span style="color:rgb(44, 131, 230) ;">
<strong>Multiprogramming</strong>: The demo simply prints two messages, simulating two programs being "run" one after the other.
</span>

<span style="color:rgb(74, 233, 140) ;">
**Multiprocessing**: The code demonstrates how to use `fork()` to create a child process. Both the parent and child processes print a message, simulating how they can run independently.
</span>

<span style="color:rgb(255, 45, 42) ;">
**Multithreading**: This example uses the `pthread` library to create two threads. Each thread prints a message, and they run concurrently within the same process.
</span>

---

Feel free to copy the above content into a `.md` file for use.


<details>
  <summary><strong><span style="color:rgb(236, 151, 15);">simple joma codes</span></strong></summary>

  ```c
  #include <stdio.h>

  int main() {
      printf("Hello from demo1.c\n");
      return 0;
  }
```
</details>

</p>

![Space Logo](https://github.com/vaaski/vaaski/blob/main/space-logo.svg)