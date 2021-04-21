all : compile

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
	
client_gui: main_client_gui.cpp client.o label.o parsing.o  menugui.o  CurrentGame.o MapHandler.o displaygamegui.o
	g++  main_client_gui.cpp  client.o label.o parsing.o menugui.o CurrentGame.o MapHandler.o displaygamegui.o $(qt_flag) $(sfml_flag) $(flag) -Wl,-O1 -o process_client_gui  $(qt_exec_flag)
	
interface.o: Interface.cpp Interface.hpp screen.hpp
	g++  -c Interface.cpp $(flag) $(sfml_flag) -o interface.o

menugui.o: MenuGui.hpp MenuGui.cpp
	g++ -c MenuGui.cpp $(qt_flag) $(sfml_flag) -o menugui.o

menuterminal.o: MenuTerminal.hpp MenuTerminal.cpp
	g++  -c MenuTerminal.cpp $(flag) $(sfml_flag) -o menuterminal.o

displaygame.o: DisplayGame.cpp DisplayGame.hpp
	g++  -c DisplayGame.cpp $(flag) -o displaygame.o

displaygamegui.o: DisplayGameGui.cpp DisplayGameGui.hpp
	g++  -c DisplayGameGui.cpp $(flag) $(sfml_flag) -o displaygamegui.o

client.o: Client.hpp Client.cpp Constante.hpp
	g++  -c Client.cpp $(flag) -o client.o 
	

Label.cpp: Label.hpp
	moc $< -o $@
label.o: Label.cpp
	g++ Label.cpp -c $(qt_flag) $(qt_exec_flag) -o label.o

database.o: game/database/database.hpp game/database/database.cpp
	g++  -c game/database/database.cpp $(flag) -o database.o

account.o: game/database/account.hpp game/database/account.cpp
	g++  -c game/database/account.cpp $(flag) -o account.o

accountandvectors.o:  game/database/accountandvectors.hpp  game/database/accountandvectors.cpp
	g++  -c  game/database/accountandvectors.cpp $(flag) -o accountandvectors.o

parsing.o: game/parsing.hpp game/parsing.cpp
	g++  -c game/parsing.cpp $(flag) -o parsing.o


CurrentGame.o: game/CurrentGame.cpp  game/MapHandler.hpp game/Player.hpp game/CurrentGame.hpp
	g++ -g -c -o CurrentGame.o game/CurrentGame.cpp $(flag)

MapHandler.o: game/MapHandler.cpp game/MapHandler.hpp game/Rect.hpp game/InternGameObject.hpp game/Player.hpp
	g++ -g -c -o MapHandler.o game/MapHandler.cpp $(flag)

Player.o: game/Player.cpp game/Player.hpp
	g++ -g -c -o Player.o Player.cpp $(flag)

compile: server client_gui client_terminal

install:
	sudo apt-get install libncurses5-dev libncursesw5-dev
	sudo apt-get install libsfml-dev
	sudo apt-get install qt5-default

run_server:	server
	./process_server

run_client_terminal: client_terminal
	./process_client_terminal

run_client_gui: client_gui
	./process_client_gui

clean:
	rm *.o
	rm /tmp/input_pipe_* /tmp/game_pipe_* /tmp/connexion /tmp/getrequest

clean_db:
	rm *.bin


