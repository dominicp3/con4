#ifndef BOARD_H
#define BOARD_H

#include <bitset>
#include <vector>
#include <array>
#include <map>

/*
        NOTE: ASSUMED YELLOW MOVES FIRST
*/

static constexpr int N_COL = 7;
static constexpr int N_ROW = 6;
static constexpr int N_BITS = N_COL * N_ROW;

enum COLOUR
{
        YELLOW,
        RED,
        BLANK,
        COLOUR_ERROR
};

enum STATE
{
        PLAYING,
        DRAW,
        WIN_YELLOW,
        WIN_RED,
        STATE_ERROR
};

namespace bitboard
{
        size_t vertical(std::vector<std::bitset<N_BITS>> &v, int n = 4);
        size_t horizontal(std::vector<std::bitset<N_BITS>> &v, int n = 4);
        size_t diagonal_pos(std::vector<std::bitset<N_BITS>> &v, int n = 4);
        size_t diagonal_neg(std::vector<std::bitset<N_BITS>> &v, int n = 4);
}

class Board
{
public:
        Board() = default;
        Board(bool red_first);
        Board(std::map<std::pair<int, int>, bool> &m,   bool red_turn = false, bool red_first = false);
        Board(std::map<std::pair<int, int>, COLOUR> &m, bool red_turn = false, bool red_first = false);

        bool play(int column);
        void swap_turn();

        bool test(int column) const;

        STATE state() const;

        COLOUR turn() const;
        COLOUR first() const;
        COLOUR cell(int col, int row) const;

        const std::bitset<N_BITS> yellow_bitset() const;
        const std::bitset<N_BITS> red_bitset() const;

        std::vector<std::vector<COLOUR>> current() const;

private:
        static const std::vector<std::bitset<N_BITS>> wins;
        static std::vector<std::bitset<N_BITS>> init_wins();

        void init_map(std::map<std::pair<int, int>, bool> &m);
        void init_map(std::map<std::pair<int, int>, COLOUR> &m);

        std::bitset<N_BITS> yellow;
        std::bitset<N_BITS> red;

        std::array<int, N_COL> col_count;

        bool red_turn = false;
        bool red_first = false;
};

#endif /* BOARD_H */
