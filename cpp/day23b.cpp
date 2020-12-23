#include <array>
#include <iostream>
#include <vector>
#include <cstdint>

using elm_t = std::uint32_t;

auto input_test = std::array<elm_t, 9>{3, 8, 9, 1, 2, 5, 4, 6, 7};
auto input = std::array<elm_t, 9>{6, 8, 5, 9, 7, 4, 2, 1, 3};

constexpr auto N = 1000000;
constexpr auto MOVES = N * 10;

int main()
{
    auto store = std::vector<elm_t>(N + 1, 0);
    for (size_t i = 1; i != input.size(); ++i) {
        store[input[i - 1]] = input[i];
    }
    store[input.back()] = input.size() + 1;
    for (size_t i = input.size() + 2; i <= N; ++i) {
        store[i - 1] = i;
    }
    store[N] = input[0];

    auto current = input[0];
    for (int move = 0; move != MOVES; ++move) {
        const auto tmp1 = store[current];
        const auto tmp2 = store[tmp1];
        const auto tmp3 = store[tmp2];

        auto tgt = current;
        do {
            --tgt;
            if (tgt == 0) {
                tgt = N;
            }
        } while (!(tgt != tmp1 && tgt != tmp2 && tgt != tmp3));

        auto new_current = store[tmp3];
        store[current] = new_current;
        auto tmp_store_tgt = store[tgt];
        store[tgt] = tmp1;
        store[tmp3] = tmp_store_tgt;
        current = new_current;
    }

    auto cup1 = std::int64_t(store[1]);
    auto cup2 = std::int64_t(store[store[1]]);
    std::cout << cup1 * cup2 << std::endl;
    return 0;
}
