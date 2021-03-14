FLAGS = -std=c++17 -masm=intel -fconcepts -pthread \
		-fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion \
		-Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
		 -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant\
		 -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override -lquadmath -pthread

main: main.o server.o parsing.o
	g++ $(FLAGS) main.o server.o parsing.o -o main

client: test_client.cpp
	g++  test_client.cpp -o clientobj.o

main.o: test_serve.cpp server.hpp
	g++ $(FLAGS) -c test_serve.cpp -o main.o
	
server.o: server.cpp server.hpp Constante.hpp
	g++ $(FLAGS) -c server.cpp -o server.o

parsing.o: parsing.hpp parsing.cpp
	g++ $(FLAGS) -c parsing.cpp -o parsing.o
clean:
	rm *.o
