flag = -std=c++17 -masm=intel -fcoroutines -fconcepts -pthread \
		-fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion \
		-Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
		 -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant\
		 -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override -lquadmath

test: test_db.cpp database.o account.o accountandvectors.o
	g++ -o test test_db.cpp database.o account.o accountandvectors.o ${flag}

database.o: database.hpp database.cpp
	g++ -c database.cpp -o database.o ${flag}

account.o: account.hpp account.cpp
	g++ -c account.cpp -o account.o ${flag}

accountandvectors.o: accountandvectors.hpp accountandvectors.cpp
	g++ -c accountandvectors.cpp -o accountandvectors.o ${flag}

run: 
	make test && ./test

clean:
	rm *.o
	rm test
	rm *.bin