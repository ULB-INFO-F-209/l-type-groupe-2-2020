#include "Client.hpp"

void test1();

int main()
{
	test1();
	//Client Django{}, Imene{},zanilia{};;
	
	return 0;
}

void test1(){
	int a = 0;
	
	Client Imene{};

    Imene.signUp("Imene", "caca");
    std::cout << "signUp fini" << std::endl<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    Imene.createGame("P&1&Imene&&100&0&3");
    Imene.read_pipe();
}