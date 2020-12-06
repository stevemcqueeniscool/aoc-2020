#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <utility>

const std::string PATH = "../../data/day04.txt";
using passport_t = std::unordered_map<std::string, std::string>;

const auto kv_regex = std::regex(" ?(\\w{3}):([^ ]+)");

passport_t parse_line(std::string line)
{
    auto kv_match = std::smatch{};
    auto ppt = passport_t{};
    auto chs = line;
    while (std::regex_search(chs, kv_match, kv_regex)) {
        ppt[kv_match[1]] = kv_match[2];
        chs = kv_match.suffix().str();
    }
    return ppt;
}

const auto validators = std::unordered_map<std::string, std::regex>{
    {"byr", std::regex("19[2-9][0-9]|200[0-2]")},
    {"iyr", std::regex("201[0-9]|2020")},
    {"eyr", std::regex("202[0-9]|2030")},
    {"hgt", std::regex("(1[5-8][0-9]|19[0-3])cm|(59|6[0-9]|7[0-6])in")},
    {"hcl", std::regex("(#[0-9a-f]{6})")},
    {"ecl", std::regex("(amb|blu|brn|gry|grn|hzl|oth)")},
    {"pid", std::regex("(\\d{9})")}};

int main()
{
    auto f = std::ifstream{PATH};
    auto line = std::string{};
    auto passports = std::vector<passport_t>{};
    auto ppt = passport_t{};

    while (std::getline(f, line)) {
        if (line.empty()) {
            passports.push_back(ppt);
            ppt.clear();
        } else {
            ppt.merge(parse_line(line));
        }
    }
    passports.push_back(ppt);

    const auto needed = std::array{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

    int result_a = 0;
    for (const auto &ppt : passports) {
        if (std::all_of(needed.begin(), needed.end(), [ppt](const auto &k) {
                return ppt.count(k) > 0;
            }))
            ++result_a;
    }
    std::cout << result_a << std::endl;

    int result_b = 0;
    for (const auto &ppt : passports) {
        if (std::all_of(validators.begin(), validators.end(), [ppt](const auto &rule) {
                return ppt.count(rule.first) > 0 &&
                       std::regex_match(ppt.at(rule.first), rule.second);
            }))

            ++result_b;
    }
    std::cout << result_b << std::endl;

    return 0;
}
