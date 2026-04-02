#include <cstdint>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

using namespace std;

void day07();
uint16_t evaluate(const string& wire, const map<string, string>& instructions, map<string, uint16_t>& cache);

int main() {
    day07();
    return 0;
}

void day07() {
    ifstream day07_data("data/2015/day07.txt");

    if (!day07_data) {
        cout << "Could not open file";
        exit(-1);
    }

    map<string, string> instructions;
    string line;
    while (getline(day07_data, line)) {
        istringstream iss(line);
        string first, second, arrow, to;

        iss >> first;

        if (first == "NOT") {
            iss >> second >> arrow >> to;
            instructions[to] = first + " " + second;
        }
        else {
            iss >> second;
            if (second == "->") {
                iss >> to;
                instructions[to] = first;
            } else {
                string third;
                iss >> third >> arrow >> to;
                instructions[to] = first + " " + second + " " + third;
            }
        }
    }

    map<string, uint16_t> cache;
    cache["b"] = static_cast<uint16_t>(46065); // PART TWO
    cout << evaluate("a", instructions, cache) << endl;
}

uint16_t evaluate(const string& wire, const map<string, string>& instructions, map<string, uint16_t>& cache){
    if (auto it = cache.find(wire); it != cache.end()) {
        return it->second;
    }

    if (isdigit(wire[0])) {
        return static_cast<uint16_t>(stoi(wire));
    }

    auto it = instructions.find(wire);
    istringstream iss(it->second);

    string first, opcode, second;
    iss >> first;

    uint16_t result = 0;

    if (!(iss>>opcode)) {
        result = evaluate(first, instructions, cache);
    }
    else if (first == "NOT") {
        result = static_cast<uint16_t>(~evaluate(opcode, instructions, cache));
    } else {
        iss >> second;

        uint16_t left = evaluate(first, instructions, cache);
        uint16_t right = evaluate(second, instructions, cache);

        if (opcode == "AND") result = left & right;
        else if (opcode == "OR") result = left | right;
        else if (opcode == "LSHIFT") result = left << right;
        else if (opcode == "RSHIFT") result = left >> right;
    }

    cache[wire] = result;
    return result;
}