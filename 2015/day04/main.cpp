#include <iostream>
#include "md5.h"

using namespace std;

void day04();

int main() {
    day04();
}

void day04() {
    string key = "iwrupvqb";
    int i = 1;

    MD5 md5;
    while (true) {
        string input = key + to_string(i);
        string hash = md5(input);

        if (hash.substr(0, 6) == "000000") {
            cout << i << endl;
            break;
        }

        i++;
    }
}