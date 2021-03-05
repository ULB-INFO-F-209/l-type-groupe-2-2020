/*
    semaine 1 : 
        géré comunication client-serveur sans raccorder la game
    semaine 2:
        raccorder le menu - interface-client-serveur
        relax : il y a une autre semaine en plus si no time
        (c'était ecrit il y a une semaine ...plus de relax)
    Note: 
        15/02 : toutes les communications ont été gérées sauf
                l'affichage du jeux et la manière d'énvoyer 
                les inputs du jeu au serveur!
        26/02 : Lien serveur-client établit 

        1/02: tester la récupération des settings pour la game et envoyer au serveur

*/

#ifndef PA2_CLIENT_HPP
#define PA2_CLIENT_HPP

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <signal.h>
#include <cstring>
#include <fstream>
#include <thread>

#include "Constante.hpp"
#include "game_test/settingServer.hpp"
#include "game_test/Interface_game.hpp"
#include "game_test/MapHandler.hpp"

class Client{
    //state
    char _pseudo[Constante::SIZE_PSEUDO]{};
    int _currentGameID=-1;
    bool _inGame=0;
    pid_t _pid;
    
    //pipes
    char _pipe_to_server[Constante::SIZE_pipe];
    char _pipe_from_server[Constante::SIZE_pipe ]; //celui avec pid
    char _pipe_input_game[Constante::SIZE_pipe];
    char _pipe_game_sett[Constante::SIZE_pipe];

    //files descriptors
    int _fd_send_query;
    int _fd_get_query;
    settingArray2 game_sett;

    

public:
    //constructor
    explicit Client();
    //Communication
    bool signIn(char *pseudo, char *pswd, bool true_conn=true);
    bool signUp(char *pseudo, char *pswd);
    bool addFriend(char *pseudo);
    int delFriend(char *pseudo);
    int sendFriendRequest(char *pseudo);
    void getFriendRequest(char *res);
    void delFriendRequest(char *pseudo); //!!new!!
    void getFriendList(char *res);
    void checkLeaderboard(char * res);
    void get_profile(char *res);
    void exit();
    void read_pipe(){

        std::cout << _pipe_game_sett << std::endl;
        //int fd = open(_pipe_game_sett,O_RDONLY);

        while(true){
            std::cout << "BEfore sleep\n";
            sleep(10);
            std::cout << "AfTer sleep\n";
            
            settingArray2 obj3;
            FILE* file;
            file = fopen("game_.bin","rb");
            if (file!=nullptr){
                fread(&obj3,sizeof(settingArray2),1,file);
                std::cout << "je bloque 3 "<<std::endl;

                std::cout << obj3.getListPlayer()[0].getnLives() << std::endl;
            }
            std::cout << "je bloque "<<std::endl;
            
            fclose(file);
            break;
        }
        //delete game_sett;
        std::cout << "je suis la apres 2 ans "<<std::endl;

    }

    //Game
    
    int createGame(char * game_info);
    
    //state
    inline bool is_playing(){return _inGame;}
    inline void get_pseudo(char *res){strcpy(res, _pseudo);}

    //destructor
    ~Client();

private:
    void communication(char *buffer);


};

#endif //PA2_CLIENT_HPP
