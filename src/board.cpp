#include "board.hpp"

Board::Board(bool red_turn, bool red_first): red_turn(red_turn), red_first(red_first) {}

Board::Board(std::map<std::pair<int, int>, bool> &m, bool red_turn, bool red_first): red_turn(red_turn), red_first(red_first)
{
        init_map(m);
}

Board::Board(std::map<std::pair<int, int>, COLOUR> &m, bool red_turn, bool red_first): red_turn(red_turn), red_first(red_first)
{
        init_map(m);
}

void Board::init_map(std::map<std::pair<int, int>, bool> &m)
{
        for (const auto &[coord, _red] : m) {
                if (coord.first < 0 || coord.first >= N_COL || coord.second < 0 || coord.second >= N_ROW)
                        continue;

                if (_red)
                        red.set(N_ROW * coord.first + coord.second);
                else
                        yellow.set(N_ROW * coord.first + coord.second);
        }
}

void Board::init_map(std::map<std::pair<int, int>, COLOUR> &m)
{
        for (const auto &[coord, colour] : m) {
                if (coord.first < 0 || coord.first >= N_COL || coord.second < 0 || coord.second >= N_ROW)
                        continue;

                if (colour == YELLOW)
                        yellow.set(N_ROW * coord.first + coord.second);

                else if (colour == RED)
                        red.set(N_ROW * coord.first + coord.second);
        }
}

bool Board::play(int column)
{
        if (column < 0 || column >= N_COL)
                return false;

        int i, count;
        std::bitset<N_BITS> &&yellow_red = yellow | red;

        for (i = N_ROW * column, count = 0; count < N_ROW && i < N_BITS && yellow_red[i]; i++, count++);

        if (count == N_ROW)
                return false;

        red_turn ? red.set(i) : yellow.set(i);
        red_turn = !red_turn;

        return true;
}

bool Board::test(int column) const
{
        if (column < 0 || column >= N_COL)
                return false;

        int i, count;
        std::bitset<N_BITS> &&yellow_red = yellow | red;

        for (i = N_ROW * column, count = 0; count < N_ROW && i < N_BITS && yellow_red[i]; i++, count++);

        return count != N_ROW;
}

void Board::swap_turn()
{
        red_turn = !red_turn;
}

STATE Board::state() const
{
        for (const auto &b : wins) {
                if ((b & yellow) == b)
                        return WIN_YELLOW;

                if ((b & red) == b)
                        return WIN_RED;
        }

        return (yellow | red).all() ? DRAW : PLAYING;
}

COLOUR Board::turn() const
{
        return red_turn ? RED : YELLOW;
}

COLOUR Board::first() const
{
        return red_first ? RED : YELLOW;
}

COLOUR Board::cell(int col, int row) const
{
        if (col < 0 || col >= N_COL || row < 0 || row >= N_ROW)
                return COLOUR_ERROR;
        
        if (yellow[N_ROW * col + row])
                return YELLOW;

        if (red[N_ROW * col + row])
                return RED;

        return BLANK;
}

std::vector<std::vector<COLOUR>> Board::current() const
{
        std::vector<std::vector<COLOUR>> v {N_COL, std::vector<COLOUR> {N_ROW, BLANK}};

        int col, row;
        for (col = 0; col < N_COL; col++) {
                for (row = 0; row < N_ROW; row++) {
                        if (yellow[N_ROW * col + row])
                                v[col][row] = YELLOW;

                        else if (red[N_ROW * col + row])
                                v[col][row] = RED;
                }
        }

        return v;
}

std::vector<std::bitset<N_BITS>> Board::init_wins()
{
        std::vector<std::bitset<N_BITS>> v;

        bitboard::vertical(v);
        bitboard::horizontal(v);
        bitboard::diagonal_pos(v);
        bitboard::diagonal_neg(v);

        return v;
}

size_t bitboard::vertical(std::vector<std::bitset<N_BITS>> &v, int n)
{
        if (n <= 0) {
                return 0;
        }

        int col, row, i;
        size_t count = 0;
        for (col = 0; col < N_COL; col++) {
                for (row = 0; row + (n - 1) < N_ROW; row++) {
                        std::bitset<N_BITS> b;
                        for (i = 0; i < n; i++) 
                                b.set(N_ROW * (col) + (row + i));
                        v.push_back(b);
                        count++;
                }
        }

        return count;
}

size_t bitboard::horizontal(std::vector<std::bitset<N_BITS>> &v, int n)
{
        if (n <= 0) {
                return 0;
        }

        int col, row, i;
        size_t count = 0;
        for (col = 0; col + (n - 1) < N_COL; col++) {
                for (row = 0; row < N_ROW; row++) {
                        std::bitset<N_BITS> b;
                        for (i = 0; i < n; i++)
                                b.set(N_ROW * (col + i) + (row));
                        v.push_back(b);
                        count++;
                }
        }

        return count;
}

size_t bitboard::diagonal_pos(std::vector<std::bitset<N_BITS>> &v, int n)
{
        if (n <= 0) {
                return 0;
        }

        int col, row, i;
        size_t count = 0;
        for (col = 0; col + (n - 1) < N_COL; col++) {
                for (row = 0; row + (n - 1) < N_ROW; row++) {
                        std::bitset<N_BITS> b;
                        for (i = 0; i < n; i++)
                                b.set(N_ROW * (col + i) + (row + i));
                        v.push_back(b);
                        count++;
                }
        }

        return count;
}

size_t bitboard::diagonal_neg(std::vector<std::bitset<N_BITS>> &v, int n)
{
        if (n <= 0) {
                return 0;
        }

        int col, row, i;
        size_t count = 0;
        for (col = 0; col + (n - 1) < N_COL; col++) {
                for (row = N_ROW - 1; row - (n - 1) >= 0; row--) {
                        std::bitset<N_BITS> b;
                        for (i = 0; i < n; i++)
                                b.set(N_ROW * (col + i) + (row - i));
                        v.push_back(b);
                        count++;
                }
        }

        return count;
}

const std::bitset<N_BITS> Board::yellow_bitset() const
{
        return yellow;
}

const std::bitset<N_BITS> Board::red_bitset() const
{
        return red;
}

const std::vector<std::bitset<N_BITS>> Board::wins {Board::init_wins()};
