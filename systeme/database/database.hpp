#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <ostream>

class Database{
	struct User{
		uint id;
		char name[90];
		char pseudo[90];
		char pswd[90];
	};
	User *_db;
	unsigned int _size;
	void _dsp (std::ostream&) const; //bd
	void _dsp2 (std::ostream&) const; //user

public:
	//constructors
	Database();
	Database(const char *path);
	//getters
	std::string player_info(std::string pseudo); //maybe utiliser dsp
	bool find(std::string pseudo);
	bool verify_login(std::string pseudo, std::string pswd);
	bool is_friend(std::string pseudo);

	//setter
	bool create_account(std::string name, std::string pseudo, std::string pswd);
	bool update_score(int score, std::string pseudo);

	//other
	void save();
	void load();

	//extern
	friend inline std::ostream& operator<< (std::ostream&, const Database&);
	friend inline std::ostream& operator<< (std::ostream&, const User&);
	//destructors
	~Database();

	
};

#endif