FLAGS = -std=c++17 -pthread

main: main.o server.o
	g++ main.o server.o -o main

client: test_client.cpp
	g++  test_client.cpp -o clientobj.o

main.o: test_serve.cpp server.hpp
	g++ -c test_serve.cpp -o main.o
	
server.o: server.cpp 
	g++ $(FLAGS) -c server.cpp -o server.o

clean:
	rm *.o