#include "day_3/schematic.h"

namespace aoc
{
    SchematicNumber::SchematicNumber() :
        value(0), part_id(id++)
    {
    }

    SchematicNumber::SchematicNumber(const int value) :
        value(value), part_id(id++)
    {
    }

    int SchematicNumber::id = 0;

} // aoc
