#include "day_16/day_16.h"

#include "utility/io.h"
#include "utility/vec.h"

#include "fmt/format.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <limits>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace aoc
{
    using LightBeam = Vec2<int64_t>;
    using LightNode = std::pair<LightBeam, LightBeam>;
    using LightGrid = std::vector<std::string>;

    namespace LightDirection
    {
        static const LightBeam north = { 0, 1 };
        static const LightBeam south = { 0, -1 };
        static const LightBeam east = { 1, 0 };
        static const LightBeam west = { -1, 0 };

    } // LightDirection

    static LightGrid parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        LightGrid grid;
        for (std::string line; std::getline(file, line); )
        {
            grid.push_back(line);
        }

        return grid;
    }

    static bool in_range(const LightGrid& grid, const LightBeam& beam)
    {
        return beam.x >= 0 && beam.x < static_cast<int64_t>(grid.front().length())
            && beam.y >= 0 && beam.y < static_cast<int64_t>(grid.size());
    }

    static int64_t count_energized(const LightGrid& grid, const LightNode& start)
    {
        std::unordered_set<LightBeam> energized;
        std::unordered_set<LightNode> visited;

        std::queue<LightNode> to_visit;
        to_visit.push(start);
        while (!to_visit.empty())
        {
            const auto node = to_visit.front();
            const auto& [current, direction] = node;
            to_visit.pop();

            // Skip if we're out of the grid
            if (!in_range(grid, current))
            {
                continue;
            }

            // Skip if we've already visited tiles while going in this direction
            if (visited.contains(node))
            {
                continue;
            }

            visited.insert(node);
            energized.insert(current);

            // Queue the next positions
            char tile = grid[current.y][current.x];
            if (tile == '/')
            {
                if (direction.x == 1)
                {
                    to_visit.emplace(current + LightDirection::south, LightDirection::south);
                }
                else if (direction.x == -1)
                {
                    to_visit.emplace(current + LightDirection::north, LightDirection::north);
                }
                else if (direction.y == 1)
                {
                    to_visit.emplace(current + LightDirection::west, LightDirection::west);
                }
                else if (direction.y == -1)
                {
                    to_visit.emplace(current + LightDirection::east, LightDirection::east);
                }
            }
            else if (tile == '\\')
            {
                if (direction.x == 1)
                {
                    to_visit.emplace(current + LightDirection::north, LightDirection::north);
                }
                else if (direction.x == -1)
                {
                    to_visit.emplace(current + LightDirection::south, LightDirection::south);
                }
                else if (direction.y == 1)
                {
                    to_visit.emplace(current + LightDirection::east, LightDirection::east);
                }
                else if (direction.y == -1)
                {
                    to_visit.emplace(current + LightDirection::west, LightDirection::west);
                }
            }
            else if (tile == '|')
            {
                if (direction.x == 1 || direction.x == -1)
                {
                    to_visit.emplace(current + LightDirection::north, LightDirection::north);
                    to_visit.emplace(current + LightDirection::south, LightDirection::south);
                }
                else
                {
                    to_visit.emplace(current + direction, direction);
                }
            }
            else if (tile == '-')
            {
                if (direction.y == 1 || direction.y == -1)
                {
                    to_visit.emplace(current + LightDirection::east, LightDirection::east);
                    to_visit.emplace(current + LightDirection::west, LightDirection::west);
                }
                else
                {
                    to_visit.emplace(current + direction, direction);
                }

            }
            else
            {
                to_visit.emplace(current + direction, direction);
            }
        }

        return energized.size();
    }

    std::string Day16::part_1(const std::filesystem::path& input_root) const
    {
        LightGrid grid = parse_input(input_root / "day_16.txt");

        int64_t energized_tiles = count_energized(grid, { {0, 0}, {1, 0} });

        return fmt::format("Day 16 Part 1 | Energized tiles: {}", energized_tiles);
    }

    std::string Day16::part_2(const std::filesystem::path& input_root) const
    {
        LightGrid grid = parse_input(input_root / "day_16.txt");

        int64_t energized_tile = std::numeric_limits<int64_t>::min();

        for (size_t y = 0; y < grid.size(); ++y)
        {
            LightNode going_east = { LightBeam(0, y), LightDirection::east};
            LightNode going_west = { LightBeam(grid.front().length() - 1, y), LightDirection::west};

            energized_tile = std::max(count_energized(grid, going_east), energized_tile);
            energized_tile = std::max(count_energized(grid, going_west), energized_tile);
        }

        for (size_t x = 0; x < grid.front().length(); ++x)
        {
            LightNode going_north = { LightBeam(x, 0), LightDirection::north };
            LightNode going_south = { LightBeam(x, grid.size() - 1), LightDirection::south };

            energized_tile = std::max(count_energized(grid, going_north), energized_tile);
            energized_tile = std::max(count_energized(grid, going_south), energized_tile);
        }

        return fmt::format("Day 16 Part 2 | Greatest amount of energized tiles: {}", energized_tile);
    }

} // aoc
