#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <iostream>
#include <ostream>
#include <cstring>
#include <vector>

class Account{
    char _pseudo[20];
    char _pswd[20];
    int _bestScore;
    std::vector<std::string> _friends{};
    friend class Database;

public:
    Account() = default;
    Account(char* pseudo, char* pswd): _bestScore(0){
        strcpy(_pseudo, pseudo);
        strcpy(_pswd, pswd);
    }
    void addFriend(std::string pseudo){ _friends.push_back(pseudo); }
    ~Account() = default;

    void printFriends(std::ostream& out){
        out << "[ ";
        for (int i = 0; i < _friends.size(); i++) {
            out << _friends.at(i) << ' ';
        }
        out << "]";
    }

    friend std::ostream& operator<< (std::ostream& out, const Account& obj){
        out << obj._bestScore << "\n" << obj._pseudo << "\n" << obj._pswd << "\n" << obj.printFriends(out) << std::endl;
        return out;
    }

    friend std::istream& operator>> (std::istream& in, Account& obj){
        in >> obj._bestScore; in >> obj._pseudo; in >> obj._pswd;
        return in;
    }
};

#endif // ACCOUNT_HPP