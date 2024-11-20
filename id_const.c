#include <stdio.h>
#include <ctype.h>

int isValidIdentifier(char *token) {
    if (!isalpha(token[0]) && token[0] != '_') return 0;  // First character must be letter or '_'
    for (int i = 1; token[i] != '\0'; i++)
        if (!isalnum(token[i]) && token[i] != '_') return 0;  // Remaining characters must be alphanumeric or '_'
    return 1;
}

int isValidConstant(char *token) {
    int i = (token[0] == '-' || token[0] == '+') ? 1 : 0;  // Allow optional sign
    for (; token[i] != '\0'; i++)
        if (!isdigit(token[i])) return 0;  // All characters must be digits
    return 1;
}

void analyzeTokensInFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) { printf("File could not be opened!\n"); return; }

    char token[100];
    while (fscanf(file, "%s", token) != EOF) {
        if (isValidIdentifier(token)) 
            printf("%s - Valid Identifier\n", token);
        else if (isValidConstant(token)) 
            printf("%s - Valid Constant\n", token);
        else 
            printf("%s - Invalid Token\n", token);
    }
    fclose(file);
}

int main() {
    analyzeTokensInFile("input3.txt");
    return 0;
}
