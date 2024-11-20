#include <stdio.h>
#include <ctype.h>

int calculate(char *expr) {
    int result = 0, term = 1, num = 0;
    char op = '+';

    printf("Evaluating: %s\n", expr);

    while (*expr) {
        if (isdigit(*expr)) {
            num = num * 10 + (*expr - '0');
        }
        if (*expr == '+' || *expr == '*' || *(expr + 1) == '\0') {
            printf("Step: Operator = %c, Number = %d, Term = %d, Result = %d\n", op, num, term, result);
            
            if (op == '*') {
                term *= num;
                printf("Multiply: Term = %d\n", term);
            } else {
                term = num;
                printf("Set Term = %d\n", term);
            }

            if (*expr == '+' || *(expr + 1) == '\0') {
                result += term;
                printf("Add: Result = %d\n", result);
                term = 1;
            }
            op = *expr;
            num = 0;
        }
        expr++;
    }
    return result;
}

int main() {
    char expr[100];
    printf("Enter expression: ");
    scanf("%s", expr);
    printf("Final Result: %d\n", calculate(expr));
    return 0;
}
