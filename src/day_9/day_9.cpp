#include "day_9/day_9.h"

#include "utility/io.h"
#include "utility/string.h"

#include "fmt/format.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace aoc
{
    static std::vector<std::vector<int64_t>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<std::vector<int64_t>> report;
        for (std::string line; std::getline(file, line); )
        {
            std::vector<int64_t> reading;
            for (const std::string& raw_value : split(line, ' '))
            {
                reading.push_back(std::stoll(raw_value));
            }

            report.push_back(reading);
        }

        return report;
    }

    static int64_t next_in_sequence(const std::vector<int64_t>& seq, const bool part_2 = false)
    {
        // Get the difference between all numbers in the sequence
        std::vector<int64_t> diff;
        for (size_t i = 1; i < seq.size(); ++i)
        {
            diff.push_back(seq[i] - seq[i - 1]);
        }

        // Return `0` if all numbers in the differences sequence are `0`
        if (std::all_of(seq.begin(), seq.end(), [](const int64_t v) { return v == 0; }))
        {
            return 0;
        }

        // If part 2 is enabled, return the number that comes before the start of the sequence
        if (part_2)
        {
            return diff.front() - next_in_sequence(diff, part_2);
        }
        
        // Return the next number in the sequence
        return diff.back() + next_in_sequence(diff, part_2);
    }

    std::string Day9::part_1(const std::filesystem::path& input_root) const
    {
        std::vector<std::vector<int64_t>> report = parse_input(input_root / "day_9.txt");

        int64_t sum = 0;
        for (const auto& reading : report)
        {
            sum += reading.back() + next_in_sequence(reading);
        }

        return std::format("Day 9 Part 1 | Sum of predicted readings: {}", sum);
    }

    std::string Day9::part_2(const std::filesystem::path& input_root) const
    {
        std::vector<std::vector<int64_t>> report = parse_input(input_root / "day_9.txt");

        int64_t sum = 0;
        for (const auto& reading : report)
        {
            sum += reading.front() - next_in_sequence(reading, true);
        }

        return std::format("Day 9 Part 2 | Sum of predicted past readings: {}", sum);
    }

} // aoc
