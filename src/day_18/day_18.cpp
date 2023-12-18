#include "day_18/day_18.h"

#include "utility/io.h"
#include "utility/vec.h"

#include "fmt/format.h"

#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

namespace aoc
{
    using LavaLagoonTile = Vec2<int64_t>;
    using LavaLagoonInstruction = std::pair<LavaLagoonTile, int64_t>;

    static std::vector<LavaLagoonInstruction> parse_input_part_1(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<LavaLagoonInstruction> instructions;
        char raw_direction = ' ';
        int64_t to_dig = 0;
        while (file >> raw_direction >> to_dig)
        {
            switch (raw_direction)
            {
                case 'U':
                    instructions.emplace_back(LavaLagoonTile(0, 1), to_dig);
                    break;
                case 'D':
                    instructions.emplace_back(LavaLagoonTile(0, -1), to_dig);
                    break;
                case 'L':
                    instructions.emplace_back(LavaLagoonTile(-1, 0), to_dig);
                    break;
                case 'R':
                    instructions.emplace_back(LavaLagoonTile(1, 0), to_dig);
                    break;
            }

            skip_line(file);
        }

        return instructions;
    }

    static std::vector<LavaLagoonInstruction> parse_input_part_2(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<LavaLagoonInstruction> instructions;
        for (std::string line; std::getline(file, line); )
        {
            size_t hex_start = line.find_first_of('#');
            int64_t to_dig = std::stoll(line.substr(hex_start + 1, 5), nullptr, 16);
            int direction = std::stoi(line.substr(hex_start + 6, 1));

            switch (direction)
            {
                case 0:
                    instructions.emplace_back(LavaLagoonTile(1, 0), to_dig);
                    break;
                case 1:
                    instructions.emplace_back(LavaLagoonTile(0, -1), to_dig);
                    break;
                case 2:
                    instructions.emplace_back(LavaLagoonTile(-1, 0), to_dig);
                    break;
                case 3:
                    instructions.emplace_back(LavaLagoonTile(0, 1), to_dig);
                    break;
            }
        }

        return instructions;
    }

    static int64_t lava_lagoon_area(const std::vector<LavaLagoonInstruction>& instructions)
    {
        LavaLagoonTile current = { 0, 0 };
        int64_t area = 0;
        int64_t border_tiles = 0;
        for (const auto& [direction, to_dig] : instructions)
        {
            LavaLagoonTile next = current + (direction * to_dig);
    
            area += (current.x * next.y) - (current.y * next.x);
            border_tiles += to_dig;
    
            current = next;
        }
    
        return (std::llabs(area) + border_tiles) / 2 + 1;
    }

    std::string Day18::part_1(const std::filesystem::path& input_root) const
    {
        std::vector<LavaLagoonInstruction> instructions = parse_input_part_1(input_root / "day_18.txt");

        int64_t area = lava_lagoon_area(instructions);

        return fmt::format("Day 18 Part 1 | Amount of lava the lagoon could hold: {}", area);
    }

    std::string Day18::part_2(const std::filesystem::path& input_root) const
    {
        std::vector<LavaLagoonInstruction> instructions = parse_input_part_2(input_root / "day_18.txt");

        int64_t area = lava_lagoon_area(instructions);

        return fmt::format("Day 18 Part 2 | Amount of lava the lagoon could hold: {}", area);
    }

} // aoc
