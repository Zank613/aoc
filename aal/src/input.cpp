#include <aal/input.h>

#include <stdexcept>
#include <sstream>

namespace aal {

    std::ifstream openFile(const std::string& path) {
        std::ifstream file(path);

        if (!file) {
            throw std::runtime_error("Could not open file: " + path);
        }

        return file;
    }

    std::vector<std::string> readLines(const std::string& path) {
        std::ifstream file = openFile(path);

        std::vector<std::string> lines;
        std::string line;

        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }

            lines.push_back(line);
        }

        if (file.bad()) {
            throw std::runtime_error("Could not read file: " + path);
        }

        return lines;
    }

    std::string readText(const std::string& path) {
        std::ifstream file = openFile(path);
        std::ostringstream buffer;

        buffer << file.rdbuf();

        if (file.bad() || buffer.fail()) {
            throw std::runtime_error("Could not read file: " + path);
        }

        return buffer.str();
    }

    std::vector<int> readIntegers(const std::string& path) {
        std::ifstream file = openFile(path);

        std::vector<int> numbers;
        int number;

        while (file >> number) {
            numbers.push_back(number);
        }

        if (!file.eof()) {
            throw std::runtime_error("Invalid integer input: " + path);
        }

        return numbers;
    }

}