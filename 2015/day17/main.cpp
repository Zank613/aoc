#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int countWays(const vector<int>& containers, int index, int remaining);
void countMinimumWays(const vector<int>& containers, int index, int remaining, int used, int& minimumUsed, int& waysWithMinimum);

int main() {
    cout << "Day 17 - AOC 2015" << endl;

    ifstream day17_data("data/2015/day17.txt");
    if (!day17_data) {cout << "Could not open file!"; return -1;}

    vector<int> containers;
    string line;
    while (getline(day17_data, line)) {
        containers.push_back(stoi(line));
    }

    cout << "Different combinations: " << countWays(containers, 0, 150) << endl;

    int minimumUsed = INT_MAX;
    int waysWithMinimum = 0;
    countMinimumWays(containers, 0, 150, 0, minimumUsed, waysWithMinimum);

    cout << "Ways with minimum: " << waysWithMinimum << endl;

    return 0;
}

int countWays(const vector<int> &containers, int index, int remaining) {
    if (remaining == 0) {
        return 1;
    }

    if (remaining < 0) {
        return 0;
    }

    if (index == containers.size()) {
        return 0;
    }

    int skip = countWays(containers, index + 1, remaining);
    int use = countWays(containers, index + 1, remaining - containers[index]);

    return skip + use;
}

void countMinimumWays(const vector<int> &containers, int index, int remaining, int used, int &minimumUsed, int &waysWithMinimum) {
    if (remaining == 0)
    {
        if (used < minimumUsed)
        {
            minimumUsed = used;
            waysWithMinimum = 1;
        }
        else if (used == minimumUsed)
        {
            waysWithMinimum++;
        }

        return;
    }

    if (remaining < 0)
        return;

    if (index == containers.size())
        return;

    // Skip this container
    countMinimumWays(containers, index + 1, remaining, used, minimumUsed, waysWithMinimum);

    // Use this container
    countMinimumWays(containers, index + 1, remaining - containers[index], used + 1, minimumUsed, waysWithMinimum);
}