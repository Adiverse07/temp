#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;

    for (i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int findOptimal(int pages[], int frames[], int n, int index, int f) {
    int pos = -1, farthest = index;
    for (int i = 0; i < f; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (pos == -1) ? 0 : pos;
}

void fifo(int pages[], int n, int f) {
    int frames[10], front = 0, faults = 0, i, j, found;

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[front] = pages[i];
            front = (front + 1) % f;
            printf("* ");
            faults++;
        }

        printf("Frame: ");
        for (j = 0; j < f; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", faults);
}

void lru(int pages[], int n, int f) {
    int frames[10], time[10], count = 0, faults = 0;
    int i, j, pos, found;

    for (i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");

    for (i = 0; i < n; i++) {
        found = 0;

        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                count++;
                time[j] = count;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (i < f) {
                frames[i] = pages[i];
                time[i] = ++count;
            } else {
                pos = findLRU(time, f);
                frames[pos] = pages[i];
                time[pos] = ++count;
            }
            printf("* ");
            faults++;
        }

        printf("Frame: ");
        for (j = 0; j < f; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", faults);
}

void optimal(int pages[], int n, int f) {
    int frames[10], i, j, k, pos, found, faults = 0;

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (i = 0; i < n; i++) {
        found = 0;

        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (i < f) {
                frames[i] = pages[i];
            } else {
                pos = findOptimal(pages, frames, n, i + 1, f);
                frames[pos] = pages[i];
            }
            printf("* ");
            faults++;
        }

        printf("Frame: ");
        for (j = 0; j < f; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults (Optimal): %d\n", faults);
}

int main() {
    int pages[50], n, f, choice;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    do {
        printf("\nPage Replacement Algorithms Menu:\n");
        printf("1. FIFO\n2. LRU\n3. Optimal\n4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            fifo(pages, n, f);
            break;
        case 2:
            lru(pages, n, f);
            break;
        case 3:
            optimal(pages, n, f);
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);
    return 0;
}