
#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};


// Display Process Table
void displayTable(struct Process processes[], int n) {
    printf("ID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}


// Function for SJF Scheduling
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
    
    return 0;
}


