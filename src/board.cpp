#include "board.hpp"
#include <iostream>

Board::Board(bool red_turn): red_turn(red_turn) {}

Board::Board(std::map<std::pair<int, int>, bool> &m, bool red_turn): red_turn(red_turn)
{
        init_map(m);
}

Board::Board(std::map<std::pair<int, int>, enum colour> &m, bool red_turn): red_turn(red_turn)
{
        init_map(m);
}

void Board::init_map(std::map<std::pair<int, int>, bool> &m)
{
        for (auto &&[coord, _red] : m) {
                if (coord.first < 0 || coord.first >= N_COL || coord.second < 0 || coord.second >= N_ROW)
                        continue;

                if (_red)
                        red.set(N_ROW * coord.first + coord.second);
                else
                        yellow.set(N_ROW * coord.first + coord.second);
        }
}

void Board::init_map(std::map<std::pair<int, int>, enum colour> &m)
{
        for (auto &&[coord, colour] : m) {
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

        for (i = N_ROW * column, count = 0; yellow_red.test(i); i++, count++);

        if (count >= N_ROW)
                return false;

        red_turn ? red.set(i) : yellow.set(i);
        red_turn = !red_turn;

        return true;
}

enum state Board::state() const
{
        for (auto &b : wins) {
                if ((b & yellow) == b)
                        return WIN_YELLOW;

                if ((b & red) == b)
                        return WIN_RED;
        }

        return (yellow | red).all() ? DRAW : PLAYING;
}

enum colour Board::turn() const
{
        return red_turn ? RED : YELLOW;
}

std::vector<std::vector<enum colour>> Board::current()
{
        std::vector<std::vector<enum colour>> v {N_COL, std::vector<enum colour> {N_ROW, BLANK}};
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

std::vector<std::bitset<N_BITS>> Board::generate_wins()
{
        std::vector<std::bitset<N_BITS>> v;

        vertical(v);
        horizontal(v);
        diagonal_pos(v);
        diagonal_neg(v);

        return v;
}

void Board::vertical(std::vector<std::bitset<N_BITS>> &v)
{
        int col, row, i;
        for (col = 0; col < N_COL; col++) {
                for (row = 0; row + 3 < N_ROW; row++) {
                        std::bitset<N_BITS> b {std::bitset<N_BITS> {}};
                        for (i = 0; i < 4; i++) 
                                b.set(N_ROW * col + row + i);
                        v.push_back(b);
                }
        }
}

void Board::horizontal(std::vector<std::bitset<N_BITS>> &v)
{
        int col, row, i;
        for (col = 0; col + 3 < N_COL; col++) {
                for (row = 0; row < N_ROW; row++) {
                        std::bitset<N_BITS> b {std::bitset<N_BITS> {}};
                        for (i = 0; i < 4; i++)
                                b.set(N_ROW * col + row + N_ROW * i);
                        v.push_back(b);
                }
        }
}

void Board::diagonal_pos(std::vector<std::bitset<N_BITS>> &v)
{
        int col, row, i;
        for (col = 0; col + 3 < N_COL; col++) {
                for (row = 0; row + 3 < N_ROW; row++) {
                        std::bitset<N_BITS> b {std::bitset<N_BITS> {}};
                        for (i = 0; i < 4; i++) {
                                b.set(N_ROW * col + row + (N_ROW + 1) * i);
                        }
                        
                        v.push_back(b);
                }
        }
}

void Board::diagonal_neg(std::vector<std::bitset<N_BITS>> &v)
{
        int col, row, i;
        for (col = 0; col + 3 < N_COL; col++) {
                for (row = N_ROW - 1; row - 3 >= 0; row--) {
                        std::bitset<N_BITS> b {std::bitset<N_BITS> {}};
                        for (i = 0; i < 4; i++)
                                b.set(N_ROW * col + row + (N_ROW - 1) * i);
                        v.push_back(b);
                }
        }
}

void Board::print_(std::bitset<N_BITS> &b)
{
        int x;
        for (int i = N_ROW - 1; i >= 0; i--) {
                for (int j = 0; j < N_COL; j++) {
                        x = i + N_ROW * j;

                        if (b[x]) {
                                std::cout << "1 | ";
                        } else {
                                std::cout << "  | ";
                        }
                }
                std::cout << '\n';
        }
        std::cout << '\n';
}

const std::vector<std::bitset<N_BITS>> Board::wins {Board::generate_wins()};
