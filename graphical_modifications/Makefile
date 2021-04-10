all : run_server run_client compile

flag = -std=c++17 -lncurses -fconcepts -pthread \
		-fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion \
		-Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
		 -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant\
		 -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override -lsfml-graphics -lsfml-window -lsfml-system


server: main_server.cpp server.o database.o account.o parsing.o CurrentGame.o MapHandler.o displaygame.o
	g++  main_server.cpp CurrentGame.o server.o database.o account.o parsing.o MapHandler.o displaygame.o $(flag) -o process_server

client: main_client.cpp client.o parsing.o interface.o screen.o menu.o CurrentGame.o MapHandler.o displaygame.o
	g++  main_client.cpp  client.o parsing.o interface.o screen.o menu.o CurrentGame.o MapHandler.o displaygame.o $(flag)  -o process_client
	
interface.o: Interface.cpp Interface.hpp screen.hpp
	g++  -c Interface.cpp $(flag) -o interface.o

screen.o:screen.hpp screen.cpp
	g++  -c screen.cpp $(flag) -o screen.o

displaygame.o: DisplayGame.cpp DisplayGame.hpp
	g++  -c DisplayGame.cpp $(flag) -o displaygame.o

menu.o: Menu.hpp Menu.cpp
	g++  -c Menu.cpp $(flag) -o menu.o

client.o: Client.hpp Client.cpp Constante.hpp
	g++  -c Client.cpp $(flag) -o client.o 
	
server.o: server.cpp server.hpp Constante.hpp 
	g++  -c server.cpp $(flag) -o server.o 

database.o: game_test/database/database.hpp game_test/database/database.cpp
	g++  -c game_test/database/database.cpp $(flag) -o database.o

CurrentGame.o: game_test/CurrentGame.cpp  game_test/MapHandler.hpp game_test/Player.hpp game_test/CurrentGame.hpp
	g++ -g -c -o CurrentGame.o game_test/CurrentGame.cpp $(flag)

MapHandler.o: game_test/MapHandler.cpp game_test/MapHandler.hpp game_test/Rect.hpp game_test/InternGameObject.hpp game_test/Player.hpp
	g++ -g -c -o MapHandler.o game_test/MapHandler.cpp $(flag)

Player.o: game_test/Player.cpp game_test/Player.hpp
	g++ -g -c -o Player.o Player.cpp $(flag)

account.o: game_test/database/account.hpp game_test/database/account.cpp
	g++  -c game_test/database/account.cpp $(flag) -o account.o

parsing.o: game_test/parsing.hpp game_test/parsing.cpp
	g++  -c game_test/parsing.cpp $(flag) -o parsing.o

compile:
	make server
	make client

run_server:
	make server && ./process_server

run_client:
	make client && ./process_client

clean:
	rm *.o
	rm /tmp/input_pipe_* /tmp/game_pipe_* /tmp/connexion /tmp/getrequest
