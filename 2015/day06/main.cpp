#include <iostream>
#include <fstream>
#include <mmintrin.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void day06();
void day06_2();
std::string getUntil(std::string&, char);
std::string getAfter(std::string&, char);

struct Light {
    bool on = false;

    void toggle() {
        on = !on;
    }

    void turn_off() {
        on = false;
    }

    void turn_on() {
        on = true;
    }
};

struct BrightLight {
    int brightness = 0;

    void toggle() {
        brightness += 2;
    }

    void turn_off() {
        if (brightness > 0) {
            brightness -= 1;
        }
    }

    void turn_on() {
        brightness += 1;
    }
};

int main() {
    day06();
    day06_2();
    return 0;
}

void day06() {
    ifstream day06_data("data/2015/day06.txt");

    if (!day06_data) {
        cout << "Could not open file.";
        exit(-1);
    }

    string line;
    Light (*lights)[1000] = new Light[1000][1000];
    while (getline(day06_data, line)) {
        istringstream iss(line);
        vector<string> tokens;
        string t;

        while (iss >> t) {
            tokens.push_back(t);
        }

        if (tokens[0] == "toggle") {
            int start_x = stoi(getUntil(tokens[1], ','));
            int start_y = stoi(getAfter(tokens[1], ','));
            int end_x = stoi(getUntil(tokens[3], ','));
            int end_y = stoi(getAfter(tokens[3], ','));

            for (int i = start_x; i <= end_x; i++) {
                for (int j = start_y; j <= end_y; j++) {
                    lights[i][j].toggle();
                }
            }
        }
        else if (tokens[0] == "turn") {
            int start_x = stoi(getUntil(tokens[2], ','));
            int start_y = stoi(getAfter(tokens[2], ','));
            int end_x = stoi(getUntil(tokens[4], ','));
            int end_y = stoi(getAfter(tokens[4], ','));

            for (int i = start_x; i <= end_x; i++) {
                for (int j = start_y; j <= end_y; j++) {
                    if (tokens[1] == "on")
                        lights[i][j].turn_on();
                    else
                        lights[i][j].turn_off();
                }
            }
        }


    }

    int howManyLightsAreOn = 0;
    for (int i = 0; i < 1000; i++) {
        for (const auto& light : lights[i]) {
            if (light.on) howManyLightsAreOn++;
        }
    }
    cout << howManyLightsAreOn << endl;
    delete [] lights;
    lights = nullptr;
    day06_data.close();
}

std::string getUntil(std::string& str, char delimiter) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == delimiter) {
            return str.substr(0, i);
        }
    }

    return str.substr(0); // return rest if delimiter not found
}

std::string getAfter(std::string& str, char delimiter) {
    auto pos = str.find(delimiter);
    return str.substr(pos+1);
}

void day06_2() {
    ifstream day06_data("data/2015/day06.txt");

    if (!day06_data) {
        cout << "Could not open file.";
        exit(-1);
    }

    string line;
    BrightLight (*lights)[1000] = new BrightLight[1000][1000];

    while (getline(day06_data, line)) {
        istringstream iss(line);
        vector<string> tokens;
        string t;

        while (iss >> t) {
            tokens.push_back(t);
        }

        if (tokens[0] == "toggle") {
            int start_x = stoi(getUntil(tokens[1], ','));
            int start_y = stoi(getAfter(tokens[1], ','));
            int end_x = stoi(getUntil(tokens[3], ','));
            int end_y = stoi(getAfter(tokens[3], ','));

            for (int i = start_x; i <= end_x; i++) {
                for (int j = start_y; j <= end_y; j++) {
                    lights[i][j].toggle();
                }
            }
        }
        else if (tokens[0] == "turn") {
            int start_x = stoi(getUntil(tokens[2], ','));
            int start_y = stoi(getAfter(tokens[2], ','));
            int end_x = stoi(getUntil(tokens[4], ','));
            int end_y = stoi(getAfter(tokens[4], ','));

            for (int i = start_x; i <= end_x; i++) {
                for (int j = start_y; j <= end_y; j++) {
                    if (tokens[1] == "on")
                        lights[i][j].turn_on();
                    else
                        lights[i][j].turn_off();
                }
            }
        }
    }

    long long totalBrightness = 0;
    for (int i = 0; i < 1000; i++) {
        for (const auto& light : lights[i]) {
            totalBrightness += light.brightness;
        }
    }
    cout << totalBrightness << endl;
    delete [] lights;
    lights = nullptr;
    day06_data.close();
}