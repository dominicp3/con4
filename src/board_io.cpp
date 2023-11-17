#include "board.hpp"
#include <iostream>

namespace board_io {
        void print_state(Board &b)
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

        void print_board(Board &b)
        {
                auto arr {b.current()};
                char c;
                std::cout << "\n   ---------------------------\n";
                for (int i = N_ROW - 1; i >= 0; i--) {
                        for (int j = 0; j < N_COL; j++) {
                                switch (arr[j][i]) {
                                case YELLOW:
                                        c = 'y';
                                        break;
                                case RED:
                                        c = 'r'; break;
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
}
