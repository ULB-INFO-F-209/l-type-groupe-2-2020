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
#include "InternGameObject.hpp"
#include "GameConstante.hpp"
#include "parsing.hpp"


class CurrentGame {
    // lance et gère la partie sur base des inputs du serveur
    rect game_area; // cadre comprenant l'espace de jeu
    rect screen_area; // cadre comprenant l'entièreté de la fenêtre
    bool twoPlayers;
    bool friendlyFire;
    int dropRate;
    difficulty dif{};

    MapHandler map;

    int tick=0;  // 1 tick = 1 boucle du jeu
    int tickGameOver = -1;
    int finalScore1{};
    int finalScore2{};

    PlayerShip* playership1;
    Player* player1;

    PlayerShip* playership2 = nullptr;
    Player* player2 = nullptr;
    
    std::vector<Player*> listPlayer=std::vector<Player*>();

    bool exit_requested = false;
    bool game_over = false;
    int lastLevel = 4;

    void execInput(int* inChar, uint_fast16_t x1, uint_fast16_t y1, bool firstPlayer);
    // Si Player a encore au moins 1 vie : reset les hp du PlayerShip à 100 après sa mort
    void heal();
    void saveScore();
    void destroyPlayership();
    std::string getPlayerState(std::string state);



public:
    CurrentGame()=default;
    int getScore(){return finalScore1+finalScore2;}
    CurrentGame(Parsing::Game_settings);
    std::string run_server(int *move_to_exec);
};


#endif //JEU_CURRENTGAME_H

