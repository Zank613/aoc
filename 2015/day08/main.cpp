#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void day08();

int main() {
    day08();
    return 0;
}

void day08() {
    ifstream day08_data("data/2015/day08.txt");

    if (!day08_data) {
        cout << "Could not open file";
        exit(-1);
    }

    string line;
    int charactersLiteral = 0;
    int charactersMemory = 0;
    int charactersEncoded = 0;
    while (getline(day08_data, line)) {
        charactersLiteral += static_cast<int>(line.size());
        charactersEncoded += 2;

        for (int i = 1; i < line.size() - 1; i++) {
            char c = line.at(i);

            if (c == '\\') {
                char d = line.at(i+1);
                if (d == '\\' || d == '\"') {
                    charactersMemory++;
                    i += 1;
                }
                else if (d == 'x') {
                    charactersMemory++;
                    i += 3;
                }
            } else {
                charactersMemory++;
            }
        }

        for (char c : line) {
            if (c == '"' || c == '\\') {
                charactersEncoded += 2;
            }
            else {
                charactersEncoded += 1;
            }
        }
    }

    cout << charactersLiteral - charactersMemory << endl;
    cout << charactersEncoded - charactersLiteral << endl;
}