#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <scn/scn.h>
#include <scn/tuple_return.h>

const std::string PATH = "../../data/day12.txt";

struct point {
    int x_;
    int y_;
};
point operator+(const point &a, const point &b) { return {a.x_ + b.x_, a.y_ + b.y_}; }
point operator-(const point &a, const point &b) { return {a.x_ - b.x_, a.y_ - b.y_}; }
point operator*(int s, const point &a) { return {s * a.x_, s * a.y_}; }

auto steps = std::unordered_map<char, point>{
    {'N', {0, 1}}, {'E', {1, 0}}, {'S', {0, -1}}, {'W', {-1, 0}}};

auto rotations = std::vector<std::function<point(point)>>{
    [](const point &p) {
        return point{p.x_, p.y_};
    },
    [](const point &p) {
        return point{p.y_, -p.x_};
    },
    [](const point &p) {
        return point{-p.x_, -p.y_};
    },
    [](const point &p) {
        return point{-p.y_, p.x_};
    }};

int main()
{
    std::ifstream input(PATH);
    std::string line;
    std::vector<std::pair<char, int>> directions;
    while (std::getline(input, line)) {
        const auto [_, cmd, amt] = scn::scan_tuple<char, int>(line, "{}{}");
        directions.emplace_back(cmd, amt);
    }

    auto ship = point{0, 0};
    auto waypoint = point{10, 1};

    for (const auto &[cmd, amt] : directions) {
        if (cmd == 'L' || cmd == 'R') {
            auto adj = cmd == 'R' ? amt : 360 - amt;
            waypoint = rotations[adj / 90](waypoint);
        } else if (cmd == 'F') {
            ship = ship + amt * waypoint;
        } else {
            waypoint = waypoint + (amt * steps[cmd]);
        }
    }

    std::cout << std::abs(ship.x_) + std::abs(ship.y_) << std::endl;
    return 0;
}
