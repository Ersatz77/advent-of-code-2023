#include "day_2/day_2.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day2::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 2 Part 1 | {}", input_root.string());
    }

    std::string Day2::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 2 Part 2 | {}", input_root.string());
    }

} // aoc
