#pragma once

#include <fstream>
#include <vector>
#include <string>

namespace aal {

    /**
     * @brief Opens a file for reading.
     * @param path Path to the file.
     * @return An open input file stream.
     * @throws std::runtime_error If the file cannot be opened.
     */
    std::ifstream openFile(const std::string& path);

    /**
     * @brief Reads every line from a file.
     * @param path Path to the file.
     * @return Vector containing all lines, including empty lines.
     * @throws std::runtime_error If the file cannot be read.
     */
    std::vector<std::string> readLines(const std::string& path);

    /**
     * @brief Reads an entire file into a string.
     * @param path Path to the file.
     * @return Complete file contents.
     * @throws std::runtime_error If the file cannot be read.
     */
    std::string readText(const std::string& path);

    /**
     * @brief Reads whitespace-separated integers from a file.
     * @param path Path to the file.
     * @return Vector containing the integers.
     * @throws std::runtime_error If the file cannot be read
     * or contains invalid integer input.
     */
    std::vector<int> readIntegers(const std::string& path);

}