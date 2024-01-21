#ifndef COMPUTER_H
#define COMPUTER_H

#include "board.hpp"
#include <limits>
#include <vector>
#include <array>

static constexpr int i_min {std::numeric_limits<int>::min()};
static constexpr int i_max {std::numeric_limits<int>::max()};

enum ORIENTATION
{
        VERTICAL,
        HORIZONTAL,
        DIAGONAL_POS,
        DIAGONAL_NEG,
        ORIENTATION_ERROR
};

class Computer
{
public:
        Computer() = default;

        Computer(int depth_stop);
        Computer(COLOUR maximising_colour);

        Computer(int depth_stop, COLOUR maximising_colour);
        Computer(COLOUR maximising_colour, int depth_stop);

        int best_move(const Board &board) const;
        int best_move(const Board &board, int &eval) const;

private:
        const int depth_stop = 9;
        const bool red_is_maximiser = false;

        int alpha_beta(const Board &board, int alpha, int beta, int depth, bool maximiser, int &best_col) const;
        int evaluation(const Board &board, COLOUR colour) const;
        std::vector<std::pair<Board, int>> possible_moves(const Board &board) const;
        int utility(const Board &board, STATE state) const;
        int allocate_points(bool first, int row, bool two_in_row) const;

        COLOUR maximiser() const;
        COLOUR minimiser() const;

        struct BoardInRow {
                std::bitset<N_BITS> bitboard;
                ORIENTATION orientation = ORIENTATION_ERROR;
                int col = -1;
                int row = -1;
                bool two_in_row = false;
        };

        static const std::vector<BoardInRow> in_row_2_3;
        static std::vector<BoardInRow> init_in_row_2_3(); 

        static const std::array<int, N_COL> indices;
        static std::array<int, N_COL> init_indices();
};

#endif /* COMPUTER_H */
