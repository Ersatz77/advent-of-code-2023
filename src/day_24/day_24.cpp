#include "day_24/day_24.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day24::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 24 Part 1 | {}", input_root.string());
    }

    std::string Day24::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 24 Part 2 | {}", input_root.string());
    }

} // aoc
