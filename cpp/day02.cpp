#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

#include <scn/scn.h>
#include <scn/tuple_return.h>

const std::string PATH = "../../data/day02.txt";

bool password_valid_a(std::string_view line)
{
    const auto [_, low, high, ch, pwd] =
        scn::scan_tuple<int, int, char, std::string>(line, "{}-{} {}: {}");
    const auto count =
        std::count_if(pwd.begin(), pwd.end(), [ch](char p) { return p == ch; });
    return (count >= low) && (count <= high);
}

bool password_valid_b(std::string_view line)
{
    const auto [_, idx_a, idx_b, ch, pwd] =
        scn::scan_tuple<int, int, char, std::string>(line, "{}-{} {}: {}");
    return (pwd[idx_a - 1] == ch) != (pwd[idx_b - 1] == ch);
}

int main()
{
    std::ifstream f(PATH);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(f, line)) {
        lines.push_back(line);
    }

    const auto result_a = std::count_if(lines.begin(), lines.end(), password_valid_a);
    std::cout << result_a << std::endl;

    const auto result_b = std::count_if(lines.begin(), lines.end(), password_valid_b);
    std::cout << result_b << std::endl;

    return 0;
}
