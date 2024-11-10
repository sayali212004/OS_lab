//Scan & Clook

#include <stdio.h>
#include <stdlib.h>
#define MAX_CYLINDERS 200

void sstf(int requests[], int n, int head) {
int completed[MAX_CYLINDERS] = {0};
int seek_count = 0;
int current_position = head;
printf("SSTF Disk Scheduling:\n");
for (int i = 0; i < n; i++) 
{
    int min_distance = 9999;
    int index = -1;
    for (int j = 0; j < n; j++) 
    {
        if (!completed[j]) 
        {
            int distance = abs(requests[j] - current_position);
            if (distance < min_distance) 
            {
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
void scan(int requests[], int n, int head, int total_cylinders) 
{
    int seek_count = 0;
    int current_position = head;
    for (int i = 0; i < n; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (requests[i] > requests[j]) 
            {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
    printf("SCAN Disk Scheduling:\n");
    for (int i = 0; i < n; i++) 
    {
        if (requests[i] >= current_position) 
        {
            seek_count += abs(current_position - requests[i]);
            current_position = requests[i];
            printf("Head moved to: %d\n", current_position);
        }
    }
    if (current_position < total_cylinders - 1) 
    {
        seek_count += abs(current_position - (total_cylinders - 1));
        current_position = total_cylinders - 1;
        printf("Head moved to: %d\n", current_position);
    }
    for (int i = 0; i < n; i++) 
    {
        if (requests[i] < current_position) 
        {
            seek_count += abs(current_position - requests[i]);
            current_position = requests[i];
            printf("Head moved to: %d\n", current_position);
        }
    }
    printf("Total seek time (SCAN): %d\n\n", seek_count);
}
void clook(int requests[], int n, int head) 
{
    int seek_count = 0;
    int current_position = head;
    for (int i = 0; i < n; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (requests[i] > requests[j]) 
            {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
    printf("C-Look Disk Scheduling:\n");
    for (int i = 0; i < n; i++) 
    {
        if (requests[i] >= current_position) 
        {
            seek_count += abs(current_position - requests[i]);
            current_position = requests[i];
            printf("Head moved to: %d\n", current_position);
        }
    }
    if (current_position != requests[n - 1]) 
    {
        seek_count += abs(current_position - requests[0]);
        current_position = requests[0];
        printf("Head moved to: %d\n", current_position);
    }
    for (int i = 1; i < n; i++) 
    {
        seek_count += abs(current_position - requests[i]);
        current_position = requests[i];
        printf("Head moved to: %d\n", current_position);
    }
    printf("Total seek time (C-Look): %d\n\n", seek_count);
}

int main() 
{
    int requests[] = { 98, 183, 37, 122, 14, 124, 65, 67 };
    int n = sizeof(requests) / sizeof(requests[0]);
    int initial_head = 50;
    int total_cylinders = MAX_CYLINDERS;
    sstf(requests, n, initial_head);
    int requests_scan[n];
    for (int i = 0; i < n; i++) 
    {
        requests_scan[i] = requests[i];
    }
    scan(requests_scan, n, initial_head, total_cylinders);
    int requests_clook[n];
    for (int i = 0; i < n; i++) 
    {
        requests_clook[i] = requests[i];
    }
    clook(requests_clook, n, initial_head);
    return 0;
}



//FCFS

#include <iostream>
#include <vector>
using namespace std;
int FIFO(int n, int p, const vector<int>& input) {
vector<int> frame(n);
int fault = 0;
int index = 0;
cout << "\nPage Replacement Process:\n";
for (int i = 0; i < p; i++) {
bool found = false;
// Check if the page is already in the frame
for (int j = 0; j < n; j++) {
if (frame[j] == input[i]) {
found = true;
break;
}
}
if (!found) {
if (index == n) {
index = 0;
}
frame[index] = input[i];
fault++;
index++;
cout << "Page " << input[i] << " replaced ";
if (index == n) {
cout << "Page " << frame[0] << endl;
index = 0;
} else if (i == 0) {
cout << "(initially empty frame)" << endl;
} else {
cout << "Page " << frame[index - 1] << endl;
}
} else {
cout << "Page " << input[i] << " already in frame" << endl;
}
cout << "Current Frame: ";
for (int j = 0; j < n; j++) {
cout << frame[j] << " ";
}
cout << endl;
}
return fault;
}
int main() {
int n, p;
cout << "Enter the size of the frame: ";
cin >> n;
cout << "Enter the No. of Input Pages: ";
cin >> p;
vector<int> input(p);
cout << "Enter the Input Pages: ";
for (int i = 0; i < p; i++) {
cin >> input[i];
}
int faults = FIFO(n, p, input);
cout << "\nThe No. of Page Faults is: " << faults << endl;
return 0;
}


//Optimal

#include <iostream>
#include <vector>
using namespace std;
int optimal(int n, int p, const vector<int>& input) {
vector<int> frame(n, -1);
int fault = 0;
cout << "\nPage Replacement Process:\n";
for (int i = 0; i < p; i++) {
bool found = false;
int index = -1;
for (int j = 0; j < n; j++) {
if (frame[j] == input[i]) {
found = true;
index = j;
break;
}
}
if (found) {
cout << "Page " << input[i] << " already in frame" << endl;
} else {
if (n > 0 && frame[0] == -1) {
frame[0] = input[i];
n--;
} else {
int farthest = 0;
int maxDist = 0;
for (int j = 0; j < n; j++) {
int dist = p;
for (int k = i + 1; k < p; k++) {
if (frame[j] == input[k]) {
dist = k - i;
break;
}
}
if (dist > maxDist) {
maxDist = dist;
farthest = j;
}
}
cout << "Page " << frame[farthest] << " replaced by ";
frame[farthest] = input[i];
}
fault++;
cout << "Page " << input[i] << endl;
}
cout << "Current Frame: ";
for (int page : frame) {
if (page != -1) {
cout << page << " ";
}
}
cout << endl;
}
return fault;
}
int main() {
int n, p;
cout << "Enter the size of the frame: ";
cin >> n;
cout << "Enter the No. of Input Pages: ";
cin >> p;
vector<int> input(p);
cout << "Enter the Input Pages: ";
for (int i = 0; i < p; i++) {
cin >> input[i];
}
int faults = optimal(n, p, input);
cout << "\nThe No. of Page Faults is: " << faults << endl;
return 0;
}


LRU

#include <iostream>
#include <vector>
#include <list>
using namespace std;
int LRU(int n, int p, const vector<int>& input) {
vector<int> frame(n, -1);
list<int> order;
int fault = 0;
cout << "\nPage Replacement Process:\n";
for (int i = 0; i < p; i++) {
bool found = false;
int index = -1;
for (int j = 0; j < n; j++) {
if (frame[j] == input[i]) {
found = true;
index = j;
break;
}
}
if (found) {
order.remove(input[i]);
order.push_front(input[i]);
cout << "Page " << input[i] << " already in frame (moved to front)" << endl;
} else {
if (order.size() == n) {
int lruPage = order.back();
order.pop_back();
for (int j = 0; j < n; j++) {
if (frame[j] == lruPage) {
index = j;
break;
}
}
cout << "Page " << lruPage << " replaced by ";
} else {
index = order.size();
}
frame[index] = input[i];
order.push_front(input[i]);
fault++;
cout << "Page " << input[i] << endl;
}
cout << "Current Frame: ";
for (int page : frame) {
if (page != -1) {
cout << page << " ";
}
}
cout << endl;
}
return fault;
}
int main() {
int n, p;
cout << "Enter the size of the frame: ";
cin >> n;
cout << "Enter the No. of Input Pages: ";
cin >> p;
vector<int> input(p);
cout << "Enter the Input Pages: ";
for (int i = 0; i < p; i++) {
cin >> input[i];
}
int faults = LRU(n, p, input);
cout << "\nThe No. of Page Faults is: " << faults << endl;
return 0;
}
