#ifndef PA2_CLIENT_HPP
#define PA2_CLIENT_HPP

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#define READ 0
#define WRITE 1

/* je vais juste gerer les communication client server ici ... */
class Client{
    // MapObject positionsBoard;
    int _currentGameID=-1;
    bool _inGame=0;

    //Menu
    std::string connexion = "Connexion"; //pipe première connection au server
    std::string pipe{};  //comm server - client connecté
    std::string _pseudo{};
    int _fd[2]{}; //file descriptor

public:
    //constructor
    Client(){
        //donnez le pid du process au server via connexion
    }

    //getters/setter
    bool sendInput(int currentGameID, int playerID, char input);
    // bool display(MapObject);
    bool delFriend(char pseudo);
    bool createGame();
    bool signIn(char *pseudo, char *pswd);
    bool signUp(char *pseudo, char *pswd);
    void checkLeaderboard(char * res);
    bool sendFriendRequest(char *pseudo);

    //state
    bool is_playing(){return _inGame;}


    //destructor
    ~Client(){ }

};

#endif //PA2_CLIENT_HPP
