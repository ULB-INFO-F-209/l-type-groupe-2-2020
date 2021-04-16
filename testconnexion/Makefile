all : run_server run_client compile

flag = -std=c++17 -lncurses -fconcepts -pthread \
		-fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion \
		-Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
		 -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant\
		 -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override 

sfml_flag = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

qt_flag = -pipe -O2 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -I. -isystem /usr/include/x86_64-linux-gnu/qt5 -isystem /usr/include/x86_64-linux-gnu/qt5/QtWidgets -isystem /usr/include/x86_64-linux-gnu/qt5/QtGui -isystem /usr/include/x86_64-linux-gnu/qt5/QtCore -I. -isystem /usr/include/libdrm -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++

qt_exec_flag = -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread 


server: main_server.cpp server.o database.o account.o parsing.o CurrentGame.o MapHandler.o displaygame.o displaygamegui.o accountandvectors.o
	g++  main_server.cpp CurrentGame.o server.o database.o account.o parsing.o MapHandler.o displaygame.o displaygamegui.o accountandvectors.o $(flag) $(sfml_flag) -o process_server

client_terminal: main_client_terminal.cpp client.o parsing.o interface.o menuterminal.o CurrentGame.o MapHandler.o displaygame.o
	g++  main_client_terminal.cpp  client.o parsing.o interface.o menuterminal.o CurrentGame.o MapHandler.o displaygame.o $(flag) $(sfml_flag) -o process_client_terminal
	
client_gui: main_client_gui.cpp client.o parsing.o  menugui.o  CurrentGame.o MapHandler.o displaygamegui.o
	g++  main_client_gui.cpp  client.o parsing.o menugui.o CurrentGame.o MapHandler.o displaygamegui.o $(qt_flag) $(sfml_flag) $(flag) -Wl,-O1 -o process_client_gui  $(qt_exec_flag)
	
interface.o: Interface.cpp Interface.hpp screen.hpp
	g++  -c Interface.cpp $(flag) $(sfml_flag) -o interface.o

menugui.o: MenuGui.hpp MenuGui.cpp
	g++ -c MenuGui.cpp $(qt_flag) $(sfml_flag) -o menugui.o

menuterminal.o: MenuTerminal.hpp MenuTerminal.cpp
	g++  -c MenuTerminal.cpp $(flag) $(sfml_flag) -o menuterminal.o

screen.o:screen.hpp screen.cpp
	g++  -c screen.cpp $(flag) -o screen.o

displaygame.o: DisplayGame.cpp DisplayGame.hpp
	g++  -c DisplayGame.cpp $(flag) -o displaygame.o

displaygamegui.o: DisplayGameGui.cpp DisplayGameGui.hpp
	g++  -c DisplayGameGui.cpp $(flag) $(sfml_flag) -o displaygamegui.o

client.o: Client.hpp Client.cpp Constante.hpp
	g++  -c Client.cpp $(flag) -o client.o 
	


database.o: game_test/database/database.hpp game_test/database/database.cpp
	g++  -c game_test/database/database.cpp $(flag) -o database.o

account.o: game_test/database/account.hpp game_test/database/account.cpp
	g++  -c game_test/database/account.cpp $(flag) -o account.o

accountandvectors.o:  game_test/database/accountandvectors.hpp  game_test/database/accountandvectors.cpp
	g++  -c  game_test/database/accountandvectors.cpp $(flag) -o accountandvectors.o

parsing.o: game_test/parsing.hpp game_test/parsing.cpp
	g++  -c game_test/parsing.cpp $(flag) -o parsing.o


CurrentGame.o: game_test/CurrentGame.cpp  game_test/MapHandler.hpp game_test/Player.hpp game_test/CurrentGame.hpp
	g++ -g -c -o CurrentGame.o game_test/CurrentGame.cpp $(flag)

MapHandler.o: game_test/MapHandler.cpp game_test/MapHandler.hpp game_test/Rect.hpp game_test/InternGameObject.hpp game_test/Player.hpp
	g++ -g -c -o MapHandler.o game_test/MapHandler.cpp $(flag)

Player.o: game_test/Player.cpp game_test/Player.hpp
	g++ -g -c -o Player.o Player.cpp $(flag)

compile:
	make server
	make client_terminal

install:
	echo "ecrire les commandes pour installer ncursus, sfml et qt5 -_- "

run_server:
	make server && ./process_server

run_client_terminal:
	make client_terminal && ./process_client_terminal

run_client_gui:
	make client_gui && ./process_client_gui

clean:
	rm *.o
	rm /tmp/input_pipe_* /tmp/game_pipe_* /tmp/connexion /tmp/getrequest

clean_db:
	rm *.bin


