#include "computer.hpp"
#include <iostream>

void print_orientation(ORIENTATION o)
{
        switch (o) {
        case VERTICAL:
                std::cout << "vertical";
                return;

        case HORIZONTAL:
                std::cout << "horizontal";
                return;

        case DIAGONAL_POS:
                std::cout << "diagonal_pos";
                return;

        case DIAGONAL_NEG:
                std::cout << "diagonal_neg";
                return;

        default:;
        }
}

void print_colour(COLOUR c)
{
        switch (c) {
        case YELLOW:
                std::cout << "yellow";
                return;
        case RED:
                std::cout << "red";
                return;
        default:;
        }
}

int Computer::utility(Board &board)
{
        return Computer::evaluation(board, RED) - Computer::evaluation(board, YELLOW);
}

int Computer::evaluation(Board &board, COLOUR colour)
{
        if (colour != RED && colour != YELLOW)
                return 0;

        int points {0};

        for (const BoardInRow &in_row : Computer::in_row_2_3) {
                if ((((colour == YELLOW) ? board.yellow_bitset() : board.red_bitset()) & in_row.bitboard) == in_row.bitboard) {
                        int n {in_row.two_in_row ? 2 : 3};
                        int col_before, row_before, col_after, row_after;
                        
                        switch (in_row.orientation) {
                        case VERTICAL:
                                col_before = N_COL;
                                row_before = N_ROW;
                                col_after = 0;
                                row_after = n;
                                break;

                        case HORIZONTAL:
                                col_before = -1;
                                row_before = 0;
                                col_after = n;
                                row_after = 0;
                                break;

                        case DIAGONAL_POS:
                                col_before = -1;
                                row_before = -1;
                                col_after = n;
                                row_after = n;
                                break;

                        case DIAGONAL_NEG:
                                col_before = -1;
                                row_before = 1;
                                col_after = n;
                                row_after = -n;
                                break;

                        default:
                                col_before = N_COL;
                                row_before = N_ROW;
                                col_after = N_COL;
                                row_after = N_ROW;
                        }

                        COLOUR cell_before {board.cell(in_row.col + col_before, in_row.row + row_before)};
                        COLOUR cell_after  {board.cell(in_row.col + col_after, in_row.row + row_after)};

                        if (cell_before == colour || cell_after == colour)
                                continue;

                        if (cell_before == BLANK) {
                                if ((colour == YELLOW && in_row.row % 2 == 0) || (colour == RED && in_row.row % 2 == 1)) {
                                        points += in_row.two_in_row ? 8 : 40;
                                } else {
                                        points += in_row.two_in_row ? 3 : 15;
                                }
                        }

                        if (cell_after == BLANK) {
                                if ((colour == YELLOW && in_row.row % 2 == 0) || (colour == RED && in_row.row % 2 == 1)) {
                                        points += in_row.two_in_row ? 8 : 40;
                                } else {
                                        points += in_row.two_in_row ? 3 : 15;
                                }
                        }
                }
        }

        return points;
}

std::vector<Board> Computer::actions(Board &board)
{
        std::vector<Board> v;

        for (int col = 0; col < N_COL; col++) {
                Board b {board};
                if (b.play(col))
                        v.push_back(b);
        }

        return v;
}

int Computer::move(Board &board, int alpha, int beta, int depth, bool maximiser)
{
        (void) board;
        (void) alpha;
        (void) beta;
        (void) depth;
        (void) maximiser;

        return 0;
}

std::vector<Computer::BoardInRow> Computer::init_in_row_2_3()
{
        std::vector<std::bitset<N_BITS>> vertical_2;
        std::vector<std::bitset<N_BITS>> vertical_3;

        std::vector<std::bitset<N_BITS>> horizontal_2;
        std::vector<std::bitset<N_BITS>> horizontal_3;

        std::vector<std::bitset<N_BITS>> diagonal_pos_2;
        std::vector<std::bitset<N_BITS>> diagonal_pos_3;

        std::vector<std::bitset<N_BITS>> diagonal_neg_2;
        std::vector<std::bitset<N_BITS>> diagonal_neg_3;

        bitboard::vertical(vertical_2, 2);
        bitboard::vertical(vertical_3, 3);

        bitboard::horizontal(horizontal_2, 2);
        bitboard::horizontal(horizontal_3, 3);

        bitboard::diagonal_pos(diagonal_pos_2, 2);
        bitboard::diagonal_pos(diagonal_pos_3, 3);

        bitboard::diagonal_neg(diagonal_neg_2, 2);
        bitboard::diagonal_neg(diagonal_neg_3, 3);

        std::vector<BoardInRow> v;

        auto push = [](std::vector<BoardInRow> &res, std::vector<std::bitset<N_BITS>> &boards, ORIENTATION o, bool two)
        {
                for (const auto &board : boards) {
                        for (int i = 0; i < N_BITS; i++) {
                                if (board[i]) {
                                        BoardInRow b {board, o, i / N_ROW, i % N_ROW, two};
                                        res.push_back(b);
                                        break;
                                }
                        }
                }
        };

        push(v, vertical_2, VERTICAL, true);
        push(v, vertical_3, VERTICAL, false);

        push(v, horizontal_2, HORIZONTAL, true);
        push(v, horizontal_3, HORIZONTAL, false);

        push(v, diagonal_pos_2, DIAGONAL_POS, true);
        push(v, diagonal_pos_3, DIAGONAL_POS, false);

        push(v, diagonal_neg_2, DIAGONAL_NEG, true);
        push(v, diagonal_neg_3, DIAGONAL_NEG, false);

        return v;
}

const std::vector<Computer::BoardInRow> Computer::in_row_2_3 {Computer::init_in_row_2_3()};
