/*
Priority Scheduling (Non-Preemptive), which schedules processes based on their priority values. 
In this version, the process with the highest priority (numerically lower value) is executed first. 
Once a process starts execution, it runs to completion (non-preemptive).
*/

#include <stdio.h>

struct Process {
    int pid;         // Process ID
    int burst_time;  // Burst time
    int priority;    // Priority
    int waiting_time;
    int turnaround_time;
};

void findWaitingTime(struct Process processes[], int n) {
    // Waiting time for the first process is always 0
    processes[0].waiting_time = 0;

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
}

void findTurnaroundTime(struct Process processes[], int n) {
    // Turnaround time is the sum of burst time and waiting time
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

void findAverageTime(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage waiting time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage turnaround time: %.2f\n", (float)total_turnaround_time / n);
}

void sortProcessesByPriority(struct Process processes[], int n) {
    // Sort processes by priority using bubble sort (higher priority first, i.e., lower priority value)
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void priorityScheduling(struct Process processes[], int n) {
    // Sort the processes based on priority
    sortProcessesByPriority(processes, n);

    // Calculate waiting time for each process
    findWaitingTime(processes, n);

    // Calculate turnaround time for each process
    findTurnaroundTime(processes, n);

    // Calculate and print average waiting and turnaround times
    findAverageTime(processes, n);

    // Print the process information
    printf("\nProcess\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].priority, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process information
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    priorityScheduling(processes, n);

    return 0;
}
