#ifndef SERVER_HPP
#define SERVER_HPP

#include <thread>
#include <vector>


class Server{

private:
    static bool _is_active = false;
    std::vector<const char *> _pipe_running = {};

public:

    Server();

    void catchInput(); // devrait se nommer handeInput(input)
    void sendPositionBoard();
    bool signIn();
    bool signUp();
    bool addFriend();
    bool delFriend();
    void checklearderboard();
    bool static isServerActive() {return _is_active;}

private:

    void initConnexions();
    void createPipe(const char*);


    ~Server()=default;

};

#endif //Server