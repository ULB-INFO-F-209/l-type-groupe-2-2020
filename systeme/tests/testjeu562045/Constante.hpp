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

    const size_t CHAR_SIZE = 2500;

    //pipe
    const char PIPE_DE_CONNEXION[] = {"connexion"};
    const char PIPE_DE_REPONSE[]   = {"getrequest"};
    const char BASE_PIPE_FILE[]    = {"pipefile_"};
    const char BASE_INPUT_PIPE[]   = {"input_pipe_"};
    const char BASE_GAME_PIPE[]    = {"game_pipe_"};
    const char PIPE_PATH[]         = {"/tmp/"};
    const int  PIPE_MODE            = 0666;

    //gestion des messages
    constexpr char ACTION_MENU_PRINCIPAL = 'M';
    constexpr char GAME_SETTINGS = 'P';
    constexpr char REPONSE_AMI = 'R';
    const char PAS_SECOND_JOUEUR[] = {"Null"};
    constexpr char ACTION_JEU[] = {"J"/* ajouter les touches possibles*/};
    constexpr char DELIMITEUR = '&';

    //client
    const size_t SIZE_PSEUDO = 20;
    const size_t SIZE_pipe = 64;

    //server
    const unsigned SERVER_SAVE_TIME = 90000;

    // MENU
    constexpr char SIGN_IN = 'a';
    constexpr char SIGN_UP = 'b';
    constexpr char ADD_FRIEND = 'c';
    constexpr char DEL_FRIEND = 'd';
    constexpr char SEND_FRIEND_REQUEST = 'e';
    constexpr char GET_FRIEND_REQUEST = 'f';
    constexpr char GET_FRIEND_LIST = 'g';
    constexpr char LEARDERBOARD = 'h';
    constexpr char VIEW_PROFILE = 'i';
    constexpr char CLIENT_EXIT = 'j';
    constexpr char DEL_FRIEND_REQUEST = 'k';

    //J1
    constexpr char KEY_J1_LEFT = 'q';
    constexpr char KEY_GAME_QUIT = 'p';
    constexpr char KEY_J1_UP = 'z';
    constexpr char KEY_J1_DOWN = 's';
    constexpr char KEY_J1_RIGHT = 'd';
    constexpr char KEY_J1_DIAG_UP_LEFT = 'z';
    constexpr char KEY_J1_DIAG_UP_RIGHT = 'e';
    constexpr char KEY_J1_DIAG_DOWN_RIGHT = 'c';
    constexpr char KEY_J1_DIAG_DOWN_LEFT = 'w';
    constexpr char KEY_J1_SHOOT = ' ';

    //J2
    constexpr char KEY_J2_LEFT = 'f';
    constexpr char KEY_J2_UP = 't';
    constexpr char KEY_J2_DOWN = 'g';
    constexpr char KEY_J2_RIGHT = 'h';
    constexpr char KEY_J2_DIAG_UP_LEFT = 'r';
    constexpr char KEY_J2_DIAG_UP_RIGHT = 'y';
    constexpr char KEY_J2_DIAG_DOWN_RIGHT = 'n';
    constexpr char KEY_J2_DIAG_DOWN_LEFT = 'v';
    constexpr char KEY_J2_SHOOT = 'm';
}

#endif // CONSTANTE_HPP
