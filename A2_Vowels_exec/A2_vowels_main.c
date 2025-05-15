#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    char input[100];
    printf("Main Program: Enter a string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        execl("./A2_vowels_exec.out", "vowel_exec", input, NULL);
        perror("exec failed");
    }
    else {
        wait(NULL);
        printf("Main Program: Child completed execution.\n");
    }

    return 0;
}
