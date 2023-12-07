#include "day_8/day_8.h"

#include "fmt/format.h"

#include <filesystem>
#include <string>

namespace aoc
{
    std::string Day8::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 8 Part 1 | {}", input_root.string());
    }

    std::string Day8::part_2(const std::filesystem::path & input_root) const
    {
        return fmt::format("Day 8 Part 2 | {}", input_root.string());
    }

} // aoc
