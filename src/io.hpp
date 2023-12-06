#ifndef BOARD_IO_H
#define BOARD_IO_H

#include "board.hpp"
#include "computer.hpp"

namespace board_io
{
        void print_board(const Board &b);

        void print_state(const Board &b);

        void print_turn(const Board &b);
}

namespace computer_io
{
        void print_orientation(ORIENTATION o);
        void print_colour(COLOUR c);
}

#endif /* BOARD_IO_H */
