#include "day_12/day_12.h"

#include "utility/io.h"
#include "utility/string.h"
#include "utility/utility.h"

#include "fmt/format.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace aoc
{
    struct HotSpringRecord
    {
        std::string pattern;
        std::vector<int> lengths;
    };

    static std::vector<HotSpringRecord> parse_input_part_1(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<HotSpringRecord> records;
        for (std::string line; std::getline(file, line); )
        {
            auto raw_record = split(line, ' ');

            std::string pattern = raw_record.front() + '.';

            std::vector<int> lengths = split(raw_record.back(), ',')
                | std::views::transform([](const std::string& s) { return std::stoi(s); })
                | std::ranges::to<std::vector<int>>();

            records.emplace_back(pattern, lengths);
        }

        return records;
    }

    static std::vector<HotSpringRecord> parse_input_part_2(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<HotSpringRecord> records;
        for (std::string line; std::getline(file, line); )
        {
            auto raw_record = split(line, ' ');

            std::string pattern = (std::ranges::repeat_view(raw_record.front(), 5)
                | std::views::join_with('?')
                | std::ranges::to<std::string>()) + '.';

            std::vector<int> lengths = std::ranges::repeat_view(split(raw_record.back(), ','), 5)
                | std::views::join
                | std::views::transform([](const std::string& s) { return std::stoi(s); })
                | std::ranges::to<std::vector<int>>();

            records.emplace_back(pattern, lengths);
        }

        return records;
    }

    static int64_t count_combinations(
        std::unordered_map<std::tuple<size_t, int64_t, size_t>, int64_t>& cache,
        const HotSpringRecord& record,
        const size_t idx,
        const int64_t current_length,
        const size_t current_length_idx)
    {
        auto key = std::make_tuple(idx, current_length, current_length_idx);
        if (cache.contains(key))
        {
            return cache[key];
        }

        int64_t count = 0;
        if (idx == record.pattern.length())
        {
            count = current_length_idx == record.lengths.size() ? 1 : 0;
        }
        else if (record.pattern[idx] == '#')
        {
            count = count_combinations(cache, record, idx + 1, current_length + 1, current_length_idx);
        }
        else if (record.pattern[idx] == '.' || current_length_idx == record.lengths.size())
        {
            if (current_length_idx < record.lengths.size() && current_length == record.lengths[current_length_idx])
            {
                count = count_combinations(cache, record, idx + 1, 0, current_length_idx + 1);
            }
            else if (current_length == 0)
            {
                count = count_combinations(cache, record, idx + 1, 0, current_length_idx);
            }
            else
            {
                count = 0;
            }
        }
        else
        {
            int64_t damaged_count = count_combinations(cache, record, idx + 1, current_length + 1, current_length_idx);
            int64_t operational_count = 0;
            if (current_length == record.lengths[current_length_idx])
            {
                operational_count = count_combinations(cache, record, idx + 1, 0, current_length_idx + 1);
            }
            else if (current_length == 0)
            {
                operational_count = count_combinations(cache, record, idx + 1, 0, current_length_idx);
            }

            count = damaged_count + operational_count;
        }

        cache[key] = count;
        return count;
    }

    std::string Day12::part_1(const std::filesystem::path& input_root) const
    {
        std::vector<HotSpringRecord> records = parse_input_part_1(input_root / "day_12.txt");
        
        int64_t combinations = 0;
        for (const HotSpringRecord& record : records)
        {
            std::unordered_map<std::tuple<size_t, int64_t, size_t>, int64_t> cache;
            combinations += count_combinations(cache, record, 0, 0, 0);
        }

        return fmt::format("Day 12 Part 1 | Hot spring combinations: {}", combinations);
    }

    std::string Day12::part_2(const std::filesystem::path& input_root) const
    {
        std::vector<HotSpringRecord> records = parse_input_part_2(input_root / "day_12.txt");

        int64_t combinations = 0;
        for (HotSpringRecord& record : records)
        {
            std::unordered_map<std::tuple<size_t, int64_t, size_t>, int64_t> cache;
            combinations += count_combinations(cache, record, 0, 0, 0);
        }

        return fmt::format("Day 12 Part 2 | Hot spring combinations: {}", combinations);
    }

} // aoc
