#ifndef COMPUTER_H
#define COMPUTER_H

#include "board.hpp"
#include <map>
#include <vector>

enum ORIENTATION {VERTICAL, HORIZONTAL, DIAGONAL_POS, DIAGONAL_NEG, ORIENTATION_ERROR};

class Computer {
public:
        static int utility(Board &board);
        static int evaluation(Board &board, COLOUR colour);

        static std::vector<Board> actions(Board &board);
        static int move(Board &board, int alpha, int beta, int depth, bool maximiser);

private:
        struct BoardInRow {
                std::bitset<N_BITS> bitboard;
                ORIENTATION orientation = ORIENTATION_ERROR;
                int col = -1;
                int row = -1;
                bool two_in_row = false;
        };

        static const std::vector<BoardInRow> in_row_2_3;
        static std::vector<BoardInRow> init_in_row_2_3();
};

#endif /* COMPUTER_H */
