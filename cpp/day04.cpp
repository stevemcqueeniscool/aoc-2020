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
const auto four_digit_regex = std::regex("(\\d{4})");
const auto height_regex = std::regex("(\\d+)(cm|in)");
const auto hair_colour_regex = std::regex("(#[0-9a-f]{6})");
const auto eye_colour_regex = std::regex("(amb|blu|brn|gry|grn|hzl|oth)");
const auto passport_id_regex = std::regex("(\\d{9})");

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

bool digit_matcher(const std::string &str, int low, int high)
{
    if (std::regex_match(str, four_digit_regex)) {
        const auto v = std::stoi(str);
        return (v >= low) && (v <= high);
    }
    return false;
}

const auto height_ranges = std::unordered_map<std::string, std::pair<int, int>>{
    {"cm", {150, 193}}, {"in", {59, 76}}};

bool height_matcher(const std::string &str)
{
    auto m = std::smatch{};
    if (std::regex_match(str, m, height_regex)) {
        const auto [low, high] = height_ranges.at(m[2]);
        const auto v = std::stoi(m[1]);
        return (v >= low) && (v <= high);
    }
    return false;
}

const auto validators =
    std::unordered_map<std::string, std::function<bool(std::string)>>{
        {"byr", [](const std::string &s) { return digit_matcher(s, 1920, 2002); }},
        {"iyr", [](const std::string &s) { return digit_matcher(s, 2010, 2020); }},
        {"eyr", [](const std::string &s) { return digit_matcher(s, 2020, 2030); }},
        {"hgt", [](const std::string &s) { return height_matcher(s); }},
        {"hcl",
         [](const std::string &s) { return std::regex_match(s, hair_colour_regex); }},
        {"ecl",
         [](const std::string &s) { return std::regex_match(s, eye_colour_regex); }},
        {"pid",
         [](const std::string &s) { return std::regex_match(s, passport_id_regex); }}};

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
        if (std::all_of(needed.begin(), needed.end(), [ppt](const auto &k) {
                return ppt.count(k) > 0 && validators.at(k)(ppt.at(k));
            }))

            ++result_b;
    }
    std::cout << result_b << std::endl;

    return 0;
}
