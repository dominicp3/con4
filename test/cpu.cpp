#include <sstream>
#include <iostream>
#include <string>
#include "../src/game.hpp"

int main(int argc, char **argv)
{
        int depth = 11;
        bool red = true;
        std::string usage = "Usage: [depth] [red/yellow]\n";

        if (argc > 3) {
                std::cout << usage;
                return -1;
        }

        if (argc >= 2) {
                std::istringstream iss(argv[1]);
                if (!(iss >> depth)) {
                        std::cout << usage;
                        return -1;
                }
        }

        if (argc == 3) {
                std::string colour = argv[2];

                if (colour.compare("red") == 0) {
                        red = true;
                } else if (colour.compare("yellow") == 0) {
                        red = false;
                } else {
                        std::cout << usage;
                        return -1;
                }
        }

        if (depth <= 0) {
                std::cout << "Depth must be a positive integer!" << std::endl;
                return -1;
        }

        std::cout << "depth = " << depth << std::endl;
        game::play(true, depth, red);
}
