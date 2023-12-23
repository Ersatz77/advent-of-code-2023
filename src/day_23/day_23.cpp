#include "day_23/day_23.h"

#include "utility/io.h"
#include "utility/vec.h"

#include "fmt/format.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace aoc
{
    static std::vector<std::string> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<std::string> hiking_trail;
        for (std::string line; std::getline(file, line); )
        {
            hiking_trail.push_back(line);
        }

        return hiking_trail;
    }

    static bool in_trail(const std::vector<std::string>& hiking_trail, const Point& p)
    {
        return p.x >= 0 && p.x < hiking_trail.front().length() && p.y >= 0 && p.y < hiking_trail.size();
    }

    static bool is_slope(const char c)
    {
        switch (c)
        {
            case '>':
            case '<':
            case '^':
            case 'v':
                return true;
            default:
                return false;
        }
    }

    static char tile_at(const std::vector<std::string>& hiking_trail, const Point& p)
    {
        return hiking_trail[static_cast<size_t>(p.y)][static_cast<size_t>(p.x)];
    }

    static std::vector<Point> get_adjacent(const std::vector<std::string>& hiking_trail, const Point& current, const bool slopes)
    {
        static const std::unordered_map<char, std::vector<Point>> directions = {
            {'>', { { 1, 0 } }},
            {'<', { { -1, 0 } }},
            {'^', { { 0, -1 } }},
            {'v', { { 0, 1 } }},
            {'.', { { 1, 0 }, { -1, 0 }, { 0, -1 }, { 0, 1 } }}
        };

        std::vector<Point> res;
        for (const Point& delta : directions.at(slopes ? tile_at(hiking_trail, current) : '.'))
        {
            Point adj = current + delta;
            if (in_trail(hiking_trail, adj) && tile_at(hiking_trail, adj) != '#')
            {
                res.push_back(adj);
            }
        }

        return res;
    }

    static std::unordered_map<Point, std::vector<std::pair<Point, int64_t>>> create_graph(const std::vector<std::string>& hiking_trail, const Point& start, const bool slopes)
    {
        std::unordered_map<Point, std::vector<std::pair<Point, int64_t>>> graph;

        std::unordered_set<Point> visited;
        std::stack<Point> to_visit;
        to_visit.push(start);

        while (!to_visit.empty())
        {
            Point current = to_visit.top();
            to_visit.pop();

            if (visited.contains(current))
            {
                continue;
            }

            for (const Point& next: get_adjacent(hiking_trail, current, slopes))
            {
                int64_t length = 1;
                Point prev = current;
                Point curr = next;
                bool ended = false;
                while (true)
                {
                    std::vector<Point> adj = get_adjacent(hiking_trail, curr, slopes);
                    if (adj.size() == 1 && adj.front() == prev && is_slope(tile_at(hiking_trail, curr)))
                    {
                        ended = true;
                        break;
                    }

                    if (adj.size() != 2)
                    {
                        break;
                    }

                    for (const Point& a : adj)
                    {
                        if (a != prev)
                        {
                            ++length;
                            prev = curr;
                            curr = a;
                            break;
                        }
                    }
                }

                if (!ended)
                {
                    graph[current].emplace_back(curr, length);
                    to_visit.push(next);
                }
            }

            visited.insert(current);
        }

        return graph;
    }

    static int64_t walk_trail(std::unordered_map<Point, std::vector<std::pair<Point, int64_t>>>& graph, const Point& start, const Point& end)
    {
        int64_t longest = 0;
        std::stack<std::tuple<Point, int64_t, std::unordered_set<Point>>> to_process;
        to_process.emplace(start, 0, std::unordered_set<Point>({ start }));

        while (!to_process.empty())
        {
            auto [current, length, visited] = to_process.top();
            to_process.pop();

            if (current == end)
            {
                longest = std::max(length, longest);
                continue;
            }

            for (const auto& [next, next_length] : graph.at(current))
            {
                if (!visited.contains(next))
                {
                    std::unordered_set<Point> next_visited = visited;
                    next_visited.insert(next);
                    to_process.emplace(next, length + next_length, next_visited);
                }
            }
        }

        return longest;
    }
    
    std::string Day23::part_1(const std::filesystem::path& input_root) const
    {
        auto hiking_trail = parse_input(input_root / "day_23.txt");

        Point start = make_point(1, 0);
        Point end = make_point(hiking_trail.front().length() - 2, hiking_trail.size() - 1);

        auto graph = create_graph(hiking_trail, start, true);
        int64_t longest = walk_trail(graph, start, end);

        return fmt::format("Day 23 Part 1 | Number of steps in the longest hike: {}", longest);
    }

    std::string Day23::part_2(const std::filesystem::path& input_root) const
    {
        auto hiking_trail = parse_input(input_root / "day_23.txt");

        Point start = make_point(1, 0);
        Point end = make_point(hiking_trail.front().length() - 2, hiking_trail.size() - 1);

        auto graph = create_graph(hiking_trail, start, false);
        int64_t longest = walk_trail(graph, start, end);

        return fmt::format("Day 23 Part 2 | Number of steps in the longest hike: {}", longest);
    }

} // aoc
