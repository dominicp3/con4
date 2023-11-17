#ifndef COMPUTER_H
#define COMPUTER_H

#include "board.hpp"

class Computer {
public:
        int utility(Board board);
        int num_in_row(int count, Board board, enum player p);
};

#endif /* COMPUTER_H */
