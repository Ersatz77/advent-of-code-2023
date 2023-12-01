#include "day_1/day_1.h"

#include "utility/io.h"

#include "fmt/format.h"

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

    static int digit_at(const std::string& line, const size_t idx)
    {
        // If `idx` is a number, immediately return it
        if (isdigit(line[idx]))
            return line[idx] - '0';

        // Otherwise, check if a word can be read
        if ((idx + 2) < line.length() && line.substr(idx, 3) == "one")
        {
            return 1;
        }
        else if ((idx + 2) < line.length() && line.substr(idx, 3) == "two")
        {
            return 2;
        }
        else if ((idx + 4) < line.length() && line.substr(idx, 5) == "three")
        {
            return 3;
        }
        else if ((idx + 3) < line.length() && line.substr(idx, 4) == "four")
        {
            return 4;
        }
        else if ((idx + 3) < line.length() && line.substr(idx, 4) == "five")
        {
            return 5;
        }
        else if ((idx + 2) < line.length() && line.substr(idx, 3) == "six")
        {
            return 6;
        }
        else if ((idx + 4) < line.length() && line.substr(idx, 5) == "seven")
        {
            return 7;
        }
        else if ((idx + 4) < line.length() && line.substr(idx, 5) == "eight")
        {
            return 8;
        }
        else if ((idx + 3) < line.length() && line.substr(idx, 4) == "nine")
        {
            return 9;
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
