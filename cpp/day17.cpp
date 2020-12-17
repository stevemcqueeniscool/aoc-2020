#include <array>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "absl/container/flat_hash_set.h"

// clang-format off
const auto input = std::vector<std::string>{
    ".#.####.",
    ".#...##.",
    "..###.##",
    "#..#.#.#",
    "#..#....",
    "#.####..",
    "##.##..#",
    "#.#.#..#",
};
// clang-format on

template <int D> using point_t = std::array<int, D>;
// template <int D> using pt_set_t = std::set<point_t<D>>;          // run time: 155ms
template <int D> using pt_set_t = absl::flat_hash_set<point_t<D>>;  // run time: 45ms

constexpr size_t ipower(int base, int power) {
    return power == 0 ? 1 : base * ipower(base, power - 1);
}

template <int D> std::vector<point_t<D>> all_neighbours(const point_t<D> &pt)
{
    static constexpr auto deltas = std::array{-1, 0, 1};
    static constexpr auto res_size = ipower(3, D);
    auto result = std::vector<point_t<D>>(res_size, pt);
    auto repeat_max = 1;
    for (size_t idx = 0; idx != pt.size(); ++idx) {
        auto result_idx = size_t{0};
        while (result_idx != result.size()) {
            for (auto delta : deltas) {
                for (auto r = 0; r != repeat_max; ++r) {
                    result[result_idx++][idx] += delta;
                }
            }
        }
        repeat_max *= deltas.size();
    }
    result.pop_back(); // remove pt itself
    return result;
}

template <int D> int simulation(std::vector<std::string> input)
{
    pt_set_t<D> points;
    for (size_t y = 0; y != input.size(); ++y) {
        for (size_t x = 0; x != input[y].size(); ++x) {
            if (input[y][x] == '#') {
                auto v = point_t<D>{};
                v[0] = x;
                v[1] = y;
                points.insert(v);
            }
        }
    }

    for (int cycle = 0; cycle != 6; ++cycle) {
        auto next_gen = pt_set_t<D>{};
        auto consider = pt_set_t<D>{};

        for (const auto &pt : points) {
            const auto ns = all_neighbours<D>(pt);
            consider.insert(ns.begin(), ns.end());
        }

        for (const auto &pt : consider) {
            const auto nbs = all_neighbours<D>(pt);
            auto n = std::count_if(nbs.begin(), nbs.end(), [&points](const auto &nbr) {
                return points.count(nbr);
            });
            const auto alive = points.count(pt) == 1;
            if (alive && ((n == 2) || (n == 3))) {
                next_gen.insert(pt);
            }
            if (!alive && n == 3) {
                next_gen.insert(pt);
            }
        }
        std::swap(points, next_gen);
    }
    return points.size();
}

int main()
{
    std::cout << simulation<3>(input) << std::endl;
    std::cout << simulation<4>(input) << std::endl;

    return 0;
}
