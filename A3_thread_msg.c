#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* display(void* arg){
    char *N = (char*) arg;
    printf("Message: %s\n", N);
    return NULL;
}

int main() {
    pthread_t tid;  
    char msg[100];
    printf("Enter Msg: ");
    scanf("%s", &msg);

    if (pthread_create(&tid, NULL, display, (void*) msg) != 0){
        perror("Failed to create thread");
        return 1;
    }

    pthread_join(tid, NULL); 

    printf("Main program finished.\n");
    return 0;
}
