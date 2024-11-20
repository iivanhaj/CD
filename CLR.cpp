#include <iostream>
#include <stack>
#include <string>
using namespace std;

void parse(string input) {
    stack<string> parseStack;
    size_t i = 0;

    cout << "Parsing: " << input << endl;

    while (i < input.size()) {
        char c = input[i];

        // Shift operation
        if (c == 'i') { // Handling id
            parseStack.push("F");
            cout << "Shift: F (id)" << endl;
            i += 1; // Skip 'd' of "id"
        } else if (c == '+' || c == '*') {
            parseStack.push(string(1, c));
            cout << "Shift: " << c << endl;
        } else if (c == '(') {
            parseStack.push("(");
            cout << "Shift: (" << endl;
        } else if (c == ')') {
            // Reduce F -> (E)
            while (!parseStack.empty() && parseStack.top() != "(") {
                parseStack.pop();
            }
            parseStack.pop(); // Remove '('
            parseStack.push("F");
            cout << "Reduce: F -> (E)" << endl;
        }

        // Perform reductions
        while (parseStack.size() >= 3) {
            string rhs1 = parseStack.top();
            parseStack.pop();
            string op = parseStack.top();
            parseStack.pop();
            string rhs2 = parseStack.top();
            parseStack.pop();

            if (op == "*" && rhs2 == "T" && rhs1 == "F") {
                parseStack.push("T");
                cout << "Reduce: T -> T*F" << endl;
            } else if (op == "+" && rhs2 == "E" && rhs1 == "T") {
                parseStack.push("E");
                cout << "Reduce: E -> E+T" << endl;
            } else {
                // Push back if no reduction is possible
                parseStack.push(rhs2);
                parseStack.push(op);
                parseStack.push(rhs1);
                break;
            }
        }

        i++;
    }

    // Final reductions
    while (parseStack.size() > 1) {
        string top = parseStack.top();
        parseStack.pop();

        if (top == "T") {
            parseStack.push("E");
            cout << "Reduce: E -> T" << endl;
        }
    }

    cout << "Parsing complete." << endl;
}

int main() {
    string input = "(id*id)+(id*id)+id";
    parse(input);
    return 0;
}
