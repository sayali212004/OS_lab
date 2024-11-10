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

// SCAN Disk Scheduling
void scan(int requests[], int n, int head, int total_cylinders) {
    int seek_count = 0;
    int current_position = head;

    // Sort requests
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    printf("SCAN Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        if (requests[i] >= current_position) {
            seek_count += abs(current_position - requests[i]);
            current_position = requests[i];
            printf("Head moved to: %d\n", current_position);
        }
    }

    if (current_position < total_cylinders - 1) {
        seek_count += abs(current_position - (total_cylinders - 1));
        current_position = total_cylinders - 1;
        printf("Head moved to: %d\n", current_position);
    }

    for (int i = 0; i < n; i++) {
        if (requests[i] < current_position) {
            seek_count += abs(current_position - requests[i]);
            current_position = requests[i];
            printf("Head moved to: %d\n", current_position);
        }
    }
    printf("Total seek time (SCAN): %d\n\n", seek_count);
}

// C-LOOK Disk Scheduling
void clook(int requests[], int n, int head) {
    int seek_count = 0;
    int current_position = head;

    // Sort requests
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    printf("C-Look Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        if (requests[i] >= current_position) {
            seek_count += abs(current_position - requests[i]);
            current_position = requests[i];
            printf("Head moved to: %d\n", current_position);
        }
    }

    if (current_position != requests[n - 1]) {
        seek_count += abs(current_position - requests[0]);
        current_position = requests[0];
        printf("Head moved to: %d\n", current_position);
    }

    for (int i = 1; i < n; i++) {
        seek_count += abs(current_position - requests[i]);
        current_position = requests[i];
        printf("Head moved to: %d\n", current_position);
    }
    printf("Total seek time (C-Look): %d\n\n", seek_count);
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
    scan(requests, n, initial_head, total_cylinders);
    clook(requests, n, initial_head);

    // Page Replacement Test
    int frame_size, page_count;
    printf("Enter the size of the frame: ");
    scanf("%d", &frame_size);
    printf("Enter the number of input pages: ");
    scanf("%d", &page_count);

    int input[page_count];
    printf("Enter the input pages: ");
    for (int i = 0; i < page_count; i++) 
    {
        scanf("%d", &input[i]);
    }

    int fifo_faults = FIFO(frame_size, page_count, input);
} 
