#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    cout << "AOC 2015 - Day 20" << endl;

    ifstream day20_data("data/2015/day20.txt");
    if (!day20_data) {
        cout << "Could not open file!";
        return -1;
    }

    int input = 0;
    string line;

    getline(day20_data, line);
    input = stoi(line);

    int limit = input / 10;

    // Part 1
    vector<int> houses(limit + 1, 0);

    for (int elf = 1; elf <= limit; elf++) {
        for (int house = elf; house <= limit; house += elf) {
            houses[house] += elf * 10;
        }
    }

    for (int house = 1; house <= limit; house++) {
        if (houses[house] >= input) {
            cout << "Part 1 - Lowest house: " << house << endl;
            break;
        }
    }

    // Part 2
    vector<int> limited_houses(limit + 1, 0);

    for (int elf = 1; elf <= limit; elf++) {
        for (int visit = 1; visit <= 50; visit++) {
            int house = elf * visit;

            if (house > limit) {
                break;
            }

            limited_houses[house] += elf * 11;
        }
    }

    for (int house = 1; house <= limit; house++) {
        if (limited_houses[house] >= input) {
            cout << "Part 2 - Lowest house: " << house << endl;
            break;
        }
    }

    return 0;
}