#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

struct Context {
    int sum;
    bool isObject;
    bool hasRed;
};

int readNumber(ifstream& file, char firstChar);
string readString(ifstream& file);
void day12();

int main() {
    day12();
    return 0;
}

void day12() {
    ifstream day12_data("data/2015/day12.txt");

    if (!day12_data) {
        cout << "Could not open file";
        exit(-1);
    }

    vector<Context> contexts;
    contexts.push_back({0, false, false}); // root context

    char c;

    while (day12_data.get(c)) {
        if (c == '{') {
            contexts.push_back({0, true, false});
        }
        else if (c == '[') {
            contexts.push_back({0, false, false});
        }
        else if (c == '}' || c == ']') {
            Context finished = contexts.back();
            contexts.pop_back();

            if (finished.isObject && finished.hasRed) {
                // Ignore
            }
            else {
                contexts.back().sum += finished.sum;
            }
        }
        else if (c == '"') {
            string str = readString(day12_data);

            if (str == "red" && contexts.back().isObject) {
                contexts.back().hasRed = true;
            }
        }
        else if (isdigit(c) || c == '-') {
            int number = readNumber(day12_data, c);
            contexts.back().sum += number;
        }
    }

    cout << contexts.back().sum << endl;

    day12_data.close();
}

int readNumber(ifstream& file, char firstChar) {
    string number;
    number += firstChar;

    char c;
    while (file.get(c)) {
        if (isdigit(c)) {
            number += c;
        }
        else {
            file.unget();
            break;
        }
    }

    return stoi(number);
}

string readString(ifstream& file) {
    string str;
    char c;

    while (file.get(c)) {
        if (c == '"') {
            break;
        }
        str += c;
    }

    return str;
}