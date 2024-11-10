
#include <stdio.h>
#include <stdbool.h>

bool find(int value, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

void update(int value, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            // Move the found value to the end (to mark it as recently used)
            arr[i] = -1; // Mark as empty
            break;
        }
    }
}

int findMax(int arr[], int size) {
    int max_index = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}

int findMin(int arr[], int size) {
    int min_index = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

void printFrame(int frame[], int size) {
    for (int i = 0; i < size; i++) {
        if (frame[i] != -1) {
            printf("%d ", frame[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

int main() {
    int reference_str[20] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0};
    int frame_size = 3;
    int len = sizeof(reference_str) / sizeof(reference_str[0]);

    if (frame_size < 3) {
        printf("Error: Frame size must be at least 3.\n");
        return 1;
    }

    // Arrays to hold the frame and the result for page fault/ hit
    int frame[frame_size], result[len];
    for (int i = 0; i < frame_size; i++) {
        frame[i] = -1; // Initialize the frame with empty slots (-1)
    }

    // FCFS algorithm
    printf("FCFS:\n");
    int fcfs_index = 0;
    int fcfs_faults = 0;

    for (int i = 0; i < len; i++) {
        if (!find(reference_str[i], frame, frame_size)) {
            frame[fcfs_index] = reference_str[i];
            fcfs_faults++;
            result[i] = -1;
            fcfs_index = (fcfs_index + 1) % frame_size;  // Move to the next frame
        } else {
            result[i] = 0;
        }
        printFrame(frame, frame_size);
    }
    printf("Total FCFS Page Faults: %d\n", fcfs_faults);

    // LRU algorithm
    printf("LRU:\n");
    int lru_faults = 0;
    for (int i = 0; i < frame_size; i++) {
        frame[i] = -1; // Reset the frame for LRU
    }

    for (int i = 0; i < len; i++) {
        if (!find(reference_str[i], frame, frame_size)) {
            // Page fault, replace the least recently used page
            int min_index = findMin(frame, frame_size);
            frame[min_index] = reference_str[i];
            lru_faults++;
            result[i] = -1;
        } else {
            result[i] = 0;
            update(reference_str[i], frame, frame_size); // Mark this page as recently used
        }
        printFrame(frame, frame_size);
    }
    printf("Total LRU Page Faults: %d\n", lru_faults);

    // Optimal algorithm
    printf("Optimal:\n");
    int optimal_faults = 0;
    for (int i = 0; i < frame_size; i++) {
        frame[i] = -1; // Reset the frame for Optimal
    }

    for (int i = 0; i < len; i++) {
        if (!find(reference_str[i], frame, frame_size)) {
            // Page fault, replace the page which will not be used for the longest period
            int farthest_index = -1, farthest_distance = -1;

            for (int j = 0; j < frame_size; j++) {
                int found = 0;
                for (int k = i + 1; k < len; k++) {
                    if (frame[j] == reference_str[k]) {
                        found = 1;
                        if (k > farthest_distance) {
                            farthest_distance = k;
                            farthest_index = j;
                        }
                        break;
                    }
                }
                if (!found) {
                    farthest_index = j;
                    break;
                }
            }

            frame[farthest_index] = reference_str[i];
            optimal_faults++;
            result[i] = -1;
        } else {
            result[i] = 0;
        }
        printFrame(frame, frame_size);
    }
    printf("Total Optimal Page Faults: %d\n", optimal_faults);

    return 0;
}