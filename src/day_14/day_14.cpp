#include "day_14/day_14.h"

#include "utility/io.h"
#include "utility/utility.h"

#include "fmt/format.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <unordered_map>

namespace aoc
{
    using ReflectorDish = std::vector<std::string>;

    static ReflectorDish parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        ReflectorDish dish;
        for (std::string line; std::getline(file, line); )
        {
            dish.push_back(line);
        }

        return dish;
    }

    static void transpose_clockwise(ReflectorDish& dish)
    {
        ReflectorDish transposed(dish.front().length());
        for (size_t x = 0; x < dish.front().length(); ++x)
        {
            for (size_t y = 0; y < dish.size(); ++y)
            {
                transposed[x] += dish[dish.size() - 1 - y][x];
            }
        }

        dish = transposed;
    }

    static void transpose_counterclockwise(ReflectorDish& dish)
    {
        ReflectorDish transposed(dish.front().length());
        for (size_t x = 0; x < dish.front().length(); ++x)
        {
            for (size_t y = 0; y < dish.size(); ++y)
            {
                transposed[x] += dish[y][dish.front().size() - 1 - x];
            }
        }

        dish = transposed;
    }

    static void tilt(ReflectorDish& dish)
    {
        for (std::string& row : dish)
        {
            row = std::ranges::split_view(row, '#')
                | std::views::transform([](auto s) { std::sort(s.begin(), s.end(), std::greater<char>());  return s; })
                | std::views::join_with('#')
                | std::ranges::to<std::string>();
        }
    }

    static void spin_cycle(ReflectorDish& dish, const int64_t cycles)
    {
        std::unordered_map<ReflectorDish, int64_t> cache;
        for (int64_t i = 0; i < cycles; ++i)
        {
            tilt(dish);
            transpose_clockwise(dish);
            tilt(dish);
            transpose_clockwise(dish);
            tilt(dish);
            transpose_clockwise(dish);
            tilt(dish);
            transpose_clockwise(dish);

            if (cache.contains(dish))
            {
                int64_t cycle_start = cache.at(dish);
                int64_t cycle_length = i - cycle_start;

                i = cycles - ((cycles - cycle_start) % cycle_length);
                cache.clear();
            }

            cache[dish] = i;
        }
    }

    static int64_t total_load(const ReflectorDish& dish)
    {
        int64_t total_load = 0;
        for (size_t y = 0; y < dish.size(); ++y)
        {
            for (const char c : dish[y])
            {
                if (c == 'O')
                {
                    total_load += dish.size() - y;
                }
            }
        }

        return total_load;
    }

    std::string Day14::part_1(const std::filesystem::path& input_root) const
    {
        ReflectorDish dish = parse_input(input_root / "day_14.txt");

        transpose_counterclockwise(dish);
        tilt(dish);
        transpose_clockwise(dish);
        
        int64_t load = total_load(dish);

        return fmt::format("Day 14 Part 1 | Total load on the northern support beams: {}", load);
    }

    std::string Day14::part_2(const std::filesystem::path& input_root) const
    {
        ReflectorDish dish = parse_input(input_root / "day_14.txt");

        transpose_counterclockwise(dish);
        spin_cycle(dish, 1000000000);
        transpose_clockwise(dish);

        int64_t load = total_load(dish);

        return fmt::format("Day 14 Part 2 | Total load after 1000000000 spin cycles: {}", load);
    }

} // aoc
