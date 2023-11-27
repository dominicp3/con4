#include "game.hpp"
#include "board.hpp"
#include "misc_io.hpp"
#include <iostream>
#include <string>

void game::game(bool cpu, int depth)
{
        if (depth <= 0) {
                return;
        }

        Board b;
        int column;
        std::string outcome;

        Computer c(depth);

        while (b.state() == PLAYING) {
                board_io::print_board_xo(b);
                board_io::print_state_xo(b);

                if (b.turn() == YELLOW || (b.turn() == RED && !cpu)) {
                        std::cin >> column;

                        if (std::cin.fail()) {
                                std::cout << "ERROR: not an integer !!" << std::endl;
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                continue;
                        } else if (column < 0 || column >= N_COL) {
                                std::cout << "\nERROR: integer out of bounds !!\n\n";
                                continue;
                        }

                        b.play(column);
                        continue;
                }

                if (b.turn() == RED && cpu) {
                        b.play(c.best_move(b));
                }
        }

        board_io::print_board_xo(b);
        board_io::print_state_xo(b);

        std::cout << "\nTHANK YOU FOR PLAYING :)\n\n";
}
