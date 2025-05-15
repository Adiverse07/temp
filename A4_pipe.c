#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

void do_parent(int p_to_c[], int c_to_p[]);
void do_child(int p_to_c[], int c_to_p[]);

int main() {
    int p_to_c[2];
    int c_to_p[2];
    pid_t x;

    pipe(p_to_c);
    pipe(c_to_p);
    
    x = fork();
    
    if (x == 0) {
        do_child(p_to_c, c_to_p);
    } 
    else {
        do_parent(p_to_c, c_to_p);
    }

    return 0;
}

void do_parent(int p_to_c[], int c_to_p[]) {
    char msg[50];
    char buff[50];
    printf("Message: ");
    scanf("%s", &msg);

    close(p_to_c[0]);
    close(c_to_p[1]);

    write(p_to_c[1], msg, strlen(msg) + 1);
    close(p_to_c[1]); 

    read(c_to_p[0], buff, sizeof(buff));
    close(c_to_p[0]);

    printf("\nParent received: %s\n", buff);
}

void do_child(int p_to_c[], int c_to_p[]) {
    char buff[50];
    int i;

    close(p_to_c[1]);
    close(c_to_p[0]);

    read(p_to_c[0], buff, sizeof(buff));
    printf("Child Reading: %s\n\n", buff);
    close(p_to_c[0]);

    for (i = 0; buff[i] != '\0'; i++) {
        printf("Converting %c to uppercase: %c\n", buff[i], toupper(buff[i]));
        buff[i] = toupper(buff[i]);
    }

    write(c_to_p[1], buff, strlen(buff) + 1);
    close(c_to_p[1]);
}
