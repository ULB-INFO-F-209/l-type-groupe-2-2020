#ifndef SERVER_HPP
#define SERVER_HPP


#include "game_test/database/database.hpp" 
#include "Constante.hpp"
#include "game_test/CurrentGame.hpp"
#include "game_test/parsing.hpp"
#include "DisplayGame.hpp"
#include "DisplayGameGui.hpp"

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
        std::thread game_thread;
        PIDinGame()=default;
        PIDinGame(char *p):in_game(false),game_thread(){strcpy(pid,p);std::cout << "my pid : " << pid << "  In game : "<< in_game <<std::endl; };
        ~PIDinGame()=default;
    };
    static std::vector<PIDinGame*> _pipe_running;    
    static Database _db;
    static std::mutex mtx;
    static std::mutex mtx_game;

public:
    Server();
    ~Server(){_db.dbSave();std::cout << "\n\n *   BYE BYE   *\n\n"<<std::endl;};
    static void close_me(int sig);
    bool static isServerActive() {return _is_active;}
    static void error_pip(int sig){std::cerr << "\n***  [ERROR PIPE]  ***\n";}

private:
	//connections
    void initConnexions();
    void createPipe(const char*);
    void remove_pipe(std::string);

    //response
    void resClient(std::string* processId, char* res);
    void resClient(std::string processId, std::string res);
    void resClient(std::string* processId, int res);
    void resClient(std::string*, bool);
    void resClient(char* pipe, std::string* res);

    //inputs
    void handleIncommingMessages();
    void catchInput(char *); 
    int read_game_input(char * pipe, int* char_tab);
    void launch_custom_game(Parsing::Level* level_sett);

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
    std::string levelsRanking();
    std::string clientLevels(char*);
    std::string oneLevel(char*);
    void addVote(char *);
    void addLevel(char *);
    Parsing::Level runLevel(char*);

    //server utils
    static void launch_db_save();
    void save_score(char* pseudo1, int score);
    void get_game_settings(char* input, Parsing::Game_settings* game_sett);
    void launch_game(Parsing::Game_settings* sett_game);
    void client_exit(std::string* pid);
    void kill_process(const char* pipe);
    
    
};

#endif //Server

