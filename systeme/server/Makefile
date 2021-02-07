FLAGS = -std=c++17 -pthread

main: server.cpp server.hpp server.o
	g++ server.o server.cpp server.hpp -o theserver

server.o: server.cpp
	g++ $(FLAGS) server.cpp -o server.o

clean:
	rm
