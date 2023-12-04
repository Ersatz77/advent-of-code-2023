#include "day_1/day_1.h"
#include "day_2/day_2.h"
#include "day_3/day_3.h"
#include "day_4/day_4.h"
#include "day_5/day_5.h"
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

    solutions.push_back(std::make_unique<aoc::Day1>());
    solutions.push_back(std::make_unique<aoc::Day2>());
    solutions.push_back(std::make_unique<aoc::Day3>());
    solutions.push_back(std::make_unique<aoc::Day4>());
    solutions.push_back(std::make_unique<aoc::Day5>());

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
