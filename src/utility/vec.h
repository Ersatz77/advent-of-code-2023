#ifndef AOC_UTILITIES_VEC_H
#define AOC_UTILITIES_VEC_H

#include "utility/utility.h"

#include "fmt/format.h"

#include <array>
#include <compare>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>

namespace aoc
{
    // --------------------------------------------------------------------------------
    // Vector 2
    // --------------------------------------------------------------------------------

    // A 2D vector with an x and y component
    template<Number T>
    class Vec2
    {
    public:
        // Returns all 4 (NESW) Vec2s around this Vec2
        std::array<Vec2<T>, 4> adjacent_cardinal() const
        {
            std::array<Vec2<T>, 4> adjacent = {};
            constexpr std::array<std::array<T, 2>, 4> offsets = { {
                {1, 0}, {-1, 0}, {0, 1}, {0, -1}
            } };
            for (size_t i = 0; i < adjacent.size(); ++i)
            {
                adjacent[i].x = x + offsets[i][0];
                adjacent[i].y = y + offsets[i][1];
            }

            return adjacent;
        }

        // Returns all 8 Vec2s around this Vec2
        std::array<Vec2<T>, 8> adjacent() const
        {
            std::array<Vec2<T>, 8> adjacent = {};
            constexpr std::array<std::array<T, 2>, 8> offsets = { {
                {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
            } };
            for (size_t i = 0; i < offsets.size(); ++i)
            {
                adjacent[i].x = x + offsets[i][0];
                adjacent[i].y = y + offsets[i][1];
            }
            return adjacent;
        }

        std::string to_string() const
        {
            return fmt::format("({}, {})", x, y);
        }

        std::array<T, 2> to_array() const
        {
            return { x, y };
        }

        auto operator<=>(const Vec2<T>& other) const = default;

        Vec2<T>& operator+=(const Vec2<T>& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vec2<T>& operator-=(const Vec2<T>& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vec2<T>& operator*=(const Vec2<T>& other)
        {
            x *= other.x;
            y *= other.y;
            return *this;
        }

        Vec2<T>& operator/=(const Vec2<T>& other)
        {
            x /= other.x;
            y /= other.y;
            return *this;
        }

        T x = 0;
        T y = 0;

        static const Vec2<T> origin;
    };

    template<Number T>
    Vec2<T> operator+(Vec2<T> lhs, const Vec2<T>& rhs)
    {
        return lhs += rhs;
    }

    template<Number T>
    Vec2<T> operator-(Vec2<T> lhs, const Vec2<T>& rhs)
    {
        return lhs -= rhs;
    }

    template<Number T>
    Vec2<T> operator*(Vec2<T> lhs, const Vec2<T>& rhs)
    {
        return lhs *= rhs;
    }

    template<Number T>
    Vec2<T> operator/(Vec2<T> lhs, const Vec2<T>& rhs)
    {
        return lhs /= rhs;
    }

    template<Number T>
    std::ostream& operator<<(std::ostream& os, const Vec2<T>& vec)
    {
        return os << vec.to_string();
    }

    template<Number T>
    const Vec2<T> Vec2<T>::origin = { 0, 0 };

    // --------------------------------------------------------------------------------
    // Vector 3
    // --------------------------------------------------------------------------------

    // A 3D vector with an x, y, and z component
    template<Number T>
    class Vec3
    {
    public:
        // Returns all 6 (NESWUD) Vec3s around this Vec3
        std::array<Vec3<T>, 6> adjacent_cardinal() const
        {
            std::array<Vec3<T>, 6> adjacent = {};
            constexpr std::array<std::array<T, 3>, 6> offsets = { {
                {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}
            } };
            for (size_t i = 0; i < offsets.size(); ++i)
            {
                adjacent[i].x = x + offsets[i][0];
                adjacent[i].y = y + offsets[i][1];
                adjacent[i].z = z + offsets[i][2];
            }
            return adjacent;
        }

        // Returns all 26 Vec3s around this Vec3
        std::array<Vec3<T>, 26> adjacent() const
        {
            std::array<Vec3<T>, 26> adjacent = {};
            constexpr std::array<std::array<T, 3>, 26> offsets = { {
                {1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1}, {1, 0, 1}, {1, 0, -1}, {-1, 0, 1}, {-1, 0, -1},
                {1, 1, 0}, {-1, 1, 0}, {0, 1, 1}, {0, 1, -1}, {1, 1, 1}, {1, 1, -1}, {-1, 1, 1}, {-1, 1, -1}, {0, 1, 0},
                {1, -1, 0}, {-1, -1, 0}, {0, -1, 1}, {0, -1, -1}, {1, -1, 1}, {1, -1, -1}, {-1, -1, 1}, {-1, -1, -1}, {0, -1, 0}
            } };
            for (size_t i = 0; i < offsets.size(); ++i)
            {
                adjacent[i].x = x + offsets[i][0];
                adjacent[i].y = y + offsets[i][1];
                adjacent[i].z = z + offsets[i][2];
            }
            return adjacent;
        }

        std::string to_string() const
        {
            return fmt::format("({}, {}, {})", x, y, z);
        }

        std::array<T, 3> to_array() const
        {
            return { x, y, z };
        }

        auto operator<=>(const Vec3<T>& other) const = default;

        Vec3<T>& operator+=(const Vec3<T>& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vec3<T>& operator-=(const Vec3<T>& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Vec3<T>& operator*=(const Vec3<T>& other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        Vec3<T>& operator/=(const Vec3<T>& other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        T x = 0;
        T y = 0;
        T z = 0;

        static const Vec3<T> origin;
    };

    template<Number T>
    const Vec3<T> Vec3<T>::origin = { 0, 0, 0 };

    template<Number T>
    Vec3<T> operator+(Vec3<T> lhs, const Vec3<T>& rhs)
    {
        return lhs += rhs;
    }

    template<Number T>
    Vec3<T> operator-(Vec3<T> lhs, const Vec3<T>& rhs)
    {
        return lhs -= rhs;
    }

    template<Number T>
    Vec3<T> operator*(Vec3<T> lhs, const Vec3<T>& rhs)
    {
        return lhs *= rhs;
    }

    template<Number T>
    Vec3<T> operator/(Vec3<T> lhs, const Vec3<T>& rhs)
    {
        return lhs /= rhs;
    }

    template<Number T>
    std::ostream& operator<<(std::ostream& os, const Vec3<T>& vec)
    {
        return os << vec.to_string();
    }

    // --------------------------------------------------------------------------------
    // Aliases for common vector types
    // --------------------------------------------------------------------------------

    using Point = Vec2<double>;
    using Point3D = Vec3<double>;

    // --------------------------------------------------------------------------------
    // Utility functions
    // --------------------------------------------------------------------------------

    template<Number T>
    Point make_point(const T x, const T y)
    {
        return Point(static_cast<double>(x), static_cast<double>(y));
    }

    template<Number T>
    Point3D make_point_3d(const T x, const T y, const T z)
    {
        return Point3D(static_cast<double>(x), static_cast<double>(y) ,static_cast<double>(z));
    }

} // aoc

namespace std
{
    template<aoc::Number T>
    struct hash<aoc::Vec2<T>>
    {
        size_t operator()(const aoc::Vec2<T>& vec) const
        {
            size_t seed = 0;
            aoc::hash_combine(seed, vec.x);
            aoc::hash_combine(seed, vec.y);
            return seed;
        }
    };

    template<aoc::Number T>
    struct hash<aoc::Vec3<T>>
    {
        size_t operator()(const aoc::Vec3<T>& vec) const
        {
            size_t seed = 0;
            aoc::hash_combine(seed, vec.x);
            aoc::hash_combine(seed, vec.y);
            aoc::hash_combine(seed, vec.z);
            return seed;
        }
    };

    template<aoc::Number T>
    struct hash<pair<aoc::Vec2<T>, aoc::Vec2<T>>>
    {
        size_t operator()(const pair<aoc::Vec2<T>, aoc::Vec2<T>>& p) const
        {
            size_t seed = 0;
            aoc::hash_combine(seed, p.first.x);
            aoc::hash_combine(seed, p.first.y);
            aoc::hash_combine(seed, p.second.x);
            aoc::hash_combine(seed, p.second.y);
            return seed;
        }
    };

    template<aoc::Number T>
    struct hash<pair<aoc::Vec3<T>, aoc::Vec3<T>>>
    {
        size_t operator()(const pair<aoc::Vec3<T>, aoc::Vec3<T>>& p) const
        {
            size_t seed = 0;
            aoc::hash_combine(seed, p.first.x);
            aoc::hash_combine(seed, p.first.y);
            aoc::hash_combine(seed, p.first.z);
            aoc::hash_combine(seed, p.second.x);
            aoc::hash_combine(seed, p.second.y);
            aoc::hash_combine(seed, p.second.z);
            return seed;
        }
    };

} // std

#endif // !AOC_UTILITIES_VEC_H
