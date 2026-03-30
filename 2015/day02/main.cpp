#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Cuboid {
    int l, w, h;
    Cuboid(int l, int w, int h) : l(l), w(w), h(h) {}

private:
    int calculateBaseWrapper() {
        return (2*l*w) + (2*w*h) + (2*h*l);
    }
    int calculateExtraWrapper() {
        if (l >= w && l >= h) {
            return w * h;
        } else if (w >= l && w >= h) {
            return l * h;
        } else {
            return l * w;
        }
    }

    int calculateBaseRibbon() {
        if (l >= w && l >= h) {
            return w*2 + h*2;
        } else if (w >= l && w >= h) {
            return l*2 + h*2;
        } else {
            return l*2 + w*2;
        }
    }

    int calculateBowRibbon() {
        return l*w*h;
    }

public:
    int calculateWrapper() {
        return calculateBaseWrapper() + calculateExtraWrapper();
    }

    int calculateRibbon() {
        return calculateBaseRibbon() + calculateBowRibbon();
    }
};

void q2();

using namespace std;

int main() {
    q2();
}

void q2() {
    ifstream q2Data("data/2015/day02.txt");

    if (!q2Data) {
        cout << "File could not be opened.";
        exit(-1);
    }

    int totalWrapper = 0;
    int totalRibbon= 0;

    string line;
    while (getline(q2Data, line)) {
        istringstream iss(line);

        int l, w, h;
        char x;

        iss >> l >> x >> w >> x >> h;
        Cuboid temp(l, w, h);
        totalWrapper += temp.calculateWrapper();
        totalRibbon += temp.calculateRibbon();
    }

    cout << "Total Wrapper required is: " << totalWrapper << endl;
    cout << "Total Ribbon required is: " << totalRibbon << endl;
    q2Data.close();
}