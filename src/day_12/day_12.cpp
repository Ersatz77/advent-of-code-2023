#include "day_12/day_12.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day12::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 12 Part 1 | {}", input_root.string());
    }

    std::string Day12::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 12 Part 2 | {}", input_root.string());
    }

} // aoc
