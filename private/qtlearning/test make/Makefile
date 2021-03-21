all: run 

qt_flag = -pipe -O2 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -I. -isystem /usr/include/x86_64-linux-gnu/qt5 -isystem /usr/include/x86_64-linux-gnu/qt5/QtWidgets -isystem /usr/include/x86_64-linux-gnu/qt5/QtGui -isystem /usr/include/x86_64-linux-gnu/qt5/QtCore -I. -isystem /usr/include/libdrm -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++

qt_exec_flag = -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread 

button.o: Button.hpp Button.cpp
	g++ -c Button.cpp $(qt_flag) -o button.o
main.o: main.cpp
	g++ -c main.cpp $(qt_flag) -o main.o

ex : button.o main.o
	g++ -Wl,-O1 -o ex  button.o main.o  $(qt_exec_flag)

run:
	make ex
	./ex