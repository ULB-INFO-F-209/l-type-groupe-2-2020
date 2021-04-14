
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
    

public:
    //constructor
    explicit Client();
    //Communication
    bool signIn(const char *pseudo,const char *pswd, bool true_conn=true);
    bool signUp(const char *pseudo,const char *pswd);
    bool addFriend(char *pseudo);
    int delFriend(char *pseudo);
    int sendFriendRequest(char *pseudo);
    void getFriendRequest(char *res);
    void delFriendRequest(char *pseudo); //!!new!!
    void getFriendList(char *res);
    void checkLeaderboard(char * res);
    void get_profile(char *res);
    std::string read_game_pipe();
    void send_game_input(std::vector<int> inp);
    void exit();
    
    //Game
    int createGame(char * game_info);
    void createLevel(const char * level_info);
    std::string viewLevels();
    std::string myLevels();
    std::string getLevel(std::string level_name,std::string author);
    void playLevel(std::string level, char *game_sett);
    void voteLevel(std::string name, std::string author);


    //state
    inline bool is_playing(){return _inGame;}
    inline void get_pseudo(char *res){strcpy(res, _pseudo);}

    //destructor
    ~Client();

private:
    void communication(char *buffer);

};

#endif //PA2_CLIENT_HPP
