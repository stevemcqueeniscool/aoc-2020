#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const auto PATH = "../../data/day18.txt";
using val_t = std::uint64_t;

val_t expr(std::vector<char> &tokens, bool prefer_plus);

val_t value(std::vector<char> &tokens, bool prefer_plus)
{
    val_t val;
    auto ch = tokens.back();
    tokens.pop_back();
    if (ch == '(') {
        val = expr(tokens, prefer_plus);
        tokens.pop_back(); // ')'
    } else {
        val = ch - '0';
    }
    return val;
}

val_t expr(std::vector<char> &tokens, bool prefer_plus)
{
    auto acc = value(tokens, prefer_plus);
    while (!tokens.empty() && (tokens.back() == '+' || tokens.back() == '*')) {
        auto op = tokens.back();
        tokens.pop_back();
        val_t rhs = (op == '*' && prefer_plus) ? expr(tokens, prefer_plus)
                                               : value(tokens, prefer_plus);
        acc = op == '+' ? (acc + rhs) : (acc * rhs);
    }
    return acc;
}

int main()
{
    std::ifstream f(PATH);
    std::string line;

    val_t result_a = 0;
    val_t result_b = 0;
    while (std::getline(f, line)) {
        std::vector<char> tokens(line.begin(), line.end());
        tokens.erase(std::remove(tokens.begin(), tokens.end(), ' '), tokens.end());
        std::reverse(tokens.begin(), tokens.end());

        std::vector<char> tokens_a = tokens;
        result_a += expr(tokens_a, false);
        result_b += expr(tokens, true);
    }

    std::cout << result_a << "\n" << result_b << std::endl;

    return 0;
}
