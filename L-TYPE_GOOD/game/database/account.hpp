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
    char _pseudo[20];
    char _pswd[20];
    int _bestScore;

    friend class AccountAndVectors;
    friend class Database;

public:
    // Constructors
    Account() = default;
    Account(char* pseudo, char* pswd);

    // Getters
    void getPseudo(char* buff){strcpy(buff, _pseudo);};
    int getScore(){return _bestScore;};

    // Setter
    void setScore(int score);

    // Destructor
    ~Account() = default;

    // Extern
    friend std::ostream& operator<< (std::ostream& out, const Account& obj);
    friend std::istream& operator>> (std::istream& in, Account& obj);
};

#endif // ACCOUNT_HPP