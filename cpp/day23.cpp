#include <array>
#include <iostream>
#include <string>

auto input_test = std::array{3, 8, 9, 1, 2, 5, 4, 6, 7};
auto input = std::array{6, 8, 5, 9, 7, 4, 2, 1, 3};

template <size_t N> std::string make_result(const std::array<int, N> &xs)
{
    auto one_idx = size_t{0};
    while (xs[one_idx++] != 1)
        ;
    auto result = std::string(xs.size(), 0);
    for (size_t idx = 0; idx != xs.size() - 1; ++idx) {
        result[idx] = '0' + xs[(one_idx + idx) % xs.size()];
    }
    return result;
}

int main()
{
    auto board = input;
    for (size_t move = 0; move != 100; ++move) {

        auto tgt = board[0];
        do {
            --tgt;
            if (tgt == 0) {
                tgt = board.size();
            }
        } while (!(tgt != board[1] && tgt != board[2] && tgt != board[3]));

        auto tmp1 = board[1];
        auto tmp2 = board[2];
        auto tmp3 = board[3];

        auto new_board = board;
        auto new_idx = size_t{0};
        auto board_idx = size_t{4};
        while (new_idx != board.size()) {
            new_board[new_idx++] = board[board_idx];
            if (board[board_idx] == tgt) {
                new_board[new_idx++] = tmp1;
                new_board[new_idx++] = tmp2;
                new_board[new_idx++] = tmp3;
            }

            board_idx = (board_idx + 1) % board.size();
        }
        std::swap(board, new_board);
    }

    std::cout << make_result(board) << std::endl;
    return 0;
}
