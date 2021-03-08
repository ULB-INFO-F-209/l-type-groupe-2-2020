#ifndef SERVER_HPP
#define SERVER_HPP

#include "database/database.hpp" 
#include "Constante.hpp"
#include "game_test/settingServer.hpp"
#include "game_test/CurrentGame.hpp"

// C++
#include <thread>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <stdexcept>
#include <mutex>
#include <csignal>
#include <cstdio>

// C
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>



class Server{

private:
    static bool _is_active; 
    std::vector<std::string> _pipe_running;    
    static  Database _db;
    static std::mutex mtx;


public:
    Server();
    ~Server(){_db.dbSave();};
    static void close_me(int sig){mtx.lock(); _db.dbSave(); mtx.unlock(); }// handle CTRL + C signal ==> save db
    bool static isServerActive() {return _is_active;}
    static void error_pip(int sig){std::cerr << "\n***  [ERROR PIPE]  ***\n";}
private:
	//connections
    void initConnexions();
    void createPipe(const char*);
    //inputs
    void handleIncommingMessages();
    void catchInput(char *); // devrait se nommer handeInput(input)
    void sendPositionBoard();
    //queries
    bool signIn(char* );
    bool signUp(char* );
    bool addFriend(char* );
    bool delFriend(char* );
    void checkleaderboard(char* );
	void friendList(char* );	
	void getFriendRequest(char* );
    bool delFriendRequest(char*);
    int sendFriendRequest(char* );
    void viewProfile(char* );
    void resClient(std::string* processId, char* res);
    void resClient(std::string* processId, int res);
    void resClient(std::string*, bool);
    void client_exit(char *input);
    static void launch_db_save();
    void launch_game(Game_settings* sett_game);
    void get_game_settings(char* input, Game_settings* game_sett);
    void resClient(char* pipe, settingArray *res);
    void resClient(char* pipe, settingArray2* res);
    void resClient(char* pipe, std::string* res);
    int read_game_input(char * pipe);
    void remove_pipe(std::string);
    void save_score(char* pseudo1, int score);
    void kill_process(const char* pipe);
};



#endif //Server

