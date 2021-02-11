/*
    semaine 1 : 
        géré comunication client-serveur sans raccorder la game
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

#define READ 0
#define WRITE 1


/* je vais juste gerer les communication client server ici ... */
class Client{
    char _pseudo[20]{};
    // MapObject positionsBoard;
    int _currentGameID=-1;
    bool _inGame=0;

    //pipes
    char _get_query[Constante::CHAR_SIZE*2];    //serveur repond au client
    char _send_query[20];                       //client repond au serveur
    int _fd_g;                                  //file descriptor for _get_query
    int _fd_s;                                  //file descriptor for _send_query 
    pid_t _pid_server;

public:
    //constructor
    Client();

    //Communication
    bool signUp(char *pseudo, char *pswd);
    bool signIn(char *pseudo, char *pswd);
    int addFriend(char *pseudo);
    int delFriend(char *pseudo);
    void getFriendRequest(char *res);
    void checkLeaderboard(char * res);
    int createGame(char * second_player);
    void log_out();
    /*bool sendInput(int currentGameID, int playerID, char input);
    bool display(MapObject);*/
    

    //state
    inline bool is_playing(){return _inGame;}


    //destructor
    ~Client();

private:
    void communication(char *buffer);


};

#endif //PA2_CLIENT_HPP
