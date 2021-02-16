#ifndef SERVER_HPP
#define SERVER_HPP

#include <thread>
#include <vector>
#include "database/database.hpp" //gardons les dossiers
//#include "database/interface/Client.hpp" //pour la clarté
//#include "database/interface/Menu.hpp" //aprés on changera

#include <cstring>
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdexcept>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <signal.h>



class Server{

private:
    static bool _is_active; 
    std::vector<const char *> _pipe_running;    
    Database _db;

public:
    Server();
    ~Server()=default;

private:

    void initConnexions();
    void createPipe(const char*);
    void resClient(std::string*, bool);
    void handleIncommingMessages();
    void catchInput(char *); // devrait se nommer handeInput(input)
    void sendPositionBoard();
    bool signIn(char* );
    bool signUp(char* );
    int sendFriendRequest(char* );
    bool addFriend(char* );
    bool delFriend(char* );
    void checkleaderboard(char* );
    bool static isServerActive() {return _is_active;}
    

};



#endif //Server

