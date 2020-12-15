cmake_minimum_required(VERSION 3.16)

project(aoc2020)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)
add_subdirectory(scnlib)

add_executable(day02 day02.cpp)
target_link_libraries(day02 scn::scn)

add_executable(day03 day03.cpp)

add_executable(day04 day04.cpp)

add_executable(day05 day05.cpp)

add_executable(day07 day07.cpp)

add_executable(day08 day08.cpp)
target_link_libraries(day08 scn::scn)

add_executable(day09 day09.cpp)

add_executable(day11 day11.cpp)

add_executable(day15 day15.cpp)
