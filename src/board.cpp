#include "board.hpp"
#include <iostream>

Board::Board() {}

Board::Board(std::map<std::pair<int, int>, enum player> &m)
{
        init_map(m);
}

Board::Board(std::map<std::pair<int, int>, enum player> &m, enum player colour): turn(colour)
{
        init_map(m);
}

void Board::init_map(std::map<std::pair<int, int>, enum player> &m)
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
        if (!play(column, turn))
                return false;

        turn = (turn == YELLOW) ? RED : YELLOW;
        return true;
}

bool Board::play(int column, enum player colour)
{
        if (column < 0 || column >= N_COL)
                return false;
        
        if (colour != YELLOW && colour != RED)
                return false;

        char i;
        int count;
        std::bitset<N_BITS> &&yellow_red = yellow | red;

        for (i = N_ROW * column, count = 0; yellow_red.test(i); i++, count++);

        if (count >= N_ROW)
                return false;

        switch (colour) {
        case YELLOW:
                yellow.set(i);
                break;
        case RED:
                red.set(i);
                break;
        default:;
        }

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

bool Board::valid() const
{
        return !(yellow & red).any();
}

void Board::print() const
{
        int x;
        std::cout << "\n   ---------------------------\n";
        for (int i = N_ROW - 1; i >= 0; i--) {
                for (int j = 0; j < N_COL; j++) {
                        x = i + N_ROW * j;

                        if (j == 0) {
                                std::cout << i << " | ";
                        }

                        if (yellow[x]) {
                                std::cout << "y | ";
                        } else if (red[x]) {
                                std::cout << "r | ";
                        } else {
                                std::cout << "  | ";
                        }
                }
                
                std::cout << '\n';
                // std::cout << "   ---------------------------\n";

                if (i == 0) {
                        std::cout << "   ---------------------------\n";
                        std::cout << "    0   1   2   3   4   5   6\n";
                }
        }
        std::cout << "\n" << std::endl;
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
