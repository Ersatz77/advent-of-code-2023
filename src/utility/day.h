#ifndef AOC_UTILITIES_DAY_H
#define AOC_UTILITIES_DAY_H

#include <cstdint>
#include <filesystem>
#include <string>

namespace aoc
{
    // Results for a day
    struct DayResults
    {
        std::string part_1_output;
        uint64_t part_1_runtime;

        std::string part_2_output;
        uint64_t part_2_runtime;
    };

    // An abstract class for a day
    class Day
    {
    public:
        Day() = default;
        virtual ~Day() = default;

        virtual std::string part_1(const std::filesystem::path& path) const = 0;
        virtual std::string part_2(const std::filesystem::path& path) const = 0;

        DayResults run(const std::filesystem::path& path) const;
    };

} // aoc

#endif // !AOC_UTILITIES_DAY_H
