#include "day_22/day_22.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day22::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 22 Part 1 | {}", input_root.string());
    }

    std::string Day22::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 22 Part 2 | {}", input_root.string());
    }

} // aoc
