#include <stdio.h>
#include <string.h>

int isValidString(char *str) {
    // Check for 'a'
    if (strcmp(str, "a") == 0) return 1;
    // Check for 'a*b'
    if (str[0] == 'a') {
        int i = 1;
        while (str[i] == 'b') i++;
        if (str[i] == '\0') return 1;
    }
    // Check for 'abb'
    if (strcmp(str, "abb") == 0) return 1;
    return 0;
}

void analyzeStringsInFile(const char *filename) {
    FILE *file = fopen(filename, "r");

    char str[100];
    while (fscanf(file, "%s", str) != EOF) {
        if (isValidString(str))
            printf("%s - Valid String\n", str);
        else
            printf("%s - Invalid String\n", str);
    }
    fclose(file);
}

int main() {
    analyzeStringsInFile("input.txt");
    return 0;
}
