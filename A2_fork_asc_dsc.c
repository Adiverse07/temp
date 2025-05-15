#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubble(int a[], int sz) {
    int i, j, temp;
    for (i = 0; i < sz - 1; i++) {
        for (j = 0; j < sz - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    printf("Ascending - Bubble Sort: ");
    for (i = 0; i < sz; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void selection(int a[], int sz) {
    int i, j, max_idx, temp;
    for (i = 0; i < sz - 1; i++) {
        max_idx = i;
        for (j = i + 1; j < sz; j++) {
            if (a[j] > a[max_idx]) {
                max_idx = j;
            }
        }
        temp = a[max_idx];
        a[max_idx] = a[i];
        a[i] = temp;
    }
    printf("Descending - Selection Sort: ");
    for (i = 0; i < sz; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void do_parent(int a[], int sz) {
    printf("Sorting array in ascending order...\n");
    bubble(a, sz);
}

void do_child(int a[], int sz) {
    printf("Sorting array in descending order...\n");
    selection(a, sz);
}

int main() {
    int arr[50];
    int sz;
    pid_t x;

    printf("Enter array size: ");
    scanf("%d", &sz);

    for (int i = 0; i < sz; i++) {
        printf("Enter element %d: ", i+1);
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
