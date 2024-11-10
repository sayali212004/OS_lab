
#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

// Function to calculate Waiting and Turnaround times for FCFS
void calculateTimesFCFS(struct Process processes[], int n) {
    processes[0].waiting_time = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

// Display Process Table
void displayTable(struct Process processes[], int n) {
    printf("ID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

// Function for FCFS Scheduling
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].id);
        scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    calculateTimesFCFS(processes, n);
    displayTable(processes, n);

    double total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    printf("First Come First Serve (FCFS)\n");
    printf("\nAverage Waiting Time of FCFS: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time of FCFS: %.2f\n\n", total_turnaround_time / n);
    

    return 0;
}



