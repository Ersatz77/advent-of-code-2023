#include "day_11/day_11.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day11::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 11 Part 1 | {}", input_root.string());
    }

    std::string Day11::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 11 Part 2 | {}", input_root.string());
    }

} // aoc
