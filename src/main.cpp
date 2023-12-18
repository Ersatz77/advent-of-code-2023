#include "day_1/day_1.h"
#include "day_2/day_2.h"
#include "day_3/day_3.h"
#include "day_4/day_4.h"
#include "day_5/day_5.h"
#include "day_6/day_6.h"
#include "day_7/day_7.h"
#include "day_8/day_8.h"
#include "day_9/day_9.h"
#include "day_10/day_10.h"
#include "day_11/day_11.h"
#include "day_12/day_12.h"
#include "day_13/day_13.h"
#include "day_14/day_14.h"
#include "day_15/day_15.h"
#include "day_16/day_16.h"
#include "day_17/day_17.h"
#include "day_18/day_18.h"
#include "day_19/day_19.h"
#include "utility/day.h"

#include "fmt/format.h"

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Expected a path to a folder with inputs\n";
        return 1;
    }

    const std::filesystem::path input_root(argv[1]);

    // Create solutions
    std::vector<std::unique_ptr<aoc::Day>> solutions;
    solutions.reserve(25);

    // solutions.push_back(std::make_unique<aoc::Day1>());
    // solutions.push_back(std::make_unique<aoc::Day2>());
    // solutions.push_back(std::make_unique<aoc::Day3>());
    // solutions.push_back(std::make_unique<aoc::Day4>());
    // solutions.push_back(std::make_unique<aoc::Day5>());
    // solutions.push_back(std::make_unique<aoc::Day6>());
    // solutions.push_back(std::make_unique<aoc::Day7>());
    // solutions.push_back(std::make_unique<aoc::Day8>());
    // solutions.push_back(std::make_unique<aoc::Day9>());
    // solutions.push_back(std::make_unique<aoc::Day10>());
    // solutions.push_back(std::make_unique<aoc::Day11>());
    // solutions.push_back(std::make_unique<aoc::Day12>());
    // solutions.push_back(std::make_unique<aoc::Day13>());
    // solutions.push_back(std::make_unique<aoc::Day14>());
    // solutions.push_back(std::make_unique<aoc::Day15>());
    // solutions.push_back(std::make_unique<aoc::Day16>());
    // solutions.push_back(std::make_unique<aoc::Day17>());
    // solutions.push_back(std::make_unique<aoc::Day18>());
    solutions.push_back(std::make_unique<aoc::Day19>());

    try
    {
        // Run solutions
        uint64_t total_runtime = 0;
        for (const auto& day : solutions)
        {
            const aoc::DayResults results = day->run(input_root);
            total_runtime += results.part_1_runtime + results.part_2_runtime;

            std::cout << fmt::format("{} | Runtime: {}ms\n{} | Runtime: {}ms\n",
                results.part_1_output, results.part_1_runtime, results.part_2_output, results.part_2_runtime);
        }

        std::cout << fmt::format("{}\nTotal runtime: {}ms\n", std::string(80, '-'), total_runtime);
    }
    catch (const std::exception& ex)
    {
        std::cerr << fmt::format("Error: {}\n", ex.what());
        return 1;
    }

    return 0;
}
