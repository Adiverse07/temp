#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 3

int A[SIZE][SIZE] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

int B[SIZE][SIZE] = {
    {9, 8, 7},
    {6, 5, 4},
    {3, 2, 1}
};

typedef struct {
    int row;
    int col;
} ThreadData;

int result[SIZE][SIZE];

void* multiply(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int row = data->row;
    int col = data->col;
    free(data);

    int* cellValue = malloc(sizeof(int));
    *cellValue = 0;

    for (int i = 0; i < SIZE; i++) {
        *cellValue += A[row][i] * B[i][col];
    }

    pthread_exit((void*) cellValue);
}

int main() {
    pthread_t threads[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            ThreadData* data = malloc(sizeof(ThreadData));
            data->row = i;
            data->col = j;

            if (pthread_create(&threads[i][j], NULL, multiply, (void*) data) != 0) {
                perror("Thread creation failed");
                return 1;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            void* retVal;
            pthread_join(threads[i][j], &retVal);
            result[i][j] = *((int*) retVal);
            free(retVal);
        }
    }

    printf("Resultant Matrix (A x B):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%4d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
