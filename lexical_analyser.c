#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

const char *keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double",
                          "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long",
                          "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct",
                          "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
const char operators[] = "+-*/=><";
const char delimiters[] = ",;(){}[]";

bool isKeyword(const char *str) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) return true;
    }
    return false;
}

void analyze(FILE *file) {
    char ch, lexeme[100];
    int i = 0;
    bool inComment = false;
    
    while ((ch = fgetc(file)) != EOF) {
        if (inComment) { if (ch == '*' && fgetc(file) == '/') inComment = false; continue; }
        if (isspace(ch)) continue;
        if (ch == '/' && fgetc(file) == '*') { inComment = true; continue; }
        
        if (isalpha(ch)) {
            lexeme[i++] = ch;
            while (isalnum(ch = fgetc(file)) || ch == '_') lexeme[i++] = ch;
            lexeme[i] = '\0'; i = 0; ungetc(ch, file);
            printf("%s - %s\n", lexeme, isKeyword(lexeme) ? "Keyword" : "Identifier");
        } 
        else if (isdigit(ch)) {
            lexeme[i++] = ch;
            while (isdigit(ch = fgetc(file))) lexeme[i++] = ch;
            lexeme[i] = '\0'; i = 0; ungetc(ch, file);
            printf("%s - Constant\n", lexeme);
        } 
        else if (strchr(operators, ch)) printf("%c - Operator\n", ch);
        else if (strchr(delimiters, ch)) printf("%c - Delimiter\n", ch);
    }
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) { printf("File could not be opened!\n"); return 1; }
    analyze(file);
    fclose(file);
    return 0;
}
