#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int P, R; // Number of processes and resources
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES]; 
int need[MAX_PROCESSES][MAX_RESOURCES];
int finished[MAX_PROCESSES] = {0}, safeSequence[MAX_PROCESSES];

// Function to check if the system is in a safe state
int isSafe() {
    int count = 0;

    // Calculate the need matrix
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    while (count < P) {
        int found = 0;
        for (int i = 0; i < P; i++) {
            if (!finished[i]) {
                int j;
                // Check if all needed resources for Pi are available
                for (j = 0; j < R; j++)
                    if (need[i][j] > available[j])
                        break;

                // If yes, simulate allocation → release
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        available[k] += allocation[i][k];

                    safeSequence[count++] = i;
                    finished[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            return 0; // No Pi could be satisfied → unsafe
    }
    return 1; // All processes can finish → safe
}

// Print the safe sequence in “P0 --> P1 --> …” format
void printSafeSequence() {
    printf("System is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < P; i++) {
        printf("P%d", safeSequence[i]);
        if (i < P - 1)
            printf(" --> ");
    }
    printf("\n");
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &P);
    printf("Enter the number of resources: ");
    scanf("%d", &R);

    // Read allocation matrix
    printf("Enter the allocation matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);

    // Read maximum demand matrix
    printf("Enter the maximum demand matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &max[i][j]);

    // Read available resources vector
    printf("Enter the available resources (%d values):\n", R);
    for (int j = 0; j < R; j++)
        scanf("%d", &available[j]);

    // Compute and display the Need matrix
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < P; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < R; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
    printf("\n");

    // Check for safety and print result
    if (isSafe()) {
        printSafeSequence();
    } else {
        printf("System is in an unsafe state!\n");
    }

    return 0;
}
