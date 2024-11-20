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
        parseStack.push(string(1, c));
        cout << "Shift: " << c << endl;

        // Perform reductions
        while (true) {
            string top;

            // Check for B -> ab
            if (parseStack.size() >= 2) {
                string second = parseStack.top();
                parseStack.pop();
                string first = parseStack.top();
                parseStack.pop();

                if (first == "a" && second == "b") {
                    parseStack.push("B");
                    cout << "Reduce: B -> ab" << endl;
                } else {
                    parseStack.push(first);
                    parseStack.push(second);
                    break;
                }
            }

            // Check for A -> Ab
            if (parseStack.size() >= 2) {
                string second = parseStack.top();
                parseStack.pop();
                string first = parseStack.top();
                parseStack.pop();

                if (first == "A" && second == "b") {
                    parseStack.push("A");
                    cout << "Reduce: A -> Ab" << endl;
                } else {
                    parseStack.push(first);
                    parseStack.push(second);
                    break;
                }
            }

            // Check for A -> B
            if (parseStack.size() >= 1) {
                string first = parseStack.top();
                parseStack.pop();

                if (first == "B") {
                    parseStack.push("A");
                    cout << "Reduce: A -> B" << endl;
                } else {
                    parseStack.push(first);
                    break;
                }
            }

            // Check for Q -> Ab
            if (parseStack.size() >= 2) {
                string second = parseStack.top();
                parseStack.pop();
                string first = parseStack.top();
                parseStack.pop();

                if (first == "A" && second == "b") {
                    parseStack.push("Q");
                    cout << "Reduce: Q -> Ab" << endl;
                } else {
                    parseStack.push(first);
                    parseStack.push(second);
                    break;
                }
            }

            break; // Exit reduction loop
        }

        i++;
    }

    // Final reduction to Q
    while (parseStack.size() > 1) {
        string top = parseStack.top();
        parseStack.pop();

        if (top == "Q") {
            cout << "Reduce: Q -> QAB" << endl;
        }
    }

    cout << "Parsing complete." << endl;
}

int main() {
    string input = "abbab";
    parse(input);
    return 0;
}
