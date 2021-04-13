#ifndef ACC_VEC
#define ACC_VEC
#include <iostream>
#include <ostream>
#include <cstring>
#include <vector>
#include "structures.hpp"

class AccountAndVectors{
    Account acc;
    std::vector<std::string> _friends_vector{};
    std::vector<std::string> _requests_vector{};
    std::vector<DatabaseLevel> _levels_vector{};
    friend class Database;

public:
    AccountAndVectors() = default;
    AccountAndVectors(Account account): acc(account){};
    
    // Getters
    int findFriend(char pseudo[20]);
    int findRequest(char pseudo[20]);
    int findLevel(std::string level);

    // Utilities
    int addRequest(char pseudo[20]);
    void removeRequest(char pseudo[20]);
    void addFriend(char pseudo[20]);
    void removeFriend(char pseudo[20]);
    void incVote(std::string levelName);
    DatabaseLevel getLevel(std::string levelName);

    // Destructor
    ~AccountAndVectors(){ 
        _friends_vector.clear();
        _requests_vector.clear();
        _levels_vector.clear();
    };
};
#endif