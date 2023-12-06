#include "day_6/day_6.h"

#include "utility/io.h"
#include "utility/math.h"

#include "fmt/format.h"

#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace aoc
{
    struct BoatRace
    {
        int64_t max_time;
        int64_t distance_record;
    };

    static std::vector<BoatRace> parse_input_part_1(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::string raw_times;
        std::string raw_distance_records;

        file.ignore(5);
        std::getline(file, raw_times);

        file.ignore(9);
        std::getline(file, raw_distance_records);

        std::istringstream times_stream(raw_times);
        std::istringstream distance_records_stream(raw_distance_records);

        std::vector<BoatRace> races;
        int64_t time = 0;
        int64_t record = 0;
        while ((times_stream >> time) && (distance_records_stream >> record))
        {
            races.emplace_back(time, record);
        }

        return races;
    }

    static BoatRace parse_input_part_2(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::string raw_times;
        std::string raw_distance_records;

        file.ignore(9);
        std::getline(file, raw_times);

        file.ignore(9);
        std::getline(file, raw_distance_records);

        std::istringstream times_stream(raw_times);
        std::istringstream distance_records_stream(raw_distance_records);

        std::string time;
        std::string distance_record;
        std::string time_chunk;
        std::string distance_record_chunk;
        while ((times_stream >> time_chunk) && (distance_records_stream >> distance_record_chunk))
        {
            time += time_chunk;
            distance_record += distance_record_chunk;
        }

        return { std::stoll(time), std::stoll(distance_record) };
    }

    static int64_t total_ways_to_beat_record(const BoatRace& race)
    {
        auto [root_1, root_2] = quadratic(-1.0, static_cast<double>(race.max_time), static_cast<double>(-race.distance_record));
        double record_beaten = std::ceil(root_2) - std::ceil(root_1);
        return static_cast<int64_t>(record_beaten);
    }

    std::string Day6::part_1(const std::filesystem::path& input_root) const
    {
        std::vector<BoatRace> races = parse_input_part_1(input_root / "day_6.txt");

        int64_t error_margin = 1;
        for (const auto& race : races)
        {
            error_margin *= total_ways_to_beat_record(race);
        }

        return fmt::format("Day 6 Part 1 | Error margin: {}",  error_margin);
    }

    std::string Day6::part_2(const std::filesystem::path& input_root) const
    {
        BoatRace race = parse_input_part_2(input_root / "day_6.txt");
        int64_t error_margin = total_ways_to_beat_record(race);

        return fmt::format("Day 6 Part 2 | Error margin: {}",  error_margin);
    }

} // aoc
