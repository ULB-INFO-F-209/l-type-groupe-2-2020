all : run_server run_client
flag = -std=c++17 -masm=intel -lncurses -fconcepts -pthread \
		-fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion \
		-Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
		 -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant\
		 -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override -lquadmath

server: main_server.cpp server.o database.o account.o parsing.o
	g++  main_server.cpp server.o database.o account.o parsing.o $(flag) -o process_server

client: main_client.cpp client.o parsing.o interface.o screen.o menu.o
	g++  main_client.cpp  client.o parsing.o interface.o screen.o menu.o  $(flag)  -o process_client

interface.o: Interface.cpp Interface.hpp screen.hpp
	g++  -c Interface.cpp $(flag) -o interface.o

screen.o:screen.hpp screen.cpp
	g++  -c screen.cpp $(flag) -o screen.o

menu.o: Menu.hpp Menu.cpp
	g++  -c Menu.cpp $(flag) -o menu.o

client.o: Client.hpp Client.cpp Constante.hpp
	g++  -c Client.cpp $(flag) -o client.o 
	
server.o: server.cpp server.hpp Constante.hpp
	g++  -c server.cpp $(flag) -o server.o 

database.o: database/database.hpp database/database.cpp
	g++  -c database/database.cpp $(flag) -o database.o

account.o: database/account.hpp database/account.cpp
	g++  -c database/account.cpp $(flag) -o account.o

parsing.o: parsing.hpp parsing.cpp
	g++  -c parsing.cpp $(flag) -o parsing.o

run_server:
	make server
	./process_server
run_client:
	make client
	./process_client
clean:
	rm *.o
	rm process_server process_client /tmp/pipefile* /tmp/connexion /tmp/reponse