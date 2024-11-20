#include <stdio.h>
#include <string.h>

int isOperator(char *token) {
    // List of valid operators
    char *validOps[] = {"+", "-", "*", "/", "%", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "=", "&", "|", "^", "~", "++", "--"};
    for (int i = 0; i < 19; i++) {
        if (strcmp(token, validOps[i]) == 0) return 1; // Match found
    }
    return 0;
}

void analyzeTokensInFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) { 
        printf("File could not be opened!\n"); 
        return; 
    }

    char token[100];
    while (fscanf(file, "%s", token) != EOF) {
        if (isOperator(token))
            printf("%s - Valid Operator\n", token);
        else
            printf("%s - Non-Operator\n", token);
    }
    fclose(file);
}

int main() {
    analyzeTokensInFile("input.txt");
    return 0;
}
