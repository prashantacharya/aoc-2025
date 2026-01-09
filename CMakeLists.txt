cmake_minimum_required(VERSION 3.14)
project(AOC_2025 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Setup GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

# 2. Define the Common Library
add_library(aoc_common common/helpers.cpp)
target_include_directories(aoc_common PUBLIC common)

# 3. Define Day-Specific Logic Libraries
# This allows us to share logic between main.cpp and test_logic.cpp
add_library(day06_logic day-6/src/logic.cpp)
target_include_directories(day06_logic PUBLIC day-6/src)

# 4. Define Day Executables
add_executable(day01 day-1/main.cpp)
add_executable(day02 day-2/main.cpp)
add_executable(day03 day-3/main.cpp)
add_executable(day04 day-4/main.cpp)
add_executable(day05 day-5/main.cpp)

# Day 06 Links to both common helpers and its own logic
add_executable(day06 day-6/src/main.cpp) 
target_link_libraries(day06 aoc_common day06_logic)

add_executable(day07 day-7/src/main.cpp) 
target_link_libraries(day07 aoc_common)

# 5. Define Tests
# Note: linking gtest_main provides the main() function for the test
add_executable(test_day06 day-6/tests/test_logic.cpp)
target_link_libraries(test_day06 day06_logic aoc_common gtest_main)
add_test(NAME Day06Test COMMAND test_day06)
