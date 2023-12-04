#include "day_4/day_4.h"

#include "day_4/scratchcard.h"
#include "utility/io.h"
#include "utility/string.h"

#include "fmt/format.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

namespace aoc
{
    static std::vector<Scratchcard> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<Scratchcard> cards;
        for (std::string line; std::getline(file, line); )
        {
            std::vector<std::string> raw_card = split(line, ':');
            std::vector<std::string> raw_numbers = split(raw_card.back(), '|');
            const std::string& raw_winning_numbers = raw_numbers.front();
            const std::string& raw_your_numbers = raw_numbers.back();

            // Get the ID
            int id = std::stoi(raw_card.front().substr(5, 3));

            // Get the winning numbers
            std::unordered_set<int> winning_numbers;
            for (size_t i = 0; i <= raw_winning_numbers.length() - 3; i += 3)
            {
                int number = std::stoi(raw_winning_numbers.substr(i, 3));
                winning_numbers.insert(number);
            }

            // Get your numbers      
            std::vector<int> your_numbers;
            for (size_t i = 0; i <= raw_your_numbers.length() - 3; i += 3)
            {
                int number = std::stoi(raw_your_numbers.substr(i, 3));
                your_numbers.push_back(number);
            }

            cards.emplace_back(id, winning_numbers, your_numbers);
        }

        return cards;
    }

    std::string Day4::part_1(const std::filesystem::path& input_root) const
    {
        std::vector<Scratchcard> cards = parse_input(input_root / "day_4.txt");

        int points = 0;
        for (const auto& card : cards)
        {
            points += card.points();
        }

        return fmt::format("Day 4 Part 1 | Sum of the points of winning cards: {}", points);
    }

    std::string Day4::part_2(const std::filesystem::path& input_root) const
    {
        std::vector<Scratchcard> cards = parse_input(input_root / "day_4.txt");

        for (size_t i = 0; i < cards.size(); ++i)
        {
            for (size_t j = 1; j <= cards[i].matching_numbers(); ++j)
            {
                cards[i + j].add_copies(cards[i].copies());
            }
        }

        int total_cards = 0;
        for (const auto& card : cards)
        {
            total_cards += card.copies();
        }
        
        return fmt::format("Day 4 Part 2 | Total cards won: {}", total_cards);
    }

} // aoc
