#include "day_11/day_11.h"

#include "utility/io.h"
#include "utility/math.h"
#include "utility/vec.h"

#include "fmt/format.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <vector>

namespace aoc
{
    using Galaxy = Vec2<int64_t>;

    struct Universe
    {
        std::vector<Galaxy> galaxies;
        std::vector<int64_t> empty_rows;
        std::vector<int64_t> empty_columns;
    };

    static std::vector<int64_t> find_empty_rows(const std::vector<std::string>& grid)
    {
        std::vector<int64_t> empty_rows;
        for (size_t y = 0; y < grid.size(); ++y)
        {
            const std::string& line = grid[y];
            if (std::count(line.begin(), line.end(), '#') == 0)
            {
                empty_rows.push_back(y);
            }
        }

        return empty_rows;
    }

    static std::vector<int64_t> find_empty_columns(const std::vector<std::string>& grid)
    {
        std::vector<int64_t> empty_columns;
        for (size_t x = 0; x < grid.front().size(); ++x)
        {
            size_t galaxies = 0;
            for (size_t y = 0; y < grid.size(); ++y)
            {
                if (grid[y][x] == '#')
                {
                    ++galaxies;
                }
            }

            if (galaxies == 0)
            {
                empty_columns.push_back(x);
            }
        }

        return empty_columns;
    }

    static Universe parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<std::string> grid;
        std::vector<Galaxy> galaxies;

        size_t y = 0;
        for (std::string line; std::getline(file, line); )
        {
            for (size_t x = 0; x < line.length(); ++x)
            {
                if (line[x] == '#')
                {
                    galaxies.emplace_back(x, y);
                }
            }

            grid.push_back(line);
            ++y;
        }

        std::vector<int64_t> empty_rows = find_empty_rows(grid);
        std::vector<int64_t> empty_columns = find_empty_columns(grid);

        return { galaxies, empty_rows, empty_columns };
    }

    static int64_t all_shortest_paths(const Universe& universe, const int64_t cosmic_expansion)
    {
        int64_t distance = 0;
        for (size_t i = 0; i < universe.galaxies.size(); ++i)
        {
            for (size_t j = i + 1; j < universe.galaxies.size(); ++j)
            {
                const Galaxy& start = universe.galaxies[i];
                const Galaxy& end = universe.galaxies[j];

                auto empty_rows = std::ranges::filter_view(universe.empty_rows,
                    [&start, &end](const int64_t y) { return (y >= start.y && y <= end.y) || (y <= start.y && y >= end.y); });
                auto empty_columns = std::ranges::filter_view(universe.empty_columns,
                    [&start, &end](const int64_t x) { return (x >= start.x && x <= end.x) || (x <= start.x && x >= end.x); });

                distance += manhattan_distance(start, end);
                distance += std::ranges::distance(empty_rows) * (cosmic_expansion - 1);
                distance += std::ranges::distance(empty_columns) * (cosmic_expansion - 1);
            }
        }

        return distance;
    }

    std::string Day11::part_1(const std::filesystem::path& input_root) const
    {
        Universe universe = parse_input(input_root / "day_11.txt");

        int64_t paths_sum = all_shortest_paths(universe, 2);

        return fmt::format("Day 11 Part 1 | Sum of the shortest paths between galaxies: {}", paths_sum);
    }

    std::string Day11::part_2(const std::filesystem::path& input_root) const
    {
        Universe universe = parse_input(input_root / "day_11.txt");

        int64_t paths_sum = all_shortest_paths(universe, 1000000);

        return fmt::format("Day 11 Part 2 | Sum of the shortest paths between galaxies: {}", paths_sum);
    }

} // aoc
