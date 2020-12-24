#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <utility>

const std::string PATH = "../../data/day24.txt";
using path_t = std::vector<std::string>;

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

    auto blacks = std::set<std::pair<int, int>>{};
    for (const auto &path : paths) {
        auto x = 0;
        auto y = 0;
        for (const auto &move : path) {
            if (move == "e") {
                ++x;
            } else if (move == "w") {
                --x;
            } else if (move == "ne") {
                --y;
            } else if (move == "nw") {
                --y;
                --x;
            } else if (move == "se") {
                ++y;
                ++x;
            } else if (move == "sw") {
                ++y;
            }
        }
        if (blacks.count({x, y}) > 0) {
            blacks.erase({x, y});
        } else {
            blacks.insert({x, y});
        }
    }

    std::cout << blacks.size() << std::endl;

    return 0;
}
