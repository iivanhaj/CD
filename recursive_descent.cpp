#include <iostream>
#include <string>
using namespace std;

string input;
int currentIndex = 0;  // Renamed variable to avoid conflict

bool match(char expected) {
    if (currentIndex < input.size() && input[currentIndex] == expected) {
        cout << "Matched: " << expected << endl; // Illustrate the match
        currentIndex++;
        return true;
    }
    cout << "Failed to match: " << expected << endl; // Illustrate the failure
    return false;
}

bool B() {
    cout << "Parsing B..." << endl;
    return match('a') || match('b');
}

bool A() {
    cout << "Parsing A..." << endl;
    if (match('a')) {
        cout << "Matched 'a' in A, now parsing B..." << endl;
        if (B()) return true;
    }
    return B(); // A -> B
}

bool Q() {
    cout << "Parsing Q..." << endl;
    if (A()) {
        cout << "Parsed A, now looking for 'A'..." << endl;
        if (A()) {
            cout << "Parsed another A, now looking for B..." << endl;
            if (B()) {
                cout << "Matched B in Q (Q -> QAB)" << endl;
                return true;
            }
        }
    }
    if (match('a')) {
        cout << "Matched 'a' in Q, now looking for B..." << endl;
        if (B()) {
            cout << "Matched B in Q (Q -> Ab)" << endl;
            return true;
        }
    }
    return false;
}

bool parse() {
    return Q() && currentIndex == input.size(); // Make sure the entire string is consumed
}

int main() {
    input = "abbab";  // String to parse
    cout << "Starting to parse the string: " << input << endl;
    if (parse()) {
        cout << "The string is successfully parsed!" << endl;
    } else {
        cout << "The string is not valid for the grammar." << endl;
    }
    return 0;
}
