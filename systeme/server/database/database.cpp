#include "database.hpp"

void Database::add(Account* account){
    _data.push_back(*account);
    _size++;
}

//getters
std::string Database::player_info(std::string pseudo){} //maybe utiliser dsp

ptrdiff_t Database::find(char pseudo[20]){
	ptrdiff_t idx = 0;
	ptrdiff_t size = _data.size();
	bool continuer = true;
	while(idx < size && continuer){ 
		continuer = !(strcmp(pseudo, _data[idx]._pseudo) == 0);
        if (continuer){idx++;}
	}
 	return !continuer ? idx : -1;
}

bool Database::verify_login(char pseudo[20], char pswd[20]){
    std::ptrdiff_t idx = find(pseudo);
    bool res = false;
    if (idx == -1){
        std::cout << "this account does not exist" << std::endl;
    } else{
        res = strcmp(pseudo, _data[idx]._pseudo) == 0 && strcmp(pswd, _data[idx]._pswd) == 0;
        if (!res){ std::cout << "incorrect password" << std::endl; }
    }
    return res;
}

bool Database::is_friend(std::string pseudo){}

//setter
bool Database::create_account(unsigned id, char pseudo[20], char pswd[20]){
    std::ptrdiff_t exists = find(pseudo);
    if (exists == -1){
        Account account(id, pseudo, pswd);
        add(&account);
    } else{
        std::cout << "pseudo " << pseudo << " already exists in database" << std::endl;
    }
}

bool Database::update_score(int score, std::string pseudo){}

//other
void Database::dbLoad(){
    FILE* f;
    const char* c_path = _path.c_str();
    // File existence
    struct stat buffer;
    if (!(stat (c_path, &buffer) == 0)){
    	f = fopen(c_path, "wb");
    	if (f == nullptr){
            throw "Could not create file!";
        }
        fclose(f);
    } 

    f = fopen(c_path, "rb");
    if (f == nullptr){
        throw "Could not open file!";
    }

    std::cout << "------------Load------------\n\n";
    Account account;
    while(fread(&account,sizeof(Account),1,f)){
        add(&account);
    }
    display(); 
    fclose(f);
}

void Database::display(){
    if(_data.size()==0){
        std::cout << "pas delement \n";
        return;
    }
    for (int i = 0; i < _data.size(); i++){
        std::cout <<"element : i = "<<i<<std::endl<< _data[i] << std::endl;
    }
}

void Database::dbSave(){
    // writing all accounts in _path file
    std::cout << "------------Save------------\n\n";
    FILE* out = fopen(_path.c_str(),"wb");
    for (Account &e : _data){
        fwrite(&e,sizeof(Account),1,out);
    }
    display();
    fclose(out);
    std::cout << "\nSAVE RUNNING\n";
}

//destructor
Database::~Database(){
    _data.clear();
}