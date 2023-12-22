#include "day_22/day_22.h"

#include "utility/io.h"
#include "utility/math.h"
#include "utility/string.h"
#include "utility/vec.h"

#include "fmt/format.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace aoc
{
    using SandBrickConnection = std::unordered_map<int, std::unordered_set<int>>;

    struct SandBrick
    {
        int id;
        Point3D begin;
        Point3D end;
    };

    static std::vector<SandBrick> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<SandBrick> bricks;
        int id = 0;
        for (std::string line; std::getline(file, line); )
        {
            std::vector<std::string> raw_brick = split(line, '~');
            std::vector<std::string> raw_brick_begin = split(raw_brick.front(), ',');
            std::vector<std::string> raw_brick_end = split(raw_brick.back(), ',');

            double x0 = std::stod(raw_brick_begin[0]);
            double y0 = std::stod(raw_brick_begin[1]);
            double z0 = std::stod(raw_brick_begin[2]);

            double x1 = std::stod(raw_brick_end[0]);
            double y1 = std::stod(raw_brick_end[1]);
            double z1 = std::stod(raw_brick_end[2]);

            Point3D begin = { x0, y0, z0 };
            Point3D end = { x1, y1, z1 };
            
            bricks.emplace_back(id, begin, end);
            ++id;
        }

        std::sort(bricks.begin(), bricks.end(), [](const SandBrick& a, const SandBrick& b) { return a.begin.z < b.begin.z; });
        return bricks;
    }

    static bool can_lower(std::unordered_map<Point3D, int>& occupied, const SandBrick& brick)
    {
        for (const Point& p : cartesian_product(brick.begin.x, brick.begin.y, brick.end.x, brick.end.y))
        {
            if (occupied.contains(make_point_3d(p.x, p.y, brick.begin.z - 1)))
            {
                return false;
            }
        }

        return brick.begin.z > 1;
    }

    static std::pair<std::vector<SandBrick>, std::unordered_map<Point3D, int>> settle_bricks(const std::vector<SandBrick>& bricks)
    {
        std::vector<SandBrick> settled;
        std::unordered_map<Point3D, int> occupied;
        for (SandBrick brick : bricks)
        {
            while (can_lower(occupied, brick))
            {
                brick.begin.z -= 1;
                brick.end.z -= 1;
            }

            settled.push_back(brick);
            for (const Point3D& p : cartesian_product(brick.begin, brick.end))
            {
                occupied[p] = brick.id;
            }
        }

        return { settled, occupied };
    }

    static std::pair<SandBrickConnection, SandBrickConnection> get_connections(const std::vector<SandBrick>& settled, const std::unordered_map<Point3D, int>& occupied)
    {
        SandBrickConnection above;
        SandBrickConnection below;
        for (const SandBrick& brick : settled)
        {
            for (const Point& p : cartesian_product(brick.begin.x, brick.begin.y, brick.end.x, brick.end.y))
            {
                auto it = occupied.find(make_point_3d(p.x, p.y, brick.begin.z - 1));
                if (it != occupied.end())
                {
                    above[it->second].insert(brick.id);
                    below[brick.id].insert(it->second);
                }
            }
        }

        return { above, below };
    }

    static void disintegrate(std::unordered_set<int>& will_fall, const SandBrickConnection& above, const SandBrickConnection& below, const int brick_id)
    {
        if (will_fall.contains(brick_id))
        {
            return;
        }

        will_fall.insert(brick_id);

        auto parents_it = above.find(brick_id);
        if (parents_it != above.end())
        {
            for (const int parent_id : parents_it->second)
            {
                auto below_it = below.find(parent_id);
                if (below_it != below.end() && std::all_of(below_it->second.begin(), below_it->second.end(), [&will_fall](const int i) { return will_fall.contains(i); }))
                {
                    disintegrate(will_fall, above, below, parent_id);
                }
            }
        }
    }

    std::string Day22::part_1(const std::filesystem::path& input_root) const
    {
        auto bricks = parse_input(input_root / "day_22.txt");

        auto [settled, occupied] = settle_bricks(bricks);
        auto [above, below] = get_connections(settled, occupied);

        int64_t could_disintegrate = 0;
        for (const SandBrick& brick : settled)
        {
            std::unordered_set<int> will_fall;
            disintegrate(will_fall, above, below, brick.id);
            if (will_fall.size() == 1)
            {
                ++could_disintegrate;
            }
        }

        return fmt::format("Day 22 Part 1 | Bricks that could be disintegrated: {}", could_disintegrate);
    }

    std::string Day22::part_2(const std::filesystem::path& input_root) const
    {
        auto bricks = parse_input(input_root / "day_22.txt");

        auto [settled, occupied] = settle_bricks(bricks);
        auto [above, below] = get_connections(settled, occupied);

        int64_t would_fall = 0;
        for (const SandBrick& brick : settled)
        {
            std::unordered_set<int> will_fall;
            disintegrate(will_fall, above, below, brick.id);
            would_fall += will_fall.size() - 1;
        }

        return fmt::format("Day 22 Part 2 | Sum of the number of bricks that would fall: {}", would_fall);
    }

} // aoc
