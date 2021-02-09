CFLAGS = -std=c++11 -Wall -pedantic

bin/main: bin/main.o bin/game.o bin/MapHandler.o bin/Player.o
	g++ -g -o bin/main bin/main.o bin/game.o bin/MapHandler.o bin/Player.o $(CFLAGS) -lncurses

bin/main.o: src/main.cpp
	mkdir -p bin	
	g++ -g -c -o bin/main.o src/main.cpp $(CFLAGS) 

bin/game.o: src/game.cpp src/game.hpp src/MapHandler.hpp
	mkdir -p bin	
	g++ -g -c -o bin/game.o src/game.cpp $(CFLAGS)

bin/MapHandler.o: src/MapHandler.cpp src/MapHandler.hpp
	mkdir -p bin	
	g++ -g -c -o bin/MapHandler.o src/MapHandler.cpp $(CFLAGS)

bin/Player.o: src/Player.cpp src/Player.hpp
	mkdir -p bin	
	g++ -g -c -o bin/Player.o src/Player.cpp $(CFLAGS)
