#include <iostream>
#include <string>

using namespace std;

void day10();
string lookAndSay(const string& number, int times);

int main() {
    day10();
    return 0;
}

void day10() {
    string number = "1113222113";
    cout << lookAndSay(number, 50).length(); // 40 times for part 1
}

string lookAndSay(const string& number, int times) {
    if (times <= 0) {
        return number;
    }

    string next;

    char current = number[0];
    int count = 1;

    for (int i = 1; i < number.size(); i++) {
        if (number[i] == current) {
            count++;
        }
        else {
            next += to_string(count);
            next += current;

            current = number[i];
            count = 1;
        }
    }

    next += to_string(count);
    next += current;

    return lookAndSay(next, times-1);
}

