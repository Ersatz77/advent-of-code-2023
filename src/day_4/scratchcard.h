#ifndef AOC_2023_DAY_4_SCRATCHCARD_H
#define AOC_2023_DAY_4_SCRATCHCARD_H

#include <unordered_set>
#include <vector>

namespace aoc
{
    class Scratchcard
    {
    public:
        Scratchcard();
        Scratchcard(const int id, const std::unordered_set<int>& winning_numbers, const std::vector<int>& your_numbers);

        int copies() const { return m_copies; }
        void add_copies(const int copies) { m_copies += copies; }

        int matching_numbers() const;
        int points() const;

    private:
        int m_id;
        int m_copies;

        std::unordered_set<int> m_winning_numbers;
        std::vector<int> m_your_numbers;
    };

} // aoc

#endif // !AOC_2023_DAY_4_SCRATCHCARD_H
