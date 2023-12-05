#include "day_5/day_5.h"

#include "day_5/almanac.h"
#include "utility/io.h"

#include "fmt/format.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

namespace aoc
{
    static std::pair<std::vector<int64_t>, std::vector<AlmanacCategoryMapper>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        // Get seeds
        file.ignore(7);

        std::string line;
        std::getline(file, line);

        std::istringstream seed_line_stream(line);
        std::vector<int64_t> seeds;
        for (int64_t seed = 0; seed_line_stream >> seed; )
        {
            seeds.push_back(seed);
        }
        
        // Get category mappers
        std::getline(file, line);

        std::vector<AlmanacCategoryMapper> mappers;
        while (file)
        {
            AlmanacCategoryMapper mapper;
            file >> mapper;
            mappers.push_back(mapper);
        }

        return { seeds, mappers };
    }

    std::string Day5::part_1(const std::filesystem::path& input_root) const
    {
        auto [seeds, mappers] = parse_input(input_root / "day_5.txt");

        for (const auto& mapper : mappers)
        {
            for (auto& seed : seeds)
            {
                seed = mapper.map(seed);
            }
        }

        int64_t lowest_location = *std::min_element(seeds.begin(), seeds.end());

        return fmt::format("Day 5 Part 1 | Lowest location: {}", lowest_location);
    }

    std::string Day5::part_2(const std::filesystem::path& input_root) const
    {
        auto [seeds, mappers] = parse_input(input_root / "day_5.txt");

        std::vector<AlmanacRange> seed_ranges;
        for (size_t i = 0; i < seeds.size(); i += 2)
        {
            seed_ranges.emplace_back(seeds[i], seeds[i] + seeds[i + 1]);
        }

        for (const auto& mapper : mappers)
        {
            std::vector<AlmanacRange> next_seed_ranges;
            for (const auto& seed_range : seed_ranges)
            {
                auto next = mapper.map_range(seed_range);
                next_seed_ranges.insert(next_seed_ranges.end(), next.begin(), next.end());
            }

            seed_ranges = next_seed_ranges;
        }

        std::sort(seed_ranges.begin(), seed_ranges.end());
        int64_t lowest_location = seed_ranges.front().begin;

        return fmt::format("Day 5 Part 2 | Lowest location: {}", lowest_location);
    }

} // aoc
