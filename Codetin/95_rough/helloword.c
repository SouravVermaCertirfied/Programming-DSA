// =============================================================================
// ELEVATOR CONTROLLER SYSTEM (Staff Level Implementation Skeleton)
// Goal: Multi-threaded, SCAN-based, VIP-aware, Livelock-free elevator system.
// =============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For sleep/usleep
#include <stdbool.h>
#include <time.h>

// --- Constants & Assumptions ---
#define BUILDING_STORY_COUNT 100
#define NUM_ELEVATORS 4
#define VIP_LATENCY_SECONDS 30

// --- Global State Management ---

// 1. Request Structures
typedef struct {
    int origin;
    int destination;
    bool is_vip;
    // Unique request ID for tracking/debugging
    int request_id;
} ElevatorRequest;

// 2. Elevator State
typedef enum {
    IDLE,
    MOVING,
    SERVING,
    OUT_OF_SERVICE
} ElevatorState;

typedef struct {
    int id;
    int current_floor;
    ElevatorState state;
    pthread_mutex_t lock;     // Granular lock for THIS elevator's state
    
    // Synchronization for movement/requests
    pthread_cond_t available_cv; // Signal when elevator is free/ready to accept work
    
    // Queue of pending stops assigned to this elevator by the scheduler
    ElevatorRequest* assigned_stops[20]; // Simple array for scheduled stops
    int stop_count;
    int next_stop_index;

} Elevator;

// --- Global System Resources ---
Elevator elevators[NUM_ELEVATORS];

// Central scheduler control
pthread_mutex_t global_request_mutex;
pthread_cond_t scheduler_cv; // Signal when a new request arrives
ElevatorRequest global_requests[500]; // Array to hold pending requests (simple fixed size pool)
int global_request_count = 0;

// VIP Queue Management
pthread_mutex_t vip_queue_mutex;
pthread_cond_t vip_cv; 
ElevatorRequest vip_requests[500];
int vip_request_count = 0;

// --- Helper Functions (Placeholders for complexity) ---

// @brief Finds the best elevator using SCAN logic among available ones.
// Must respect current location, direction, and pending VIP needs.
// This is the core, complex scheduling function.
int scan_algorithm_select_elevator(int origin, int destination, bool is_vip) {
    // !!! STAFF LEVEL IMPLEMENTATION REQUIRED HERE !!!
    // This function must iterate over all 4 elevators, check their current state,
    // and calculate the lowest-cost path based on SCAN principles, 
    // while giving high priority/weighting to VIP needs to meet the 30s bound.
    printf("[Scheduler]: Applying advanced SCAN logic...\n");
    
    // For this skeleton, we return the first available elevator ID as a placeholder.
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        if (elevators[i].state == IDLE) {
            return i;
        }
    }
    return -1; // No elevator available
}

// @brief Attempts to assign a request to a specific elevator, checking for conflicts.
bool assign_request_to_elevator(int elevator_id, const ElevatorRequest* req) {
    // !!! STAFF LEVEL IMPLEMENTATION REQUIRED HERE !!!
    // Logic to append request to the elevator's assigned_stops queue without race conditions.
    return true; 
}

// --- Public API: Request Elevator ---

/**
 * @brief Handles passenger requests, managing queues and signaling the scheduler.
 * @param origin The starting floor.
 * @param dest The destination floor.
 * @param is_vip Whether the request is VIP.
 */
void request_elevator(int origin, int dest, bool is_vip) {
    if (origin == dest) return;
    
    ElevatorRequest new_req = {origin, dest, is_vip, global_request_count + 1};
    
    // 1. Critical Section: Global Queue Update
    pthread_mutex_lock(&global_request_mutex);
    
    int best_elev_id = -1;

    if (is_vip) {
        // 2. VIP Handling: Attempt immediate service check (High Priority)
        // Check if any elevator is close enough to service VIP within 30s.
        best_elev_id = scan_algorithm_select_elevator(origin, dest, true);
        if (best_elev_id != -1) {
            // If we found one, we assign it immediately (Simplified)
            // In reality, this would involve updating the elevator's direct queue.
            printf("[VIP ALERT] Attempting immediate service for VIP request %d -> %d.\n", origin, dest);
            // Assuming success for skeleton purposes
        } else {
            // If no elevator can handle it immediately, place it in the dedicated VIP queue.
            printf("[VIP QUEUE] No immediate service available. Adding to VIP Queue.\n");
            // Logic to add to vip_requests[vip_request_count++]
        }
    } else {
        // 3. Standard Request Queue
        // Check the pool for a general assignment.
        printf("[Standard Request] Queuing request %d -> %d.\n", origin, dest);
        // Logic to add to global_requests[global_request_count++]
    }
    
    // 4. Signal Scheduler (Wakes up waiting elevator controllers)
    pthread_cond_signal(&scheduler_cv);
    pthread_mutex_unlock(&global_request_mutex);
}

// --- Elevator Thread Loop ---

void* elevator_controller(void* arg) {
    int id = *(int*)arg;
    Elevator* self = &elevators[id];

    printf("Elevator %d Initialized. State: IDLE at Floor %d.\n", id, self->current_floor);

    while (1) {
        // This is the main execution loop for the elevator thread.
        
        // Wait for a signal that work is available (from scheduler_cv or vip_cv)
        pthread_mutex_lock(&self->lock);
        
        // Wait until the scheduler signals OR a work item is explicitly assigned.
        // This replaces busy-waiting.
        pthread_cond_wait(self->available_cv, &self->lock);
        
        // --- Execution after being signaled ---
        
        // 1. Process Assigned Stops (The Core SCAN Execution)
        if (self->stop_count > 0) {
            // Simplified movement logic: just go to the first scheduled stop.
            int next_stop = self->assigned_stops[self->next_stop_index]->destination;
            
            printf("E%d: Moving from %d to %d...\n", id, self->current_floor, next_stop);
            // Simulate movement time
            usleep(500000); // 0.5 seconds wait
            self->current_floor = next_stop;
            
            // 2. Service Stop (Check for VIP pickup/dropoff logic here)
            // If this stop fulfills a VIP requirement, the hard latency timer starts here.
            
            // 3. Advance internal pointers and update state
            self->next_stop_index++;
            // ... (Rest of the complex logic for dequeuing stops)
        }

        // 4. Cycle End
        printf("Elevator %d arrived at Floor %d. State: IDLE.\n", id, self->current_floor);
        
        // Wait a moment before idling again to prevent thrashing
        pthread_mutex_unlock(&self->lock);
        usleep(100000); 
    }
    return NULL;
}

// --- Initialization & Main ---

void initialize_system() {
    // 1. Initialize Global Locks/CVs
    pthread_mutex_init(&global_request_mutex, NULL);
    pthread_cond_init(&scheduler_cv, NULL);
    pthread_mutex_init(&vip_queue_mutex, NULL);
    pthread_cond_init(&vip_cv, NULL);

    // 2. Initialize Elevator States and Locks
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        elevators[i].id = i;
        elevators[i].current_floor = 1; // Start at lobby
        elevators[i].state = IDLE;
        pthread_mutex_init(&elevators[i].lock, NULL);
        pthread_cond_init(&elevators[i].available_cv, NULL);
    }
}

void cleanup_system() {
    // Destroy all synchronization primitives to prevent resource leaks
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        pthread_mutex_destroy(&elevators[i].lock);
        pthread_cond_destroy(&elevators[i].available_cv);
    }
    pthread_mutex_destroy(&global_request_mutex);
    pthread_cond_destroy(&scheduler_cv);
    pthread_mutex_destroy(&vip_queue_mutex);
    pthread_cond_destroy(&vip_cv);
}

int main() {
    printf("--- Elevator Controller System Starting ---\n");

    // 1. Initialize all locks and CVs
    initialize_system();

    // 2. Create and start the 4 elevator threads
    pthread_t threads[NUM_ELEVATORS];
    int ids[NUM_ELEVATORS];
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, elevator_controller, &ids[i]);
    }

    // --- Simulation Loop ---
    printf("\n--- Simulation Start (Running 10 concurrent requests) ---\n");

    // Simulate a "thundering herd" of requests over a short period
    request_elevator(1, 50, false);
    request_elevator(90, 5, true); // VIP Request
    request_elevator(2, 10, false);
    request_elevator(70, 30, false);
    
    // Simulate a second wave shortly after
    sleep(2); 
    request_elevator(1, 75, false);
    request_elevator(5, 1, true); // Another VIP
    request_elevator(10, 20, false);

    // Wait long enough for the simulation to process (In a real system, this runs forever)
    printf("\n--- Simulation running for 10 seconds to demonstrate functionality. Press Ctrl+C to exit. ---\n");
    sleep(10);

    // --- Cleanup ---
    printf("\n--- Simulation End. Cleaning up resources. ---\n");
    // In a real system, we would signal all threads to exit gracefully before joining.
    // For this skeleton, we just clean up synchronization primitives.
    cleanup_system();
    
    return 0;
}
// =============================================================================
// END OF FILE
// =============================================================================
