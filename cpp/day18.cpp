#include <algorithm>
#include <cstdint>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>

const auto PATH = "../../data/day18.txt";
using val_t = std::uint64_t;

val_t expr(std::queue<char> &tokens, bool prefer_plus);

val_t value(std::queue<char> &tokens, bool prefer_plus)
{
    val_t val;
    auto ch = tokens.front();
    tokens.pop();
    if (ch == '(') {
        val = expr(tokens, prefer_plus);
        tokens.pop(); // ')'
    } else {
        val = ch - '0';
    }
    return val;
}

val_t expr(std::queue<char> &tokens, bool prefer_plus)
{
    auto acc = value(tokens, prefer_plus);
    while (!tokens.empty() && (tokens.front() == '+' || tokens.front() == '*')) {
        auto op = tokens.front();
        tokens.pop();
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

    val_t result_a = 0, result_b = 0;
    while (std::getline(f, line)) {
        std::deque<char> tokens;
        std::copy_if(line.begin(), line.end(), std::back_inserter(tokens), [](auto ch) {
            return ch != ' ';
        });

        std::queue<char> tokens_a(tokens);
        result_a += expr(tokens_a, false);
        std::queue<char> tokens_b(tokens);
        result_b += expr(tokens_b, true);
    }

    std::cout << result_a << "\n" << result_b << std::endl;

    return 0;
}
