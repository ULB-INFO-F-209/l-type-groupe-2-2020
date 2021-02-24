#ifndef CONSTANTE_HPP
#define CONSTANTE_HPP

#include <cstddef>

/**
 * 
 * Constante lier au serveur et au client 
 * (rajouter vos constante si besoin)
 * 
 **/
namespace Constante{

    const size_t CHAR_SIZE = 264;

    //pipe
    const char PIPE_DE_CONNEXION[] = {"connexion"};
    const char PIPE_DE_REPONSE[] = {"getrequest"};
    const char BASE_PIPE_FILE[] = {"pipefile_"};
    const char PIPE_PATH[] = {"/tmp/"};
    const int PIPE_MODE = 0666;

    //gestion des messages
    constexpr char ACTION_MENU_PRINCIPAL[] = {"Mabcdefghijklmopqrstuvwxyz"};
    constexpr char REPONSE_AMI = 'R';
    const char PAS_SECOND_JOUEUR[] = {"Null"};
    constexpr char ACTION_JEU[] = {"J"/* ajouter les touches possibles*/};
    constexpr char DELIMITEUR = '&';

    //client
    const size_t SIZE_PSEUDO  = 20;
    const size_t SIZE_pipe =64;

    //server
    const int SERVER_SAVE_TIME = 90;

    constexpr char J1_LEFT = 'q';
    constexpr char GAME_QUIT = 'p';
    constexpr char J1_UP = 'z';
    constexpr char J1_DOWN = 's';
    constexpr char J1_RIGHT = 'd';
    constexpr char J1_DIAG_UP_LEFT = 'z';
    constexpr char J1_DIAG_UP_RIGHT = 'e';
    constexpr char J1_DIAG_DOWN_RIGHT = 'c';
    constexpr char J1_DIAG_DOWN_LEFT = 'w';
    constexpr char J1_SHOOT = ' ';

    //J2
    constexpr char J2_LEFT = 'f';
    constexpr char J2_UP = 't';
    constexpr char J2_DOWN = 'g';
    constexpr char J2_RIGHT = 'h';
    constexpr char J2_DIAG_UP_LEFT = 'r';
    constexpr char J2_DIAG_UP_RIGHT = 'y';
    constexpr char J2_DIAG_DOWN_RIGHT = 'n';
    constexpr char J2_DIAG_DOWN_LEFT = 'v';
    constexpr char J2_SHOOT = 'm';
}

#endif // CONSTANTE_HPP
