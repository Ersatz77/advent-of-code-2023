#include "day_9/day_9.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day9::part_1(const std::filesystem::path& input_root) const
    {
        return std::format("Day 9 Part 1 | {}", input_root.string());
    }

    std::string Day9::part_2(const std::filesystem::path& input_root) const
    {
        return std::format("Day 9 Part 2 | {}", input_root.string());
    }

} // aoc
