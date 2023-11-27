#include <sstream>
#include <iostream>
#include <string>
#include "../src/game.hpp"

using namespace std;

int main(int argc, char **argv)
{
        if (argc != 2) {
                cout << "Usage: [depth]\n";
                return -1;
        }

        std::istringstream iss(argv[1]);
        int val;

        if (!(iss >> val)) {
                cout << "Invalid input\n";
                return -1;
        }

        game::play(true, val, true);
}
