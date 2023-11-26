#include "utility/io.h"

#include "fmt/format.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace aoc
{
    std::ifstream open_file(const std::filesystem::path& path)
    {
        std::ifstream file(path);
        if (!file)
        {
            throw std::runtime_error(fmt::format("Unable to open {}", path.filename().string()));
        }

        return file;
    }

} // aoc
