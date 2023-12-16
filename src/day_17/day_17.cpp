#include "day_17/day_17.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day17::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 17 Part 1 | {}", input_root.string());
    }

    std::string Day17::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 17 Part 2 | {}", input_root.string());
    }

} // aoc
