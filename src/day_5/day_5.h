#ifndef AOC_2023_DAY_5_H
#define AOC_2023_DAY_5_H

#include "utility/day.h"

#include <filesystem>
#include <string>

namespace aoc
{
    class Day5 : public Day
    {
        virtual std::string part_1(const std::filesystem::path& input_root) const override;
        virtual std::string part_2(const std::filesystem::path& input_root) const override;
    };

} // aoc

#endif // !AOC_2023_DAY_5_H
