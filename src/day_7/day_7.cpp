#include "day_7/day_7.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day7::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 7 Part 1 | {}", input_root.string());
    }

    std::string Day7::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 7 Part 2 | {}", input_root.string());
    }

} // aoc
