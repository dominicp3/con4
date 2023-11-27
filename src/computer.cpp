#include "computer.hpp"
#include <algorithm>
#include <random>
#include <utility>

const std::vector<Computer::BoardInRow> Computer::in_row_2_3 {Computer::init_in_row_2_3()};
const std::array<int, N_COL> Computer::indices {Computer::init_indices()};

Computer::Computer(int depth_stop): depth_stop(depth_stop) {}
Computer::Computer(COLOUR maximising_colour): red_is_maximiser(maximising_colour == RED ? true : false) {}
Computer::Computer(int depth_stop, COLOUR maximising_colour): depth_stop(depth_stop), red_is_maximiser(maximising_colour == RED ? true : false) {}
Computer::Computer(COLOUR maximising_colour, int depth_stop): depth_stop(depth_stop), red_is_maximiser(maximising_colour == RED ? true : false) {}

int Computer::best_move(const Board &board) const
{
        int best_col = -1;
        alpha_beta(board, i_min, i_max, depth_stop, board.turn() == maximiser(), best_col);
        return best_col;
}

int Computer::best_move(const Board &board, int &eval) const
{
        int best_col = -1;
        eval = alpha_beta(board, i_min, i_max, depth_stop, board.turn() == maximiser(), best_col);
        return best_col;
}

int Computer::alpha_beta(const Board &board, int alpha, int beta, int depth, bool maximiser, int &best_col) const
{
        STATE state = board.state();

        if (depth == 0 || state != PLAYING) {
                return utility(board, state);
        }

        if (maximiser) {
                int value = i_min;
                for (const auto &[action, col] : possible_moves(board)) {
                        int tmp = alpha_beta(action, alpha, beta, depth - 1, false, best_col);

                        if (tmp > value) {
                                value = tmp;

                                if (depth == depth_stop) {
                                        best_col = col;
                                }
                        }

                        alpha = std::max(alpha, value);

                        if (alpha >= beta) {
                                break;
                        }
                }

                return value;
        } else {
                int value = i_max;
                for (const auto &[action, col] : possible_moves(board)) {
                        int tmp = alpha_beta(action, alpha, beta, depth - 1, true, best_col);

                        if (tmp < value) {
                                value = tmp;

                                if (depth == depth_stop) {
                                        best_col = col;
                                }
                        }

                        beta = std::min(beta, value);

                        if (alpha >= beta) {
                                break;
                        }
                }

                return value;
        }
}

std::vector<std::pair<Board, int>> Computer::possible_moves(const Board &board) const
{
        std::vector<std::pair<Board, int>> v;

        for (const int &col : indices) {
                if (board.test(col)) {
                        Board next {board};
                        next.play(col);
                        v.push_back(std::make_pair(next, col));
                }
        }

        return v;
}

int Computer::utility(const Board &board, STATE state) const
{
        switch (state) {
        case WIN_YELLOW:
                return maximiser() == YELLOW ? i_max : i_min;
        case WIN_RED:
                return maximiser() == RED    ? i_max : i_min;
        default:
                return Computer::evaluation(board, maximiser()) - Computer::evaluation(board, minimiser());
        }
}

int Computer::evaluation(const Board &board, COLOUR colour) const
{
        if (colour != RED && colour != YELLOW) {
                return 0;
        }

        COLOUR cell_before, cell_after;
        int points = 0;

        const auto &full_board = ((colour == YELLOW) ? board.yellow_bitset() : board.red_bitset());

        for (const auto &b : Computer::in_row_2_3) {
                if ((full_board & b.bitboard) == b.bitboard) {

                        int n = b.two_in_row ? 2 : 3;
                        int row_before, row_after, col_before, col_after;

                        switch (b.orientation) {
                        case VERTICAL:
                                col_before = -1;
                                row_before = -1;

                                col_after = b.col;
                                row_after = b.row + n;

                                break;

                        case HORIZONTAL:
                                col_before = b.col - 1;
                                row_before = b.row;

                                col_after = b.col + n;
                                row_after = b.row;

                                break;

                        case DIAGONAL_POS:
                                col_before = b.col - 1;
                                row_before = b.row - 1;

                                col_after = b.col + n;
                                row_after = b.row + n;

                                break;

                        case DIAGONAL_NEG:
                                col_before = b.col - 1;
                                row_before = b.row + 1;

                                col_after = b.col + n;
                                row_after = b.row - n;

                                break;

                        default:
                                continue;
                        }

                        cell_before = board.cell(col_before, row_before);
                        cell_after  = board.cell(col_after, row_after);

                        if (cell_before == colour || cell_after == colour) {
                                continue;
                        }

                        if (cell_before == BLANK) {
                                points += allocate_points(colour == board.first(), row_before, b.two_in_row);
                        }

                        if (cell_after == BLANK) {
                                points += allocate_points(colour == board.first(), row_after, b.two_in_row);
                        }
                }
        }

        return points;
}

int Computer::allocate_points(bool first, int row, bool two_in_row) const
{
        if ((first && row % 2 == 0) || (!first && row % 2 == 1))
                return two_in_row ? 8 : 40;
        return two_in_row ? 3 : 15;
}

COLOUR Computer::maximiser() const
{
        return red_is_maximiser ? RED : YELLOW;
}

COLOUR Computer::minimiser() const
{
        return red_is_maximiser ? YELLOW : RED;
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

std::array<int, N_COL> Computer::init_indices()
{
        std::array<int, N_COL> arr;
        for (int i = 0; i < N_COL; i++) {
                arr[i] = i;
        }

        auto rd = std::random_device {};
        auto rng = std::default_random_engine {rd()};
        std::shuffle(std::begin(arr), std::end(arr), rng);

        return arr;
}
