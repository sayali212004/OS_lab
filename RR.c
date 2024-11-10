
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


// Function for Round Robin Scheduling
int main() {
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
    
    return 0;
}


