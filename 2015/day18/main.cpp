#include <iostream>
#include <fstream>
using namespace std;

struct Light {
    bool on = false;

    void turn_off() {on = false;}
    void turn_on() {on = true;}
};

#define SIZE 100
#define STEPS 100

int countNeighbours(const Light (*lights)[SIZE], int row, int col);
void turnOnCorners(Light (*lights)[SIZE]);

int main() {
    cout << "Day 18 - AOC 2015" << endl;

    ifstream day18_data("data/2015/day18.txt");
    if (!day18_data) {
        cout << "Could not open file!";
        return -1;
    }

    Light (*lights)[SIZE] = new Light[SIZE][SIZE];
    Light (*nextLights)[SIZE] = new Light[SIZE][SIZE];

    int row = 0;
    string line;
    while (getline(day18_data, line)) {
        for (int col = 0; col < SIZE; col++) {
            if (line[col] == '#') {
                lights[row][col].turn_on();
            }
            else {
                lights[row][col].turn_off();
            }
        }
        row++;
    }

    turnOnCorners(lights);

    for (int step = 0; step < STEPS; step++) {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                int neighbours = countNeighbours(lights, row, col);

                if (lights[row][col].on && (neighbours == 2 || neighbours == 3)) {
                    nextLights[row][col].turn_on();
                }
                else if (!lights[row][col].on && neighbours == 3) {
                    nextLights[row][col].turn_on();
                }
                else {
                    nextLights[row][col].turn_off();
                }
            }
        }

        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                lights[row][col] = nextLights[row][col];
            }
        }
        turnOnCorners(lights);
    }

    int count = 0;
    for (int row1 = 0; row1 < SIZE; row1++) {
        for (int col = 0; col < SIZE; col++) {
            if (lights[row1][col].on) {
                count++;
            }
        }
    }

    cout << "This many lights are on: " << count << endl;

    delete[] lights;
    lights = nullptr;
    delete[] nextLights;
    nextLights = nullptr;
    return 0;
}

int countNeighbours(const Light (*lights)[SIZE], int row, int col) {
    int count = 0;

    for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
        for (int colOffset = -1; colOffset <= 1; colOffset++) {
            if (rowOffset == 0 && colOffset == 0) {
                continue;
            }

            int neighbourRow = row + rowOffset;
            int neighbourCol = col + colOffset;

            if (neighbourRow < 0 || neighbourRow >= SIZE) {continue;}
            if (neighbourCol < 0 || neighbourCol >= SIZE) {continue;}

            if (lights[neighbourRow][neighbourCol].on) {
                count++;
            }
        }
    }

    return count;
}

void turnOnCorners(Light (*lights)[100]) {
    lights[0][0].turn_on();
    lights[0][SIZE - 1].turn_on();
    lights[SIZE - 1][0].turn_on();
    lights[SIZE - 1][SIZE - 1].turn_on();
}
