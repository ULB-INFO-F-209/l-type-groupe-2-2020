#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include "account.hpp"

struct Profile
{
	char* pseudo;
	int score;
};

class Database{
    const std::string _path = "accounts.bin";
    std::vector<Account> _data{};
	unsigned _size = 0;
	std::vector<Profile> _profiles{};

    void add(Account* account);

public:
	// Constructor
	Database() = default;

	// Getters
	std::ptrdiff_t find(char pseudo[20]);
	bool verifyLogin(char pseudo[20], char pswd[20]);
	Profile getProfile(char pseudo[20]);
    std::vector<char*> getFriendRequest(char pseudo[20]);
    std::vector<char*> getFriendList(char pseudo[20]);
	std::vector<Profile> checkLeaderboard();
    //bool areFriends(char pseudo1[20], char pseudo2[20]);

	// Utilities
	bool createAccount(char pseudo[20], char pswd[20]);
	bool updateScore(int score, char pseudo[20]);
	int friendRequest(char pseudoSrc[20], char pseudoDest[20]);
	bool addFriend(char pseudo1[20], char pseudo2[20]);
    bool removeFriend(char pseudo1[20], char pseudo2[20]);

    // File management
    void dbLoad();
    void dbSave();
	void display();

	// Extern
	friend inline std::ostream& operator<< (std::ostream&, const Database&);

	// Destructor
	~Database();
};

#endif