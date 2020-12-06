#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const std::string PATH = "../../data/day05.txt";

int code_to_int(std::string str)
{
    int result = 0;
    for (const auto ch : str) {
        result = (result * 2) + ((ch == 'R' || ch == 'B') ? 1 : 0);
    }
    return result;
}

int main()
{
    std::ifstream f(PATH);
    std::string line;
    std::vector<int> codes;
    int result_a = 0;
    while (std::getline(f, line)) {
        const int code = code_to_int(line);
        result_a = std::max(result_a, code);
        codes.push_back(code);
    }
    std::cout << result_a << std::endl;

    std::sort(codes.begin(), codes.end());
    const auto r = std::adjacent_find(
        codes.begin(), codes.end(), [](int x, int y) { return y == x + 2; });
    std::cout << *r + 1 << std::endl;

    return 0;
}
