#include <algorithm>
#include <array>
#include <bitset>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <utility>

const std::string PATH = "../../data/day14.txt";

const auto r = std::regex{"mask = ([X10]+)|mem\\[(\\d+)] = (\\d+)"};

using word_t = std::bitset<36>;
auto memory = std::unordered_map<word_t, word_t>{};
auto mask = std::string{};

int main()
{
    auto f = std::ifstream{PATH};
    auto line = std::string{};

    while (std::getline(f, line)) {
        auto match = std::smatch{};
        std::regex_match(line, match, r);
        if (match[1].length() > 0) {
            mask = match[1];
        } else {
            const auto addr = word_t(std::stoul(match[2]));
            auto val = word_t(std::stoul(match[3]));
            for (size_t i = 0; i != 36; ++i) {
                if (const auto m = mask[35 - i]; m != 'X') {
                    val.set(i, m == '1' ? 1 : 0);
                }
            }
            memory[addr] = val;
        }
    }

    unsigned long result = 0;
    for (const auto [k, v] : memory) {
        result += v.to_ulong();
    }
    std::cout << result << std::endl;

    return 0;
}
