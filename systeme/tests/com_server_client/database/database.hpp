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
	char pseudo[20];
	int score;
	Profile()=default;
	Profile(char *p, int s){sprintf(pseudo,"%s", p); score=s;}
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
	std::ptrdiff_t find(char* pseudo);
	bool verifyLogin(char* pseudo, char* pswd);
	Profile getProfile(char* pseudo);
    std::vector<std::string> getFriendRequest(char* pseudo);
	bool delFriendRequest(char *pseudo1, char *pseudo2);
    std::vector<std::string> getFriendList(char* pseudo);
	std::vector<Profile> checkLeaderboard();
    //bool areFriends(char *pseudo1, char *pseudo2);

	// Utilities
	bool createAccount(char* pseudo, char* pswd);
	bool updateScore(int score, char* pseudo);
	int friendRequest(char* pseudoSrc, char* pseudoDest);
	bool addFriend(char *pseudo1, char *pseudo2);
    bool removeFriend(char *pseudo1, char *pseudo2);

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
