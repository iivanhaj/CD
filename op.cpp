#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Helper to determine operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*') return 2;
    return 0; // '(' has the lowest precedence
}

// Check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '*';
}

// Perform reduction and display the steps
void reduce(stack<char>& operators, stack<string>& operands) {
    char op = operators.top();
    operators.pop();
    string right = operands.top();
    operands.pop();
    string left = operands.top();
    operands.pop();
    operands.push("(" + left + op + right + ")");
    cout << "Reducing: " << left << " " << op << " " << right << endl;
}

// Parse the input expression
void parse(const string& input) {
    stack<char> operators;
    stack<string> operands;

    cout << "Parsing: " << input << endl;

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        if (isalnum(c)) { // Operand (id -> i)
            operands.push(string(1, c));
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                reduce(operators, operands);
            }
            operators.pop(); // Pop '('
        } else if (isOperator(c)) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                reduce(operators, operands);
            }
            operators.push(c);
        }
    }

    // Reduce remaining operators
    while (!operators.empty()) {
        reduce(operators, operands);
    }

    // Final parsing result
    cout << "Final parsing result: " << operands.top() << endl;
}

int main() {
    string input = "(i*i)+(i*i)+i";
    parse(input);
    return 0;
}
