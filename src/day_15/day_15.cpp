#include "day_15/day_15.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day15::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 15 Part 1 | {}", input_root.string());
    }

    std::string Day15::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 15 Part 2 | {}", input_root.string());
    }

} // aoc
