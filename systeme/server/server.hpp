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
	//connections
    void initConnexions();
    void createPipe(const char*);
    void resClient(std::string*, bool);
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
	bool friendList(char* );	
	bool getFriendRequest(char* );
    bool sendFriendRequest(char* );
    bool viewProfile(char* );
    bool logOut(char* );
    
    bool static isServerActive() {return _is_active;}
    

};



#endif //Server

