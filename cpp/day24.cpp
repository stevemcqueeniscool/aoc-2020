#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>

#include "absl/container/flat_hash_set.h"

const std::string PATH = "../../data/day24.txt";
using vec = std::pair<int, int>;
using board_t = absl::flat_hash_set<vec>;

vec add_vec(const vec &a, const vec &b)
{
    return {a.first + b.first, a.second + b.second};
}

auto deltas =
    std::map<std::string, vec>{{"e", {1, 0}},    {"w", {-1, 0}}, {"ne", {0, -1}},
                               {"nw", {-1, -1}}, {"se", {1, 1}}, {"sw", {0, 1}}};

int main()
{
    auto f = std::ifstream{PATH};
    auto dir_regex = std::regex{"sw|se|nw|ne|w|e"};
    auto line = std::string{};
    auto today = board_t{};
    while (std::getline(f, line)) {
        auto pos = vec{0, 0};
        auto matches_begin = std::sregex_iterator(line.begin(), line.end(), dir_regex);
        auto matches_end = std::sregex_iterator();
        for (auto i = matches_begin; i != matches_end; ++i) {
            pos = add_vec(pos, deltas[(*i)[0]]);
        }
        if (today.count(pos) > 0) {
            today.erase(pos);
        } else {
            today.insert(pos);
        }
    }

    std::cout << today.size() << std::endl;

    for (int day = 0; day != 100; ++day) {
        auto tomorrow = board_t{};
        for (const auto &b : today) {
            for (const auto &[_, dir] : deltas) {
                const auto p = add_vec(b, dir);
                auto ncount = std::count_if(
                    deltas.begin(), deltas.end(), [&p, &today](const auto &d) {
                        return today.count(add_vec(p, d.second)) > 0;
                    });
                auto black = today.count(p) > 0;
                if ((black && (ncount == 1 || ncount == 2)) ||
                    (!black && ncount == 2)) {
                    tomorrow.insert(p);
                }
            }
        }
        today = std::move(tomorrow);
    }

    std::cout << today.size() << std::endl;
    return 0;
}
