all : run_server run_client
flag = -std=c++17 -masm=intel -lncurses -fconcepts -pthread \
		-fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion \
		-Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
		 -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant\
		 -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override -lquadmath

server: main_server.cpp server.o database.o account.o parsing.o CurrentGame.o MapHandler.o game_test/settingServer.hpp interface_game.o
	g++  main_server.cpp CurrentGame.o server.o database.o account.o parsing.o MapHandler.o interface_game.o $(flag) -o process_server

client: main_client.cpp client.o parsing.o interface.o screen.o menu.o CurrentGame.o MapHandler.o interface_game.o
	g++  main_client.cpp  client.o parsing.o interface.o screen.o menu.o CurrentGame.o MapHandler.o interface_game.o $(flag)  -o process_client

test_client: test_client1.cpp client.o parsing.o interface.o screen.o menu.o CurrentGame.o MapHandler.o interface_game.o
	g++  test_client1.cpp  client.o parsing.o interface.o screen.o menu.o CurrentGame.o MapHandler.o interface_game.o $(flag)  -o test_client1
	
interface.o: Interface.cpp Interface.hpp screen.hpp
	g++  -c Interface.cpp $(flag) -o interface.o

screen.o:screen.hpp screen.cpp
	g++  -c screen.cpp $(flag) -o screen.o

interface_game.o: game_test/Interface_game.cpp game_test/MapHandler.hpp game_test/Player.hpp game_test/CurrentGame.hpp 
	g++ -g -c -o interface_game.o game_test/Interface_game.cpp $(flag)


menu.o: Menu.hpp Menu.cpp
	g++  -c Menu.cpp $(flag) -o menu.o

client.o: Client.hpp Client.cpp Constante.hpp
	g++  -c Client.cpp $(flag) -o client.o 
	
server.o: server.cpp server.hpp Constante.hpp game_test/settingServer.hpp
	g++  -c server.cpp $(flag) -o server.o 

database.o: database/database.hpp database/database.cpp
	g++  -c database/database.cpp $(flag) -o database.o

CurrentGame.o: game_test/CurrentGame.cpp game_test/settingServer.hpp game_test/MapHandler.hpp game_test/Interface_game.hpp game_test/Player.hpp game_test/CurrentGame.hpp
	g++ -g -c -o CurrentGame.o game_test/CurrentGame.cpp $(flag)

MapHandler.o: game_test/MapHandler.cpp game_test/MapHandler.hpp game_test/settingServer.hpp game_test/Rect.hpp game_test/InternGameObject.hpp game_test/Player.hpp
	g++ -g -c -o MapHandler.o game_test/MapHandler.cpp $(flag)

Player.o: game_test/Player.cpp game_test/Player.hpp
	g++ -g -c -o Player.o Player.cpp $(flag)


account.o: database/account.hpp database/account.cpp
	g++  -c database/account.cpp $(flag) -o account.o

parsing.o: parsing.hpp parsing.cpp
	g++  -c parsing.cpp $(flag) -o parsing.o

run_test_client: 
	make test_client
	./test_client1

run_server:
	make server
	./process_server
run_client:
	make client
	./process_client
clean:
	rm *.o
	rm process_server process_client /tmp/pipefile* /tmp/connexion /tmp/reponse