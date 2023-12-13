#include "day_13/day_13.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <vector>

using RockPattern = std::vector<std::string>;
using RockPatternRowBits = std::bitset<64>;

namespace aoc
{
    static std::vector<RockPattern> parse_input(const std::filesystem::path& path)
    {
        std::vector<RockPattern> patterns;
        std::ifstream file = open_file(path);

        while (file)
        {
            RockPattern pattern;
            for (std::string line; std::getline(file, line) && !line.empty(); )
            {
                pattern.push_back(line);
            }

            patterns.push_back(pattern);
        }

        return patterns;
    }

    static RockPattern transpose(const RockPattern& pattern)
    {
        RockPattern transposed(pattern.front().size());
        for (size_t x = 0; x < pattern.front().size(); ++x)
        {
            for (size_t y = 0; y < pattern.size(); ++y)
            {
                transposed[x] += pattern[y][x];
            }
        }

        return transposed;
    }

    static size_t difference_between(const RockPatternRowBits& left, const RockPatternRowBits& right)
    {
        // Returns the number of bits the pair doesn't have in common
        // Ex: 0111 ^ 0011 == 0100
        return (left ^ right).count();
    }

    static int64_t summarize_pattern(const RockPattern& pattern, const int64_t allowed_smudges = 0)
    {
        std::vector<RockPatternRowBits> rows(pattern.size());
        for (const auto& [i, row] : std::ranges::enumerate_view(pattern))
        {
            for (const char c : row)
            {
                rows[i] <<= 1;
                rows[i] |= (c == '#');
            }
        }

        for (size_t i = 1; i < rows.size(); ++i)
        {
            // Create ranges that go in opposite direction from a potential reflection line
            auto going_left = std::ranges::subrange(rows.begin(), rows.begin() + i) | std::views::reverse;
            auto going_right = std::ranges::subrange(rows.begin() + i, rows.end());

            // Total number of differences at this line of reflection
            int64_t diff = std::ranges::fold_left(std::ranges::zip_transform_view(difference_between, going_left, going_right), 0, std::plus<int64_t>());
            if (diff == allowed_smudges)
            {
                return i;
            }
        }

        return 0;
    }

    std::string Day13::part_1(const std::filesystem::path& input_root) const
    {
        std::vector<RockPattern> patterns = parse_input(input_root / "day_13.txt");

        int64_t summary = 0;
        for (const RockPattern& pattern : patterns)
        {
            summary += summarize_pattern(pattern) * 100;
            summary += summarize_pattern(transpose(pattern));
        }

        return fmt::format("Day 13 Part 1 | Summary of rock patterns: {}", summary);
    }

    std::string Day13::part_2(const std::filesystem::path& input_root) const
    {
        std::vector<RockPattern> patterns = parse_input(input_root / "day_13.txt");

        int64_t summary = 0;
        for (const RockPattern& pattern : patterns)
        {
            summary += summarize_pattern(pattern, 1) * 100;
            summary += summarize_pattern(transpose(pattern), 1);
        }

        return fmt::format("Day 13 Part 2 | Summary of rock patterns: {}", summary);
    }

} // aoc
