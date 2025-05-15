#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int count_vowels(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        char ch = tolower(str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
            count++;
    }
    return count;
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        char str[100];
        printf("Child Process: Enter a string: ");
        fgets(str, sizeof(str), stdin);
        
        int vcount = count_vowels(str);
        printf("Child Process: Number of vowels = %d\n", vcount);
    }
    else {
        wait(NULL);
        printf("Parent Process: Child completed vowel counting.\n");
    }

    return 0;
}
