#include "database.hpp"

//getters
std::string Database::player_info(std::string pseudo){} //maybe utiliser dsp

ptrdiff_t Database::find(char pseudo[20]){
	ptrdiff_t idx = 0;
	ptrdiff_t size = _data.size();
	bool continuer = true;
	while(idx < size && continuer){ 
		continuer = !(strcmp(pseudo, _data[idx]._pseudo) == 0);
		idx++; 
	}
 	return !continuer ? idx : -1;
}

bool Database::verify_login(std::string pseudo, std::string pswd){}
bool Database::is_friend(std::string pseudo){}

//setter
bool Database::create_account(unsigned id, char pseudo[20], char pswd[20]){
    Account account(id, pseudo, pswd);
    add(&account);
}

bool Database::update_score(int score, std::string pseudo){}

//other
void Database::dbLoad(){

	struct stat buffer;   

    FILE* f;
    const char* c_path = _path.c_str();
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

void Database::add(Account* account){
    _data.push_back(*account);
    _size++;
}

//destructor
Database::~Database(){}