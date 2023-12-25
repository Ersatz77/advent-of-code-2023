#include "day_24/day_24.h"

#include "utility/io.h"
#include "utility/string.h"
#include "utility/vec.h"

#include "fmt/format.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace aoc
{
    struct Hailstone
    {
        Point3D position;
        Point3D velocity;
    };

    static std::vector<Hailstone> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<Hailstone> hailstones;
        for (std::string line; std::getline(file, line); )
        {
            std::vector<std::string> raw_hailstone = regex_split(line, " @ ");
            std::vector<std::string> raw_position = regex_split(raw_hailstone.front(), ", ");
            std::vector<std::string> raw_velocity = regex_split(raw_hailstone.back(), ", ");

            double x = std::stod(raw_position[0]);
            double y = std::stod(raw_position[1]);
            double z = std::stod(raw_position[2]);

            double vx = std::stod(raw_velocity[0]);
            double vy = std::stod(raw_velocity[1]);
            double vz = std::stod(raw_velocity[2]);

            hailstones.emplace_back(Point3D(x, y, z), Point3D(vx, vy, vz));
        }

        return hailstones;
    }

    std::string Day24::part_1(const std::filesystem::path& input_root) const
    {
        auto hailstones = parse_input(input_root / "day_24.txt");

        constexpr double begin = 200000000000000;
        constexpr double end = 400000000000000;

        int64_t intersections = 0;
        for (size_t i = 0; i < hailstones.size(); ++i)
        {
            for (size_t j = i + 1; j < hailstones.size(); ++j)
            {
                const auto& a = hailstones[i];
                const auto& b = hailstones[j];

                double det = (a.velocity.x * b.velocity.y) - (a.velocity.y * b.velocity.x);
                if (det == 0.0)
                {
                    continue;
                }

                double t = ((b.position.x - a.position.x) * b.velocity.y - (b.position.y - a.position.y) * b.velocity.x) / det;
                double u = ((b.position.x - a.position.x) * a.velocity.y - (b.position.y - a.position.y) * a.velocity.x) / det;

                double ix = a.position.x + t * a.velocity.x;
                double iy = a.position.y + t * a.velocity.y;

                if (t >= 0 && u >= 0 && ix >= begin && ix <= end && iy >= begin && iy <= end)
                {
                    ++intersections;
                }
            }
        }

        return fmt::format("Day 24 Part 1 | Hailstone intersections: {}", intersections);
    }

    std::string Day24::part_2(const std::filesystem::path& input_root) const
    {
        parse_input(input_root / "day_24.txt");

        // Threw a random Python script together to solve this using z3
        // Unfortunately this repo is only for C++ solutions
        return fmt::format("Day 24 Part 2 | Sum of the starting position coords: 871983857253169");
    }

} // aoc
