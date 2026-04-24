FLAGS = -pedantic-errors -std=c++11

start.o: start.cpp game.hpp game_guide.hpp game_progress.hpp get_input.hpp win_lose.hpp
	g++ $(FLAGS) -c start.cpp

game.o: game.cpp game.hpp get_input.hpp
	g++ $(FLAGS) -c game.cpp

play: start.o game.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f *.o play game.tgz

tar:
	tar -czvf game.tgz *.cpp *.hpp *.txt

.PHONY: clean tar