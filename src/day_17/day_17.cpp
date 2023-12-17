#include "day_17/day_17.h"

#include "utility/io.h"
#include "utility/vec.h"

#include "fmt/format.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace aoc
{
    using CityGrid = std::vector<std::vector<int64_t>>;
    using CityTile = Vec2<int64_t>;

    namespace CityGridDirection
    {
        static const CityTile north = { 0, 1 };
        static const CityTile south = { 0, -1 };
        static const CityTile east = { 1, 0 };
        static const CityTile west = { -1, 0 };

    } // CityGridDirection
    
    static CityGrid parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        CityGrid grid;
        for (std::string line; std::getline(file, line); )
        {
            std::vector<int64_t> row;
            for (const char c : line)
            {
                row.push_back(c - '0');
            }

            grid.push_back(row);
        }

        return grid;
    }

    static bool in_city(const CityGrid& grid, const CityTile& pos)
    {
        return pos.x >= 0 && pos.x < static_cast<int64_t>(grid.front().size())
            && pos.y >= 0 && pos.y < static_cast<int64_t>(grid.size());
    }

    static int64_t walk_city(const CityGrid& grid, const CityTile& end, const int min_chain, const int max_chain)
    {
        using CityGridWalkState = std::tuple<CityTile, CityTile, int, int64_t>;
        using CityGridWalkKey = std::tuple<CityTile, CityTile, int>;

        auto cmp = [](const CityGridWalkState& a, const CityGridWalkState& b) {
            int64_t a_loss = std::get<3>(a);
            int64_t b_loss = std::get<3>(b);
            return a_loss > b_loss;
        };

        std::priority_queue<CityGridWalkState, std::vector<CityGridWalkState>, decltype(cmp)> to_visit(cmp);
        std::unordered_map<CityGridWalkKey, int64_t> cache;

        to_visit.emplace(CityTile(1, 0), CityGridDirection::east, 1, 0);
        to_visit.emplace(CityTile(0, 1), CityGridDirection::north, 1, 0);

        while (!to_visit.empty())
        {
            const auto [current, direction, chain, heat] = to_visit.top();
            to_visit.pop();

            if (!in_city(grid, current))
            {
                continue;
            }

            int64_t heat_loss = grid[current.y][current.x] + heat;
            if (current == end)
            {
                return heat_loss;
            }

            CityGridWalkKey key = std::make_tuple(current, direction, chain);
            if (cache.contains(key) && cache.at(key) <= heat_loss)
            {
                continue;
            }

            cache[key] = heat_loss;

            if (chain >= min_chain)
            {
                if (direction == CityGridDirection::north || direction == CityGridDirection::south)
                {
                    to_visit.emplace(current + CityGridDirection::east, CityGridDirection::east, 1, heat_loss);
                    to_visit.emplace(current + CityGridDirection::west, CityGridDirection::west, 1, heat_loss);
                }
                else if (direction == CityGridDirection::east || direction == CityGridDirection::west)
                {
                    to_visit.emplace(current + CityGridDirection::north, CityGridDirection::north, 1, heat_loss);
                    to_visit.emplace(current + CityGridDirection::south, CityGridDirection::south, 1, heat_loss);
                }
            }

            if (chain < max_chain)
            {
                to_visit.emplace(current + direction, direction, chain + 1, heat_loss);
            }
        }

        return 0;
    }

    std::string Day17::part_1(const std::filesystem::path& input_root) const
    {
        CityGrid grid = parse_input(input_root / "day_17.txt");

        CityTile end(grid.front().size() - 1, grid.size() - 1);
        int64_t heat_loss = walk_city(grid, end, 1, 3);

        return fmt::format("Day 17 Part 1 | Lowest amount of heat loss for a crucible: {}", heat_loss);
    }

    std::string Day17::part_2(const std::filesystem::path& input_root) const
    {
        CityGrid grid = parse_input(input_root / "day_17.txt");

        CityTile end(grid.front().size() - 1, grid.size() - 1);
        int64_t heat_loss = walk_city(grid, end, 4, 10);

        return fmt::format("Day 17 Part 2 | Lowest amount of heat loss for an ultra crucible: {}", heat_loss);
    }

} // aoc
