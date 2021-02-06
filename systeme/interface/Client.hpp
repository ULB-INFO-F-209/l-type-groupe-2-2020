#ifndef PA2_CLIENT_HPP
#define PA2_CLIENT_HPP

#include <ostream>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#define READ 0
#define WRITE 1

class Client{
    // MapObject positionsBoard;
    int _currentGameID=-1;
    bool _inGame=0;
    int *_com; //metrre le pipe nommée
public:
    //constructor
    Client(int *obj);

    //getters/setter
    void sendInput(int currentGameID, int playerID, char input);
    // void display(MapObject);
    void startGame();
    void delFriend(char pseudo);
    void createGame();
    //void signIn(); dans le serveur pas dans client
   // void signUp();
    void setSettings();
    void checkLeaderboard();

    void sendFriendRequest(char pseudo);

    //destructor
    ~Client() = default;

};

#endif //PA2_CLIENT_HPP
