#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Selection Sort (Ascending)
void selection_sort(int a[], int sz) {
    int i, j, min_idx, temp;
    for (i = 0; i < sz - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < sz; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        temp = a[min_idx];
        a[min_idx] = a[i];
        a[i] = temp;
    }
    printf("Ascending - Selection Sort: ");
    for (i = 0; i < sz; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// Insertion Sort (Descending)
void insertion_sort(int a[], int sz) {
    int i, j, key;
    for (i = 1; i < sz; i++) {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] < key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
    printf("Descending - Insertion Sort: ");
    for (i = 0; i < sz; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void do_parent(int a[], int sz) {
    printf("Sorting array in ascending order using Selection Sort...\n");
    selection_sort(a, sz);
}

void do_child(int a[], int sz) {
    printf("Sorting array in descending order using Insertion Sort...\n");
    insertion_sort(a, sz);
}

int main() {
    int arr[50];
    int sz;
    pid_t x;

    printf("Enter array size: ");
    scanf("%d", &sz);

    for (int i = 0; i < sz; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    printf("\n");

    x = fork();

    switch (x) {
        case 0:
            do_child(arr, sz);
            exit(0);
        case -1:
            printf("Fork failed\n");
            exit(-1);
        default:
            wait(NULL);
            do_parent(arr, sz);
            exit(0);
    }

    return 0;
}
