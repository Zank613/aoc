#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void q1();

int main() {
    q1();
}

void q1() {
    ifstream q1Data("data/2015/day01.txt");

    if (!q1Data) {
        cout << "File could not be opened";
        exit(-1);
    }

    char sign;
    int floor = 0;
    int position = 0;
    cout << "Starting loop." << endl;
    while (q1Data.get(sign)) {
        ++position;
        //cout << "Doing loop" << endl;
        switch (sign) {
            case '(' :
                floor += 1; break;
            case ')' :
                floor -= 1; break;
        }
        if (floor < 0) {
            cout << "Position when entering basement is: " << position << endl;
            break;
        }
    }
    cout << floor << endl;
    q1Data.close();
}