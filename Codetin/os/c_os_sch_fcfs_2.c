#include <stdio.h>

#define MAX 10

// Define a structure to represent a process
struct Process {
    int pid;         // Process ID
    int bt;          // Burst Time
    int wt;          // Waiting Time
    int tat;         // Turnaround Time
};

// Function to calculate the waiting time for each process
void calculateWaitingTime(struct Process processes[], int n) {
    processes[0].wt = 0; // First process has zero waiting time
    
    for (int i = 1; i < n; i++) {
        processes[i].wt = processes[i - 1].bt + processes[i - 1].wt;
    }
}

// Function to calculate the turnaround time for each process
void calculateTurnaroundTime(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].tat = processes[i].bt + processes[i].wt;
    }
}

// Function to calculate average waiting time and turnaround time
void calculateAverageTimes(struct Process processes[], int n) {
    int total_wt = 0, total_tat = 0;
    
    for (int i = 0; i < n; i++) {
        total_wt += processes[i].wt;
        total_tat += processes[i].tat;
    }

    printf("\nAverage waiting time: %.2f\n", (float)total_wt / n);
    printf("Average turnaround time: %.2f\n", (float)total_tat / n);
}

// Function to display the results of FCFS scheduling
void displayResults(struct Process processes[], int n) {
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].bt, processes[i].wt, processes[i].tat);
    }
}

int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Array of processes
    struct Process processes[MAX];

    // Input burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;  // Assign process ID (1, 2, 3, ...)
        printf("Enter burst time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].bt);
    }

    // Calculate waiting time and turnaround time
    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);

    // Display the results and calculate average times
    displayResults(processes, n);
    calculateAverageTimes(processes, n);

    return 0;
}
