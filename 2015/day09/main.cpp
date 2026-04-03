#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

void day09();

int main() {
    day09();
    return 0;
}

void day09() {
    ifstream day09_data("data/2015/day09.txt");

    if (!day09_data) {
        cout << "Could not open file.";
        exit(-1);
    }

    string line;
    map<std::pair<string, string>, int> distances;
    set<string> cities;
    while (getline(day09_data, line)) {
        stringstream iss(line);
        string firstCity, to, secondCity, equal;
        int distance;

        iss >> firstCity >> to >> secondCity >> equal >> distance;

        distances[{firstCity, secondCity}] = distance;
        distances[{secondCity, firstCity}] = distance;
        cities.insert(firstCity);
        cities.insert(secondCity);
    }

    vector<string> cityList(cities.begin(), cities.end());
    sort(cityList.begin(), cityList.end());

    int shortest = INT_MAX;
    int longest = INT_MIN;

    do {
        int total = 0;

        for (int i = 0; i < cityList.size() - 1; i++) {
            total += distances[{cityList[i], cityList[i+1]}];
        }

        if (total < shortest) {
            shortest = total;
        }

        if (total > longest) {
            longest = total;
        }
    } while (next_permutation(cityList.begin(), cityList.end()));

    /*
    for (const auto& it : distances) {
        cout << it.first.first << " : " << it.first.second <<
            " = " << it.second << endl;
    }
    */

    cout << shortest << endl;
    cout << longest << endl;

    day09_data.close();
}