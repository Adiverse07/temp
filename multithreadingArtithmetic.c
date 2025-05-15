# write a multithreaded program to perform arithmetic operations.
#include <stdio.h>
#include <pthread.h>

// Structure to hold operands
typedef struct {
    int a;
    int b;
} Operands;

// Function for addition
void* add(void* args) {
    Operands* op = (Operands*) args;
    printf("Addition: %d + %d = %d\n", op->a, op->b, op->a + op->b);
    return NULL;
}

// Function for subtraction
void* subtract(void* args) {
    Operands* op = (Operands*) args;
    printf("Subtraction: %d - %d = %d\n", op->a, op->b, op->a - op->b);
    return NULL;
}

// Function for multiplication
void* multiply(void* args) {
    Operands* op = (Operands*) args;
    printf("Multiplication: %d * %d = %d\n", op->a, op->b, op->a * op->b);
    return NULL;
}

// Function for division
void* divide(void* args) {
    Operands* op = (Operands*) args;
    if (op->b != 0)
        printf("Division: %d / %d = %.2f\n", op->a, op->b, (float)op->a / op->b);
    else
        printf("Division: Division by zero is not allowed.\n");
    return NULL;
}

int main() {
    pthread_t t1, t2, t3, t4;
    Operands values;

    // Input from user
    printf("Enter two integers: ");
    scanf("%d %d", &values.a, &values.b);

    // Create threads
    pthread_create(&t1, NULL, add, &values);
    pthread_create(&t2, NULL, subtract, &values);
    pthread_create(&t3, NULL, multiply, &values);
    pthread_create(&t4, NULL, divide, &values);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    return 0;
}
// To run
// gcc arithmetic_threads.c -o arithmetic_threads -pthread
// ./arithmetic_threads