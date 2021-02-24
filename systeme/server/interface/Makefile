all : run
flag = -std=c++17 -masm=intel -fcoroutines -fconcepts -pthread \
		-fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion \
		-Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
		 -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant\
		 -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override -lquadmath

session : main.cpp  interface.o screen.o menu.o
	g++ main.cpp interface.o screen.o menu.o $(flag) -lncurses -o session
interface.o: Interface.cpp Interface.hpp screen.hpp
	g++  -c Interface.cpp $(flag) -lncurses -o interface.o
screen.o:screen.hpp screen.cpp
	g++  -c screen.cpp $(flag) -lncurses -o screen.o

menu.o: Menu.hpp Menu.cpp
	g++  -c Menu.cpp $(flag) -lncurses -o menu.o
run:
	make session
	./session
clean:
	rm *.o
	rm session