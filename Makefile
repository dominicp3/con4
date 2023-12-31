CXX=clang++
CXXFLAGS=-std=c++20 -O3 -Wall -Wextra -pedantic -Werror -Werror=vla -Wno-unused-variable
SRC=src/board.cpp src/io.cpp src/game.cpp src/computer.cpp

.PHONY: clean

bin/cpu: test/cpu.cpp $(SRC) bin/
	$(CXX) $(CXXFLAGS) -o $@ $< $(filter src/%.cpp, $^)

bin/test: test/test.cpp $(SRC) bin/
	$(CXX) $(CXXFLAGS) -o $@ $< $(filter src/%.cpp, $^)

bin/pvp: test/pvp.cpp $(SRC) bin/
	$(CXX) $(CXXFLAGS) -o $@ $< $(filter src/%.cpp, $^)

obj/board.o: src/board.cpp src/board.hpp obj/
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/board_io.o: src/board_io.cpp src/board_io.hpp obj/
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/game.o: src/game.cpp src/game.hpp obj/
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/computer.o: src/computer.cpp src/computer.hpp obj/
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/:
	mkdir obj/

bin/:
	mkdir bin/

clean:
	rm -rf bin/ obj/
