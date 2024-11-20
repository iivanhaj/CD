#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <string>
using namespace std;

// Define the predictive parsing table
map<pair<string, string>, vector<string>> parseTable;

void initializeParseTable() {
    parseTable[{"E", "i"}] = {"T", "E'"};
    parseTable[{"E", "("}] = {"T", "E'"};

    parseTable[{"E'", "*"}] = {"*", "T", "E'"};
    parseTable[{"E'", "+"}] = {"epsilon"};
    parseTable[{"E'", ")"}] = {"epsilon"};
    parseTable[{"E'", "$"}] = {"epsilon"};

    parseTable[{"T", "i"}] = {"F", "T'"};
    parseTable[{"T", "("}] = {"F", "T'"};

    parseTable[{"T'", "+"}] = {"+", "F", "T'"};
    parseTable[{"T'", "*"}] = {"epsilon"};
    parseTable[{"T'", ")"}] = {"epsilon"};
    parseTable[{"T'", "$"}] = {"epsilon"};

    parseTable[{"F", "i"}] = {"i"};
    parseTable[{"F", "("}] = {"(", "E", ")"};
}

void parse(string input) {
    stack<string> parseStack;
    parseStack.push("$");  // End of stack
    parseStack.push("E");  // Start symbol

    input += "$";  // Append end marker
    int i = 0;

    cout << "Stack\t\tInput\t\tAction\n";
    while (!parseStack.empty()) {
        string top = parseStack.top();
        string currentInput(1, input[i]);  // Current input character as string

        // Print stack and input
        stack<string> tempStack = parseStack;
        string stackContents;
        while (!tempStack.empty()) {
            stackContents = tempStack.top() + " " + stackContents;
            tempStack.pop();
        }
        cout << stackContents << "\t\t" << input.substr(i) << "\t\t";

        if (top == currentInput) {
            // Match terminal
            cout << "Match " << top << endl;
            parseStack.pop();
            i++;  // Move to the next character in the input
        } else if (parseTable.find({top, currentInput}) != parseTable.end()) {
            // Apply production rule
            parseStack.pop();
            vector<string> production = parseTable[{top, currentInput}];
            cout << "Output " << top << " -> ";
            for (const string &s : production) cout << s << " ";
            cout << endl;

            if (production[0] != "epsilon") {
                for (auto it = production.rbegin(); it != production.rend(); ++it) {
                    parseStack.push(*it);
                }
            }
        } else {
            // Error handling
            cout << "Error: Invalid input\n";
            return;
        }
    }

    if (input[i] == '$') {
        cout << "Parsing successful!\n";
    } else {
        cout << "Error: Unmatched input\n";
    }
}

int main() {
    initializeParseTable();
    string input = "i*i+i";  // Replace with the desired input
    parse(input);
    return 0;
}
