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
    const char PIPE_DE_REPONSE[] = {"reponse"};
    const char BASE_PIPE_FILE[] = {"pipefile_"};
    const char PIPE_PATH[] = {"/tmp/"};
    const int PIPE_MODE = 0666;

    //gestion des messages
    constexpr char ACTION_MENU_PRINCIPAL[] = {"Mabcdefg"};
    constexpr char REPONSE_AMI = 'R';
    const char PAS_SECOND_JOUEUR[] = {"Null"};
    constexpr char ACTION_JEU[] = {"J"/* ajouter les touches possibles*/};
    constexpr char DELIMITEUR = '_';

    //client
    const size_t SIZE_PSEUDO  = 20;
    const size_t SIZE_pipe =64;

    
    
    
}



#endif // CONSTANTE_HPP
