#pragma once

#include <string>
#include <vector>

namespace aal {

    /**
     * @brief Splits a string using a delimiter.
     * @param text String to split.
     * @param delimiter Character separating the fields.
     * @return Vector containing the fields, including empty ones.
     */
    std::vector<std::string> split(const std::string& text, char delimiter);

    /**
     * @brief Removes leading and trailing whitespace.
     * @param text String to trim.
     * @return Trimmed string.
     */
    std::string trim(const std::string& text);

    /**
     * @brief Replaces every occurrence of a substring.
     * @param text Original string.
     * @param from Substring to replace.
     * @param to Replacement substring.
     * @return Modified string.
     * @throws std::invalid_argument If from is empty.
     */
    std::string replaceAll(std::string text, const std::string& from, const std::string& to);

    /**
     * @brief Extracts signed integers from a string.
     * @param text String containing integers.
     * @return Vector containing the extracted integers.
     * @throws std::out_of_range If an integer exceeds the range of int.
     */
    std::vector<int> extractIntegers(const std::string& text);

    /**
     * @brief Checks whether a string begins with a prefix.
     * @param text String to examine.
     * @param prefix Expected prefix.
     * @return True if the string begins with the prefix.
     */
    bool startsWith(const std::string& text, const std::string& prefix);

    /**
     * @brief Checks whether a string ends with a suffix.
     * @param text String to examine.
     * @param suffix Expected suffix.
     * @return True if the string ends with the suffix.
     */
    bool endsWith(const std::string& text, const std::string& suffix);

}