#include "../src/board.hpp"
#include <map>
#include <iostream>

using namespace std;

void print_state(Board &b)
{
        switch (b.state()) {
        case WIN_YELLOW:
                cout << "YELLOW WON !!\n";
                break;

        case WIN_RED:
                cout << "RED WON !!\n";
                break;

        case DRAW:
                cout << "DRAW !!\n";
                break;

        case PLAYING:
                cout << "GAME IN PROGRESS !!\n";
                break;

        default:
                cout << "ERROR STATE !!\n";
        }
}

void test_diagonal_yellow_win()
{
        cout << "test_diagonal_yellow_win\n" << endl;

        std::map<std::pair<int, int>, enum player> m;

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
        b.print();
        print_state(b);
}

void test_vertical_red_win()
{
        cout << "test_vertical_red_win\n" << endl;

        map<pair<int, int>, enum player> m;

        m[make_pair(0, 0)] = YELLOW;
        m[make_pair(0, 1)] = YELLOW;

        m[make_pair(0, 2)] = RED;
        m[make_pair(0, 3)] = RED;
        m[make_pair(0, 4)] = RED;
        m[make_pair(0, 5)] = RED;
        m[make_pair(0, 6)] = RED;

        Board b {m};
        b.print();
        print_state(b);
}

void test_draw()
{
        cout << "test_draw" << endl;

        bool p {false};
        map<pair<int, int>, enum player> m;
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
        b.print();
        print_state(b);
}

int main()
{
        // test_vertical_red_win();
        // test_diagonal_yellow_win();
        // test_draw();

        Board b;
        cout << sizeof (Board) << endl;
}
