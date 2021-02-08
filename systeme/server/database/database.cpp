#include "database.hpp"

//constructor
Database::Database(){}

//getters
std::string Database::player_info(std::string pseudo){} //maybe utiliser dsp
bool Database::find(std::string pseudo){}
bool Database::verify_login(std::string pseudo, std::string pswd){}
bool Database::is_friend(std::string pseudo){}

//setter
bool Database::create_account(unsigned id, char pseudo[90], char pswd[90]){
    Account account(id, pseudo, pswd);
    add(account);
}

bool Database::update_score(int score, std::string pseudo){}

//other
void Database::dbLoad(){
    struct stat db_stat;
    FILE* f;
    if (stat(_path, &db_stat) != 0){            // check if file _path exists
        f = fopen(_path, "w");           // creating it if not
        if (f == nullptr){
            throw "Could not create file!";
        }
        fclose(f);
    }
    f = fopen(_path, "r");
    if (f == nullptr){
        throw "Could not open file!";
    }
    long unsigned nb_account = (db_stat.st_size)/sizeof(Account);
    for (size_t i = 0; i < nb_account; i++){
        Account account;
        if (fread(&account, sizeof(Account), 1, f) == 0){
            throw "Could not read the account!";
        }
        add(account);
    }
    fclose(f);
}

void Database::dbSave(){
    FILE* f = fopen(_path, "w");
    if (f == nullptr){
        throw "Could not create file!";
    }
    // writing all accounts in _path file
    fwrite(&_data, sizeof(Account), _size, f);
    fclose(f);
}

void Database::add(Account account){
    _data.push_back(account);
    _size++;
}

//destructor
Database::~Database(){}