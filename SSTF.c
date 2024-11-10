
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CYLINDERS 200

// SSTF Disk Scheduling
void sstf(int requests[], int n, int head) {
    int completed[MAX_CYLINDERS] = {0};
    int seek_count = 0;
    int current_position = head;
    printf("SSTF Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        int min_distance = 9999;
        int index = -1;
        for (int j = 0; j < n; j++) {
            if (!completed[j]) {
                int distance = abs(requests[j] - current_position);
                if (distance < min_distance) {
                    min_distance = distance;
                    index = j;
                }
            }
        }
        completed[index] = 1;
        seek_count += min_distance;
        current_position = requests[index];
        printf("Head moved to: %d\n", current_position);
    }
    printf("Total seek time (SSTF): %d\n\n", seek_count);
}


// FCFS Page Replacement
int FIFO(int n, int p, int input[]) {
    int frame[n];
    int fault = 0;
    int index = 0;

    printf("\nPage Replacement Process (FCFS):\n");
    for (int i = 0; i < p; i++) {
        int found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < n; j++) {
            if (frame[j] == input[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frame[index] = input[i];
            fault++;
            index = (index + 1) % n;
            printf("Page %d inserted into frame\n", input[i]);
        } else {
            printf("Page %d already in frame\n", input[i]);
        }

        printf("Current Frame: ");
        for (int j = 0; j < n; j++) {
            printf("%d ", frame[j]);
        }
        printf("\n");
    }
    return fault;
}

// Optimal Page Replacement
int optimal(int n, int p, int input[]) {
    int frame[n];
    for (int i = 0; i < n; i++) frame[i] = -1;
    int fault = 0;

    printf("\nPage Replacement Process (Optimal):\n");
    for (int i = 0; i < p; i++) {
        int found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < n; j++) {
            if (frame[j] == input[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int index = -1;
            int farthest = i + 1;

            for (int j = 0; j < n; j++) {
                if (frame[j] == -1) {
                    index = j;
                    break;
                }

                int pos = p;
                for (int k = i + 1; k < p; k++) {
                    if (frame[j] == input[k]) {
                        pos = k;
                        break;
                    }
                }
                if (pos > farthest) {
                    farthest = pos;
                    index = j;
                }
            }

            frame[index] = input[i];
            fault++;
            printf("Page %d replaced into frame\n", input[i]);
        } else {
            printf("Page %d already in frame\n", input[i]);
        }

        printf("Current Frame: ");
        for (int j = 0; j < n; j++) {
            printf("%d ", frame[j]);
        }
        printf("\n");
    }
    return fault;
}

// LRU Page Replacement
int LRU(int n, int p, int input[]) {
    int frame[n];
    int recent[n];
    for (int i = 0; i < n; i++) frame[i] = -1;
    int fault = 0;

    printf("\nPage Replacement Process (LRU):\n");
    for (int i = 0; i < p; i++) {
        int found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < n; j++) {
            if (frame[j] == input[i]) {
                found = 1;
                recent[j] = i;
                break;
            }
        }

        if (!found) {
            int lru = 0;
            for (int j = 1; j < n; j++) {
                if (recent[j] < recent[lru]) lru = j;
            }

            frame[lru] = input[i];
            recent[lru] = i;
            fault++;
            printf("Page %d replaced into frame\n", input[i]);
        } else {
            printf("Page %d already in frame\n", input[i]);
        }

        printf("Current Frame: ");
        for (int j = 0; j < n; j++) {
            printf("%d ", frame[j]);
        }
        printf("\n");
    }
    return fault;
}

int main()
{
    // Disk Scheduling Test
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int initial_head = 50;
    int total_cylinders = MAX_CYLINDERS;

    sstf(requests, n, initial_head);

return 0;

}    
