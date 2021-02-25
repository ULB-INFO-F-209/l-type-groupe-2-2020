all : run
flag = -std=c++17 -masm=intel -fcoroutines -fconcepts -pthread \
		-fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion \
		-Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
		 -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant\
		 -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override -lquadmath

session : main.cpp  interface.o screen.o menu.o parsing.o test.o
	g++ main.cpp interface.o screen.o menu.o parsing.o test.o $(flag) -lncurses -o session

interface.o: Interface.cpp Interface.hpp screen.hpp
	g++  -c Interface.cpp $(flag) -lncurses -o interface.o

screen.o:screen.hpp screen.cpp
	g++  -c screen.cpp $(flag) -lncurses -o screen.o

menu.o: Menu.hpp Menu.cpp
	g++  -c Menu.cpp $(flag) -lncurses -o menu.o

parsing.o: parsing.hpp parsing.cpp
	g++  -c parsing.cpp $(flag) -lncurses -o parsing.o

test.o: test.hpp test.cpp
	g++  -c test.cpp $(flag) -lncurses -o test.o

run:
	make session
	./session
clean:
	rm *.o
	rm session