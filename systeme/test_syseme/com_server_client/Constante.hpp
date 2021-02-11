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

    const std::size_t CHAR_SIZE = 100;

    //pipe
    const char PIPE_DE_CONNEXION[] = {"connexion"};
    const char PIPE_DE_REPONSE[] = {"reponse"};
    const char BASE_PIPE_FILE[] = {"pipefile_"};
    const char PIPE_PATH[] = "";
    const int PIPE_MODE = 0666;

    //gestion des messages
    constexpr char ACTION_MENU_PRINCIPAL[] = {"Mabcdefg"};
    constexpr char REPONSE_AMI = 'R';
    const char PAS_SECOND_JOUEUR[] = {"Null"};
    constexpr char ACTION_JEU[] = {"J"/* ajouter les touches possibles*/};
    constexpr char DELIMITEUR = '&';
    
    
    
}



#endif // CONSTANTE_HPP
