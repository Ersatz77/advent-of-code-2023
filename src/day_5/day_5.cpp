#include "day_5/day_5.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day5::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 5 Part 1 | {}", input_root.string());
    }

    std::string Day5::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 5 Part 2 | {}", input_root.string());
    }

} // aoc
