#include "day_4/day_4.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day4::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 4 Part 1 | {}", input_root.string());
    }

    std::string Day4::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 4 Part 2 | {}", input_root.string());
    }

} // aoc
