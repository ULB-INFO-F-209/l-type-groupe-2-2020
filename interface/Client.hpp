#ifndef PA2_CLIENT_HPP
#define PA2_CLIENT_HPP

class Client{
    // MapObject positionsBoard;
    int _currentGameID;
    bool _firstPlayer;
    bool _inGame;
public:
    Client() = default;

    void sendInput(int currentGameID, int playerID, char input);
    // void display(MapObject);
    void startGame();
    void delFriend(char pseudo);
    void createGame();
    void signIn();
    void signUp();
    void setSettings();
    void checkLeaderboard();
    void sendFriendRequest(char pseudo);

    ~Client() = default;

};

#endif //PA2_CLIENT_HPP
