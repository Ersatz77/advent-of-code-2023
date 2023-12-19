#include "day_20/day_20.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day20::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 20 Part 1 | {}", input_root.string());
    }

    std::string Day20::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 20 Part 2 | {}", input_root.string());
    }

} // aoc
