#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

#define RACE_DURATION 2503

using namespace std;

class Reindeer {
public:
    string name;
    int speed;
    int speedDuration;
    int restDuration;
    int score;
    Reindeer(string name, const int speed, const int speedDuration, const int restDuration) :
    name(std::move(name)), speed(speed), speedDuration(speedDuration), restDuration(restDuration) {
        score = 0;
    }

    int distanceAt(const int seconds) const {
        const int cycleDuration = speedDuration + restDuration;

        const int fullCycles = seconds / cycleDuration;
        const int remainingTime = seconds % cycleDuration;

        const int flyingTime =
            fullCycles * speedDuration + std::min(remainingTime, speedDuration);

        return flyingTime * speed;
    }

    void addPoint() {score += 1;}
};

int main() {
    std::cout << "AOC 2015 - Day 14\n" << std::endl;

    std::ifstream day14_data("data/2015/day14.txt");

    if (!day14_data) {
        std::cout << "Could not open file!";
        return -1;
    }

    vector<Reindeer> reindeers;
    string line;
    while (getline(day14_data, line)) {
        istringstream iss(line);
        string name, filler;
        int speed, speedDuration, restDuration;
        iss >> name >> filler >> filler >> speed >> filler >> filler
        >> speedDuration >> filler >> filler >> filler >> filler >> filler
        >> filler >> restDuration >> filler;
        reindeers.emplace_back(name, speed, speedDuration, restDuration);
    }

    // for (auto &it : reindeers) {
    //     cout << it.name << endl;
    //     cout << it.speed << endl;
    //     cout << it.speedDuration << endl;
    //     cout << it.restDuration << endl;
    // }

    int best = INT_MIN;
    for (auto &it : reindeers) {
        int currentDist = 0;
        currentDist = it.distanceAt(2503);
        if (best < currentDist) {
            best = currentDist;
        }
    }

    std::cout << "Best: " << best << " ====== PART 1" << endl;

    for (int second = 1; second <= RACE_DURATION; second++) {
        int best1 = 0;

        for (const Reindeer& r : reindeers) {
            int distance = r.distanceAt(second);

            if (distance > best1) {
                best1 = distance;
            }
        }

        for (Reindeer& r : reindeers) {
            int distance = r.distanceAt(second);

            if (distance == best1) {
                r.addPoint();
            }
        }
    }
    int bestScore = INT_MIN;
    for (auto &it : reindeers) {
        if (bestScore < it.score) {
            bestScore = it.score;
        }
    }
    cout << "Best: " << bestScore << " ====== PART 2" << endl;

    return 0;
}