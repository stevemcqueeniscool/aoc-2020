#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <utility>

#include "absl/container/flat_hash_set.h"

const std::string PATH = "../../data/day24.txt";
using path_t = std::vector<std::string>;

struct vec {
    int x_;
    int y_;

    template <typename H> friend H AbslHashValue(H h, const vec &v)
    {
        return H::combine(std::move(h), v.x_, v.y_);
    }
};

using board_t = absl::flat_hash_set<vec>;

bool operator==(const vec &a, const vec &b)
{
    return std::make_pair(a.x_, a.y_) == std::make_pair(b.x_, b.y_);
}

vec operator+(const vec &a, const vec &b) { return {a.x_ + b.x_, a.y_ + b.y_}; }

auto deltas =
    std::map<std::string, vec>{{"e", {1, 0}},    {"w", {-1, 0}}, {"ne", {0, -1}},
                               {"nw", {-1, -1}}, {"se", {1, 1}}, {"sw", {0, 1}}};

board_t potential_tiles(const board_t &blacks)
{
    auto result = board_t{};
    for (const auto &p : blacks) {
        for (const auto &[_, d] : deltas) {
            result.insert(p + d);
        }
    }
    return result;
}

size_t simulate(board_t today, int days)
{
    for (int day = 0; day != days; ++day) {
        auto tomorrow = board_t{};
        for (const auto &p : potential_tiles(today)) {
            auto ncount = std::count_if(
                deltas.begin(), deltas.end(),
                [&p, &today](const auto &d) { return today.count(p + d.second) > 0; });

            if ((today.count(p) && (ncount == 1 || ncount == 2)) ||
                (today.count(p) == 0 && ncount == 2)) {
                tomorrow.insert(p);
            }
        }
        today = std::move(tomorrow);
    }
    return today.size();
}

int main()
{
    auto direction_regex = std::regex{"ne|nw|se|sw|e|w"};

    auto paths = std::vector<path_t>{};

    auto f = std::ifstream{PATH};
    auto line = std::string{};
    while (std::getline(f, line)) {
        auto path = path_t{};
        auto matches_begin =
            std::sregex_iterator(line.begin(), line.end(), direction_regex);
        auto matches_end = std::sregex_iterator();
        for (auto i = matches_begin; i != matches_end; ++i) {
            path.push_back((*i)[0]);
        }
        paths.push_back(path);
    }

    auto blacks = board_t{};
    for (const auto &path : paths) {
        auto pos = vec{0, 0};
        for (const auto &move : path) {
            pos = pos + deltas[move];
        }

        if (blacks.count(pos) > 0) {
            blacks.erase(pos);
        } else {
            blacks.insert(pos);
        }
    }

    std::cout << blacks.size() << std::endl;
    std::cout << simulate(blacks, 100) << std::endl;
    return 0;
}
