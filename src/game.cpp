#include "game.hpp"
#include "board.hpp"
#include "computer.hpp"
#include "io.hpp"
#include <iostream>
#include <string>

void game::play(bool cpu, int depth, bool player_red)
{
        if (depth <= 0) {
                return;
        }

        int column;
        Board b {player_red};
        std::string outcome;

        COLOUR player = player_red ? RED : YELLOW;

        Computer c {depth};

        std::cout << "Depth: " << depth << '\n';

        while (b.state() == PLAYING) {
                board_io::print_board(b);
                board_io::print_state(b);

                if (b.turn() == player || (b.turn() != player && !cpu)) {
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

                if (b.turn() != player && cpu) {
                        int eval;
                        int x = c.best_move(b, eval);
                        b.play(x);
                        std::cout << x << '\n';
                        std::cout << "Eval: " << eval << '\n';
                }
        }

        board_io::print_board(b);
        board_io::print_state(b);

        std::cout << "\nTHANK YOU FOR PLAYING :)\n\n";
}
