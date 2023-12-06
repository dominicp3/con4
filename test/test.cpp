#include <sstream>
#include <iostream>
#include <string>
#include "../src/board.hpp"
#include "../src/computer.hpp"
#include "../src/io.hpp"

int main()
{
        std::map<std::pair<int, int>, COLOUR> m;
        // m[std::make_pair(0, 0)] = RED;

        m[std::make_pair(1, 0)] = YELLOW;
        m[std::make_pair(1, 1)] = RED;
        m[std::make_pair(1, 2)] = YELLOW;

        m[std::make_pair(2, 0)] = YELLOW;

        m[std::make_pair(3, 0)] = RED;
        m[std::make_pair(3, 1)] = RED;
        m[std::make_pair(3, 2)] = RED;
        m[std::make_pair(3, 3)] = YELLOW;

        m[std::make_pair(4, 0)] = RED;

        m[std::make_pair(5, 0)] = RED;
        m[std::make_pair(5, 1)] = RED;
        m[std::make_pair(5, 2)] = YELLOW;
        m[std::make_pair(5, 3)] = YELLOW;
        m[std::make_pair(5, 4)] = RED;
        m[std::make_pair(5, 5)] = RED;

        m[std::make_pair(6, 0)] = YELLOW;
        m[std::make_pair(6, 1)] = RED;
        m[std::make_pair(6, 2)] = YELLOW;
        m[std::make_pair(6, 3)] = YELLOW;

        Board b(m, false, true);
        board_io::print_board(b);

        // board_io::print_state(b);

        int eval;

        Computer c(12, RED);
        int col = c.best_move(b, eval);

        std::cout << "col = " << col << '\n';
        std::cout << "eval = " << eval << '\n';
}
