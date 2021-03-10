//
// Created by jean on 19/02/2021.
//

#ifndef GAME_CURRENTGAME_H
#define GAME_CURRENTGAME_H

#include <unistd.h>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include "MapHandler.hpp"
#include "Interface_game.hpp"
#include "InternGameObject.hpp"

class CurrentGame {

    rect game_area;
    rect screen_area;
    bool twoPlayers;
    bool friendlyFire;
    int dropRate;
    difficulty dif{};

    MapHandler map;

    int tick=0;
    int finalScore1{};
    int finalScore2{};

    PlayerShip* playership1;
    Player* player1;

    PlayerShip* playership2 = nullptr;
    Player* player2 = nullptr;
    
    std::vector<Player*> listPlayer=std::vector<Player*>();

    int in_char = 0;
    bool exit_requested = false;
    bool game_over = false;

    // méthodes privées
    void execInput(int inChar, uint_fast16_t x1, uint_fast16_t y1, bool firstPlayer);
    void heal();
    void saveScore();

public:
    CurrentGame()=default;
    CurrentGame(bool twoP, int dropR, difficulty d, bool ff):twoPlayers(twoP),dropRate(dropR),map(dropR,d){ dif=d; friendlyFire=ff;}
    CurrentGame(bool twoP, int dropR, difficulty d, bool ff, Interface_game* anInterface):twoPlayers(twoP),dropRate(dropR),map(dropR,d){ dif=d; friendlyFire=ff;
        playership1 = new PlayerShip(10, 5, { {10 - 1, 5 }, { 3, 2 } }, '0',100, 0,100,0);
        player1 = new Player(1);
        listPlayer.push_back(player1);

        if(twoPlayers){
            playership2 = new PlayerShip(50, 5, { { 50 - 1, 5 }, { 3, 2 } }, '1',100, 1,100,0);
            player2 = new Player(1);
            listPlayer.push_back(player2);
        }
        
        map.playerInit(playership1,playership2);
        map.setBounds(anInterface->get_game_area());
        game_area = anInterface->get_game_area();
        screen_area = anInterface->get_screen_area();
    }
    CurrentGame(Game_settings game_sett):twoPlayers(game_sett.nb_player == 2? true:false),friendlyFire(game_sett.ally_shot), dropRate(game_sett.drop_rate),dif(game_sett.diff),screen_area( {0, 0}, {80, 24}),game_area( {0, 0}, {static_cast<uint_fast16_t>(screen_area.width() - 2), static_cast<uint_fast16_t>(screen_area.height() - 4 - 4)}) {
        
        playership1 = new PlayerShip(10, 5, { {10 - 1, 5 }, { 3, 2 } }, '0',100, 0,100,0);
        player1 = new Player(game_sett.nb_lives);
        listPlayer.push_back(player1);

        if(twoPlayers){
            playership2 = new PlayerShip(50, 5, { { 50 - 1, 5 }, { 3, 2 } }, '1',100, 1,100,0);
            player2 = new Player(game_sett.nb_lives);
            listPlayer.push_back(player2);
        }
        map.playerInit(playership1,playership2);
        map.setBounds(game_area);
    }
    void run_test(theSettings* setting_to_fill,char in_char);
    int getInput() const{return in_char;};
    void getSettings(theSettings* settings);
    char* run_server(char * move_to_exec);
    void run_client(char * parametre_to_change);



    void run();
};


#endif //JEU_CURRENTGAME_H

