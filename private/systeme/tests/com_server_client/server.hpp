#ifndef SERVER_HPP
#define SERVER_HPP

#include "database/database.hpp" 
#include "Constante.hpp"

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
    std::vector<const char *> _pipe_running;    
    static  Database _db;
    static std::mutex mtx;


public:
    Server();
    ~Server(){_db.dbSave();};
    static void close_me(int sig){mtx.lock(); _db.dbSave(); mtx.unlock(); }// handle CTRL + C signal ==> save db

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
    bool logOut(char* );
    void resClient(std::string* processId, char* res);
    void resClient(std::string* processId, int res);
    void resClient(std::string*, bool);
    void client_exit(char *input);
    static void launch_db_save();
    bool static isServerActive() {return _is_active;}
    void launch_game();
    void get_game_settings(char *);
    

};



#endif //Server

