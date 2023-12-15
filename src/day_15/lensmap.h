#ifndef AOC_2023_DAY_15_LENSMAP_H
#define AOC_2023_DAY_15_LENSMAP_H

#include <array>
#include <cstdint>
#include <list>
#include <string>
#include <utility>

namespace aoc
{
    enum class LavaInitOperation
    {
        ADD,
        REMOVE,
    };

    struct LavaInitStep
    {
        std::string label;
        LavaInitOperation op;
        int64_t focal_length;

        std::string raw;
    };

    class LensMap
    {
    public:
        LensMap() = default;

        void add(const std::string& key, const int64_t value);
        void remove(const std::string& key);

        int64_t size() const;
        int64_t focusing_power() const;

        static size_t hasher(const std::string& key);

    private:
        using Lens = std::pair<std::string, int64_t>;

        std::array<std::list<Lens>, 256> m_boxes;
    };

} // aoc

#endif // !AOC_2023_DAY_15_LENSMAP_H
