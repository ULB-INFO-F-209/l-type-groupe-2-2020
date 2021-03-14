#ifndef SERVER_HPP
#define SERVER_HPP

#include "database/database.hpp" 
#include "Constante.hpp"
#include "parsing.hpp"
// #include "game_test/settingServer.hpp"
// #include "game_test/CurrentGame.hpp"

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
    struct PIDinGame{
        char pid[Constante::SIZE_pipe];
        bool in_game;
        PIDinGame()=default;
        PIDinGame(char *p):in_game(false){strcpy(pid,p);};
        ~PIDinGame()=default;
    };
    static std::vector<PIDinGame*> _pipe_running;    
    static Database _db;
    static std::mutex mtx;

public:
    Server();
    ~Server(){_db.dbSave();std::cout << "\n\n-----------------------|   HUUUUM C'EST TRES DELICIEUSE    |-----------------------\n\n"<<std::endl;};
    static void close_me(int sig){mtx.lock(); _db.dbSave(); mtx.unlock(); mtx.lock(); for(size_t i=0;i < _pipe_running.size();i++){ kill(atoi(_pipe_running.at(i)->pid),SIGUSR1); } std::cout <<"\n -----------------------|    FERMETURE EN COURS    |-----------------------\n\n " << std::endl;sleep(5);}// handle CTRL + C signal ==> save db
    bool static isServerActive() {return _is_active;}
    static void error_pip(int sig){std::cerr << "\n***  [ERROR PIPE " << sig <<"]  ***\n";}

private:
	//connections
    void initConnexions();
    void createPipe(const char*);
    void remove_pipe(std::string);

    //response
    void resClient(std::string* processId, char* res);
    void resClient(std::string* processId, int res);
    void resClient(std::string*, bool);
    void resClient(char* pipe, std::string* res);

    //inputs
    void handleIncommingMessages();
    void catchInput(char *); 
    int read_game_input(char * pipe);

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

    //server utils
    static void launch_db_save();
    void save_score(char* pseudo1, int score);
    void get_game_settings(char* input, Parsing::Game_settings* game_sett);
    void launch_game(Parsing::Game_settings* sett_game);
    void client_exit(std::string* pid);
    void kill_process(const char* pipe);
    
    
};



#endif //Server

