#include <fstream>
#include <iostream>
#include <optional>
#include <unordered_set>
#include <utility>

const std::string PATH = "../data/day01.txt";

using opt_pair_t = std::optional<std::pair<int, int>>;
opt_pair_t find_pair(int target, const std::unordered_set<int> &xs)
{
    for (int x : xs) {
        const auto y = target - x;
        if (xs.count(y) != 0) {
	    return std::make_pair(x, y);
        }
    }
    return std::nullopt;
}

int main()
{
    std::fstream f(PATH, std::ios_base::in);
    std::unordered_set<int> xs;
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
