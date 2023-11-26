#ifndef AOC_UTILITIES_UTILITY_H
#define AOC_UTILITIES_UTILITY_H

#include <array>
#include <concepts>
#include <cstdint>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace aoc
{
    template<typename T>
    concept Number = std::is_arithmetic_v<T>;

    template<typename T>
    inline void hash_combine(size_t& seed, const T& v)
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9E3779B9 + (seed << 6) + (seed >> 2);
    }

    // Creates an integer number out of a vector of digits
    template<std::integral T>
    T vec_to_int(const std::vector<T>& vec)
    {
        T result = 0;
        for (const T i : vec)
        {
            result += i;
            result *= 10;
        }

        return result;
    }

    // Creates an integer number out of an array of digits
    template<std::integral T, size_t N>
    T array_to_int(const std::array<T, N>& arr)
    {
        T result = 0;
        for (const T i : arr)
        {
            result *= 10;
            result += i;
        }

        return result;
    }

} // aoc

namespace std
{
    template<>
    struct hash<pair<char, char>>
    {
        size_t operator()(const pair<char, char>& p)
        {
            size_t seed = 0;
            aoc::hash_combine(seed, p.first);
            aoc::hash_combine(seed, p.second);
            return seed;
        }
    };

    template<>
    struct hash<pair<string, string>>
    {
        size_t operator()(const pair<string, string>& p)
        {
            size_t seed = 0;
            aoc::hash_combine(seed, p.first);
            aoc::hash_combine(seed, p.second);
            return seed;
        }
    };

    template<>
    struct hash<pair<int, int>>
    {
        size_t operator()(const pair<int, int>& p)
        {
            size_t seed = 0;
            aoc::hash_combine(seed, p.first);
            aoc::hash_combine(seed, p.second);
            return seed;
        }
    };

} // std

#endif // !AOC_UTILITIES_UTILITY_H
