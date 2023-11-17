#ifndef BOARD_H
#define BOARD_H

#include <bitset>
#include <vector>
#include <map>

enum player {BLANK, YELLOW, RED};
enum state {PLAYING, DRAW, WIN_YELLOW, WIN_RED};

static constexpr int N_COL = 7;
static constexpr int N_ROW = 6;
static constexpr int N_BITS = N_COL * N_ROW;

class Board {
public:
        Board();
        Board(std::map<std::pair<int, int>, enum player> &m);
        Board(std::map<std::pair<int, int>, enum player> &m, enum player colour);

        bool play(int column);
        bool play(int column, enum player colour);

        enum state state() const;

        bool valid() const;

        void print() const;

private:
        static const std::vector<std::bitset<N_BITS>> wins;

        static std::vector<std::bitset<N_BITS>> generate_wins();

        static void vertical(std::vector<std::bitset<N_BITS>> &v);
        static void horizontal(std::vector<std::bitset<N_BITS>> &v);
        static void diagonal_pos(std::vector<std::bitset<N_BITS>> &v);
        static void diagonal_neg(std::vector<std::bitset<N_BITS>> &v);
        static void print_(std::bitset<N_BITS> &b);

        void init_map(std::map<std::pair<int, int>, enum player> &m);

        std::bitset<N_BITS> yellow;
        std::bitset<N_BITS> red;

        enum player turn = YELLOW;
};

#endif /* BOARD_H */
