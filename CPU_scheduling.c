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
void FCFS() {
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
    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n\n", total_turnaround_time / n);
}

// Function for SJF Scheduling
void SJF() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].id);
        scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    int current_time = 0;
    int completed[n];
    for (int i = 0; i < n; i++) completed[i] = 0;

    for (int i = 0; i < n; i++) {
        int shortest = -1;
        int min_burst = 10000;

        for (int j = 0; j < n; j++) {
            if (!completed[j] && processes[j].arrival_time <= current_time && processes[j].burst_time < min_burst) {
                min_burst = processes[j].burst_time;
                shortest = j;
            }
        }

        if (shortest == -1) {
            current_time++;
            i--;
            continue;
        }

        processes[shortest].waiting_time = current_time - processes[shortest].arrival_time;
        current_time += processes[shortest].burst_time;
        processes[shortest].turnaround_time = processes[shortest].waiting_time + processes[shortest].burst_time;
        completed[shortest] = 1;
    }

    displayTable(processes, n);

    double total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n\n", total_turnaround_time / n);
}

// Function for Round Robin Scheduling
void RoundRobin() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].id);
        scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].waiting_time = processes[i].burst_time;
    }

    int time = 0, remain = n, flag = 0, i;
    float total_waiting_time = 0, total_turnaround_time = 0;

    for (i = 0; remain != 0;) {
        if (processes[i].waiting_time <= tq && processes[i].waiting_time > 0) {
            time += processes[i].waiting_time;
            processes[i].waiting_time = 0;
            flag = 1;
        } else if (processes[i].waiting_time > 0) {
            processes[i].waiting_time -= tq;
            time += tq;
        }

        if (processes[i].waiting_time == 0 && flag == 1) {
            remain--;
            processes[i].turnaround_time = time - processes[i].arrival_time;
            total_waiting_time += time - processes[i].arrival_time - processes[i].burst_time;
            total_turnaround_time += processes[i].turnaround_time;
            flag = 0;
        }

        if (i == n - 1)
            i = 0;
        else if (processes[i + 1].arrival_time <= time)
            i++;
        else
            i = 0;
    }

    printf("ID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].turnaround_time - processes[i].burst_time, processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    printf("Select Scheduling Algorithm:\n");
    printf("1. First Come First Serve (FCFS)\n");
    printf("2. Shortest Job First (SJF) Non-preemptive\n");
    printf("3. Round Robin\n");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            FCFS();
            break;
        case 2:
            SJF();
            break;
        case 3:
            RoundRobin();
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}
