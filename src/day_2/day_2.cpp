#include "day_2/day_2.h"

#include "utility/io.h"
#include "utility/string.h"

#include "fmt/format.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <limits>
#include <string>
#include <vector>

namespace aoc
{
    enum class CubeColor
    {
        RED,
        GREEN,
        BLUE
    };

    struct CubeStats
    {
        CubeColor color;
        int count;
    };

    struct CubeGame
    {
        int id;
        std::vector<CubeStats> shown_cubes;
    };

    static std::vector<CubeGame> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<CubeGame> games;
        for (std::string line; std::getline(file, line); )
        {
            // Split string at the `:` and get the ID
            std::vector<std::string> raw_game = split(line, ':');
            int id = std::stoi(raw_game.front().substr(5));

            // Split string at the `;` to get each round
            std::vector<CubeStats> cubes;
            for (const std::string& raw_round : split(raw_game.back(), ';'))
            {
                // Split the round at the `,` to get each cube
                for (const std::string& raw_cube : split(raw_round, ','))
                {
                    int count = std::stoi(raw_cube.substr(0, 3));
                    if (raw_cube.ends_with("red"))
                    {
                        cubes.emplace_back(CubeColor::RED, count);
                    }
                    else if (raw_cube.ends_with("green"))
                    {
                        cubes.emplace_back(CubeColor::GREEN, count);
                    }
                    else if (raw_cube.ends_with("blue"))
                    {
                        cubes.emplace_back(CubeColor::BLUE, count);
                    }
                }
            }

            games.emplace_back(id, cubes);
        }

        return games;
    }

    static bool is_possible(const CubeGame& game, const int total_red, const int total_green, const int total_blue)
    {
        for (const auto& cube : game.shown_cubes)
        {
            bool has_valid_count = (cube.color == CubeColor::RED && cube.count <= total_red)
                || (cube.color == CubeColor::GREEN && cube.count <= total_green)
                || (cube.color == CubeColor::BLUE && cube.count <= total_blue);
            if (!has_valid_count)
            {
                return false;
            }
        }

        return true;
    }

    static int cube_power(const CubeGame& game)
    {
        int min_red = std::numeric_limits<int>::min();
        int min_green = std::numeric_limits<int>::min();
        int min_blue = std::numeric_limits<int>::min();
        for (const auto& cube : game.shown_cubes)
        {
            switch (cube.color)
            {
                case CubeColor::RED:
                    min_red = std::max(cube.count, min_red);
                    break;
                case CubeColor::GREEN:
                    min_green = std::max(cube.count, min_green);
                    break;
                case CubeColor::BLUE:
                    min_blue = std::max(cube.count, min_blue);
                    break;
                default:
                    break;
            }
        }

        return min_red * min_green * min_blue;
    }
 
    std::string Day2::part_1(const std::filesystem::path& input_root) const
    {
        std::vector<CubeGame> games = parse_input(input_root / "day_2.txt");
        constexpr int total_red = 12;
        constexpr int total_green = 13;
        constexpr int total_blue = 14;

        // Sum the IDs of possible games
        int game_id_sum = 0;
        for (const auto& game : games)
        {
            if (is_possible(game, total_red, total_green, total_blue))
            {
                game_id_sum += game.id;
            }
        }

        return fmt::format("Day 2 Part 1 | Sum of the IDs of possible games: {}", game_id_sum);
    }

    std::string Day2::part_2(const std::filesystem::path& input_root) const
    {
        std::vector<CubeGame> games = parse_input(input_root / "day_2.txt");

        // Sum the cube power of each game
        int cube_power_sum = 0;
        for (const auto& game : games)
        {
            cube_power_sum += cube_power(game);
        }

        return fmt::format("Day 2 Part 2 | Sum of the cube power of each game: {}", cube_power_sum);
    }

} // aoc
