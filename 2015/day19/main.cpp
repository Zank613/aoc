#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <cctype>

struct Replacement {
    std::string from;
    std::string to;
};

int main() {
    std::cout << "AOC 2015 - Day 19" << std::endl;

    std::ifstream day19_data("data/2015/day19.txt");
    if (!day19_data) {
        std::cout << "Could not open file.";
        return -1;
    }

    std::vector<Replacement> replacements;
    std::string medicine;

    std::string line;
    bool readingMedicine = false;

    while (std::getline(day19_data, line)) {
        if (line.empty()) {
            readingMedicine = true;
            continue;
        }

        if (!readingMedicine) {
            std::istringstream iss(line);

            std::string from;
            std::string arrow;
            std::string to;

            iss >> from >> arrow >> to;

            replacements.push_back({from, to});
        }
        else {
            medicine = line;
        }
    }

    std::set<std::string> generatedMolecules;
    for (const Replacement& replacement : replacements) {
        std::size_t position = medicine.find(replacement.from);
        while (position != std::string::npos) {
            std::string generated = medicine;

            generated.replace(
                position,
                replacement.from.length(),
                replacement.to
            );

            generatedMolecules.insert(generated);

            position = medicine.find(replacement.from, position+1);
        }
    }

    std::cout << generatedMolecules.size() << std::endl;

    int token_count = 0;
    int rn_count = 0;
    int ar_count = 0;
    int y_count = 0;

    for (std::size_t i = 0; i < medicine.length(); i++) {
        std::string token(1, medicine[i]);

        if (i+1 < medicine.length() && std::islower(static_cast<unsigned char>(medicine[i+1]))) {
            token += medicine[i+1];
            i++;
        }

        token_count++;
        if (token == "Rn") {
            rn_count++;
        } else if (token == "Ar") {
            ar_count++;
        } else if (token == "Y") {
            y_count++;
        }
    }

    int steps = token_count - rn_count - ar_count - (2 * y_count) - 1;

    std::cout << "Fewest fabrication steps: " << steps << std::endl;

    return 0;
}