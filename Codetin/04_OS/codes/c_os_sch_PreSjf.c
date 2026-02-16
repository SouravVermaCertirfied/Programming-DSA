#include <stdio.h>

#define MAX_PROCESSES 100

// Structure to store process details
typedef struct {
    int pid;           // Process ID
    int arrival_time;  // Arrival time
    int burst_time;    // Burst time
    int remaining_time;// Remaining time
    int completion_time;
    int turn_around_time;
    int waiting_time;
} Process;

// Function to find the process with the minimum remaining time at the current time
int findShortestRemainingTime(Process processes[], int n, int current_time) {
    int min_time = 9999;  // A large value
    int min_index = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
            if (processes[i].remaining_time < min_time) {
                min_time = processes[i].remaining_time;
                min_index = i;
            }
        }
    }
    return min_index;
}

// Function to calculate the turnaround time and waiting time
void calculateTimes(Process processes[], int n) {
    int total_turnaround_time = 0, total_waiting_time = 0;

    for (int i = 0; i < n; i++) {
        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;

        total_turnaround_time += processes[i].turn_around_time;
        total_waiting_time += processes[i].waiting_time;
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

// Function to implement Shortest Remaining Time First (SRTF)
void SRTF(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int prev = -1;

    // Run until all processes are completed
    while (completed < n) {
        // Find the process with the minimum remaining time
        int index = findShortestRemainingTime(processes, n, current_time);

        if (index != -1) {
            // If a process is found, reduce its remaining time
            if (prev != index) {
                printf("\nAt time %d, Process %d is executing\n", current_time, processes[index].pid);
                prev = index;
            }
            processes[index].remaining_time--;
            current_time++;

            // If the process has completed
            if (processes[index].remaining_time == 0) {
                processes[index].completion_time = current_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }

    // Calculate and print turnaround and waiting times
    calculateTimes(processes, n);
}

int main() {
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[MAX_PROCESSES];

    // Input the process details (PID, Arrival Time, Burst Time)
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Run the Shortest Remaining Time First (SRTF) scheduling
    SRTF(processes, n);

    // Output the completion time, turnaround time, and waiting time for each process
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turn_around_time, processes[i].waiting_time);
    }

    return 0;
}
