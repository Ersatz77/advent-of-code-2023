#include "day_5/almanac.h"

#include <algorithm>
#include <compare>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace aoc
{
    // --------------------------------------------------------------------------------
    // Almanac range
    // --------------------------------------------------------------------------------

    AlmanacRange AlmanacRange::intersect(const AlmanacRange& rhs) const
    {
        return AlmanacRange(std::max(begin, rhs.begin), std::min(end, rhs.end));
    }

    AlmanacRange::operator bool() const
    {
        return begin < end;
    }

    std::strong_ordering operator<=>(const AlmanacRange& lhs, const AlmanacRange& rhs)
    {
        return lhs.begin <=> rhs.begin;
    }

    std::strong_ordering operator<=>(const AlmanacRange& lhs, const int64_t rhs)
    {
        if (rhs < lhs.begin)
        {
            return std::strong_ordering::greater;
        }

        if (rhs >= lhs.end)
        {
            return std::strong_ordering::less;
        }

        return std::strong_ordering::equal;
    }

    std::strong_ordering operator<=>(const int64_t lhs, const AlmanacRange& rhs)
    {
        return 0 <=> (rhs <=> lhs);
    }

    // --------------------------------------------------------------------------------
    // Almanac range converter
    // --------------------------------------------------------------------------------

    int64_t AlmanacRangeConverter::convert(const int64_t value) const
    {
        return value + offset;
    }

    std::strong_ordering operator<=>(const AlmanacRangeConverter& lhs, const AlmanacRangeConverter& rhs)
    {
        return lhs.range <=> rhs.range;
    }

    std::strong_ordering operator<=>(const AlmanacRangeConverter& lhs, const int64_t rhs)
    {
        return lhs.range <=> rhs;
    }

    std::strong_ordering operator<=>(const int64_t lhs, const AlmanacRangeConverter& rhs)
    {
        return 0 <=> (rhs.range <=> lhs);
    }

    // --------------------------------------------------------------------------------
    // Almanac category mapper
    // --------------------------------------------------------------------------------

    AlmanacCategoryMapper::AlmanacCategoryMapper(const std::vector<AlmanacRangeConverter>& converters) :
        m_converters(converters)
    {
    }

    int64_t AlmanacCategoryMapper::map(const int64_t value) const
    {
        auto it = std::lower_bound(m_converters.begin(), m_converters.end(), value);
        if (it != m_converters.end() && (*it <=> value) == 0)
        {
            return it->convert(value);
        }

        return value;
    }

    std::vector<AlmanacRange> AlmanacCategoryMapper::map_range(AlmanacRange range) const
    {
        std::vector<AlmanacRange> next_ranges;
        while (range)
        {
            auto it = std::lower_bound(m_converters.begin(), m_converters.end(), range.begin);
            if (it == m_converters.end())
            {
                next_ranges.push_back(range);
                break;
            }

            if ((*it <=> range.begin) == 0)
            {
                AlmanacRange left = range.intersect(it->range);
                next_ranges.emplace_back(left.begin + it->offset, left.end + it->offset);
                range.begin = left.end;
            }
            else
            {
                AlmanacRange left = range.intersect(AlmanacRange((it == m_converters.begin() ? 0 : (it - 1)->range.end), it->range.begin));
                next_ranges.push_back(left);
                range.begin = left.end;
            }
        }

        return next_ranges;
    }

    std::istream& operator>>(std::istream& is, AlmanacCategoryMapper& mapper)
    {
        std::string junk;
        std::getline(is, junk);
        
        for (std::string line; std::getline(is, line) && !line.empty(); )
        {
            std::istringstream line_stream(line);

            int64_t dest = 0;
            int64_t src = 0;
            int64_t length = 0;

            line_stream >> dest >> src >> length;

            mapper.m_converters.emplace_back(AlmanacRange(src, src + length), dest - src);
        }

        std::sort(mapper.m_converters.begin(), mapper.m_converters.end());

        return is;
    }

} // aoc
