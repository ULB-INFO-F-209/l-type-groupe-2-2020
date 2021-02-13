#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <iostream>
#include <ostream>
#include <cstring>
#include <vector>

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
    friend class Database;

public:
    // Constructors
    Account() = default;
    Account(char* pseudo, char* pswd);

    // Getter
    std::ptrdiff_t findFriend(char pseudo[20]);
    std::ptrdiff_t findRequest(char pseudo[20]);

    // Utilities
    int addRequest(char pseudo[20]);
    void removeFriend(char pseudo[20]);
    void addFriend(char pseudo[20]);

    // Destructor
    ~Account() = default;

    // Extern
    friend std::ostream& operator<< (std::ostream& out, const Account& obj);
    friend std::istream& operator>> (std::istream& in, Account& obj);
};

#endif // ACCOUNT_HPP