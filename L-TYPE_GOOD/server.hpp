#ifndef SERVER_HPP
#define SERVER_HPP


#include "game/database/database.hpp" 
#include "Constante.hpp"
#include "game/CurrentGame.hpp"
#include "game/parsing.hpp"
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
        PIDinGame()=default;
        PIDinGame(char *p):in_game(false){strcpy(pid,p);};
        ~PIDinGame()=default;
    };
    static std::vector<PIDinGame*> _pipe_running;    
    static Database _db;
    static std::mutex mtx;
    static std::mutex mtx_game;

public:
    Server();
    ~Server(){_db.dbSave();std::cout << "\n\n *   BYE BYE   *\n\n"<<std::endl;};
    static void closeMe(int sig);
    bool static isServerActive() {return _is_active;}
    static void inline errorPipe(int sig){std::cerr << "\n***  [ERROR PIPE] "<< sig << " ***\n";}

private:
	//connections
    void initConnexions();
    void createPipe(const char*);
    void removePipe(std::string);

    //response
    void resClient(std::string* processId, char* res);
    void resClient(std::string processId, std::string res);
    void resClient(std::string* processId, int res);
    void resClient(std::string*, bool);
    void resClient(char* pipe, std::string* res);

    //inputs
    void handleIncommingMessages();
    void catchInput(char *); 
    int readGameInput(char * pipe, int* char_tab);
    void launchCustomGame(Parsing::Level, Parsing::Game_settings);

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
    Parsing::Level runLevel(char*, Parsing::Game_settings&);
    void launchGame(Parsing::Game_settings* sett_game);

    //server utils
    static void launchDBSave();
    void saveScore(char* pseudo1, int score);
    void clientExit(std::string* pid);
    void killProcess(const char* pipe);
};

#endif //Server

