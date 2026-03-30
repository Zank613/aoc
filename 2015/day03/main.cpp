#include <iostream>
#include <fstream>
#include <map>
#include <set>

struct Location {
    int vertical;
    int horizontal;
    Location() : vertical(0), horizontal(0) {}
    Location(int v, int h) : vertical(v), horizontal(h) {}

    bool operator<(const Location& other) const {
        if (vertical != other.vertical) return vertical < other.vertical;
        return horizontal < other.horizontal;
    }
};

using namespace std;

void day03();

int main() {
    day03();
}

void day03() {
    ifstream day03_data("data/2015/day03.txt");
    if (!day03_data) {
        cout << "Could not open file.";
        exit(-1);
    }

    map<Location, int> santa_visited;
    map<Location, int> robot_visited;
    Location santa_location;
    Location robot_location;
    santa_visited[santa_location]++;
    robot_visited[robot_location]++;

    bool santaTurn = true;

    char sign;
    while (day03_data.get(sign)) {
        if (santaTurn) {
            switch (sign) {
                case 'v':
                    santa_location.vertical--; break;
                case '^':
                    santa_location.vertical++; break;
                case '>':
                    santa_location.horizontal++; break;
                case '<':
                    santa_location.horizontal--; break;
            }
            santa_visited[santa_location]++;
            santaTurn = false;
        } else {
            switch (sign) {
                case 'v':
                    robot_location.vertical--; break;
                case '^':
                    robot_location.vertical++; break;
                case '>':
                    robot_location.horizontal++; break;
                case '<':
                    robot_location.horizontal--; break;
            }
            robot_visited[robot_location]++;
            santaTurn = true;
        }
    }

    set<Location> unique_houses;

    for (auto it : robot_visited) {
        unique_houses.insert(it.first);
    }

    for (auto it : santa_visited) {
        unique_houses.insert(it.first);
    }

    //cout << "Houses with at least one present: " << santa_visited.size() << endl;
    cout << "Houses with at least one present with Robot Santa: " << unique_houses.size() << endl;
    day03_data.close();
}