#include "day_19/day_19.h"

#include "utility/io.h"
#include <utility/string.h>

#include "fmt/format.h"

#include <array>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <utility>

namespace aoc
{
    enum class RuleOperation
    {
        LESS_THAN,
        GREATER_THAN,
        NONE
    };

    struct Rule
    {
        size_t category_idx;
        RuleOperation op;
        int64_t value;
        std::string destination;
    };

    using Workflow = std::vector<Rule>;
    using Workflows = std::unordered_map<std::string, Workflow>;

    using Part = std::array<int64_t, 4>;
    using PartRange = std::array<int64_t, 8>;

    static std::pair<Workflows, std::vector<Part>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        // Parse rules
        static const std::regex rules_pattern(R"((?:([xmas])([<>])(\d+)\:(\w+))|(?:(\w+)\}))");

        Workflows workflows;
        for (std::string line; std::getline(file, line) && !line.empty(); )
        {
            size_t rules_start_idx = line.find_first_of('{');
            std::string name = line.substr(0, rules_start_idx);

            auto begin = std::sregex_iterator(line.begin(), line.end(), rules_pattern);
            auto end = std::sregex_iterator();
            for (auto& it = begin; it != end; ++it)
            {
                const auto& match = *it;
                if (match[4].str().empty())
                {
                    workflows[name].emplace_back(0, RuleOperation::NONE, 0, match[5].str());
                    continue;
                }

                size_t category_idx = 0;
                switch (match[1].str().front())
                {
                    case 'x':
                        category_idx = 0;
                        break;
                    case 'm':
                        category_idx = 1;
                        break;
                    case 'a':
                        category_idx = 2;
                        break;
                    case 's':
                        category_idx = 3;
                        break;
                }

                RuleOperation op = RuleOperation::NONE;
                switch (match[2].str().front())
                {
                    case '<':
                        op = RuleOperation::LESS_THAN;
                        break;
                    case '>':
                        op = RuleOperation::GREATER_THAN;
                        break;
                }

                int64_t value = std::stoll(match[3]);
                std::string destination = match[4];

                workflows[name].emplace_back(category_idx, op, value, destination);
            }
        }

        // Parse parts
        std::vector<Part> parts;
        for (std::string line; std::getline(file, line); )
        {
            std::vector<std::string> raw_part = split(line, ',');
            
            Part part = {};
            for (size_t i = 0; i < raw_part.size(); ++i)
            {
                size_t equal_idx = raw_part[i].find('=');
                part[i] = std::stoll(raw_part[i].substr(equal_idx + 1));
            }

            parts.push_back(part);
        }

        return { workflows, parts };
    }

    static std::string check_workflow(const Workflow& workflow, const Part& part)
    {
        for (const Rule& rule : workflow)
        {
            if (rule.op == RuleOperation::NONE)
            {
                return rule.destination;
            }
            else if (rule.op == RuleOperation::LESS_THAN && part[rule.category_idx] < rule.value)
            {
                return rule.destination;
            }
            else if (rule.op == RuleOperation::GREATER_THAN && part[rule.category_idx] > rule.value)
            {
                return rule.destination;
            }
        }

        return "";
    }

    static std::vector<PartRange> create_ranges(const Workflows& workflows, const std::string& to_run, PartRange range)
    {
        if (to_run == "A")
        {
            return { range };
        }
        else if (to_run == "R")
        {
            return {};
        }

        std::vector<PartRange> ranges;
        for (const Rule& rule : workflows.at(to_run))
        {
            if (rule.op == RuleOperation::NONE)
            {
                auto res = create_ranges(workflows, rule.destination, range);
                ranges.insert(ranges.end(), res.begin(), res.end());
            }
            else if (rule.op == RuleOperation::LESS_THAN)
            {
                PartRange adjusted_range = range;
                adjusted_range[(rule.category_idx * 2) + 1] = rule.value - 1;

                auto res = create_ranges(workflows, rule.destination, adjusted_range);
                ranges.insert(ranges.end(), res.begin(), res.end());

                range[rule.category_idx * 2] = rule.value;
            }
            else if (rule.op == RuleOperation::GREATER_THAN)
            {
                PartRange adjusted_range = range;
                adjusted_range[rule.category_idx * 2] = rule.value + 1;

                auto res = create_ranges(workflows, rule.destination, adjusted_range);
                ranges.insert(ranges.end(), res.begin(), res.end());

                range[(rule.category_idx * 2) + 1] = rule.value;
            }
        }

        return ranges;
    }

    std::string Day19::part_1(const std::filesystem::path& input_root) const
    {
        auto [workflows, parts] = parse_input(input_root / "day_19.txt");

        int64_t part_sum = 0;
        for (const Part& part : parts)
        {
            std::string current = "in";
            while (!current.empty())
            {
                current = check_workflow(workflows.at(current), part);
                if (current == "A")
                {
                    part_sum += (part[0] + part[1] + part[2] + part[3]);
                    break;
                }
                else if (current == "R")
                {
                    break;
                }
            }
        }

        return fmt::format("Day 19 Part 1 | Sum of accepted parts: {}", part_sum);
    }

    std::string Day19::part_2(const std::filesystem::path& input_root) const
    {
        auto [workflows, _] = parse_input(input_root / "day_19.txt");

        PartRange start_range = { {1, 4000, 1, 4000, 1, 4000, 1, 4000} };
        int64_t part_range_sum = 0;
        for (const PartRange& range : create_ranges(workflows, "in", start_range))
        {
            int64_t range_value = 1;
            for (size_t i = 1; i < range.size(); i += 2)
            {
                range_value *= (range[i] - range[i - 1]) + 1;
            }

            part_range_sum += range_value;
        }

        return fmt::format("Day 19 Part 2 | Sum of accepted part ranges: {}", part_range_sum);
    }

} // aoc
