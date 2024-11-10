
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CYLINDERS 200


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

int main()
{
    // Disk Scheduling Test
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int initial_head = 50;
    int total_cylinders = MAX_CYLINDERS;

    scan(requests, n, initial_head, total_cylinders);
    
    return 0;
}
