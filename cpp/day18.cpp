#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const auto PATH = "../../data/day18.txt";

using val_t = std::uint64_t;

char pop(std::vector<char> &tokens)
{
    auto r = tokens.back();
    tokens.pop_back();
    return r;
}

val_t expr(std::vector<char> &tokens);

val_t value(std::vector<char> &tokens)
{
    val_t val;
    char ch = pop(tokens);
    if (ch == '(') {
        val = expr(tokens);
        pop(tokens); // ')'
    } else {
        val = ch - '0';
    }
    return val;
}

val_t expr(std::vector<char> &tokens)
{
    auto acc = value(tokens);
    while (!tokens.empty() && (tokens.back() == '+' || tokens.back() == '*')) {
        char op = pop(tokens);
        auto rhs = value(tokens);
        acc = op == '+' ? (acc + rhs) : (acc * rhs);
    }
    return acc;
}

std::vector<char> tokenize(const std::string &line)
{
    std::vector<char> result;
    for (const auto ch : line) {
        if (ch != ' ') {
            result.push_back(ch);
        }
    }
    std::reverse(result.begin(), result.end());
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

    val_t total = 0;
    for (const auto &l : lines) {
        auto tokens = tokenize(l);
        total += expr(tokens);
    }
    std::cout << total << std::endl;

    return 0;
}
