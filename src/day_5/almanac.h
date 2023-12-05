#ifndef AOC_2023_DAY_5_ALMANAC_H
#define AOC_2023_DAY_5_ALMANAC_H

#include <compare>
#include <cstdint>
#include <iostream>
#include <iostream>
#include <string>
#include <vector>

namespace aoc
{
    class AlmanacRange
    {
    public:
        AlmanacRange intersect(const AlmanacRange& rhs) const;

        operator bool() const;

        int64_t begin;
        int64_t end;
    };

    std::strong_ordering operator<=>(const AlmanacRange& lhs, const AlmanacRange& rhs);
    std::strong_ordering operator<=>(const AlmanacRange& lhs, const int64_t rhs);
    std::strong_ordering operator<=>(const int64_t lhs, const AlmanacRange& rhs);

    class AlmanacRangeConverter
    {
    public:
        int64_t convert(const int64_t value) const;

        AlmanacRange range;
        int64_t offset;
    };

    std::strong_ordering operator<=>(const AlmanacRangeConverter& lhs, const AlmanacRangeConverter& rhs);
    std::strong_ordering operator<=>(const AlmanacRangeConverter& lhs, const int64_t rhs);
    std::strong_ordering operator<=>(const int64_t lhs, const AlmanacRangeConverter& rhs);

    class AlmanacCategoryMapper
    {
    public:
        AlmanacCategoryMapper() = default;
        explicit AlmanacCategoryMapper(const std::vector<AlmanacRangeConverter>& converters);

        int64_t map(const int64_t value) const;
        std::vector<AlmanacRange> map_range(AlmanacRange range) const;

        friend std::istream& operator>>(std::istream& is, AlmanacCategoryMapper& mapper);

    private:
        std::vector<AlmanacRangeConverter> m_converters;
    };

    std::istream& operator>>(std::istream& is, AlmanacCategoryMapper& mapper);

} // aoc

#endif // !AOC_2023_DAY_5_ALMANAC_H
