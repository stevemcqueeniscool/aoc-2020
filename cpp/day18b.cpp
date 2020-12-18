#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <stack>
#include <string>
#include <vector>

const auto PATH = "../../data/day18.txt";
using val_t = std::uint64_t;

bool isoperator(char ch) { return ch == '+' || ch == '*'; }

std::vector<char> shunter(std::string line, std::map<char, int> precedence)
{
    std::vector<char> output;
    std::stack<char> operators;
    for (const auto ch : line) {
        if (ch == ' ') {
            continue;
        }
        if (std::isdigit(ch)) {
            output.push_back(ch);
        } else if (isoperator(ch)) {
            while (!operators.empty() &&
                   precedence[operators.top()] >= precedence[ch] &&
                   operators.top() != '(') {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(ch);
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (operators.top() != '(') {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.pop();
        }
    }
    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}

val_t eval(std::vector<char> input)
{
    std::stack<val_t> stk;
    for (const auto ch : input) {
        if (isoperator(ch)) {
            val_t a = stk.top();
            stk.pop();
            val_t b = stk.top();
            stk.pop();
            stk.push(ch == '+' ? a + b : a * b);
        } else {
            stk.push(ch - '0');
        }
    }
    return stk.top();
}

int main()
{
    std::ifstream f(PATH);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(f, line)) {
        lines.push_back(line);
    }

    auto precedence = std::map<char, int>{{'+', 0}, {'*', 0}};
    const auto result_a = std::accumulate(
        lines.begin(), lines.end(), val_t{0},
        [&](val_t acc, const auto &l) { return acc + eval(shunter(l, precedence)); });

    precedence['+'] = 1;
    const auto result_b = std::accumulate(
        lines.begin(), lines.end(), val_t{0},
        [&](val_t acc, const auto &l) { return acc + eval(shunter(l, precedence)); });

    std::cout << result_a << std::endl;
    std::cout << result_b << std::endl;

    return 0;
}
