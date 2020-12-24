cmake_minimum_required(VERSION 3.16)

project(aoc2020)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-march=znver1 -g -Wall -Wextra)

add_subdirectory(scnlib)
add_subdirectory(abseil-cpp)

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

add_executable(day12 day12.cpp)
target_link_libraries(day12 scn::scn)
add_executable(day12b day12b.cpp)
target_link_libraries(day12b scn::scn)

add_executable(day14 day14.cpp)
add_executable(day14b day14b.cpp)

add_executable(day15 day15.cpp)

add_executable(day17 day17.cpp)
target_link_libraries(day17 absl::flat_hash_map)

add_executable(day18 day18.cpp)

add_executable(day22 day22.cpp)
target_link_libraries(day22 absl::flat_hash_map)

add_executable(day23 day23.cpp)
add_executable(day23b day23b.cpp)

add_executable(day24 day24.cpp)
