#include <aal/strings.h>

#include <sstream>
#include <algorithm>
#include <cctype>
#include <charconv>
#include <stdexcept>

namespace aal {

    std::vector<std::string> split(const std::string& text, char delimiter) {
        std::vector<std::string> result;
        std::istringstream iss(text);

        std::string token;

        while (std::getline(iss, token, delimiter)) {
            result.push_back(token);
        }

        // Preserve empty fields, including trailing ones.
        if (text.empty() || text.back() == delimiter) {
            result.push_back("");
        }

        return result;
    }

    std::string trim(const std::string& text) {
        size_t start = 0;
        size_t end = text.length();

        while (start < end && std::isspace(static_cast<unsigned char>(text[start]))) {
            start++;
        }

        while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1]))) {
            end--;
        }

        return text.substr(start, end - start);
    }

    std::string replaceAll(std::string text, const std::string& from, const std::string& to) {
        if (from.empty()) {
            throw std::invalid_argument("Replacement pattern cannot be empty");
        }

        size_t pos = 0;

        while ((pos = text.find(from, pos)) != std::string::npos) {
            text.replace(pos, from.length(), to);
            pos += to.length();
        }

        return text;
    }

    std::vector<int> extractIntegers(const std::string& text) {
        std::vector<int> numbers;

        size_t i = 0;

        while (i < text.length()) {
            if (!std::isdigit(static_cast<unsigned char>(text[i])) &&
                text[i] != '-' && text[i] != '+') {
                i++;
                continue;
            }

            size_t start = i;

            if (text[i] == '-' || text[i] == '+') {
                i++;
            }

            if (i >= text.length() ||
                !std::isdigit(static_cast<unsigned char>(text[i]))) {
                continue;
            }

            const char* begin = text.data() + start;
            const char* end = text.data() + text.length();

            // std::from_chars accepts a minus sign but not a plus sign.
            if (*begin == '+') {
                begin++;
            }

            int number = 0;
            auto result = std::from_chars(begin, end, number);

            if (result.ec == std::errc::result_out_of_range) {
                throw std::out_of_range("Integer exceeds int range");
            }

            if (result.ec != std::errc{}) {
                throw std::runtime_error("Could not parse integer");
            }

            numbers.push_back(number);
            i = static_cast<size_t>(result.ptr - text.data());
        }

        return numbers;
    }

    bool startsWith(const std::string& text, const std::string& prefix) {
        if (prefix.length() > text.length()) {
            return false;
        }

        return text.compare(0, prefix.length(), prefix) == 0;
    }

    bool endsWith(const std::string& text, const std::string& suffix) {
        if (suffix.length() > text.length()) {
            return false;
        }

        return text.compare(text.length() - suffix.length(), suffix.length(), suffix) == 0;
    }

}