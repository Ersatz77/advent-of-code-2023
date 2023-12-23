cmake_minimum_required(VERSION 3.27)
project(advent_of_code_2023
    LANGUAGES CXX
    VERSION 1.0.0
)

# Check for in-source builds
include(cmake/ban_in_source_builds.cmake)

# ------------------------------------------------------------------------------
# Create target for specifying the C++ standard and compiler specific options
# ------------------------------------------------------------------------------
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(project_options INTERFACE)
target_compile_features(project_options
    INTERFACE
        cxx_std_23
)

# Enable multi-processor compilation on MSVC
if(MSVC)
    target_compile_options(project_options
        INTERFACE
            /MP
    )
endif()

# ------------------------------------------------------------------------------
# Create target for compiler warnings
# ------------------------------------------------------------------------------
include(cmake/compiler_warnings.cmake)
add_library(project_warnings INTERFACE)
option(project_warnings_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
set_project_warnings(project_warnings
    ${project_warnings_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
)

# ------------------------------------------------------------------------------
# Manage dependencies
# ------------------------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(fmt
    GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
    GIT_TAG        "10.1.1"
)

message(STATUS "Populating dependencies...")
FetchContent_MakeAvailable(fmt)

# ------------------------------------------------------------------------------
# Create executable
# ------------------------------------------------------------------------------
add_executable(aoc_2023_app "src/main.cpp" "src/utility/utility.h" "src/utility/day.h" "src/utility/day.cpp" "src/utility/io.h" "src/utility/io.cpp" "src/utility/string.h" "src/utility/string.cpp" "src/utility/vec.h" "src/utility/math.h" "src/utility/math.cpp" "src/day_1/day_1.h" "src/day_1/day_1.cpp" "src/day_2/day_2.h" "src/day_2/day_2.cpp" "src/day_3/day_3.h" "src/day_3/day_3.cpp" "src/day_4/day_4.h" "src/day_4/day_4.cpp" "src/day_4/scratchcard.h" "src/day_4/scratchcard.cpp" "src/day_5/day_5.h" "src/day_5/day_5.cpp" "src/day_5/almanac.h" "src/day_5/almanac.cpp" "src/day_6/day_6.h" "src/day_6/day_6.cpp" "src/day_7/day_7.h" "src/day_7/day_7.cpp" "src/day_7/camel_cards.h" "src/day_7/camel_cards.cpp" "src/day_8/day_8.h" "src/day_8/day_8.cpp" "src/day_9/day_9.h" "src/day_9/day_9.cpp" "src/day_10/day_10.h" "src/day_10/day_10.cpp" "src/day_11/day_11.h" "src/day_11/day_11.cpp" "src/day_12/day_12.h" "src/day_12/day_12.cpp" "src/day_13/day_13.h" "src/day_13/day_13.cpp" "src/day_14/day_14.h" "src/day_14/day_14.cpp" "src/day_15/day_15.h" "src/day_15/day_15.cpp" "src/day_15/lensmap.h" "src/day_15/lensmap.cpp" "src/day_16/day_16.h" "src/day_16/day_16.cpp" "src/day_17/day_17.h" "src/day_17/day_17.cpp" "src/day_18/day_18.h" "src/day_18/day_18.cpp" "src/day_19/day_19.h" "src/day_19/day_19.cpp" "src/day_20/day_20.h" "src/day_20/day_20.cpp" "src/day_20/machine_module.h" "src/day_20/machine_module.cpp" "src/day_21/day_21.h" "src/day_21/day_21.cpp" "src/day_22/day_22.h" "src/day_22/day_22.cpp" "src/day_23/day_23.h" "src/day_23/day_23.cpp" "src/day_24/day_24.h" "src/day_24/day_24.cpp")

target_include_directories(aoc_2023_app
    PRIVATE
        "src/"
)

target_link_libraries(aoc_2023_app
    PRIVATE
        project_options
        project_warnings
        fmt::fmt
)

# ------------------------------------------------------------------------------
# Install options
# ------------------------------------------------------------------------------
install(
    TARGETS
        aoc_2023_app
)