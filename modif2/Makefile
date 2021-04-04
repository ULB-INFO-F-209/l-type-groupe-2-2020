all: run_server run_client compile 

qt_flag = -pipe -O2 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -I. -isystem /usr/include/x86_64-linux-gnu/qt5 -isystem /usr/include/x86_64-linux-gnu/qt5/QtWidgets -isystem /usr/include/x86_64-linux-gnu/qt5/QtGui -isystem /usr/include/x86_64-linux-gnu/qt5/QtCore -I. -isystem /usr/include/libdrm -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++

qt_exec_flag = -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread 

flag = -std=c++17 -masm=intel -lncurses -fconcepts -pthread \
		-fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion \
		-Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
		 -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant\
		 -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override -lquadmath

server: main_server.cpp server.o database.o account.o parsing.o  accountandvectors.o
	g++  main_server.cpp server.o database.o account.o parsing.o  accountandvectors.o $(flag) -o process_server

client: main_client.cpp client.o parsing.o  menu.o 
	g++  main_client.cpp  client.o parsing.o  menu.o $(qt_flag) $(flag) -Wl,-O1 -o process_client  $(qt_exec_flag)
	
menu.o: Menu.hpp Menu.cpp
	g++ -c Menu.cpp $(qt_flag) -o menu.o

client.o: Client.hpp Client.cpp Constante.hpp
	g++  -c Client.cpp $(flag) -o client.o 
	
server.o: server.cpp server.hpp Constante.hpp 
	g++  -c server.cpp $(flag) -o server.o 

database.o: database/database.hpp database/database.cpp
	g++  -c database/database.cpp $(flag) -o database.o

account.o: database/account.hpp database/account.cpp
	g++  -c database/account.cpp $(flag) -o account.o

accountandvectors.o:  database/accountandvectors.hpp  database/accountandvectors.cpp
	g++  -c  database/accountandvectors.cpp $(flag) -o accountandvectors.o

parsing.o: parsing.hpp parsing.cpp
	g++  -c parsing.cpp $(flag) -o parsing.o

run_server:
	make server && ./process_server

run_client:
	make client && ./process_client

clean:
	rm *.o
	rm /tmp/input_pipe_* /tmp/game_pipe_* /tmp/connexion /tmp/getrequest
