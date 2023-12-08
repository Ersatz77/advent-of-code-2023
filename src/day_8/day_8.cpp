#include "day_8/day_8.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace aoc
{
    enum class DesertMapDirection
    {
        LEFT,
        RIGHT,
        UNKNOWN
    };

    struct DesertMap
    {
        std::queue<DesertMapDirection> directions;
        std::unordered_map<std::string, std::pair<std::string, std::string>> nodes;
    };

    static DesertMap parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        // Get the directions
        std::string raw_directions;
        std::getline(file, raw_directions);

        std::queue<DesertMapDirection> directions;
        for (const char c : raw_directions)
        {
            switch (c)
            {
                case 'L':
                    directions.push(DesertMapDirection::LEFT);
                    break;
                case 'R':
                    directions.push(DesertMapDirection::RIGHT);
                    break;
                default:
                    directions.push(DesertMapDirection::UNKNOWN);
                    break;
            }
        }

        // Skip the empty line
        skip_line(file);

        // Get the nodes
        std::unordered_map<std::string, std::pair<std::string, std::string>> nodes;
        for (std::string line; std::getline(file, line); )
        {
            std::string node_name = line.substr(0, 3);
            std::string left = line.substr(7, 3);
            std::string right = line.substr(12, 3);

            nodes[node_name] = std::make_pair(left, right);
        }

        return { directions, nodes };
    }

    static DesertMapDirection next_direction(DesertMap& map)
    {
        DesertMapDirection next = map.directions.front();
        map.directions.pop();
        map.directions.push(next);
        return next;
    }

    static std::string next_step(const DesertMap& map, const std::string& current_node, const DesertMapDirection direction)
    {
        switch (direction)
        {
            case DesertMapDirection::LEFT:
                return map.nodes.at(current_node).first;
            case DesertMapDirection::RIGHT:
                return map.nodes.at(current_node).second;
            default:
                return "";
        }
    }

    static int64_t walk_map(DesertMap& map, const std::string& start_node, const std::string& end_node)
    {
        int64_t steps = 0;
        std::string current_node = start_node;
        while (current_node != end_node)
        {
            DesertMapDirection direction = next_direction(map);
            current_node = next_step(map, current_node, direction);
            ++steps;
        }

        return steps;
    }

    static int64_t walk_ghost_map(DesertMap& map, const char start_node_ends_with, const char end_node_ends_with)
    {
        // Get all nodes that end with 'A'
        std::vector<std::string> currents;
        for (const auto& [node_name, _] : map.nodes)
        {
            if (node_name.ends_with(start_node_ends_with))
            {
                currents.push_back(node_name);
            }
        }

        // Walk all paths until they all reach a node that ends in 'Z' while also calculating the LCM
        int64_t ghost_steps = 1;
        int64_t steps = 0;
        while (!currents.empty())
        {
            DesertMapDirection direction = next_direction(map);

            std::vector<std::string> next_currents;
            for (const std::string& current : currents)
            {
                if (current.ends_with(end_node_ends_with))
                {
                    ghost_steps = std::lcm(steps, ghost_steps);
                    continue;
                }

                next_currents.push_back(next_step(map, current, direction));
            }

            ++steps;
            currents = next_currents;
        }
        return ghost_steps;
    }

    std::string Day8::part_1(const std::filesystem::path& input_root) const
    {
        DesertMap map = parse_input(input_root / "day_8.txt");

        int64_t steps = walk_map(map, "AAA", "ZZZ");

        return fmt::format("Day 8 Part 1 | Steps required to reach node ZZZ: {}", steps);
    }

    std::string Day8::part_2(const std::filesystem::path & input_root) const
    {
        DesertMap map = parse_input(input_root / "day_8.txt");

        int64_t steps = walk_ghost_map(map, 'A', 'Z');

        return fmt::format("Day 8 Part 2 | Steps required for all nodes to end with Z: {}", steps);
    }

} // aoc
