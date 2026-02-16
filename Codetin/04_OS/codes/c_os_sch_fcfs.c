#include <stdio.h>

// Define a structure to represent a process
typedef struct {
    int process_id;        // Process ID (e.g., P1, P2, P3, etc.)
    int burst_time;        // Burst time (time needed for execution)
    int arrival_time;      // Arrival time (when the process arrives in the ready queue)
    int completion_time;   // Completion time (time when the process finishes execution)
    int waiting_time;      // Waiting time (time spent in the ready queue)
    int turnaround_time;   // Turnaround time (total time from arrival to completion)
} Process;

// Function to calculate and display FCFS scheduling details
void FCFS(Process processes[], int n) {
    // Variables to calculate the total waiting time and turnaround time
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Completion time for the first process is simply its arrival time + burst time
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;

    // Loop through all processes to calculate their completion time
    for (int i = 1; i < n; i++) {
        // If the next process arrives after the previous one has completed
        // then it will start executing at its arrival time + burst time
        // Otherwise, it will start after the previous process completes
        if (processes[i].arrival_time > processes[i-1].completion_time) {
            // If the process arrives after the previous process finishes, start at arrival time
            processes[i].completion_time = processes[i].arrival_time + processes[i].burst_time;
        } else {
            // If the process arrives before the previous one finishes, start after previous completion
            processes[i].completion_time = processes[i-1].completion_time + processes[i].burst_time;
        }
    }

    // Loop through all processes to calculate their waiting and turnaround times
    for (int i = 0; i < n; i++) {
        // Turnaround time = Completion time - Arrival time
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        
        // Waiting time = Turnaround time - Burst time
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        
        // Accumulate the total waiting time and total turnaround time
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    // Print the header for the output table
    printf("Process ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time\n");

    // Loop through all processes and display their information
    for (int i = 0; i < n; i++) {
        printf("%10d | %12d | %10d | %15d | %12d | %15d\n",
               processes[i].process_id,           // Process ID
               processes[i].arrival_time,         // Arrival time
               processes[i].burst_time,           // Burst time
               processes[i].completion_time,      // Completion time
               processes[i].waiting_time,         // Waiting time
               processes[i].turnaround_time);     // Turnaround time
    }

    // Calculate and display the average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;

    // Prompt the user to enter the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Declare an array of processes based on the user input
    Process processes[n];

    // Get the arrival time and burst time for each process from the user
    for (int i = 0; i < n; i++) {
        // Prompt the user to enter the arrival time and burst time for each process
        printf("\nEnter Arrival Time and Burst Time for Process %d: ", i + 1);
        processes[i].process_id = i + 1;  // Assign process ID as i + 1 (e.g., P1, P2, etc.)
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    // Call the FCFS function to calculate and display the scheduling details
    FCFS(processes, n);

    return 0;
}
