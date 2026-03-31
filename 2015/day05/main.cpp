#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isNicePart1(const string& word);
bool isNicePart2(const string& word);
void day05();

int main() {
    day05();
}

bool isNicePart1(const string& word) {
    int vowelCount = 0;
    bool doubleLetter = false;
    bool forbidden = false;

    for (size_t i = 0; i < word.size(); i++) {
        char c = word[i];

        switch (c) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                vowelCount++;
                break;
        }

        if (i > 0) {
            if (word[i] == word[i - 1]) {
                doubleLetter = true;
            }

            char prev = word[i - 1];
            if ((prev == 'a' && c == 'b') ||
                (prev == 'c' && c == 'd') ||
                (prev == 'p' && c == 'q') ||
                (prev == 'x' && c == 'y')) {
                forbidden = true;
            }
        }
    }

    return vowelCount >= 3 && doubleLetter && !forbidden;
}

bool isNicePart2(const string& word) {
    bool hasPairTwice = false;
    bool hasRepeatWithGap = false;

    for (size_t i = 0; i + 1 < word.size(); i++) {
        string pair = word.substr(i, 2);

        for (size_t j = i + 2; j + 1 < word.size(); j++) {
            if (word.substr(j, 2) == pair) {
                hasPairTwice = true;
                break;
            }
        }

        if (hasPairTwice) {
            break;
        }
    }

    for (size_t i = 0; i + 2 < word.size(); i++) {
        if (word[i] == word[i + 2]) {
            hasRepeatWithGap = true;
            break;
        }
    }

    return hasPairTwice && hasRepeatWithGap;
}

void day05() {
    ifstream day05_data("data/2015/day05.txt");
    if (!day05_data) {
        cout << "Could not open file." << endl;
        exit(-1);
    }

    int nice_strings_part1 = 0;
    int nice_strings_part2 = 0;
    string word;

    while (getline(day05_data, word)) {
        if (isNicePart1(word)) {
            nice_strings_part1++;
        }

        if (isNicePart2(word)) {
            nice_strings_part2++;
        }
    }

    cout << "Nice strings Part 1: " << nice_strings_part1 << endl;
    cout << "Nice strings Part 2: " << nice_strings_part2 << endl;
}