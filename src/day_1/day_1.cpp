#include "day_1/day_1.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <array>
#include <cctype>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <limits>
#include <string>
#include <vector>

namespace aoc
{
    static std::vector<std::string> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<std::string> lines;
        for (std::string line; std::getline(file, line); )
        {
            lines.push_back(line);
        }

        return lines;
    }

    static int digit_at(const std::string& line, const size_t start_idx)
    {
        // If `start_idx` is at a number, immediately return it
        if (isdigit(line[start_idx]))
        {
            return line[start_idx] - '0';
        }

        // Otherwise, try to read a word
        constexpr std::array<std::string_view, 10> digit_words = {
            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
        };

        for (size_t digit = 1; digit < 10; ++digit)
        {
            size_t i = start_idx;
            size_t j = 0;
            while (i < line.length() && j < digit_words[digit].length())
            {
                if (line[i] != digit_words[digit][j])
                {
                    break;
                }

                ++i;
                ++j;
            }

            if (j == digit_words[digit].length())
            {
                return static_cast<int>(digit);
            }
        }

        return std::numeric_limits<int>::min();
    }

    std::string Day1::part_1(const std::filesystem::path& input_root) const
    {
        std::vector<std::string> lines = parse_input(input_root / "day_1.txt");

        int calibration_sum = 0;
        for (const std::string& line : lines)
        {
            int left = std::numeric_limits<int>::min();
            int right = std::numeric_limits<int>::min();
            for (const char c : line)
            {
                if (!std::isdigit(c))
                {
                    continue;
                }

                right = (c - '0');
                if (left < 0)
                {
                    left = (c - '0');
                }
            }

            calibration_sum += (left * 10) + right;
        }

        return fmt::format("Day 1 Part 1 | Sum of all calibration values: {}", calibration_sum);
    }

    std::string Day1::part_2(const std::filesystem::path& input_root) const
    {
        std::vector<std::string> lines = parse_input(input_root / "day_1.txt");

        int calibration_sum = 0;
        for (const std::string& line : lines)
        {
            int left = std::numeric_limits<int>::min();
            int right = std::numeric_limits<int>::min();
            for (size_t i = 0; i < line.length(); ++i)
            {
                int value = digit_at(line, i);
                if (value < 0)
                {
                    continue;
                }

                right = value;
                if (left < 0)
                {
                    left = value;
                }
            }

            calibration_sum += (left * 10) + right;
        }

        return fmt::format("Day 1 Part 2 | Sum of all calibration values: {}", calibration_sum);
    }

} // aoc
