#include "utility/math.h"
#include "utility/string.h"
#include "utility/vec.h"

#include "fmt/format.h"

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

int main()
{
    std::cout << aoc::manhattan_distance(aoc::Point3D::origin, aoc::Point3D(2, 3, 2)) << '\n';

    return 0;
}