#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

const std::string PATH = "../../data/day09.txt";
const int WINDOW = 25;

bool valid(const std::unordered_set<int> &wind, int target)
{
    return std::any_of(
        wind.begin(), wind.end(), [&](auto x) { return wind.count(target - x); });
}

int find_target(const std::vector<int> &xs, int target)
{
    for (size_t i = 0; i != xs.size(); ++i) {
        auto sum = xs[i];
        for (size_t j = i + 1; j != xs.size(); ++j) {
            sum += xs[j];
            if (sum == target) {
                auto min = std::min_element(xs.begin() + i, xs.begin() + j + 1);
                auto max = std::max_element(xs.begin() + i, xs.begin() + j + 1);
                return *min + *max;
            }
        }
    }
    return -1;
}

int main()
{
    std::vector<int> xs;
    std::fstream f(PATH, std::ios_base::in);
    int x;
    while (f >> x) {
        xs.push_back(x);
    }

    int result_a = 0;
    auto wind = std::unordered_set<int>(xs.begin(), xs.begin() + WINDOW);
    for (size_t i = WINDOW; i != xs.size(); ++i) {
        if (valid(wind, xs[i])) {
            wind.erase(xs[i - WINDOW]);
            wind.insert(xs[i]);
        } else {
            result_a = xs[i];
            break;
        }
    }
    std::cout << result_a << std::endl;
    std::cout << find_target(xs, result_a) << std::endl;

    return 0;
}
