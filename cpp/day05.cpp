#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const std::string PATH = "../../data/day05.txt";

int code_to_int(std::string str)
{
    auto result = 0;
    for (const auto ch : str) {
        result <<= 1;
        if ((ch == 'R') || (ch == 'B')) {
            result += 1;
        }
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

    int result_b = 0;
    std::sort(codes.begin(), codes.end());
    for (size_t i = 0; i != codes.size() - 1; ++i) {
        if (codes[i + 1] != codes[i] + 1) {
            result_b = codes[i] + 1;
        }
    }
    std::cout << result_b << std::endl;

    return 0;
}
