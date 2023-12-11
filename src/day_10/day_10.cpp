#include "day_10/day_10.h"

#include "utility/io.h"
#include "utility/vec.h"

#include "fmt/format.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace aoc
{
    enum PipeDirection : uint8_t
    {
        NONE  = 0x0,
        NORTH = 0x1,
        SOUTH = 0x2,
        EAST  = 0x4,
        WEST  = 0x8
    };

    using PipeBits = uint8_t;
    struct PipePresets
    {
        static const PipeBits vertical = PipeDirection::NORTH | PipeDirection::SOUTH;
        static const PipeBits horizontal = PipeDirection::EAST | PipeDirection::WEST;
        static const PipeBits south_to_east = PipeDirection::SOUTH | PipeDirection::EAST;
        static const PipeBits south_to_west = PipeDirection::SOUTH | PipeDirection::WEST;
        static const PipeBits north_to_east = PipeDirection::NORTH | PipeDirection::EAST;
        static const PipeBits north_to_west = PipeDirection::NORTH | PipeDirection::WEST;
        static const PipeBits empty = PipeDirection::NONE;
    };

    struct PipeField
    {
        std::unordered_map<Point, PipeBits> pipes;
        Point start;
    };

    static PipeBits get_starting_shape(const PipeField& field)
    {
        const PipeBits left = field.pipes.at(field.start + make_point(-1, 0));
        const PipeBits right = field.pipes.at(field.start + make_point(1, 0));
        const PipeBits up = field.pipes.at(field.start + make_point(0, 1));
        const PipeBits down = field.pipes.at(field.start + make_point(0, -1));

        if (up & PipeDirection::SOUTH && down & PipeDirection::NORTH)
        {
            return PipePresets::vertical;
        }
        else if (left & PipeDirection::EAST && right & PipeDirection::WEST)
        {
            return PipePresets::horizontal;
        }
        else if (up & PipeDirection::SOUTH && left & PipeDirection::EAST)
        {
            return PipePresets::south_to_west;
        }
        else if (up & PipeDirection::SOUTH && right & PipeDirection::WEST)
        {
            return PipePresets::south_to_east;
        }
        else if (down & PipeDirection::NORTH && left & PipeDirection::EAST)
        {
            return PipePresets::north_to_west;
        }
        else if (down & PipeDirection::NORTH && right & PipeDirection::WEST)
        {
            return PipePresets::north_to_east;
        }

        return PipePresets::empty;
    }

    static PipeField parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        Point start;
        std::unordered_map<Point, PipeBits> pipes;

        size_t y = 0;
        for (std::string line; std::getline(file, line); )
        {

            for (size_t x = 0; x < line.length(); ++x)
            {
                switch (line[x])
                {
                    case 'S':
                        start = make_point(x, y);
                        break;
                    case '|':
                        pipes[make_point(x, y)] = PipePresets::vertical;
                        break;
                    case '-':
                        pipes[make_point(x, y)] = PipePresets::horizontal;
                        break;
                    case 'L':
                        pipes[make_point(x, y)] = PipePresets::south_to_east;
                        break;
                    case 'J':
                        pipes[make_point(x, y)] = PipePresets::south_to_west;
                        break;
                    case 'F':
                        pipes[make_point(x, y)] = PipePresets::north_to_east;
                        break;
                    case '7':
                        pipes[make_point(x, y)] = PipePresets::north_to_west;
                        break;
                    case '.':
                        pipes[make_point(x, y)] = PipePresets::empty;
                        break;
                }
            }

            ++y;
        }

        PipeField field = { pipes, start };
        field.pipes[start] = get_starting_shape(field);

        return field;
    }

    static bool can_move_to(const PipeField& field, const Point& current_pos, const Point& next_pos)
    {
        if (!field.pipes.contains(next_pos))
        {
            return false;
        }

        const PipeBits current = field.pipes.at(current_pos);
        const PipeBits next = field.pipes.at(next_pos);
        const Point delta = next_pos - current_pos;

        if (delta.x == 1 && (current & PipeDirection::EAST))
        {
            return next & PipeDirection::WEST;
        }
        else if (delta.x == -1 && (current & PipeDirection::WEST))
        {
            return next & PipeDirection::EAST;
        }
        if (delta.y == 1 && (current & PipeDirection::NORTH))
        {
            return next & PipeDirection::SOUTH;
        }
        else if (delta.y == -1 && (current & PipeDirection::SOUTH))
        {
            return next & PipeDirection::NORTH;
        }

        return false;
    }

    static std::pair<std::vector<Point>, int> walk_loop(const PipeField& field)
    {
        std::vector<Point> shape;
        int furthest = 0;

        std::unordered_set<Point> visited;
        std::queue<std::pair<Point, int>> to_visit;
        to_visit.emplace(field.start, 0);
        while (!to_visit.empty())
        {
            const auto [pos, cost] = to_visit.front();
            to_visit.pop();

            if (visited.contains(pos))
            {
                continue;
            }

            visited.insert(pos);
            shape.push_back(pos);
            furthest = std::max(cost, furthest);

            for (const auto& adj : pos.adjacent_cardinal())
            {
                if (!visited.contains(adj) && can_move_to(field, pos, adj))
                {
                    to_visit.emplace(adj, cost + 1);
                    break;
                }
            }
        }

        return { shape, (furthest / 2) + 1};
    }

    static int loop_area(const std::vector<Point>& loop)
    {
        int area = 0;
        for (size_t i = 0; i < loop.size(); ++i)
        {
            Point current = loop[i];
            Point next = loop[(i + 1) % loop.size()];
            area += static_cast<int>((current.x * next.y) - (current.y * next.x));
        }

        area = std::abs(area) / 2;
        return (area - static_cast<int>(loop.size()) / 2) + 1;
    }

    std::string Day10::part_1(const std::filesystem::path& input_root) const
    {
        PipeField field = parse_input(input_root / "day_10.txt");
        
        auto [_, furthest] = walk_loop(field);

        return fmt::format("Day 10 Part 1 | Furthest position in the loop: {}", furthest);
    }

    std::string Day10::part_2(const std::filesystem::path& input_root) const
    {
        PipeField field = parse_input(input_root / "day_10.txt");

        auto [loop, _] = walk_loop(field);
        int area = loop_area(loop);

        return fmt::format("Day 10 Part 2 | Tiles enclosed by the loop: {}", area);
    }

} // aoc
