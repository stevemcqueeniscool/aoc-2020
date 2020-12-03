cmake_minimum_required(VERSION 3.16)

project(aoc2020)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)

add_subdirectory(scnlib)
add_executable(day02 day02.cpp)
target_link_libraries(day02 scn::scn)
