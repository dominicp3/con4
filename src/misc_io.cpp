#include "board.hpp"
#include "computer.hpp"
#include <iostream>

namespace board_io
{
        void print_board(const Board &b)
        {
                auto arr {b.current()};
                char c;
                std::cout << "\n   ---------------------------\n";
                for (int i = N_ROW - 1; i >= 0; i--) {
                        for (int j = 0; j < N_COL; j++) {
                                switch (arr[j][i]) {
                                case YELLOW:
                                        c = 'X';
                                        break;
                                case RED:
                                        c = 'O'; break;
                                case BLANK:
                                        c = ' '; break;
                                default:;
                                }

                                if (j == 0)
                                        std::cout << i << " | ";
                                std::cout << c << " | ";
                        }
                        std::cout << '\n';\
                        if (i == 0) {
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
                        std::cout << "GAME IN PROGRESS !!\n";
                        break;

                default:
                        std::cout << "ERROR STATE !!\n";
                }
        }

        void print_state_xo(const Board &b)
        {
                switch (b.state()) {
                case WIN_YELLOW:
                        std::cout << "X WON !!\n";
                        break;

                case WIN_RED:
                        std::cout << "O WON !!\n";
                        break;

                case DRAW:
                        std::cout << "DRAW !!\n";
                        break;

                case PLAYING:
                        std::cout << "GAME IN PROGRESS !!\n";
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

