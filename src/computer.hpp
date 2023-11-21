#ifndef COMPUTER_H
#define COMPUTER_H

#include "board.hpp"
#include <vector>
#include <memory>
#include <map>
#include <array>
#include <tuple>

static constexpr int i_min {std::numeric_limits<int>::min()};
static constexpr int i_max {std::numeric_limits<int>::max()};

enum ORIENTATION {VERTICAL, HORIZONTAL, DIAGONAL_POS, DIAGONAL_NEG, ORIENTATION_ERROR};

class Computer {
public:
        Computer() = default;
        Computer(int depth_stop);
        Computer(COLOUR maximising_colour);
        Computer(int depth_stop, COLOUR maximising_colour);

        int utility(const Board &board);
        int evaluation(const Board &board, COLOUR colour);

        COLOUR maximiser() const;
        COLOUR minimiser() const;

        std::vector<std::tuple<Board, int, STATE>> actions(const Board &board);
        int next_move(const Board &board, int alpha, int beta, int depth, bool maximiser);
        Board next_board(const Board &board);

        static int next_move_count;
        static int eval_count;

private:
        struct BoardInRow {
                std::bitset<N_BITS> bitboard;
                ORIENTATION orientation = ORIENTATION_ERROR;
                int col = -1;
                int row = -1;
                bool two_in_row = false;
        };

        int allocate_points(COLOUR colour, COLOUR first, int row, bool two_in_row) const;

        static const std::array<int, N_COL> indices;
        static std::array<int, N_COL> init_indices();

        static const std::vector<BoardInRow> in_row_2_3;
        static std::vector<BoardInRow> init_in_row_2_3();

        const int depth_stop = 9;
        const bool red_is_maximiser = RED;
};

#endif /* COMPUTER_H */
