#include "day_20/day_20.h"

#include "day_20/machine_module.h"
#include "utility/io.h"
#include "utility/string.h"

#include "fmt/format.h"

#include <cctype>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

namespace aoc
{
    static std::unordered_map<std::string, MachineModule> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::unordered_map<std::string, MachineModule> modules;
        for (std::string line; std::getline(file, line); )
        {
            std::vector<std::string> raw_module = regex_split(line, R"(.->.)");

            std::string name = raw_module.front();
            if (!std::isalpha(name.front()))
            {
                name = name.substr(1);
            }

            MachineModuleType type = MachineModuleType::NONE;
            switch (raw_module.front().front())
            {
                case '%':
                    type = MachineModuleType::FLIP_FLOP;
                    break;
                case '&':
                    type = MachineModuleType::CONJUNCTION;
                    break;
                default:
                    type = MachineModuleType::BROADCAST;
                    break;
            }

            MachineModule mod(name, type);
            for (const std::string& output_name : regex_split(raw_module.back(), R"(,.)"))
            {
                mod.add_output(output_name);
            }

            modules[name] = mod;
        }

        for (const auto& [name, mod] : modules)
        {
            for (const std::string& output_name : mod.outputs())
            {
                modules[output_name].watch(name);
            }
        }

        return modules;
    }

    static int64_t press_button(std::unordered_map<std::string, MachineModule>& modules, const size_t button_presses)
    {
        int64_t lows = 0;
        int64_t highs = 0;

        std::queue<MachinePulse> to_process;
        for (size_t i = 0; i < button_presses; ++i)
        {
            to_process.emplace("button", "broadcaster", MachinePulseType::LOW);
            while (!to_process.empty())
            {
                MachinePulse current_pulse = to_process.front();
                to_process.pop();

                switch (current_pulse.type)
                {
                    case MachinePulseType::LOW:
                        ++lows;
                        break;
                    case MachinePulseType::HIGH:
                        ++highs;
                        break;
                }

                std::vector<MachinePulse> next_pulses = modules[current_pulse.destination].trigger(current_pulse);
                to_process.push_range(next_pulses);
            }
        }

        return lows * highs;
    }

    static int64_t start_rx(std::unordered_map<std::string, MachineModule>& modules)
    {
        std::string rx_source_name = modules["rx"].watching().begin()->first;
        MachineModule& rx_source_module = modules[rx_source_name];

        std::unordered_map<std::string, int64_t> cycle_lengths;
        std::unordered_map<std::string, int64_t> cycle_lengths_prev;
        std::vector<int64_t> all_lengths;

        std::queue<MachinePulse> to_process;
        for (size_t i = 0; ; ++i)
        {
            to_process.emplace("button", "broadcaster", MachinePulseType::LOW);
            while (!to_process.empty())
            {
                MachinePulse current_pulse = to_process.front();
                to_process.pop();

                std::vector<MachinePulse> next_pulses = modules[current_pulse.destination].trigger(current_pulse);
                to_process.push_range(next_pulses);

                if (!(current_pulse.destination == rx_source_name && current_pulse.type == MachinePulseType::HIGH))
                {
                    continue;
                }

                if (cycle_lengths.contains(current_pulse.source))
                {
                    continue;
                }

                if (!cycle_lengths_prev.contains(current_pulse.source))
                {
                    cycle_lengths_prev[current_pulse.source] = i;
                    continue;
                }

                int64_t diff = i - cycle_lengths_prev[current_pulse.source];
                cycle_lengths[current_pulse.source] = diff;
                all_lengths.push_back(diff);

                if (all_lengths.size() == rx_source_module.watching().size())
                {
                    int64_t result = 1;
                    for (const int64_t& v : all_lengths)
                    {
                        result = std::lcm(result, v);
                    }

                    return result;
                }
            }
        }

        return 0;
    }

    std::string Day20::part_1(const std::filesystem::path& input_root) const
    {
        auto modules = parse_input(input_root / "day_20.txt");

        int64_t pulse_product = press_button(modules, 1000);

        return fmt::format("Day 20 Part 1 | Product of high and low pulses: {}", pulse_product);
    }

    std::string Day20::part_2(const std::filesystem::path& input_root) const
    {
        auto modules = parse_input(input_root / "day_20.txt");

        int64_t button_presses = start_rx(modules);

        return fmt::format("Day 20 Part 2 | Fewest button presses to send a low pulse to \"rx\": {}", button_presses);
    }

} // aoc
