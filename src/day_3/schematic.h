#ifndef AOC_2023_DAY_3_SCHEMATIC_H
#define AOC_2023_DAY_3_SCHEMATIC_H

#include "utility/utility.h"
#include "utility/vec.h"

#include <compare>

namespace aoc
{
    class SchematicNumber
    {
    public:
        SchematicNumber();
        explicit SchematicNumber(const int value);

        auto operator<=>(const SchematicNumber& other) const = default;

        int value;
        int part_id;

    private:
        static int id;
    };
    
    
    struct SchematicSymbol
    {
        char glyph;
        Point pos;
    };

} // aoc

namespace std
{
    template<>
    struct hash<aoc::SchematicNumber>
    {
        size_t operator()(const aoc::SchematicNumber& num) const
        {
            size_t seed = 0;
            aoc::hash_combine(seed, num.value);
            aoc::hash_combine(seed, num.part_id);
            return seed;
        }
    };

} // std

#endif // !AOC_2023_DAY_3_SCHEMATIC_H
