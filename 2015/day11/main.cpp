#include <iostream>
#include <string>

using namespace std;

void day11_01(string& input);
void incrementPassword(string& input);
bool isValid(const string& password);
void day11_02(string& input);

int main() {
    string input = "hepxcrrq";
    day11_01(input);
    cout << input << endl;
    input = "hepxxyzz";
    day11_02(input);
    cout << input << endl;
}

void day11_01(string& input) {
    while (true) {
        incrementPassword(input);

        if (isValid(input)) {
            break;
        }
    }
}

void day11_02(string &input) {
    while (true) {
        incrementPassword(input);

        if (isValid(input)) {
            break;
        }
    }
}


void incrementPassword(string& input) {
    for (int i = input.size() - 1; i >= 0; --i) {
        if (input[i] == 'z') {
            input[i] = 'a';
        }
        else {
            input[i] += 1;
            break;
        }
    }
}

bool isValid(const string& password) {
    bool hasStraight = false;
    bool onePair = false;
    bool twoPair = false;
    char firstPairChar = '\0';

    for (int i = 0; i < password.size(); ++i) {
        if (password[i] == 'i' || password[i] == 'l' || password[i] == 'o') {
            return false;
        }
    }

    for (int i = 0; i < password.size() - 2; ++i) {
        if (password[i + 1] == password[i] + 1 &&
            password[i + 2] == password[i] + 2) {
            hasStraight = true;
            break;
            }
    }

    for (int i = 0; i < password.size() - 1; ++i) {
        if (password[i] == password[i + 1]) {
            if (!onePair) {
                onePair = true;
                firstPairChar = password[i];
                ++i;
            }
            else if (password[i] != firstPairChar) {
                twoPair = true;
                ++i;
                break;
            }
            else {
                ++i;
            }
        }
    }

    return hasStraight && onePair && twoPair;
}