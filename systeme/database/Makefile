flag = -std=c++17 -masm=intel -fcoroutines -fconcepts -pthread \
		-fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion \
		-Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
		 -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant\
		 -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override -lquadmath

test: test_db.cpp database.o
	gcc -o test test_db database.o ${flag}

database.o: database.hpp database.cpp
	gcc -c database.cpp -o database.o ${flag}

run: 
	make test && ./test

clean:
	rm database.o
	rm test
