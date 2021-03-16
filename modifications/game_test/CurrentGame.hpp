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
#include "GameConstante.hpp"

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
    
    CurrentGame(Game_settings game_sett):twoPlayers(game_sett.nb_player == 2? true:false),friendlyFire(game_sett.ally_shot), dropRate(game_sett.drop_rate),dif(game_sett.diff),
        screen_area( {0, 0}, {80, 24}),game_area( {0, 0}, {78, 16}),map(dropRate,dif)
    int getInput() const{return in_char;}   //sert a quoi?
    std::string run_server(char move_to_exec);
    void execInput(int inChar, uint_fast16_t x1, uint_fast16_t y1, bool firstPlayer,std::string to_fill);
    
    void run();
};


#endif //JEU_CURRENTGAME_H

