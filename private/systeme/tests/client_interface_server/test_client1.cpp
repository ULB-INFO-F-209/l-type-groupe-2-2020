#include "Client.hpp"
#include "game_test/CurrentGame.hpp"
#include "game_test/settingServer.hpp"
#include "game_test/Interface_game.hpp"


void test1();

int main()
{
	test1();
	std::cout << "je suis vraiment sortie de la !!" << std::endl;
	return 0;
}

void test1(){
	int a = 0;
	
	Client Imene{};

    Imene.signIn("Imene", "caca",false);
    std::cout << "signIn fini" << std::endl<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout<< "SLEEP FINI "<< std::endl << std::endl;

    Imene.createGame("1&Imene&&100&0&8");
    std::cout << "create game fini" << std::endl<<std::endl;

    Imene.read_pipe();
    std::cout << "je suis sortie de la "<< std::endl;
}