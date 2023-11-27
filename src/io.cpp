#include "io.hpp"
#include <iostream>
#include <string>

namespace board_io
{
        void print_board(const Board &b)
        {
                auto arr {b.current()};
                std::string s;
                std::cout << "   ---------------------------\n";
                for (int row = N_ROW - 1; row >= 0; row--) {
                        for (int col = 0; col < N_COL; col++) {
                                switch (arr[col][row]) {
                                case YELLOW:
                                        s = "\033[1;33mO\033[0m";
                                        break;
                                case RED:
                                        s = "\033[1;31mO\033[0m";
                                        break;
                                case BLANK:
                                        s = " "; break;
                                default:;
                                }

                                if (col == 0)
                                        std::cout << row << " | ";
                                std::cout << s << " | ";
                        }
                        std::cout << '\n';
                        if (row == 0) {
                                std::cout << "   ---------------------------\n";
                                std::cout << "    0   1   2   3   4   5   6\n";
                        }
                }
                std::cout << "\n" << std::endl;
        }

        void print_state(const Board &b)
        {
                switch (b.state()) {
                case WIN_YELLOW:
                        std::cout << "YELLOW WON !!\n";
                        break;

                case WIN_RED:
                        std::cout << "RED WON !!\n";
                        break;

                case DRAW:
                        std::cout << "DRAW !!\n";
                        break;

                case PLAYING:
                        if (b.turn() == RED) {
                                std::cout << "RED's turn: ";
                        } else if (b.turn() == YELLOW) {
                                std::cout << "YELLOW's turn: ";
                        }
                        break;

                default:
                        std::cout << "ERROR STATE !!\n";
                }
        }

        void print_turn(const Board &b)
        {
                switch (b.turn()) {
                case YELLOW:
                        std::cout << "Yellow's turn\n";
                        return;
                
                case RED:
                        std::cout << "Red's turn\n";
                        return;
                
                default:
                        std::cout << "TURN ERROR !!\n";
                }
        }

        void print_turn_xo(const Board &b)
        {
                switch (b.turn()) {
                case YELLOW:
                        std::cout << "X's turn\n";
                        return;
                
                case RED:
                        std::cout << "O's turn\n";
                        return;
                
                default:
                        std::cout << "TURN ERROR !!\n";
                }
        }
}

namespace computer_io
{
        void print_orientation(ORIENTATION o)
        {
                switch (o) {
                case VERTICAL:
                        std::cout << "vertical";
                        return;

                case HORIZONTAL:
                        std::cout << "horizontal";
                        return;

                case DIAGONAL_POS:
                        std::cout << "diagonal_pos";
                        return;

                case DIAGONAL_NEG:
                        std::cout << "diagonal_neg";
                        return;

                default:;
                }
        }

        void print_colour(COLOUR c)
        {
                switch (c) {
                case YELLOW:
                        std::cout << "yellow";
                        return;
                case RED:
                        std::cout << "red";
                        return;
                default:;
                }
        }
}
