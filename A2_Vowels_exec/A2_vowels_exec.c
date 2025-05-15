#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_vowels(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        char ch = tolower(str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
            count++;
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./A2_vowels_exec.out <string>\n");
        return 1;
    }

    int vcount = count_vowels(argv[1]);
    printf("Exec Program: Vowel count in \"%s\" = %d\n", argv[1], vcount);
    return 0;
}
