#include "day_6/day_6.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day6::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 6 Part 1 | {}", input_root.string());
    }

    std::string Day6::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 6 Part 2 | {}", input_root.string());
    }

} // aoc
