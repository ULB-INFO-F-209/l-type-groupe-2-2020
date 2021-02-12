#include "database.hpp"

void Database::add(Account* account){
    _data.push_back(*account);
    _size++;
}

//getters
std::ptrdiff_t Database::find(char pseudo[20]){
    std::ptrdiff_t idx = 0;
	bool continuer = true;
	while(idx < _data.size() && continuer){
		continuer = !(strcmp(pseudo, _data[idx]._pseudo) == 0);
        if (continuer){idx++;}
	}
 	return !continuer ? idx : -1;
}

bool Database::verifyLogin(char pseudo[20], char pswd[20]){
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

/*
bool Database::areFriends(char pseudo1[20], char pseudo2[20]){
    std::ptrdiff_t idx1 = find(pseudo1);
    std::ptrdiff_t idx2 = find(pseudo2);
    bool res = false;
    if (idx1 != -1 && idx2 != -1){
        std::ptrdiff_t idx_pseudo2 = _data[idx1].findFriend(pseudo2);
        std::ptrdiff_t idx_pseudo1 = _data[idx2].findFriend(pseudo1);
        if (idx_pseudo2 != -1 && idx_pseudo1 != -1){
            res = true;
        }
        if (idx_pseudo2 == -1){std::cout << pseudo1 << " is not friends with " << pseudo2 << std::endl;}
        if (idx_pseudo1 == -1){std::cout << pseudo2 << " is not friends with " << pseudo1 << std::endl;}
    }
    if (idx1 == -1){std::cout << pseudo1 << " does not exist" << std::endl;}
    if (idx2 == -1){std::cout << pseudo2 << " does not exist" << std::endl;}
    return res;

}
 */

//setter
bool Database::createAccount(char pseudo[20], char pswd[20]){
    std::ptrdiff_t exists = find(pseudo);
    bool res = false;
    if (exists == -1){
        Account account(pseudo, pswd);
        add(&account);
        res = true;
    } else{
        std::cout << "pseudo " << pseudo << " already exists in database" << std::endl;
    }
    return res;
}

bool Database::updateScore(int score, char pseudo[20]){
    std::ptrdiff_t idx = find(pseudo);
    bool res = false;
    if (idx == -1){
        std::cout << "this account does not exist" << std::endl;
    } else{
        if(_data[idx]._bestScore < score){_data[idx]._bestScore = score;}
        res = true;
    }
    return res;
}

bool Database::addFriend(char pseudo1[20], char pseudo2[20]){       // n'envoie pas encore de demande d'amis
    std::ptrdiff_t idx1 = find(pseudo1);                            // mais ajoute directement
    std::ptrdiff_t idx2 = find(pseudo2);
    bool res = false;
    if (idx1 != -1 && idx2 != -1){
        _data[idx1].addFriend(pseudo2);
        _data[idx2].addFriend(pseudo1);
        res = true;
    }
    if (idx1 == -1){std::cout << pseudo1 << " does not exist" << std::endl;}
    if (idx2 == -1){std::cout << pseudo2 << " does not exist" << std::endl;}
    return res;
}

bool Database::removeFriend(char pseudo1[20], char pseudo2[20]){
    std::ptrdiff_t idx1 = find(pseudo1);
    std::ptrdiff_t idx2 = find(pseudo2);
    bool res = false;
    if (idx1 != -1 && idx2 != -1){
        _data[idx1].addFriend(pseudo2);
        _data[idx2].addFriend(pseudo1);
        res = true;
    }
    if (idx1 == -1){std::cout << pseudo1 << " does not exist" << std::endl;}
    if (idx2 == -1){std::cout << pseudo2 << " does not exist" << std::endl;}
    return res;
}

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

void Database::dbSave(){
    // writing all accounts in _path file
    std::cout << "\n------------Save------------\n\n";
    FILE* out = fopen(_path.c_str(),"wb");
    for (Account &e : _data){
        fwrite(&e,sizeof(Account),1,out);
    }
    display();
    fclose(out);
    std::cout << "\nSAVE RUNNING\n";
}

void Database::display(){
    if(_data.size()==0){
        std::cout << "pas d'element \n";
        return;
    }
    for (int i = 0; i < _data.size(); i++){
        std::cout <<"element : i = "<<i<<std::endl<< _data[i] << std::endl;
    }
}

//destructor
Database::~Database(){
    _data.clear();
}