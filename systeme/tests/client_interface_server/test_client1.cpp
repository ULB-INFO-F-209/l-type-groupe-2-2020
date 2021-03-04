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

    Imene.signIn("Imene", "caca",false);
    std::cout << "signIn fini" << std::endl<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    Imene.createGame("1&Imene&&100&0&2");
    std::cout << "create game fini" << std::endl<<std::endl;
    Imene.read_pipe();
}