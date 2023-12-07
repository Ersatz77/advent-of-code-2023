#include "day_7/camel_cards.h"

#include <cstdint>
#include <string>
#include <unordered_map>

namespace aoc
{
    bool compare_camel_cards(const CamelCardHand& lhs, const CamelCardHand& rhs)
    {
        if (lhs.type == rhs.type)
        {
            constexpr std::string_view card_values = "23456789TJQKA";
            for (size_t i = 0; i < lhs.cards.length(); ++i)
            {
                char left = lhs.cards[i];
                char right = rhs.cards[i];
                if (left != right)
                {
                    return card_values.find(left) < card_values.find(right);
                }
            }
        }

        return lhs.type < rhs.type;
    }

    bool compare_camel_cards_with_jokers(const CamelCardHand& lhs, const CamelCardHand& rhs)
    {
        if (lhs.type == rhs.type)
        {
            constexpr std::string_view card_values = "J23456789TQKA";
            for (size_t i = 0; i < lhs.cards.length(); ++i)
            {
                char left = lhs.cards[i];
                char right = rhs.cards[i];
                if (left != right)
                {
                    return card_values.find(left) < card_values.find(right);
                }
            }
        }

        return lhs.type < rhs.type;
    }

    CamelCardHandType get_hand_type(const std::string& cards)
    {
        std::unordered_map<char, size_t> card_counts;
        for (const char card : cards)
        {
            ++card_counts[card];
        }

        std::unordered_map<size_t, size_t> count_counts;
        for (const auto& [_, count] : card_counts)
        {
            ++count_counts[count];
        }

        if (count_counts[5] == 1)
        {
            return CamelCardHandType::FIVE_OF_A_KIND;
        }
        else if (count_counts[4] == 1)
        {
            return CamelCardHandType::FOUR_OF_A_KIND;
        }
        else if (count_counts[3] == 1 && count_counts[2] == 1)
        {
            return CamelCardHandType::FULL_HOUSE;
        }
        else if (count_counts[3] == 1)
        {
            return CamelCardHandType::THREE_OF_A_KIND;
        }
        else if (count_counts[2] == 2)
        {
            return CamelCardHandType::TWO_PAIR;
        }
        else if (count_counts[2] == 1)
        {
            return CamelCardHandType::ONE_PAIR;
        }
        else
        {
            return CamelCardHandType::HIGH_CARD;
        }
    }

    CamelCardHandType get_hand_type_with_jokers(const std::string& cards)
    {
        std::unordered_map<char, size_t> card_counts;
        for (const char card : cards)
        {
            ++card_counts[card];
        }

        std::unordered_map<size_t, size_t> count_counts;
        for (const auto& [card, count] : card_counts)
        {
            if (card == 'J')
            {
                continue;
            }

            ++count_counts[count];
        }

        switch (card_counts['J'])
        {
            case 5:
            case 4:
            {
                return CamelCardHandType::FIVE_OF_A_KIND;
            }
            case 3:
            {
                if (count_counts[2] == 1)
                {
                    return CamelCardHandType::FIVE_OF_A_KIND;
                }
                else
                {
                    return CamelCardHandType::FOUR_OF_A_KIND;
                }
            }
            case 2:
            {
                if (count_counts[3] == 1)
                {
                    return CamelCardHandType::FIVE_OF_A_KIND;
                }
                else if (count_counts[2] == 1)
                {
                    return CamelCardHandType::FOUR_OF_A_KIND;
                }
                else
                {
                    return CamelCardHandType::THREE_OF_A_KIND;
                }
            }
            case 1:
            {
                if (count_counts[4] == 1)
                {
                    return CamelCardHandType::FIVE_OF_A_KIND;
                }
                else if (count_counts[3] == 1)
                {
                    return CamelCardHandType::FOUR_OF_A_KIND;
                }
                else if (count_counts[2] == 2)
                {
                    return CamelCardHandType::FULL_HOUSE;
                }
                else if (count_counts[2] == 1)
                {
                    return CamelCardHandType::THREE_OF_A_KIND;
                }
                else
                {
                    return CamelCardHandType::ONE_PAIR;
                }
            }
            default:
            {
                if (count_counts[5] == 1)
                {
                    return CamelCardHandType::FIVE_OF_A_KIND;
                }
                else if (count_counts[4] == 1)
                {
                    return CamelCardHandType::FOUR_OF_A_KIND;
                }
                else if (count_counts[3] == 1 && count_counts[2] == 1)
                {
                    return CamelCardHandType::FULL_HOUSE;
                }
                else if (count_counts[3] == 1)
                {
                    return CamelCardHandType::THREE_OF_A_KIND;
                }
                else if (count_counts[2] == 2)
                {
                    return CamelCardHandType::TWO_PAIR;
                }
                else if (count_counts[2] == 1)
                {
                    return CamelCardHandType::ONE_PAIR;
                }
                else
                {
                    return CamelCardHandType::HIGH_CARD;
                }
            }
        }
    }

} // aoc
