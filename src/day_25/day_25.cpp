#include "day_25/day_25.h"

#include "utility/io.h"
#include "utility/string.h"

#include "fmt/format.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <limits>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace aoc
{
    static size_t index_of(std::unordered_map<std::string, size_t>& names, const std::string& n)
    {
        if (names.find(n) != names.end())
        {
            return names[n];
        }

        size_t idx = names.size();
        names[n] = idx;
        return idx;
    }

    static std::pair<std::vector<std::vector<int>>, std::unordered_map<std::string, size_t>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<std::pair<size_t, size_t>> connections;
        std::unordered_map<std::string, size_t> names;
        for (std::string line; std::getline(file, line); )
        {
            std::vector<std::string> raw_connection = regex_split(line, ": ");

            std::string component = raw_connection.front();
            std::vector<std::string> connected_to = split(raw_connection.back(), ' ');

            size_t base_idx = index_of(names, component);
            for (const std::string& c : connected_to)
            {
                connections.emplace_back(base_idx, index_of(names, c));
            }
        }

        std::vector<std::vector<int>> adj(names.size(), std::vector<int>(names.size(), 0));
        for (const auto& [k, v] : connections)
        {
            adj[k][v] = 1;
            adj[v][k] = 1;
        }

        return { adj, names };
    }

    static std::pair<int, std::vector<int>> min_cut(std::vector<std::vector<int>>& adj)
    {
        std::vector<std::vector<int>> co(adj.size());
        for (size_t i = 0; i < adj.size(); ++i)
        {
            co[i] = { static_cast<int>(i) };
        }

        std::pair<int, std::vector<int>> best = { std::numeric_limits<int>::max(), {} };
        for (size_t i = 1; i < adj.size(); ++i)
        {
            std::vector<int> w = adj[0];
            size_t s = 0;
            size_t t = 0;
            for (size_t j = 0; j < adj.size() - i; ++j)
            {
                w[t] = std::numeric_limits<int>::min();
                s = t;
                t = std::max_element(w.begin(), w.end()) - w.begin();
                for (size_t k = 0; k < adj.size(); ++k)
                {
                    w[k] += adj[t][k];
                }
            }

            best = std::min(best, { w[t] - adj[t][t], co[t] });
            co[s].insert(co[s].end(), co[t].begin(), co[t].end());

            for (size_t k = 0; k < adj.size(); ++k)
            {
                adj[s][k] += adj[t][k];
            }

            for (size_t k = 0; k < adj.size(); ++k)
            {
                adj[k][s] = adj[s][k];
            }

            adj[0][t] = std::numeric_limits<int>::min();
        }

        return best;
    }

    std::string Day25::part_1(const std::filesystem::path& input_root) const
    {
        auto [adj, names] = parse_input(input_root / "day_25.txt");

        auto result = min_cut(adj);
        size_t group_size = result.second.size() * (names.size() - result.second.size());

        return fmt::format("Day 25 Part 1 | Product of the two group sizes: {}", group_size);
    }

    std::string Day25::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("Day 25 Part 2 | You push the big red button");
    }

} // aoc
