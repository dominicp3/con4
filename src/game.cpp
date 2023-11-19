#include "game.hpp"
#include "board.hpp"
#include "board_io.hpp"
#include <iostream>
#include <string>

void game::game()
{
        Board b;
        int column;
        STATE state;
        std::string outcome;

        while (true) {
                board_io::print_board(b);

                if (b.turn() == YELLOW) {
                        std::cout << "Yellow's turn, enter a column: ";
                } else if (b.turn() == RED) {
                        std::cout << "Red's turn, enter a column: ";
                }

                std::cin >> column;

                if (std::cin.fail()) {
                        std::cout << "ERROR: not an integer !!\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                } else if (column < 0 || column >= N_COL) {
                        std::cout << "\nERROR: integer out of bounds !!\n\n";
                        continue;
                }

                b.play(column);
                state = b.state();

                if (state == WIN_YELLOW) {
                        outcome = "YELLOW WINS !!\n";
                        break;
                }

                if (state == WIN_RED) {
                        outcome = "RED WINS !!\n";
                        break;
                }

                if (state == DRAW) {
                        outcome = "DRAW !!\n";
                        break;
                }
        }

        board_io::print_board(b);
        std::cout << outcome;
        std::cout << "\nTHANK YOU FOR PLAYING :)\n\n";
}
