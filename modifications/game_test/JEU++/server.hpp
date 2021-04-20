#ifndef SERVER_HPP
#define SERVER_HPP


#include "game_test/database/database.hpp" 
#include "Constante.hpp"
#include "game_test/CurrentGame.hpp"
#include "game_test/parsing.hpp"
#include "DisplayGame.hpp"

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
<<<<<<< HEAD:private/modifications/server.hpp
        std::thread game_thread;
        PIDinGame()=default;
        PIDinGame(char *p):in_game(false),game_thread(){strcpy(pid,p);std::cout << "my pid : " << pid << "  In game : "<< in_game <<std::endl; };
=======
        PIDinGame()=default;
        PIDinGame(char *p):in_game(false){strcpy(pid,p);std::cout << "my pid : " << pid << "  In game : "<< in_game <<std::endl; };
>>>>>>> systeme:modifications/game_test/JEU++/server.hpp
        ~PIDinGame()=default;
    };
    static std::vector<PIDinGame*> _pipe_running;    
    static Database _db;
    static std::mutex mtx;
<<<<<<< HEAD:private/modifications/server.hpp
    static std::mutex mtx_game;
=======
>>>>>>> systeme:modifications/game_test/JEU++/server.hpp

public:
    Server();
    ~Server(){_db.dbSave();std::cout << "\n\n *   BYE BYE   *\n\n"<<std::endl;};
<<<<<<< HEAD:private/modifications/server.hpp
    static void close_me(int sig);
=======
    static void close_me(int sig){mtx.lock(); _db.dbSave(); mtx.unlock(); mtx.lock(); for(size_t i=0;i < _pipe_running.size();i++){ kill(atoi(_pipe_running.at(i)->pid),SIGINT); } std::cout <<"\n -----------------------|    FERMETURE EN COURS    |-----------------------\n\n " << std::endl;sleep(10);}// handle CTRL + C signal ==> save db
>>>>>>> systeme:modifications/game_test/JEU++/server.hpp
    bool static isServerActive() {return _is_active;}
    static void error_pip(int sig){std::cerr << "\n***  [ERROR PIPE]  ***\n";}

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
<<<<<<< HEAD:private/modifications/server.hpp
    void get_game_settings(char* input, Parsing::Game_settings* game_sett);
    void launch_game(Parsing::Game_settings* sett_game);
=======
    void get_game_settings(char* input, Game_settings* game_sett);
    void launch_game(Game_settings* sett_game);
>>>>>>> systeme:modifications/game_test/JEU++/server.hpp
    void client_exit(std::string* pid);
    void kill_process(const char* pipe);
    
    
};



#endif //Server

