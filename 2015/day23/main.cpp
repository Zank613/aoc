
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>

int main() {
    std::cout << "AOC 2015 - Day 23\n";

    std::ifstream day23_input("data/2015/day23.txt");

    if (!day23_input) {
        std::cerr << "Could not open file!\n";
        return -1;
    }

    std::vector<std::string> program;
    std::string line;

    // Load the entire program into memory.
    while (std::getline(day23_input, line)) {
        if (!line.empty()) {
            program.push_back(line);
        }
    }

    uint64_t a = 1;
    uint64_t b = 0;

    int ip = 0;

    while (ip >= 0 && ip < static_cast<int>(program.size())) {
        std::istringstream stream(program[ip]);

        std::string opcode;
        stream >> opcode;

        if (opcode == "hlf" ||
            opcode == "tpl" ||
            opcode == "inc") {

            char reg;
            stream >> reg;

            uint64_t& r = (reg == 'a') ? a : b;

            if (opcode == "hlf") {
                r /= 2;
            }
            else if (opcode == "tpl") {
                r *= 3;
            }
            else {
                ++r;
            }

            ++ip;
        }
        else if (opcode == "jmp") {
            int offset;
            stream >> offset;

            ip += offset;
        }
        else if (opcode == "jie" || opcode == "jio") {
            char reg;
            char comma;
            int offset;

            stream >> reg >> comma >> offset;

            uint64_t& r = (reg == 'a') ? a : b;

            if (opcode == "jie" && r % 2 == 0) {
                ip += offset;
            }
            else if (opcode == "jio" && r == 1) {
                ip += offset;
            }
            else {
                ++ip;
            }
        }
        else {
            std::cerr << "Unknown instruction: "
                      << program[ip] << '\n';
            return -1;
        }
    }

    std::cout << "Register a: " << a << '\n';
    std::cout << "Register b: " << b << '\n';

    return 0;
}
