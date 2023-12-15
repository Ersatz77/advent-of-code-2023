#include "day_15/lensmap.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <list>
#include <string>
#include <utility>

namespace aoc
{
    void LensMap::add(const std::string& key, const int64_t value)
    {
        size_t idx = hasher(key);
        std::list<Lens>& box = m_boxes[idx];

        auto it = std::find_if(box.begin(), box.end(), [&key](const Lens& lens) { return lens.first == key; });
        if (it != box.end())
        {
            it->second = value;
            return;
        }

        box.emplace_back(key, value);
    }

    void LensMap::remove(const std::string& key)
    {
        size_t idx = hasher(key);
        std::list<Lens>& box = m_boxes[idx];

        box.remove_if([&key](const Lens& lens) { return lens.first == key; });
    }

    int64_t LensMap::size() const
    {
        size_t total_size = 0;
        for (const std::list<Lens> box : m_boxes)
        {
            total_size += box.size();
        }

        return total_size;
    }

    int64_t LensMap::focusing_power() const
    {
        int64_t power = 0;
        for (size_t i = 0; i < m_boxes.size(); ++i)
        {
            const std::list<Lens>& box = m_boxes[i];

            auto it = box.begin();
            size_t j = 0;
            while (it != box.end())
            {
                power += (i + 1) * (j + 1) * it->second;

                ++it;
                ++j;
            }
        }

        return power;
    }

    size_t LensMap::hasher(const std::string& key)
    {
        int64_t hash = 0;
        for (const char c : key)
        {
            hash += static_cast<int64_t>(c);
            hash *= 17;
            hash %= 256;
        }

        return hash;
    }

} // aoc
