#include "day_4/scratchcard.h"

#include <unordered_set>
#include <vector>

namespace aoc
{
    Scratchcard::Scratchcard() :
        m_id(-1), m_copies(1)
    {
    }

    Scratchcard::Scratchcard(const int id, const std::unordered_set<int>& winning_numbers, const std::vector<int>& your_numbers) :
        m_id(id), m_copies(1), m_winning_numbers(winning_numbers), m_your_numbers(your_numbers)
    {
    }

    int Scratchcard::matching_numbers() const
    {
        int matches = 0;
        for (const int number : m_your_numbers)
        {
            if (m_winning_numbers.contains(number))
            {
                ++matches;
            }
        }

        return matches;
    }

    int Scratchcard::points() const
    {
        int matches = matching_numbers();
        if (matches == 0)
        {
            return matches;
        }

        int total_points = 1;
        for (int i = 0; i < matches - 1; ++i)
        {
            total_points *= 2;
        }

        return total_points;
    }

} // aoc
