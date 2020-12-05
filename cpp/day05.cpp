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
    std::vector<std::string> lines;
    while (std::getline(f, line)) {
        lines.push_back(line);
    }

    int result_a = 0;
    for (const auto &ln : lines) {
        const int code = code_to_int(ln);
        result_a = std::max(result_a, code);
    }
    std::cout << result_a << std::endl;

    return 0;
}
