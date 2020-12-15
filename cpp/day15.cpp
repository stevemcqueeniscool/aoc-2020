#include <iostream>
#include <unordered_map>
#include <vector>

int main()
{
    const auto input = std::vector<int>{18, 8, 0, 5, 4, 1, 20};

    auto lookup = std::unordered_map<int, int>{};
    auto last_played = 0;
    auto turn = 1;
    for (auto i : input) {
        last_played = i;
        lookup[i] = turn;
        ++turn;
    }

    int next_play = 0;
    for (; turn <= 30000000; ++turn) {
        last_played = next_play;
        next_play = lookup.count(last_played) == 0 ? 0 : turn - lookup[last_played];
        lookup[last_played] = turn;
    }

    std::cout << last_played << std::endl;
    return 0;
}
