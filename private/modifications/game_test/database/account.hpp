#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <iostream>
#include <ostream>
#include <cstring>
#include <vector>

struct Friend{
    char _pseudo[20];
    char _friend[20];
    Friend()=default;
    Friend(char* psd, const char* frnd){sprintf(_pseudo,"%s", psd); sprintf(_friend,"%s", frnd);}
};

struct Request{
    char _pseudo[20];
    char _request[20];
    Request()=default;
    Request(char* psd, const char* req){sprintf(_pseudo,"%s", psd); sprintf(_request,"%s", req);}
};

class Account{
    static const size_t _max_friend_nb = 10;
    static const size_t _max_request_nb = 5;
    size_t _curr_friend_nb = 0;
    size_t _curr_request_nb = 0;
    char _pseudo[20];
    char _pswd[20];
    int _bestScore;
    char _friends[_max_friend_nb][20]{};             // 10 amis de 20 char
    char _friend_requests[_max_request_nb][20]{};
    friend class AccountAndVectors;
    friend class Database;

public:
    // Constructors
    Account() = default;
    Account(char* pseudo, char* pswd);

    // Getter
    void getPseudo(char* buff){strcpy(buff, _pseudo);};
    int getScore(){return _bestScore;};
    std::ptrdiff_t findFriend(char pseudo[20]);
    std::ptrdiff_t findRequest(char pseudo[20]);

    // Utilities
    int addRequest(char pseudo[20]);
    void removeRequest(char pseudo[20]);
    void addFriend(char pseudo[20]);
    void removeFriend(char pseudo[20]);

    // Destructor
    ~Account() = default;

    // Extern
    friend std::ostream& operator<< (std::ostream& out, const Account& obj);
    friend std::istream& operator>> (std::istream& in, Account& obj);
};

class AccountAndVectors{
    Account acc;
    std::vector<std::string> _friends_vector{};
    std::vector<std::string> _requests_vector{};
    friend class Database;

public:
    AccountAndVectors() = default;
    AccountAndVectors(Account account): acc(account){};
    operator Account(){return acc;};
    ~AccountAndVectors(){ 
        _friends_vector.clear();
        _requests_vector.clear(); };
};

#endif // ACCOUNT_HPP