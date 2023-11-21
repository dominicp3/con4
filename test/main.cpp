#include "../src/board.hpp"
#include "../src/misc_io.hpp"
#include "../src/game.hpp"
#include "../src/computer.hpp"
#include <map>
#include <iostream>

using namespace std;

Board make_board()
{
        std::map<std::pair<int, int>, COLOUR> m;

        m[std::make_pair(0, 0)] = YELLOW;

        m[std::make_pair(1, 0)] = RED;
        m[std::make_pair(1, 1)] = YELLOW;

        m[std::make_pair(2, 0)] = YELLOW;
        m[std::make_pair(2, 1)] = RED;
        m[std::make_pair(2, 2)] = YELLOW;

        m[std::make_pair(3, 0)] = YELLOW;
        m[std::make_pair(3, 1)] = RED;
        m[std::make_pair(3, 2)] = YELLOW;

        m[std::make_pair(4, 0)] = RED;
        m[std::make_pair(4, 1)] = RED;

        return Board {m};
}

void test_utility()
{
        cout << "test_utility\n" << endl;

        Board b {make_board()};
        board_io::print_board(b);

        Computer c(YELLOW);
        board_io::print_turn(b);

        // [2, 6, 5, 0, 4, 1, 3] <- worst performing indices
        Board next {c.next_board(b)};
        board_io::print_board(next);
        cout << "next_move_count = " << Computer::next_move_count << '\n';
        cout << "eval_count = " << Computer::eval_count << '\n';
}

void test_diagonal_yellow_win()
{
        cout << "test_diagonal_yellow_win\n" << endl;

        std::map<std::pair<int, int>, COLOUR> m;

        m[std::make_pair(0, 0)] = YELLOW;

        m[std::make_pair(1, 0)] = RED;
        m[std::make_pair(1, 1)] = YELLOW;

        m[std::make_pair(2, 0)] = YELLOW;
        m[std::make_pair(2, 1)] = RED;
        m[std::make_pair(2, 2)] = YELLOW;

        m[std::make_pair(3, 0)] = YELLOW;
        m[std::make_pair(3, 1)] = RED;
        m[std::make_pair(3, 2)] = YELLOW;
        m[std::make_pair(3, 3)] = YELLOW;

        Board b {m};

        board_io::print_board(b);
        board_io::print_state(b);
}

void test_vertical_red_win()
{
        cout << "test_vertical_red_win\n" << endl;

        map<pair<int, int>, COLOUR> m;

        m[make_pair(0, 0)] = YELLOW;
        m[make_pair(0, 1)] = YELLOW;

        m[make_pair(0, 2)] = RED;
        m[make_pair(0, 3)] = RED;
        m[make_pair(0, 4)] = RED;
        m[make_pair(0, 5)] = RED;
        m[make_pair(0, 6)] = RED;

        Board b {m};

        board_io::print_board(b);
        board_io::print_state(b);
}

void test_draw()
{
        cout << "test_draw" << endl;

        bool p {false};
        map<pair<int, int>, COLOUR> m;
        int col, row;
        for (col = 0; col < 3; col++) {
                for (row = 0; row < N_ROW; row++) {
                        m[make_pair(col, row)] = p ? YELLOW : RED;
                        p = !p;
                }
        }

        for (col = 3; col < 6; col++) {
                for (row = 0; row < N_ROW; row++) {
                        m[make_pair(col, row)] = p ? RED : YELLOW;
                        p = !p;
                }
        }

        for (row = 0; row < N_ROW; row++) {
                m[make_pair(N_COL - 1, row)] = p ? YELLOW : RED;
                p = !p;
        }

        Board b {m};

        board_io::print_board(b);
        board_io::print_state(b);
}

void test_generate_boards()
{
        vector<bitset<N_BITS>> v;
        bitboard::vertical(v, 3);
        bitboard::horizontal(v, 3);
        bitboard::diagonal_pos(v, 3);
        bitboard::diagonal_neg(v, 3);
        for (auto x : v) {
                bitboard::print(x);
        }
        cout << "size: " << v.size() << endl;
}

int main()
{
        // game::game(false);
        test_utility();
        
}
