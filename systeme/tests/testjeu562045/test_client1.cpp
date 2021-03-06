#include "Client.hpp"
#include "game_test/CurrentGame.hpp"
#include "game_test/settingServer.hpp"
#include "game_test/Interface_game.hpp"
#include "parsing.hpp"


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

    Interface_game interface_game{};
    interface_game.init();
    interface_game.initialDraw();
    theSettings setting_to_diplay{};
    CurrentGame my_game{};
    bool gameOn = true;
    while(gameOn){

        int inp = wgetch(interface_game.get_main_window());
        Imene.send_game_input(inp);
        std::string val = Imene.read_game_pipe();
        Parsing::parsing_settings_game(val,&my_game);
        my_game.run_client(inp,&setting_to_diplay);
        interface_game.display(&setting_to_diplay);
        //display

    }
    //Imene.read_pipe();
    //std::cout << "je suis sortie de la "<< std::endl;
}