#include <iostream>
#include <cstdint>

int main() {
    std::cout << "AOC 2015 - Day 25" << std::endl;

    const uint64_t row = 2947;
    const uint64_t column = 3029;

    const uint64_t diagonal = row + column - 1;
    const uint64_t position =
        diagonal * (diagonal - 1) / 2 + column;

    uint64_t code = 20151125;

    for (uint64_t i = 1; i < position; i++) {
        code = (code * 252533) % 33554393;
    }

    std::cout << "Position: " << position << std::endl;
    std::cout << "Code: " << code << std::endl;

    return 0;
}
