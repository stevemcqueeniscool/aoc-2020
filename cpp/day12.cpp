#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <scn/scn.h>
#include <scn/tuple_return.h>

const std::string PATH = "../../data/day12.txt";

using inst_t = std::pair<char, int>;

struct point {
    int x_;
    int y_;
};
point operator+(const point &a, const point &b) { return {a.x_ + b.x_, a.y_ + b.y_}; }
point operator*(int s, const point &a) { return {s * a.x_, s * a.y_}; }

auto steps = std::unordered_map<char, point>{
    {'N', {0, -1}}, {'E', {1, 0}}, {'S', {0, 1}}, {'W', {-1, 0}}};

const auto compass = std::string{"ESWN"};

int main()
{
    std::ifstream input(PATH);
    std::string line;
    std::vector<inst_t> directions;
    while (std::getline(input, line)) {
        const auto [_, cmd, amt] = scn::scan_tuple<char, int>(line, "{}{}");
        directions.emplace_back(cmd, amt);
    }

    auto pos = point{0, 0};
    auto heading = 'E';

    for (const auto &[cmd, amt] : directions) {
        if (cmd == 'L' || cmd == 'R') {
            auto idx = compass.find(heading);
            auto m = cmd == 'R' ? 1 : -1;
            auto turns = m * (amt / 90);

            heading = compass[(idx + turns) % 4];
        } else if (cmd == 'F') {
            pos = pos + (amt * steps[heading]);
        } else {
            pos = pos + (amt * steps[cmd]);
        }
    }
    std::cout << std::abs(pos.x_) + std::abs(pos.y_) << std::endl;

    return 0;
}
