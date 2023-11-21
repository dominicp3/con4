CXX=clang++
CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic -Werror -Werror=vla
DEBUG=-g -fsanitize=address

.PHONY: clean

bin/main: test/main.cpp src/board.cpp src/misc_io.cpp src/game.cpp src/computer.cpp bin/
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $@ $< $(filter src/%.cpp, $^)

# bin/main: test/main.cpp obj/board.o obj/board_io.o obj/game.o obj/computer.o bin/
# 	$(CXX) $(CXXFLAGS) $(DEBUG) -o $@ $< $(filter obj/%.o, $^)

obj/board.o: src/board.cpp src/board.hpp obj/
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $@ -c $<

obj/board_io.o: src/board_io.cpp src/board_io.hpp obj/
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $@ -c $<

obj/game.o: src/game.cpp src/game.hpp obj/
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $@ -c $<

obj/computer.o: src/computer.cpp src/computer.hpp obj/
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $@ -c $<

obj/:
	mkdir obj/

bin/:
	mkdir bin/

clean:
	rm -rf bin/ obj/
