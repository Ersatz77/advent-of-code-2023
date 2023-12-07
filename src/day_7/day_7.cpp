#include "day_7/day_7.h"

#include "day_7/camel_cards.h"
#include "utility/io.h"

#include "fmt/format.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace aoc
{

    static std::vector<CamelCardHand> parse_input_part_1(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<CamelCardHand> hands;
        for (std::string line; std::getline(file, line); )
        {
            std::string cards = line.substr(0, 5);
            int64_t bid = std::stoi(line.substr(6));
            hands.emplace_back(cards, bid, get_hand_type(cards));
        }

        return hands;
    }

    static std::vector<CamelCardHand> parse_input_part_2(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<CamelCardHand> hands;
        for (std::string line; std::getline(file, line); )
        {
            std::string cards = line.substr(0, 5);
            int64_t bid = std::stoi(line.substr(6));
            hands.emplace_back(cards, bid, get_hand_type_with_jokers(cards));
        }

        return hands;
    }

    std::string Day7::part_1(const std::filesystem::path& input_root) const
    {
        std::vector<CamelCardHand> hands = parse_input_part_1(input_root / "day_7.txt");

        std::sort(hands.begin(), hands.end(), compare_camel_cards);

        int64_t winnings = 0;
        for (size_t i = 0; i < hands.size(); ++i)
        {
            winnings += hands[i].bid * (i + 1);
        }

        return fmt::format("Day 7 Part 1 | Camel cards winnings: {}", winnings);
    }

    std::string Day7::part_2(const std::filesystem::path& input_root) const
    {
        std::vector<CamelCardHand> hands = parse_input_part_2(input_root / "day_7.txt");

        std::sort(hands.begin(), hands.end(), compare_camel_cards_with_jokers);

        int64_t winnings = 0;
        for (size_t i = 0; i < hands.size(); ++i)
        {
            winnings += hands[i].bid * (i + 1);
        }

        return fmt::format("Day 7 Part 2 | Camel cards winnings: {}", winnings);
    }

} // aoc
