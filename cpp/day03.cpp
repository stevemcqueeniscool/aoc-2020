#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int count_trees(const std::vector<std::string>& data, int dx, int dy)
{
    size_t width = data[0].size(), height = data.size();
    size_t x = 0, y = 0;
    int result = 0;

    while (y < height) {
	if (data[y][x % width] == '#') {
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
    std::vector<std::string> data;
    while (std::getline(input, line)) {
        data.push_back(line);
    }

    auto result_a = count_trees(data, 3, 1);
    auto result_b = count_trees(data, 1, 1) * count_trees(data, 3, 1) *
                    count_trees(data, 5, 1) * count_trees(data, 7, 1) *
                    count_trees(data, 1, 2);

    std::cout << result_a << std::endl;
    std::cout << result_b << std::endl;

    return 0;
}
