#ifndef SERVER_HPP
#define SERVER_HPP


Class Server{


public:

    Server();

    void catchInput(); // devrait se nommer handeInput(input)
    void sendPositionBoard();
    bool signIn();
    bool signUp();
    bool addFriend();
    bool delFriend();
    void checklearderboard();
    



    ~Server()=default;

}

#endif //Server