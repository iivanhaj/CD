#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int tempCount = 1;

void generateThreeAddressCode(char *op, int operand1, int operand2, char *result) {
    printf("%s = %d %s %d\n", result, operand1, op, operand2);
}

int evaluateExpression(int operand1, int operand2, char op) {
    if (op == '+') return operand1 + operand2;
    if (op == '-') return operand1 - operand2;
    if (op == '*') return operand1 * operand2;
    if (op == '/') return operand1 / operand2;
    return 0;
}

int processExpression(char *expr) {
    int stack[100];
    int top = -1;
    char *result = (char *)malloc(10);
    for (int i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            stack[++top] = expr[i] - '0'; // Push digit onto stack
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            int operand2 = stack[top--];
            int operand1 = stack[top--];
            int res = evaluateExpression(operand1, operand2, expr[i]);

            // Generate unique result label
            sprintf(result, "t%d", tempCount++);
            generateThreeAddressCode(&expr[i], operand1, operand2, result);
            stack[++top] = res; // Push result onto stack
        }
    }
    return stack[top];
}

int main() {
    char expression[] = "23+5*";  // Example expression
    int result = processExpression(expression);
    printf("Result: %d\n", result);
    return 0;
}
