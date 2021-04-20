#ifndef CONSTANTE_HPP
#define CONSTANTE_HPP

#include <cstddef>
#include <string>

/**
 * 
 * Constante lier au serveur et au client 
 * (rajouter vos constante si besoin)
 * 
 **/
namespace Constante{

    const size_t CHAR_SIZE = 2500;                      /** Tailles d'un message à lire sur les pipes, grand car possibilité de faire passer le classement  **/

    //pipe
    const char PIPE_DE_CONNEXION[] = {"connexion"};     /** recoit les 1er connexions des clients **/
    const char PIPE_DE_REPONSE[]   = {"getrequest"};    /** recois les requests de tous les clients **/
    const char BASE_PIPE_FILE[]    = {"pipefile_"};     /** envois les reponses des requests au clients concerner **/
    const char BASE_INPUT_PIPE[]   = {"input_pipe_"};   /** recois les inputs du jeu pout 1 clients  **/
    const char BASE_GAME_PIPE[]    = {"game_pipe_"};    /** envoies les objets a cree pour le jeu au client  **/
    const char PIPE_PATH[]         = {"/tmp/"};
    const int  PIPE_MODE            = 0666;             /** Mode de créations des PIPE **/

    //gestion des messages
    constexpr char ACTION_MENU_PRINCIPAL = 'M';
    constexpr char GAME_SETTINGS = 'P';
    constexpr char REPONSE_AMI = 'R';
    const char NO_PARTENER[] = {"Null"};
    constexpr char DELIMITEUR = '&';

    //client
    const size_t SIZE_PSEUDO = 20;
    const size_t SIZE_pipe = 64;

    //server
    const unsigned SERVER_SAVE_TIME = 9000;
    const bool GAME_CAN_BE_LAUNCH = true;
<<<<<<< HEAD:modif2/Constante.hpp
    const int ERROR_PIPE_GAME = -100;
    const int CLIENT_END_GAME = -101;
    const int CLIENT_LEAVE_GAME = -1000;
    const std::string GAME_END = "END GAME";
=======
>>>>>>> systeme:modifications/game_test/JEU++/Constante.hpp

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
