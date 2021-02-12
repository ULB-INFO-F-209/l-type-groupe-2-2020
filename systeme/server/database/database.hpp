#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <ostream>
#include <vector>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include "account.hpp"

class Database{
    const std::string _path = "accounts.bin";
    std::vector<Account> _data{};
	unsigned _size = 0;
	void _dsp (std::ostream&) const; //bd

    void add(Account* account);

public:
	//constructor
	Database() = default;

	//getters
	std::ptrdiff_t find(char pseudo[20]);
	bool verifyLogin(char pseudo[20], char pswd[20]);
	bool isFriend(char pseudo[20]);

	//setter
	bool createAccount(char pseudo[20], char pswd[20]);
	bool updateScore(int score, char pseudo[20]);
	bool addFriend(char pseudo1[20], char pseudo2[20]);
    bool removeFriend(char pseudo1[20], char pseudo2[20]);

    //other
    void dbLoad();
    void dbSave();
	void display();

	//extern
	friend inline std::ostream& operator<< (std::ostream&, const Database&);

	//destructors
	~Database();

	
};

#endif