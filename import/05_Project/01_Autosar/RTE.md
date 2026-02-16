# RTE
> ⚠️This is not a formal text book definition, but something that you can read to understand, **Hows and Whys* of the RTE.  

The approach is write a pseudo code to understand the purpose of RTE.

But first, let us understand a few thins about RTE.

| Purpose of RTE                   | Role                                   |
| -------------------------------- | -------------------------------------- |
| Enforce clean communication      | Mediator between SWCs and BSW          |
| Decouple software components     | Allow independent development          |
| Encapsulate service access       | Route service calls (e.g., NVM, DCM)   |
| Enable automatic code generation | Generate glue code for ECU integration |

### 🔄 Without RTE:
- Components would be tightly coupled.
- You’d risk direct, unauthorized access between modules.
- Portability and reuse would be significantly harder.

### 🛠️ What RTE Actually Does (The "How")
RTE is code that AUTOSAR tools generate based on the system configuration. It’s generated glue that ensures:
- SWC-to-SWC communication works
- SWC-to-service communication (e.g., to NVRAM, CAN) is routed correctly
- The application layer does not talk to BSW directly

### 🔍 What RTE Is NOT
- ❗It's not a runtime OS scheduler or real-time framework.
- ❗It doesn’t “run” like an RTOS; it’s just generated glue code (functions, macros).
- ❗It doesn’t contain logic — it routes data and calls between components.

## Types of Communication Types in RTE

| **Comm. Type**         | **Description**                                            | **When to Use**                                             | **Braking ECU Example**                                                              |
| ---------------------- | ---------------------------------------------------------- | ----------------------------------------------------------- | ------------------------------------------------------------------------------------ |
| **Sender/Receiver**    | One-way data transfer from sender to one or more receivers | For broadcasting sensor data or system states               | Brake pedal sensor **sends position** to ABS, ESP, and Brake Light Controller        |
| **Client/Server**      | Synchronous or asynchronous request-response model         | When you need to request a service or computation           | ABS logic requests **wheel speed calculation** from a shared speed monitoring module |
| **Mode Communication** | Notify components of mode/state changes                    | For coordinating component behavior during mode transitions | Switch between **“Normal Braking”** and **“Emergency Braking”** mode across SWCs     |
| **Trigger Interface**  | Triggers an operation or action                            | Event-driven command patterns                               | Trigger **Brake Boost** when emergency detected, without returning data              |
| **Service Access**     | Standardized access to BSW services via the RTE            | When app SWCs need to access services like NVRAM, COM       | Store last brake fault status in **non-volatile memory** (NvM\_WriteBlock)           |


## <span style="color:blue;">1. Sender / Reciver</span>

**WAP** Implement your own RTE (demo psudo code based)
If you can implement a lightweight simulation of RTE behavior:
- Port-based communication
- Data exchange between SWCs
- Encapsulation and isolation

> Approch to attack this interview question, take below items to implement.
✅ What You Should Implement (In C)  

> Let’s implement a mini RTE supporting:
    - 2 software components (SWCs)  
    - 1 signal (e.g., RPM value)  
    - Sender/Receiver interface  
    - Functions like Rte_Write() and Rte_Read()

**Diagram**

```plaintext
+-------------------------+             +------------------------+
|  EngineControlComponent |             |   DashboardComponent   |
|     (Sender SWC)        |             |     (Receiver SWC)     |
|                         |             |                        |
|  +-------------------+  |             |  +------------------+  |
|  | Rte_Write_RPM( )  |  |             |  | Rte_Read_RPM( )  |  |
|  +-------------------+  |             |  +------------------+  |
|           |             |             |           ^            |
|           v             |             |           |            |
|  Sends RPM to RTE       |             |  Reads RPM from RTE    |
+-----------|-------------+             +-----------|------------+
            |                                       |
            v                                       ^
        +---------------------------- Shared ---------------------------+
        |                          RTE_RPM_Buffer                        |
        +----------------------------------------------------------------+
```

### Coding time, but the approch first!
1. Define a shared signal - 
2. Define RTE API
3. Define software components
4. Simulate RTE application.

<details>
<summary><strong>Code</strong></summary>

```c
// 1. RTE Buffer
static int rte_buffer = 0;

// 2. rpm singal is taken for demo - RTE wrtie API 
void Rte_Write_RPM(int rpm){
        rte_buffer = rpm;
}

void Rte_Read_RPM(int *rpm){
    if(rpm)
        *rpm = rte_buffer;
}

// 3. SWC (software compenent)
void EngineControlComponent_Run(){
    int currentRPM = 5000;
    Rte_Write_RPM(currentRPM);
}

void DashboadComponent_Run(int *rpm){
    int displayRPM;
    Rte_Read_RPM(&displayRPM);
    printf("The RPM is %d", displayRPM);
}

// 4. Main Function
int main(){
    EngineControlComponent_Run();
    DashboadComponent_Run();
    return 0;
}
```
**Output**
```
The RPM is 5000
```
</details>

## <span style="color:blue;">2. Client / Server</span>

Wdiscuss 3 examples in this:  
1. Synchronous - where the client is waiting for the server to respond  
2. Asynchronous - where the client does not wait, rather it goes to do its other jobs  
    2.a Without using thread - just demo  
    2.b Using threads (POSIX) to make it more real  

<hr>

**1. WAP**  
Can you implement a simple example of Client/Server communication in C, similar to how AUTOSAR RTE works?
1. Simulate a Client SWC calling a service provided by a Server SWC
2. Use function calls via RTE glue layer
3. Implement synchronous communication (the client waits for the result)


<details>
<summary><strong>Code</strong></summary>

| Concept       | Code Part             |
| ------------- | --------------------- |
| Server        | `getSlipRatio()`      |
| Client        | `runClient()`         |
| RTE glue code | `call_getSlipRatio()` |

```c
#include <stdio.h>
#include <stdint.h>

#define OK      0
#define NOT_OK  1

// ----------------------
// Server Function
// ----------------------
uint8_t getSlipRatio(float* value) {
    if (value == NULL) return NOT_OK;
    *value = 0.25f;  // Simulated slip ratio
    return OK;
}

// ----------------------
// RTE Layer (Glue)
// ----------------------
uint8_t call_getSlipRatio(float* value) {
    return getSlipRatio(value);
}

// ----------------------
// Client Function
// ----------------------
void runClient() {
    float slip = 0.0f;
    if (call_getSlipRatio(&slip) == OK) {
        printf("Client: Slip ratio = %.2f\n", slip);
    } else {
        printf("Client: Failed to get slip ratio\n");
    }
}

// ----------------------
// Main (ECU Simulation)
// ----------------------
int main() {
    runClient();
    return 0;
}

```
**Output**
```
Client: Slip ratio = 0.25

```
</details>

<hr>

### 2. Asynchronous
| Feature                   | Implementation                                          |
| ------------------------- | ------------------------------------------------------- |
| Client sends request      | Triggers the service but doesn't wait                   |
| Server runs in background | Simulated by a separate function (could be task/thread) |
| Response later            | Client checks if result is ready (via flag)             |


| Feature                   | Implementation                                          |
| ------------------------- | ------------------------------------------------------- |
| Client sends request      | Triggers the service but doesn't wait                   |
| Server runs in background | Simulated by a separate function (could be task/thread) |
| Response later            | Client checks if result is ready (via flag)             |

<hr>
<br>

**2.a WAP**

We'll simulate:
- A global flag (slipReady) set by the server
- A global variable to hold the slip ratio result
- The client sends request, then polls for the result later

<details>
<summary><strong>Code</strong></summary>

```c
#include <stdio.h>
#include <stdint.h>

// Status codes
#define OK      0
#define NOT_OK  1

// Shared "RTE-style" buffer
float slipResult = 0.0f;
uint8_t slipReady = 0;  // Flag to indicate response is ready

// ----------------------------
// Server Side (Async Service)
// ----------------------------
void processSlipRequest() {
    printf("Server: Calculating slip ratio...\n");

    // Simulate computation delay (in real life, time-based or interrupt-based)
    for (volatile int i = 0; i < 100000000; ++i);  // Dummy delay

    slipResult = 0.24f;  // Set result
    slipReady = 1;       // Notify client
    printf("Server: Done. Slip ratio ready.\n");
}

// ----------------------------
// RTE Layer
// ----------------------------
void requestSlipRatio() {
    // Just trigger the service
    processSlipRequest();  // Could be scheduled in real life
}

// ----------------------------
// Client Side
// ----------------------------
void runClient() {
    printf("Client: Sending request...\n");
    requestSlipRatio();  // Async: just sends the request

    // Do other work...
    printf("Client: Doing other work...\n");

    // Now poll for result
    if (slipReady) {
        printf("Client: Got slip ratio = %.2f\n", slipResult);
    } else {
        printf("Client: Slip ratio not ready yet.\n");
    }
}

// ----------------------------
// Main (Simulate ECU Run)
// ----------------------------
int main() {
    runClient();  // In real-time systems, this would loop or run as a task
    return 0;
}

```
```
Client: Sending request...
Server: Calculating slip ratio...
Server: Done. Slip ratio ready.
Client: Doing other work...
Client: Got slip ratio = 0.24

```
</details>

<hr>

**2.b WAP**
Goal: Make Async Truly Concurrent Using Threads  
We'll now simulate true asynchronous behavior by:  
1. Running the server logic in a separate thread
2. Having the client continue doing its own work without waiting
3. Using shared memory + synchronization (basic, not mutexed for simplicity)

This better simulates how an AUTOSAR runtime environment or RTOS would separate task contexts.

<details>
<summary><strong>Code</strong></summary>

```c
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

// Shared variables (simulate RTE buffers)
float slipResult = 0.0f;
volatile uint8_t slipReady = 0;  // Volatile to ensure visibility across threads

// --------------------------
// Server Thread Function
// --------------------------
void* serverThread(void* arg) {
    printf("Server: Started processing slip ratio...\n");

    // Simulate some computation delay
    sleep(2);  // 2 seconds

    slipResult = 0.26f;
    slipReady = 1;

    printf("Server: Slip ratio calculated.\n");
    return NULL;
}

// --------------------------
// Client Logic
// --------------------------
void runClient() {
    pthread_t server_tid;

    printf("Client: Requesting slip ratio from server...\n");
    pthread_create(&server_tid, NULL, serverThread, NULL);

    printf("Client: Doing other work while waiting...\n");

    // Simulate doing other tasks
    for (int i = 0; i < 5; ++i) {
        printf("Client: Working... (%d)\n", i + 1);
        sleep(1);

        if (slipReady) {
            printf("Client: Received slip ratio = %.2f\n", slipResult);
            break;
        }
    }

    // Wait for server thread to finish
    pthread_join(server_tid, NULL);
}

// --------------------------
// Main Function
// --------------------------
int main() {
    runClient();
    return 0;
}

```
```
Client: Requesting slip ratio from server...
Client: Doing other work while waiting...
Server: Started processing slip ratio...
Client: Working... (1)
Client: Working... (2)
Server: Slip ratio calculated.
Client: Received slip ratio = 0.26

```
</details>

| Feature                      | Implemented                |
| ---------------------------- | -------------------------- |
| Client/server separated      | ✅ via threads              |
| True async behavior          | ✅ yes (parallel execution) |
| Shared data + sync (basic)   | ✅ slipReady + slipResult   |
| Simulated real-time response | ✅ with sleep and polling   |


