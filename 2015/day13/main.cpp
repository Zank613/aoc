#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>

using namespace std;

void day13();

int main() {
    day13();
    return 0;
}

void day13() {
    ifstream day13_data("data/2015/day13.txt");

    if (!day13_data) {
        cout << "Could not open file";
        exit(-1);
    }

    set<string> peopleSet;
    map<pair<string, string>, int> happinessMatrix;
    string line;
    while (getline(day13_data, line)) {
        istringstream iss(line);
        string name, X, operation, secondName;
        int number;

        iss >> name >> X >> operation >> number >> X >> X >> X >> X >> X >> X >> secondName;

        if (operation == "lose") {
            number *= -1;
        }

        // Remove the DOT
        secondName.pop_back();

        happinessMatrix[{name, secondName}] = number;
        peopleSet.insert(name);
        peopleSet.insert(secondName);
    }

    vector<string> people(peopleSet.begin(), peopleSet.end());

    string me = "Me";

    for (const auto& person : people) {
        happinessMatrix[{me, person}] = 0;
        happinessMatrix[{person, me}] = 0;
    }

    people.push_back(me);

    sort(people.begin(), people.end());
    int bestHappiness = INT_MIN;
    string fixed = people[0];
    vector<string> others(people.begin() + 1, people.end());
    sort(others.begin(), others.end());

    do {
        vector<string> seating;
        seating.push_back(fixed);
        int total = 0;

        for (const auto& p : others) {
            seating.push_back(p);
        }

        for (int i = 0; i < seating.size(); i++) {
            int left = (i - 1 + seating.size()) % seating.size();
            int right = (i + 1) % seating.size();
            total += happinessMatrix[{seating[i], seating[left]}];
            total += happinessMatrix[{seating[i], seating[right]}];
        }

        bestHappiness = max(bestHappiness, total);

    } while (next_permutation(others.begin(), others.end()));

    cout << bestHappiness << endl;
    day13_data.close();
}