#include "day_21/day_21.h"

#include "utility/io.h"
#include "utility/math.h"
#include "utility/vec.h"

#include "fmt/format.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace aoc
{
    using GardenTile = Vec2<int64_t>;

    static std::pair<std::vector<std::string>, GardenTile> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<std::string> garden;
        GardenTile start;

        size_t y = 0;
        for (std::string line; std::getline(file, line); )
        {
            for (size_t x = 0; x < line.length(); ++x)
            {
                if (line[x] == 'S')
                {
                    line[x] = '.';
                    start = { static_cast<int64_t>(x), static_cast<int64_t>(y) };
                }
            }

            garden.push_back(line);

            ++y;
        }

        return { garden, start };
    }

    static bool is_plot(const std::vector<std::string>& garden, const GardenTile& p)
    {
        int64_t width = garden.front().length();
        int64_t height = garden.size();

        int64_t x = euclid_mod(p.x, width);
        int64_t y = euclid_mod(p.y, height);

        return garden[y][x] != '#';
    }

    static int64_t walk_garden(const std::vector<std::string>& garden, const GardenTile& start, const int64_t max_steps)
    {
        int64_t plots = 0;
        std::unordered_set<GardenTile> visited;
        std::queue<std::pair<GardenTile, int64_t>> to_visit;

        visited.insert(start);
        to_visit.emplace(start, max_steps);

        while (!to_visit.empty())
        {
            auto [pos, steps] = to_visit.front();
            to_visit.pop();

            if (steps % 2 == 0)
            {
                ++plots;
            }

            if (steps == 0)
            {
                continue;
            }

            for (const GardenTile& adj : pos.adjacent_cardinal())
            {
                if (is_plot(garden, adj) && !visited.contains(adj))
                {
                    visited.insert(adj);
                    to_visit.emplace(adj, steps - 1);
                }
            }
        }

        return plots;
    }

    std::string Day21::part_1(const std::filesystem::path& input_root) const
    {
        auto [garden, start] = parse_input(input_root / "day_21.txt");

        int64_t visited_plots = walk_garden(garden, start, 64);

        return fmt::format("Day 21 Part 1 | Visited garden plots: {}", visited_plots);
    }

    std::string Day21::part_2(const std::filesystem::path& input_root) const
    {
        auto [garden, start] = parse_input(input_root / "day_21.txt");

        int64_t a0 = walk_garden(garden, start, 0 * 131 + 65);
        int64_t a1 = walk_garden(garden, start, 1 * 131 + 65);
        int64_t a2 = walk_garden(garden, start, 2 * 131 + 65);

        int64_t b0 = a0;
        int64_t b1 = a1 - a0;
        int64_t b2 = a2 - a1;

        constexpr int64_t x = (26501365 - 65) / 131;
        int64_t visited_plots = ((b0 + (b1 * x) + (x * (x - 1) / 2) * (b2 - b1)));

        return fmt::format("Day 21 Part 2 | Visited garden plots: {}", visited_plots);
    }

} // aoc
