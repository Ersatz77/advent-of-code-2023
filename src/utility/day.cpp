#include "utility/day.h"

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <string>

namespace aoc
{
    DayResults Day::run(const std::filesystem::path& input_root) const
    {
        auto part_1_begin = std::chrono::high_resolution_clock::now();
        std::string part_1_output = part_1(input_root);
        auto part_1_end = std::chrono::high_resolution_clock::now();

        auto part_2_begin = std::chrono::high_resolution_clock::now();
        std::string part_2_output = part_2(input_root);
        auto part_2_end = std::chrono::high_resolution_clock::now();

        uint64_t part_1_runtime = std::chrono::duration_cast<std::chrono::milliseconds>(part_1_end - part_1_begin).count();
        uint64_t part_2_runtime = std::chrono::duration_cast<std::chrono::milliseconds>(part_2_end - part_2_begin).count();

        return { part_1_output, part_1_runtime, part_2_output, part_2_runtime };
    }

} // aoc
