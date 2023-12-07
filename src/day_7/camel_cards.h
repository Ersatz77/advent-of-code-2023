#ifndef AOC_2023_DAY_7_CAMEL_CARDS_H
#define AOC_2023_DAY_7_CAMEL_CARDS_H

#include <cstdint>
#include <string>

namespace aoc
{
    enum class CamelCardHandType
    {
        HIGH_CARD,
        ONE_PAIR,
        TWO_PAIR,
        THREE_OF_A_KIND,
        FULL_HOUSE,
        FOUR_OF_A_KIND,
        FIVE_OF_A_KIND
    };

    struct CamelCardHand
    {
        std::string cards;
        int64_t bid;
        CamelCardHandType type;
    };

    bool compare_camel_cards(const CamelCardHand& lhs, const CamelCardHand& rhs);
    bool compare_camel_cards_with_jokers(const CamelCardHand& lhs, const CamelCardHand& rhs);

    CamelCardHandType get_hand_type(const std::string& cards);
    CamelCardHandType get_hand_type_with_jokers(const std::string& cards);

} // aoc

#endif // !AOC_2023_DAY_7_CAMEL_CARDS_H
