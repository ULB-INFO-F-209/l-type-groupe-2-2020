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

    

public:
    //constructor
    explicit Client();
    settingArray game_sett;
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

        while(true){
			int res = read(_fd_get_query , &game_sett, sizeof(settingArray));
			if (res == -1){
                std::cout << " [ERROR] " <<_pid << "n'a pas reussit a lire"<<std::endl;
            }
            else{
                std::cout << game_sett.list_player[0].getnLives() << std::endl; 
                break;
            };
        }
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
