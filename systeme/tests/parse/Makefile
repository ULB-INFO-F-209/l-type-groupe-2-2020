all : run

flag = -std=c++17 -masm=intel -lncurses -fconcepts -pthread \
		-fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion \
		-Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
		 -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant\
		 -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override -lquadmath

main: main_client.cpp parsing.o 
	g++  main_client.cpp parsing.o $(flag) -o ex
parsing.o: parsing.hpp parsing.cpp
	g++  -c parsing.cpp $(flag) -o parsing.o
run:
	make main
	./ex
clean:
	rm ex parsing.o