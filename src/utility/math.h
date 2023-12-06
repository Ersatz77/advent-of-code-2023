#ifndef AOC_UTILITIES_MATH_H
#define AOC_UTILITIES_MATH_H

#include "utility/utility.h"
#include "utility/vec.h"

#include <cmath>
#include <concepts>
#include <utility>

namespace aoc
{
    template<std::integral T>
    T manhattan_distance(const T x1, const T y1, const T x2, const T y2)
    {
        return std::abs(x2 - x1) + std::abs(y2 - y1);
    }

    template<std::integral T>
    T manhattan_distance(const T x1, const T y1, const T x2, const T y2, const T z1, const T z2)
    {
        return std::abs(x2 - x1) + std::abs(y2 - y1) + std::abs(z2 - z1);
    }

    template<Number T>
    T manhattan_distance(const Vec2<T>& vec1, const Vec2<T>& vec2)
    {
        return std::abs(vec2.x - vec1.x) + std::abs(vec2.y - vec1.y);
    }

    template<Number T>
    T manhattan_distance(const Vec3<T>& vec1, const Vec3<T>& vec2)
    {
        return std::abs(vec2.x - vec1.x) + std::abs(vec2.y - vec1.y) + std::abs(vec2.z - vec1.z);
    }

    template<std::integral T>
    T signum(const T v)
    {
        return (0 < v) - (v < 0);
    }

    template<Number T>
    T gaussian_sum(const T a, const T b)
    {
        return ((b - a) * (b - a + 1)) / 2;
    }

    template<Number T>
    T euclid_mod(const T a, const T b)
    {
        return ((a % b) + b) % b;
    }

    template<std::integral T>
    T pow(T base, T exp)
    {
        T result = 1;
        while (exp)
        {
            if (exp % 2)
            {
                result *= base;
            }

            exp /= 2;
            base *= base;
        }

        return result;
    }

    std::pair<double, double> quadratic(const double a, const double b, const double c)
    {
        double determinant = (b * b) - (4.0 * a * c);
        double root_1 = (-b + std::sqrt(determinant)) / (2 * a);
        double root_2 = (-b - std::sqrt(determinant)) / (2 * a);

        return { root_1, root_2 };
    }

    std::pair<float, float> quadratic(const float a, const float b, const float c)
    {
        float determinant = (b * b) - (4.0 * a * c);
        float root_1 = (-b + std::sqrtf(determinant)) / (2 * a);
        float root_2 = (-b - std::sqrtf(determinant)) / (2 * a);

        return { root_1, root_2 };
    }

} // aoc

#endif // !AOC_UTILITIES_MATH_H
