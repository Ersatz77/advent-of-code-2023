#include "day_21/day_21.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day21::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 21 Part 1 | {}", input_root.string());
    }

    std::string Day21::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 21 Part 2 | {}", input_root.string());
    }

} // aoc
