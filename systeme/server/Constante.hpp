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

    const char PIPE_DE_CONNEXION[] = {"connexion"};
    constexpr char ACTION_MENU_PRINCIPAL[] = {"Mabcdefg"};
    constexpr char REPONSE_AMI = 'R';
    const char PAS_SECOND_JOUEUR[] = {"Null"};
    constexpr char ACTION_JEU[] = {"J"/* ajouter les touches possibles*/};
    constexpr char DELIMITEUR = '_';
    const char BASE_PIPE_FILE[] = {"pipefile_"};
    const char PIPE_PATH[] = {"database/interface/"};
    
}



#endif // CONSTANTE_HPP