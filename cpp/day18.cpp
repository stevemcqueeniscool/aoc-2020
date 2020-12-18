#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

const auto PATH = "../../data/day18.txt";
using val_t = std::uint64_t;

val_t expr(const std::string &line, size_t &idx, bool pt2);

val_t value(const std::string &line, size_t &idx, bool pt2)
{
    val_t val;
    auto ch = line[idx++];
    if (ch == '(') {
        val = expr(line, idx, pt2);
        ++idx; // ')'
    } else {
        val = ch - '0';
    }
    return val;
}

val_t expr(const std::string &line, size_t &idx, bool pt2)
{
    auto acc = value(line, idx, pt2);
    while (idx != line.size() && (line[idx] == '+' || line[idx] == '*')) {
        const auto op = line[idx++];
        val_t rhs = (op == '*' && pt2) ? expr(line, idx, pt2) : value(line, idx, pt2);
        acc = op == '+' ? (acc + rhs) : (acc * rhs);
    }
    return acc;
}

int main()
{
    std::ifstream f(PATH);
    std::string line;

    val_t result_a = 0, result_b = 0;
    while (std::getline(f, line)) {
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        size_t idx = 0;
        result_a += expr(line, idx, false);
        idx = 0;
        result_b += expr(line, idx, true);
    }
    std::cout << result_a << "\n" << result_b << std::endl;

    return 0;
}
