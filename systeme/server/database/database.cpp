#include "database.hpp"

//getters
std::string Database::player_info(std::string pseudo){} //maybe utiliser dsp
bool Database::find(std::string pseudo){}
bool Database::verify_login(std::string pseudo, std::string pswd){}
bool Database::is_friend(std::string pseudo){}

//setter
bool Database::create_account(unsigned id, char pseudo[90], char pswd[90]){
    Account account(id, pseudo, pswd);
    add(&account);
}

bool Database::update_score(int score, std::string pseudo){}

//other
void Database::dbLoad(){
    struct stat db_stat;
    FILE* f;
    const char* c_path = _path.c_str();
    if (stat(c_path, &db_stat) != 0){            // check if file _path exists
        f = fopen(c_path, "w");           // creating it if not
        if (f == nullptr){
            throw "Could not create file!";
        }
        fclose(f);
    }
    /*
    std::ifstream in_file(_path, std::ios::binary);
    in_file.seekg(0, std::ios::end);
    int file_size = in_file.tellg();
    std::cout<<"Size of the file is"<<" "<< file_size <<" "<<"bytes"<< std::endl;
    */

    //size_t nb_student = (db_stat.st_size)/sizeof(Account);

    
   
    std::ifstream in(_path, std::ios::ate|std::ios::binary);
    size_t nb_student = in.tellg();
    nb_student = nb_student/sizeof(Account);
    std::cout<<"Size of the file is" << " "<< nb_student << std::endl;
    
    /*
    for (size_t i = 0; i < nb_student; i++){
        Account account;
        in>>account;
        add(&account);

        std::cout << "hello" << std::endl;
    }
    */
    Account account;
    while(in>>account){
        add(&account);
        std::cout << "hello" << std::endl;
    }
    in.close();
}

void Database::dbSave(){
    // writing all accounts in _path file
    //fwrite(&_data, sizeof(Account), _size, f);
    std::ofstream out(_path);
    for (const auto &e : _data) out << e << "\n";
    out.close();
}

void Database::add(Account* account){
    _data.push_back(*account);
    _size++;
}

//destructor
Database::~Database(){}