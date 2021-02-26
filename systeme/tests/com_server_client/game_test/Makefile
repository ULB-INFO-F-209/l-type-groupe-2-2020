CFLAGS = -std=c++11 -Wall -pedantic

all: test_currentgame

main: main.cpp	CurrentGame.o MapHandler.o Interface.o Player.o
	g++ -g  -o main main.cpp CurrentGame.o MapHandler.o Interface.o Player.o $(CFLAGS) -lncurses

test_currentgame: test_currentgame.cpp Interface.o CurrentGame.o MapHandler.o Player.o
	g++ -g -o run1 test_currentgame.cpp Interface.o CurrentGame.o MapHandler.o Player.o $(CFLAGS) -lncurses

Interface.o: Interface.cpp MapHandler.hpp Player.hpp CurrentGame.hpp 
	g++ -g -c -o Interface.o Interface.cpp $(CFLAGS)

CurrentGame.o: CurrentGame.cpp MapHandler.hpp Interface.hpp Player.hpp
	g++ -g -c -o CurrentGame.o CurrentGame.cpp $(CFLAGS)

MapHandler.o: MapHandler.cpp Rect.hpp InternGameObject.hpp Player.hpp
	g++ -g -c -o MapHandler.o MapHandler.cpp $(CFLAGS)

Player.o: Player.cpp Player.hpp
	g++ -g -c -o Player.o Player.cpp $(CFLAGS)

clean:
	rm *.o
