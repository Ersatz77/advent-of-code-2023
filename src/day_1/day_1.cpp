#include "day_1/day_1.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day1::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 1 Part 1 | {}", input_root.string());
    }

    std::string Day1::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 1 Part 2 | {}", input_root.string());
    }

} // aoc
