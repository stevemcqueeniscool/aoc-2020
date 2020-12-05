#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const std::string PATH = "../../data/day05.txt";

int code_to_int2(std::string str)
{
    std::replace(str.begin(), str.end(), 'R', '1');
    std::replace(str.begin(), str.end(), 'L', '0');
    std::replace(str.begin(), str.end(), 'B', '1');
    std::replace(str.begin(), str.end(), 'F', '0');
    return std::stoi(str, nullptr, 2);
}

int main()
{
    std::ifstream f(PATH);
    std::string line;
    std::vector<int> codes;
    int result_a = 0;
    while (std::getline(f, line)) {
        const int code = code_to_int2(line);
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
