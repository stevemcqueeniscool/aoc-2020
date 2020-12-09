#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

const std::string PATH = "../../data/day09.txt";
const int WINDOW = 25;

bool valid(const std::unordered_set<int> &wind, int target)
{
    for (auto x : wind) {
        const auto y = target - x;
        if (wind.count(y) > 0) {
            return true;
        }
    }
    return false;
}

int main()
{
    std::vector<int> xs;
    std::fstream f(PATH, std::ios_base::in);
    int x;
    while (f >> x) {
        xs.push_back(x);
    }

    auto wind = std::unordered_set<int>(xs.begin(), xs.begin() + WINDOW);
    for (size_t i = WINDOW; i != xs.size(); ++i) {
        if (valid(wind, xs[i])) {
            wind.erase(xs[i - WINDOW]);
            wind.insert(xs[i]);
        } else {
            std::cout << xs[i] << std::endl;
            break;
        }
    }

    return 0;
}
