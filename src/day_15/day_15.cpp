#include "day_15/day_15.h"

#include "day_15/lensmap.h"
#include "utility/io.h"
#include "utility/string.h"

#include "fmt/format.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace aoc
{
    static std::vector<LavaInitStep> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::string line;
        std::getline(file, line);

        std::vector<LavaInitStep> sequence;
        for (const std::string& raw_step : split(line, ','))
        {
            auto it = std::find_if(raw_step.begin(), raw_step.end(), [](const char c) { return c == '=' || c == '-'; });
            std::string label(raw_step.begin(), it);
            
            if (*it == '=')
            {
                std::string raw_focal_length(it + 1, raw_step.end());
                sequence.emplace_back(label, LavaInitOperation::ADD, std::stoll(raw_focal_length), raw_step);
            }
            else if (*it == '-')
            {
                sequence.emplace_back(label, LavaInitOperation::REMOVE, 0, raw_step);
            }
        }

        return sequence;
    }

    std::string Day15::part_1(const std::filesystem::path& input_root) const
    {
        std::vector<LavaInitStep> sequence = parse_input(input_root / "day_15.txt");

        int64_t hash_sum = 0;
        for (const LavaInitStep& step : sequence)
        {
            hash_sum += LensMap::hasher(step.raw);
        }

        return fmt::format("Day 15 Part 1 | Sum of initialization sequence hashes: {}", hash_sum);
    }

    std::string Day15::part_2(const std::filesystem::path& input_root) const
    {
        std::vector<LavaInitStep> sequence = parse_input(input_root / "day_15.txt");

        LensMap lenses;
        for (const LavaInitStep& step : sequence)
        {
            switch (step.op)
            {
                case LavaInitOperation::ADD:
                    lenses.add(step.label, step.focal_length);
                    break;
                case LavaInitOperation::REMOVE:
                    lenses.remove(step.label);
                    break;
            }
        }

        return fmt::format("Day 15 Part 2 | Focusing power of this lens configuration: {}", lenses.focusing_power());
    }

} // aoc
