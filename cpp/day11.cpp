#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const std::string PATH = "../../data/day11.txt";

struct point {
    int x_;
    int y_;
};
point operator+(const point &a, const point &b) { return {a.x_ + b.x_, a.y_ + b.y_}; }

bool inrange(const point &pt, const std::vector<std::string> &plan)
{
    auto width = static_cast<int>(plan[0].size());
    auto height = static_cast<int>(plan.size());
    return ((pt.x_ >= 0) && (pt.y_ >= 0) && (pt.x_ < width) && (pt.y_ < height));
}

const auto directions = std::vector<point>{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                           {0, 1},   {1, -1}, {1, 0},  {1, 1}};

int neighbours(const std::vector<std::string> &plan, int x, int y, bool check_ray)
{
    auto count = 0;
    for (const auto &dir : directions) {
        auto pt = point{x, y} + dir;
        while (check_ray && inrange(pt, plan) && plan[pt.y_][pt.x_] == '.') {
            pt = pt + dir;
        }
        if (inrange(pt, plan) && plan[pt.y_][pt.x_] == '#') {
            ++count;
        }
    }
    return count;
}

int run_until_static(std::vector<std::string> plan, int crowd, bool check_ray)
{
    auto width = plan[0].size();
    auto height = plan.size();

    auto next_plan = plan;
    bool changed = false;

    do {
        changed = false;
        for (size_t x = 0; x != width; ++x) {
            for (size_t y = 0; y != height; ++y) {
                auto s = plan[y][x];
                auto next = s;
                auto count = neighbours(
                    plan, static_cast<int>(x), static_cast<int>(y), check_ray);
                if (s == 'L' && count == 0) {
                    changed = true;
                    next = '#';
                } else if (s == '#' && count >= crowd) {
                    changed = true;
                    next = 'L';
                }
                next_plan[y][x] = next;
            }
        }
        std::swap(next_plan, plan);
    } while (changed);

    auto seats = 0;
    for (const auto &line : plan) {
        seats += std::count(line.begin(), line.end(), '#');
    }
    return seats;
}

int main()
{
    auto f = std::ifstream{PATH};
    auto line = std::string{};
    auto empty_plan = std::vector<std::string>{};

    while (std::getline(f, line)) {
        empty_plan.push_back(line);
    }

    std::cout << run_until_static(empty_plan, 4, false) << std::endl;
    std::cout << run_until_static(empty_plan, 5, true) << std::endl;

    return 0;
}
