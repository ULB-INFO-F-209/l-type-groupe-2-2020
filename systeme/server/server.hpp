#ifndef SERVER_HPP
#define SERVER_HPP

#include <thread>
#include <vector>
//#include "database/Database.hpp" //gardons les dossiers
//#include "database/interface/Client.hpp" //pour la clarté
//#include "database/interface/Menu.hpp" //aprés on changera

#include <cstring>
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdexcept>

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>



class Server{

private:
    static bool _is_active;
    std::vector<const char *> _pipe_running = {};
    //Database _db; 
public:

    Server();

    
    ~Server()=default;

private:

    void initConnexions();
    void createPipe(const char*);
    void resClient(std::string*, bool);

    void catchInput(); // devrait se nommer handeInput(input)
    void sendPositionBoard();
    bool signIn(char* );
    bool signUp(char* );
    bool addFriend(char* );
    bool delFriend(char* );
    void checkleaderboard(char* );
    bool static isServerActive() {return _is_active;}
    

};



#endif //Server

