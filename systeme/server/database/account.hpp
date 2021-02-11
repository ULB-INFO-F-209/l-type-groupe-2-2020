#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <cstring>

class Account{
    unsigned _id;
    char _pseudo[20];
    char _pswd[20];
    friend class Database;
public:
    Account() = default;
    Account(unsigned id, char* pseudo, char* pswd): _id(id){
        strcpy(_pseudo, pseudo);
        strcpy(_pswd, pswd);
    }
    ~Account() = default;

    friend std::ostream& operator<< (std::ostream& out, const Account& obj){
        out << obj._id << "\n" << obj._pseudo<<"\n"<<obj._pswd<<std::endl;
        return out;
    }

    friend std::istream& operator>> (std::istream& in, Account& obj){
        in >> obj._id; in >> obj._pseudo; in >> obj._pswd;
        return in;
    }
};

#endif // ACCOUNT_HPP