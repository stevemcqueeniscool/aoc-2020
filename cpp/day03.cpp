#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using point_t = std::pair<size_t, size_t>;

class forest
{
public:
    forest(const std::vector<std::string> &data)
        : width_(data[0].size()), height_(data.size())
    {
        for (size_t row = 0; row != height_; ++row) {
            for (size_t col = 0; col != width_; ++col) {
                if (data[row][col] == '#') {
                    trees_.emplace(col, row);
                }
            }
        }
    }

    bool is_tree(size_t x, size_t y) const { return trees_.count({x % width_, y}); }

    size_t width_;
    size_t height_;
    std::set<point_t> trees_;
};

int count_slope(const forest &f, int dx, int dy)
{
    size_t x = 0, y = 0;
    int result = 0;
    while (y < f.height_) {
        if (f.is_tree(x, y)) {
            ++result;
        }
        x += dx;
        y += dy;
    }
    return result;
}

const std::string PATH = "../../data/day03.txt";

int main()
{
    std::ifstream input(PATH);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }

    forest f{lines};
    auto result_a = count_slope(f, 3, 1);
    auto result_b = count_slope(f, 1, 1) * count_slope(f, 3, 1) * count_slope(f, 5, 1) *
                    count_slope(f, 7, 1) * count_slope(f, 1, 2);

    std::cout << result_a << std::endl;
    std::cout << result_b << std::endl;

    return 0;
}
