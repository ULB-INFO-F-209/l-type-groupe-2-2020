#include "database.hpp"

//constructors
Database::Database(){}
Database::Database(const char *path){}

//getters
std::string Database::player_info(std::string pseudo){} //maybe utiliser dsp
bool Database::find(std::string pseudo){}
bool Database::verify_login(std::string pseudo, std::string pswd){}
bool Database::is_friend(std::string pseudo){}

//setter
bool Database::create_account(std::string name, std::string pseudo, std::string pswd){}
bool Database::update_score(int score, std::string pseudo){}

//other
void Database::save(){}
void Database::load(){}


//destructors
~Database(){}