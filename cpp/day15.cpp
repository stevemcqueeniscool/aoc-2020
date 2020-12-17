#include <cstdint>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int solve(std::uint32_t N, const std::vector<int> &input)
{
    auto lookup = std::vector<std::uint32_t>(N, std::numeric_limits<uint32_t>::max());
    std::uint32_t turn = 1;
    for (auto i : input) {
        lookup[i] = turn++;
    }

    std::uint32_t speak = 0;
    for (; turn != N; ++turn) {
        speak = turn - std::exchange(lookup[speak], turn);
        if (speak > turn) {         // implements saturated subtraction without branching
            speak = 0;              // see https://godbolt.org/z/Wj9a87
        }
    }
    return speak;
}

int main()
{
    const auto input = std::vector<int>{18, 8, 0, 5, 4, 1, 20};

    std::cout << solve(2020, input) << std::endl;
    std::cout << solve(30000000, input) << std::endl;

    return 0;
}
