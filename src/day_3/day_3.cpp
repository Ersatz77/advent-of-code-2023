#include "day_3/day_3.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day3::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 3 Part 1 | {}", input_root.string());
    }

    std::string Day3::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 3 Part 2 | {}", input_root.string());
    }

} // aoc
