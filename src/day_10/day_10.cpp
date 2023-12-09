#include "day_10/day_10.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day10::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 10 Part 1 | {}", input_root.string());
    }

    std::string Day10::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 10 Part 2 | {}", input_root.string());
    }

} // aoc
