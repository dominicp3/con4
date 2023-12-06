#include "game.hpp"
#include "board.hpp"
#include "computer.hpp"
#include "io.hpp"
#include <iostream>
#include <string>

void game::play(bool cpu, int depth, bool player_red)
{
        if (cpu && depth <= 0) {
                return;
        }

        int column;
        Board b {player_red};
        std::string outcome;

        COLOUR player = player_red ? RED : YELLOW;
        Computer comp(depth, player_red ? RED : YELLOW);

        while (b.state() == PLAYING) {
                board_io::print_board(b);

                print_state:
                board_io::print_state(b);

                if (b.turn() == player || (b.turn() != player && !cpu)) {
                        std::cin >> column;

                        if (std::cin.fail()) {
                                std::cout << "ERROR: not an integer !!" << std::endl;
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                goto print_state;
                        } else if (column < 0 || column >= N_COL) {
                                std::cout << "ERROR: integer out of bounds !!\n\n";
                                goto print_state;
                        }

                        b.play(column);
                        continue;
                }

                if (b.turn() != player && cpu) {
                        std::cout << "Calculating... ";
                        std::cout.flush();

                        int eval;
                        int column = comp.best_move(b, eval);
                        b.play(column);
                        std::cout << column << '\n';
                        std::cout << "Eval: " << eval << '\n';
                }
        }

        board_io::print_board(b);
        board_io::print_state(b);

        std::cout << "\nTHANK YOU FOR PLAYING :)\n\n";
}
