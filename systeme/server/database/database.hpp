#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <ostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <filesystem>  
#include "account.hpp"

class Database{
    const std::string _path = "accounts.bin";
    std::vector<Account> _data{};
	unsigned _size = 0;
	void _dsp (std::ostream&) const; //bd

public:
	//constructor
	Database(){};
	//getters
	std::string player_info(std::string pseudo); //maybe utiliser dsp
	bool find(std::string pseudo);
	bool verify_login(std::string pseudo, std::string pswd);
	bool is_friend(std::string pseudo);

	//setter
	bool create_account(unsigned id, char pseudo[90], char pswd[90]);
	bool update_score(int score, std::string pseudo);

    //other
    void dbLoad();
    void dbSave();

	//extern
	friend inline std::ostream& operator<< (std::ostream&, const Database&);
    friend inline std::ostream& operator<< (std::ostream&, const Account&);
	//destructors
	~Database();

//private:
    void add(Account* account);

	
};

#endif