#ifndef SERVER_HPP
#define SERVER_HPP

#include <thread>
#include <vector>
#include "database/Database.hpp" //gardons les dossiers
#include "database/interface/Client.hpp" //pour la clarté
#include "database/interface/Menu.hpp" //aprés on changera


class Server{

private:
    static bool _is_active = false;
    std::vector<const char *> _pipe_running = {};
    Database _db; 
public:

    Server();

    void catchInput(char* input); // devrait se nommer handeInput(input)
    void sendPositionBoard();
    bool signIn(char* input);
    bool signUp(char* input);
    bool addFriend(char* input);
    bool delFriend(char* input);
    void checkleaderboard(char* input);
    bool static isServerActive() {return _is_active;}
    ~Server()=default;

private:

    void initConnexions();
    void createPipe(const char*);
    template<typename T>;
    void resClient(char*, T);
    

};
template<typename T>;
void resClient(char* processId, T res) {
	char* message(res);
	int fd;
	fd = open("pipefile_processId",O_WRONLY);
    if (fd != -1){
        write(fd,message,strlen(message)+1);
    }
    else{
        printf("pas de connexion\n");
    }
    close(fd);
}

#endif //Server

