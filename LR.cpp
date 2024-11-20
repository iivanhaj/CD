#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Helper function to simulate reduction
void reduce(stack<string>& parseStack, string production) {
    string rhs = parseStack.top();
    parseStack.pop();
    parseStack.push(production);
    cout << "Reducing: " << production << " -> " << rhs << endl;
}

// Simulate LR Parsing
void parse(string input) {
    stack<string> parseStack; // Stack for parse states
    size_t i = 0;             // Pointer for the input string

    cout << "Parsing: " << input << endl;
    while (i < input.size()) {
        char c = input[i];

        if (c == 'i') { // Shift operation for id (i)
            parseStack.push("F");
            cout << "Shifting: F" << endl;
        } else if (c == '+' || c == '^' || c == '*') {
            parseStack.push(string(1, c));
            cout << "Shifting: " << c << endl;
        } else if (c == '(') {
            parseStack.push("(");
            cout << "Shifting: (" << endl;
        } else if (c == ')') {
            // Handle ')' by reducing F -> (E)
            while (!parseStack.empty() && parseStack.top() != "(") {
                parseStack.pop();
            }
            parseStack.pop(); // Remove '('
            parseStack.push("F");
            cout << "Reducing: F -> (E)" << endl;
        }

        // Perform reductions based on precedence
        if (parseStack.size() >= 3) {
            string rhs1 = parseStack.top();
            parseStack.pop();
            string op = parseStack.top();
            parseStack.pop();
            string rhs2 = parseStack.top();
            parseStack.pop();

            if ((rhs1 == "F" && rhs2 == "T" && op == "+") || 
                (rhs1 == "T" && rhs2 == "E" && op == "^")) {
                parseStack.push("E");
                cout << "Reducing: E -> E" << op << rhs1 << endl;
            } else if (rhs1 == "F" && op == "*") {
                parseStack.push("T");
                cout << "Reducing: T -> T*F" << endl;
            } else {
                // Push back if no reduction is possible
                parseStack.push(rhs2);
                parseStack.push(op);
                parseStack.push(rhs1);
            }
        }

        i++;
    }

    // Final reduction
    while (parseStack.size() > 1) {
        parseStack.pop();
        cout << "Reducing: Final Reduction to E" << endl;
    }

    cout << "Parsing complete." << endl;
}

int main() {
    string input = "(i^*i)+i^*(i+i)";
    parse(input);
    return 0;
}
