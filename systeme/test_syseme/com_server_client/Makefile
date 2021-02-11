FLAGS = -std=c++17 -pthread

all: server client 

server: main_server.cpp server.o
	g++ $(FLAGS) main_server.cpp server.o -o process_server
client: main_client.cpp client.o
	g++  main_client.cpp  client.o -o process_client

client.o: Client.hpp Client.cpp Constante.hpp
	g++ $(FLAGS) -c Client.cpp -o client.o 
	
server.o: server.cpp server.hpp Constante.hpp
	g++ $(FLAGS) -c server.cpp -o server.o 

clean:
	rm *.o
	rm process_server
	rm process_client