#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <cstring>

class Account{
    unsigned _id;
    char _pseudo[20];
    char _pswd[20];

public:
    Account() = default;
    Account(unsigned id, char* pseudo, char* pswd): _id(id){
        strcpy(_pseudo, pseudo);
        strcpy(_pswd, pswd);
    }
    ~Account() = default;
};

#endif // ACCOUNT_HPP