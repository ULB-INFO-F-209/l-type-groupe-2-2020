all : run

flag = -std=c++17 -masm=intel -fcoroutines -fconcepts -pthread \
		-fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion \
		-Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
		 -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant\
		 -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override -lquadmath

session : main.cpp  interface.o Interface.hpp
	g++ main.cpp interface.o $(flag) -lncurses -o session
interface.o: Interface.cpp Interface.hpp
	g++  -c Interface.cpp $(flag) -lncurses -o interface.o
run:
	make session
	./session
clean:
	rm *.o
	rm session