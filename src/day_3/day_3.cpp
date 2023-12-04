#include "day_3/day_3.h"

#include "utility/io.h"
#include "utility/vec.h"

#include "fmt/format.h"

#include <cctype>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace aoc
{
    struct SchematicSymbol
    {
        char glyph;
        Point pos;
    };

    struct EngineSchematic
    {
        std::unordered_map<Point, std::shared_ptr<int>> part_numbers;
        std::vector<SchematicSymbol> symbols;
    };

    static bool is_symbol(const char c)
    {
        return !(std::isdigit(c) || c == '.');
    }

    static std::pair<int, size_t> read_number(const std::string& line, const size_t start_idx)
    {
        size_t end_idx = start_idx;;
        while (std::isdigit(line[end_idx]))
        {
            ++end_idx;
        }

        size_t length = (end_idx - start_idx);
        int value = std::stoi(line.substr(start_idx, length));

        return { value, length };
    }

    static EngineSchematic parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::unordered_map<Point, std::shared_ptr<int>> part_numbers;
        std::vector<SchematicSymbol> symbols;

        size_t y = 0;
        for (std::string line; std::getline(file, line); )
        {
            for (size_t x = 0; x < line.length(); )
            {
                char current = line[x];
                if (std::isdigit(current))
                {
                    const auto [value, length] = read_number(line, x);

                    std::shared_ptr<int> number = std::make_shared<int>(value);
                    for (size_t dx = x; dx < (x + length); ++dx)
                    {
                        part_numbers[make_point(dx, y)] = number;
                    }

                    x += length;
                }
                else if (is_symbol(current))
                {
                    symbols.emplace_back(current, make_point(x, y));
                    ++x;
                }
                else
                {
                    ++x;
                }
            }

            ++y;
        }

        return { part_numbers, symbols };
    }

    static std::unordered_set<std::shared_ptr<int>> nearby_parts(const SchematicSymbol& symbol, const EngineSchematic& schematic)
    {
        std::unordered_set<std::shared_ptr<int>> nearby;
        for (const auto& adj : symbol.pos.adjacent())
        {
            const auto it = schematic.part_numbers.find(adj);
            if (it != schematic.part_numbers.end())
            {
                nearby.insert(it->second);
            }
        }

        return nearby;
    }

    static int gear_ratio(const SchematicSymbol& symbol, const EngineSchematic& schematic)
    {
        if (symbol.glyph != '*')
        {
            return 0;
        }

        const auto nearby = nearby_parts(symbol, schematic);
        if (nearby.size() != 2)
        {
            return 0;
        }

        int ratio = 1;
        for (const auto& part_number : nearby)
        {
            ratio *= *part_number;
        }

        return ratio;
    }

    std::string Day3::part_1(const std::filesystem::path& input_root) const
    {
        EngineSchematic schematic = parse_input(input_root / "day_3.txt");

        int part_sum = 0;
        for (const auto& symbol : schematic.symbols)
        {
            for (const auto& part_number : nearby_parts(symbol, schematic))
            {
                part_sum += *part_number;
            }
        }

        return fmt::format("Day 3 Part 1 | Sum of valid part numbers: {}", part_sum);
    }

    std::string Day3::part_2(const std::filesystem::path& input_root) const
    {
        EngineSchematic schematic = parse_input(input_root / "day_3.txt");

        int gear_sum = 0;
        for (const auto& symbol : schematic.symbols)
        {
            gear_sum += gear_ratio(symbol, schematic);
        }

        return fmt::format("Day 3 Part 2 | Sum of all gear ratios: {}", gear_sum);
    }

} // aoc
