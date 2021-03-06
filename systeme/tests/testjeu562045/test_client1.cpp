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

    Imene.createGame("1&Imene&&100&0&1&easy");
    std::cout << "create game fini" << std::endl<<std::endl;


    Game_settings option_jeu;
    option_jeu.ally_shot = false; option_jeu.diff = easy; option_jeu.drop_rate =100; option_jeu.nb_lives = 1; option_jeu.nb_player = 1; strcpy(option_jeu.pseudo_hote,"Imene");
    Interface_game interface_game;
    interface_game.init();
    interface_game.initialDraw();
    settingServer setting_to_diplay{};
    CurrentGame my_game(option_jeu);
    bool gameOn = true;
    int inp{};

    while(gameOn){

        inp = wgetch(interface_game.get_main_window());
        Imene.send_game_input(inp);

        std::string val = Imene.read_game_pipe();
        Parsing::parsing_settings_game(val,&my_game);
        my_game.run_client(inp,&setting_to_diplay);
        //inp = -10;
        //Imene.send_game_input(inp);
        
        interface_game.display(&setting_to_diplay);
        
        gameOn = !setting_to_diplay.game_over;
    

    }
    interface_game.close();

}