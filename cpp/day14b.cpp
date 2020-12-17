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

int main()
{
    auto f = std::ifstream{PATH};
    auto line = std::string{};
    auto memory = std::unordered_map<word_t, word_t>{};
    auto mask = std::string{};

    while (std::getline(f, line)) {
        auto match = std::smatch{};
        std::regex_match(line, match, r);
        if (match[1].length() > 0) {
            mask = match[1];
        } else {
            auto addr = word_t(std::stoul(match[2]));
            const auto val = word_t(std::stoul(match[3]));
            auto floaters = std::vector<size_t>{};

            for (size_t i = 0; i != 36; ++i) {
                const auto m = mask[35 - i];
                if (m == '1') {
                    addr.set(i, 1);
                } else if (m == 'X') {
                    floaters.push_back(i);
                }
            }
            for (unsigned long j = 0; j != (1UL << floaters.size()); ++j) {
                const auto jbits = word_t(j);
                auto applied_addr = addr;
                for (size_t k = 0; k != floaters.size(); ++k) {
                    applied_addr.set(floaters[k], jbits[k]);
                }
                memory[applied_addr] = val;
            }
        }
    }

    unsigned long result = 0;
    for (const auto [k, v] : memory) {
        result += v.to_ulong();
    }
    std::cout << result << std::endl;

    return 0;
}
