FLAGS = -std=c++17 -pthread

all: server client client2

server: main_server.cpp server.o database.o account.o parsing.o
	g++ $(FLAGS) main_server.cpp server.o database.o account.o parsing.o -o process_server

client: main_client.cpp client.o
	g++  main_client.cpp  client.o -o process_client

client2: test_client2.cpp client.o
	g++  test_client2.cpp  client.o -o process_client2

client.o: Client.hpp Client.cpp Constante.hpp
	g++ $(FLAGS) -c Client.cpp -o client.o 
	
server.o: server.cpp server.hpp Constante.hpp
	g++ $(FLAGS) -c server.cpp -o server.o 

database.o: database/database.hpp database/database.cpp
	g++ ${FLAGS} -c database/database.cpp -o database.o

account.o: database/account.hpp database/account.cpp
	g++ ${FLAGS} -c database/account.cpp -o account.o

parsing.o: parsing.hpp parsing.cpp
	g++ ${FLAGS} -c parsing.cpp -o parsing.o

run_server:
	./process_server
run_client:
	./process_client

clean:
	rm *.o process_server process_client /tmp/pipefile* /tmp/connexion /tmp/reponse