#include "day_23/day_23.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day23::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 23 Part 1 | {}", input_root.string());
    }

    std::string Day23::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 23 Part 2 | {}", input_root.string());
    }

} // aoc
