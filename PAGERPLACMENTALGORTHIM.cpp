#include <stdio.h>
#include <string.h>

// Function to implement FIFO page replacement algorithm
void fifo(int pages[], int n, int capacity) {
    int frame[capacity], front = 0, page_faults = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frame[front] = pages[i];
            front = (front + 1) % capacity;
            page_faults++;
        }
    }

    printf("FIFO Page Faults: %d\n", page_faults);
}

// Function to implement LRU page replacement algorithm
void lru(int pages[], int n, int capacity) {
    int frame[capacity], time[capacity], page_faults = 0, counter = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0, lru_index = 0;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                time[j] = ++counter;
                break;
            }
        }
        if (!found) {
            int min_time = counter + 1;
            for (int j = 0; j < capacity; j++) {
                if (time[j] < min_time) {
                    min_time = time[j];
                    lru_index = j;
                }
            }
            frame[lru_index] = pages[i];
            time[lru_index] = ++counter;
            page_faults++;
        }
    }

    printf("LRU Page Faults: %d\n", page_faults);
}

// Function to implement LFU page replacement algorithm
void lfu(int pages[], int n, int capacity) {
    int frame[capacity], count[capacity], page_faults = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0, lfu_index = 0;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                count[j]++;
                break;
            }
        }

        if (!found) {
            int min_count = n + 1;
            for (int j = 0; j < capacity; j++) {
                if (frame[j] == -1) {
                    lfu_index = j;
                    break;
                } else if (count[j] < min_count) {
                    min_count = count[j];
                    lfu_index = j;
                }
            }

            frame[lfu_index] = pages[i];
            count[lfu_index] = 1;
            page_faults++;
        }
    }

    printf("LFU Page Faults: %d\n", page_faults);
}

// Function to implement Optimal page replacement algorithm
void optimal(int pages[], int n, int capacity) {
    int frame[capacity], page_faults = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0, replace_index = 0;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int farthest = i + 1;

            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k])
                        break;
                }
                if (k == n) {
                    replace_index = j;
                    break;
                } else if (k > farthest) {
                    farthest = k;
                    replace_index = j;
                }
            }

            frame[replace_index] = pages[i];
            page_faults++;
        }
    }

    printf("Optimal Page Faults: %d\n", page_faults);
}

// Main function to run the page replacement algorithms based on user input
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <algorithm>\n", argv[0]);
        printf("Algorithms: fifo, lru, lfu, optimal\n");
        return 1;
    }

    int pages[] = {1, 3, 0, 3, 5, 6};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    if (strcmp(argv[1], "fifo") == 0) {
        fifo(pages, n, capacity);
    } else if (strcmp(argv[1], "lru") == 0) {
        lru(pages, n, capacity);
    } else if (strcmp(argv[1], "lfu") == 0) {
        lfu(pages, n, capacity);
    } else if (strcmp(argv[1], "optimal") == 0) {
        optimal(pages, n, capacity);
    } else {
        printf("Invalid algorithm. Use fifo, lru, lfu, or optimal.\n");
        return 1;
    }

    return 0;
}
