/*
    semaine 1 : 
        géré comunication client-serveur sans raccorder la game
    semaine 2:
        raccorder la game et le menu 
        relax : il y a une autre semaine en plus si no time
    Note: 
        15/02 : tous les communications ont été gérées sauf
                l'affichage du jeux et la manière d'énvoyer 
                les inputs du jeu au serveur!

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

#include "Constante.hpp"

class Client{
    //state
    char _pseudo[Constante::SIZE_PSEUDO]{};
    int _currentGameID=-1;
    bool _inGame=0;
    pid_t _pid;
    //pipes
    char _pipe_to_server[Constante::SIZE_pipe];
    char _pipe_from_server[Constante::SIZE_pipe ]; //celui avec pid

    //files descriptors
    int _fd_send_query;
    int _fd_get_query;

public:
    //constructor
    explicit Client();

    //Communication
    bool signIn(char *pseudo, char *pswd);
    bool signUp(char *pseudo, char *pswd);
    bool addFriend(char *pseudo);
    int delFriend(char *pseudo);
    int sendFriendRequest(char *pseudo);
    void getFriendRequest(char *res);
    bool delFriendRequest(char *pseudo); //!!new!!
    void getFriendList(char *res);
    void checkLeaderboard(char * res);
    void get_profile(char *res);
    void log_out();

    //Game
    bool checkID(char *pseudo, char*pswd);
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
