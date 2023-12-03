#include "day_3/day_3.h"

#include "day_3/schematic.h"
#include "utility/io.h"
#include "utility/vec.h"

#include "fmt/format.h"

#include <cctype>
#include <filesystem>
#include <fstream>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace aoc
{
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

    static std::pair<std::unordered_map<Point, SchematicNumber>, std::vector<SchematicSymbol>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::unordered_map<Point, SchematicNumber> part_numbers;
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
                    SchematicNumber number(value);
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

    static std::unordered_set<SchematicNumber> nearby_parts(const SchematicSymbol symbol, const std::unordered_map<Point, SchematicNumber>& part_numbers)
    {
        std::unordered_set<SchematicNumber> nearby;
        for (const auto& adj : symbol.pos.adjacent())
        {
            const auto it = part_numbers.find(adj);
            if (it != part_numbers.end())
            {
                nearby.insert(it->second);
            }
        }

        return nearby;
    }

    std::string Day3::part_1(const std::filesystem::path& input_root) const
    {
        const auto [part_numbers, symbols] = parse_input(input_root / "day_3.txt");

        int part_sum = 0;
        for (const auto& symbol : symbols)
        {
            const auto nearby = nearby_parts(symbol, part_numbers);
            part_sum += std::reduce(nearby.begin(), nearby.end(), 0, [](const int acc, const auto& p) { return acc + p.value; });
        }

        return fmt::format("Day 3 Part 1 | Sum of valid part numbers: {}", part_sum);
    }

    std::string Day3::part_2(const std::filesystem::path& input_root) const
    {
        const auto [part_numbers, symbols] = parse_input(input_root / "day_3.txt");

        int gear_sum = 0;
        for (const auto& symbol : std::ranges::filter_view(symbols, [](const auto& s) { return s.glyph == '*'; }))
        {
            const auto nearby = nearby_parts(symbol, part_numbers);
            if (nearby.size() != 2)
            {
                continue;
            }

            gear_sum += std::reduce(nearby.begin(), nearby.end(), 1, [](const int acc, const auto& p) { return acc * p.value; });
        }

        return fmt::format("Day 3 Part 2 | Sum of all gear ratios: {}", gear_sum);
    }

} // aoc
