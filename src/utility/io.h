#ifndef AOC_UTILITIES_IO_H
#define AOC_UTILITIES_IO_H

#include <filesystem>
#include <fstream>

namespace aoc
{
    // Simplifies the opening of a file by hiding away common checks.
    // If the file can't be opened, an exception will be thrown.
    std::ifstream open_file(const std::filesystem::path& path);

} // aoc

#endif // !AOC_UTILITIES_IO_H
