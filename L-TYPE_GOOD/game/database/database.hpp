#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "account.hpp"
#include "accountandvectors.hpp"
#include "structures.hpp"



class Database{
    const std::string _path = "accounts.bin";
    const std::string _path_frnd = "friends.bin";
    const std::string _path_req = "requests.bin";
    const std::string _path_level = "levels.bin";

    std::vector<AccountAndVectors> _data{};
	std::vector<Profile> _profiles{};
	std::vector<DatabaseLevel> _levels{};

    void add(Account account);
	void add(Friend frnd);
	void add(Request request);

public:
	// Constructor
	Database() = default;

	// Getters
	std::ptrdiff_t find(const char* pseudo);
	bool verifyLogin(char* pseudo, char* pswd);
	Profile getProfile(char* pseudo);
    std::vector<Profile> getFriendRequest(char* pseudo);
	bool delFriendRequest(char *pseudo1, char *pseudo2);
    std::vector<Profile> getFriendList(char* pseudo);
	std::vector<Profile> checkLeaderboard();
	std::vector<DatabaseLevel> checkLevels();
	std::vector<DatabaseLevel> checkMyLevels(std::string pseudo);
	DatabaseLevel checkALevel(std::string pseudo, std::string levelName);

	// Utilities
	bool createAccount(char* pseudo, char* pswd);
	bool updateScore(int score, char* pseudo);
	int friendRequest(char* pseudoSrc, char* pseudoDest);
	bool addFriend(char *pseudo1, char *pseudo2);
    int removeFriend(char *pseudo1, char *pseudo2);
	void add(std::string pseudo, std::string level, std::string nameLevel, int vote);
	void incrementVote(std::string pseudo, std::string level);

    // File management
    void dbLoad();
    void dbSave();
	void display();

	// Extern
	friend  std::ostream& operator<< (std::ostream&, const Database&);

	// Destructor
	~Database();
};

#endif
