#include <fstream>
#include <iostream>
#include <optional>
#include <set>
#include <utility>

const std::string PATH = "../data/day01.txt";

using opt_pair_t = std::optional<std::pair<int, int>>;
opt_pair_t find_pair(int target, const std::set<int> &xs)
{
    auto result = opt_pair_t{};
    for (int x : xs) {
        const auto y = target - x;
        if (xs.count(y) != 0) {
            result = std::make_pair(x, y);
        }
    }
    return result;
}

int main()
{
    std::fstream f(PATH, std::ios_base::in);
    std::set<int> xs;
    int x;
    while (f >> x)
    {
	xs.insert(x);
    }

    const auto part_a = find_pair(2020, xs);
    std::cout << part_a->first * part_a->second << std::endl;

    for (int z: xs) {
	if (const auto m = find_pair(2020 - z, xs); m) {
	    std::cout << z * m->first * m->second << std::endl;
	    break;
	}
    }

    return 0;
}
