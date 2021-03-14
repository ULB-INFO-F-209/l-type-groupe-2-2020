#include "database.hpp"

void Database::add(Account* account){
    _data.push_back(*account);
    _size++;
}

//getters
std::ptrdiff_t Database::find(char* pseudo){
    std::ptrdiff_t idx = 0;
	bool continuer = true;
	while(idx < _data.size() && continuer){
		continuer = !(strcmp(pseudo, _data[idx]._pseudo) == 0);
        if (continuer){idx++;}
	}
 	return !continuer ? idx : -1;       // -1 if not found, idx in db if found
}

bool Database::verifyLogin(char* pseudo, char* pswd){
    std::ptrdiff_t idx = find(pseudo);
    bool res = false;
    if (idx == -1){
        std::cout << pseudo << " does not exist" << std::endl;
    } else{
        res = strcmp(pseudo, _data[idx]._pseudo) == 0 && strcmp(pswd, _data[idx]._pswd) == 0;
        if (!res){ std::cout << "incorrect password" << std::endl; }
    }
    return res;
}

Profile Database::getProfile(char* pseudo){
    std::ptrdiff_t idx = find(pseudo);
    Profile res;
    if (idx == -1){
        std::cout << pseudo << " does not exist" << std::endl;
    } else{
        Profile ret_val {_data[idx]};
        res = ret_val;
    }
    return res;
}

std::vector<Profile> Database::getFriendRequest(char* pseudo){
    std::vector<Profile> requests;
    std::ptrdiff_t idx = find(pseudo);
    if (idx == -1){
        std::cout << pseudo << " does not exist" << std::endl;
    } else{
        for (char* req : _data[idx]._friend_requests){
            if(req[0] != '\0'){
                idx = find(req);
                Profile prof{_data[idx]};
                requests.push_back(prof);
            }
        }
    }
    return requests;
}

std::vector<Profile> Database::getFriendList(char* pseudo){
    std::vector<Profile> friends;
    std::ptrdiff_t idx = find(pseudo);
    if (idx == -1){
        std::cout << pseudo << " does not exist" << std::endl;
    } else{ 
        for (auto frnd : _data[idx]._friends){
            if (frnd[0] != '\0'){
                idx = find(frnd);
                Profile f{_data[idx]};
                friends.push_back(f);
            }
        }
    }
    return friends;
}

std::vector<Profile> Database::checkLeaderboard(){
    _profiles.clear();
    for (Account &acc : _data){
        _profiles.push_back(Profile{acc._pseudo, acc._bestScore});
    }
    std::sort(_profiles.begin(), _profiles.end(), [](Profile a, Profile b) {
        return a.score > b.score;
    });
    for (auto x : _profiles)
        std::cout << x.pseudo << " -> " << x.score << std::endl;
    std::cout << "-----------------" << std::endl;
    return _profiles;
}

//setter
bool Database::createAccount(char* pseudo, char* pswd){
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

bool Database::updateScore(int score, char* pseudo){
    std::ptrdiff_t idx = find(pseudo);
    bool res = false;
    if (idx == -1){
        std::cout << pseudo << " does not exist" << std::endl;
    } else{
        if(_data[idx]._bestScore < score){_data[idx]._bestScore = score;}
        res = true;
    }
    return res;
}

int Database::friendRequest(char* pseudoSrc, char* pseudoDest){
    int res;
    std::ptrdiff_t idxSrc = find(pseudoSrc);
    std::ptrdiff_t idxDest = find(pseudoDest);
    if (idxSrc != -1 && idxDest != -1 && idxSrc != idxDest){
        res = _data[idxDest].addRequest(pseudoSrc);     // res=0 if request is sent, res=1 if already requested
    }                                                   // res=2 if already friends
    if (idxSrc == -1){std::cout << pseudoSrc << " does not exist" << std::endl; res = 3;}  // res=3 if pseudo doesn't exist
    if (idxDest == -1){std::cout << pseudoDest << " does not exist" << std::endl; res = 3;}
    if (idxSrc == idxDest){std::cout << pseudoSrc << " can not add him/herself :  "<< std::endl; res = 4;}
    return res;
}

bool Database::addFriend(char* pseudo1, char* pseudo2){
    std::ptrdiff_t idx1 = find(pseudo1);
    std::ptrdiff_t idx2 = find(pseudo2);
    bool res = false;
    if (idx1 != -1 && idx2 != -1){
        _data[idx1].addFriend(pseudo2);
        _data[idx1].removeRequest(pseudo2);             // supprimer la requete de la liste
        _data[idx2].addFriend(pseudo1);
        res = true;
    }
    if (idx1 == -1){std::cout << pseudo1 << " does not exist" << std::endl;}
    if (idx2 == -1){std::cout << pseudo2 << " does not exist" << std::endl;}
    std::cout << res << std::endl;
    return res;
}

bool Database::delFriendRequest(char *pseudo1, char *pseudo2){
    // supprime dans la liste des requete de pseudo1 le pseudo numero 2
    std::ptrdiff_t idx1 = find(pseudo1);
    std::ptrdiff_t idx2 = find(pseudo2);
    bool res = false;
    if (idx1 != -1 && idx2 != -1){
        _data[idx1].removeRequest(pseudo2);
        res = true;
    }
    if (idx1 == -1){std::cout << pseudo1 << " does not exist" << std::endl;}
    if (idx2 == -1){std::cout << pseudo2 << " does not exist" << std::endl;}
    return res;
}

int Database::removeFriend(char* pseudo1, char* pseudo2){
    std::ptrdiff_t idx1 = find(pseudo1);
    std::ptrdiff_t idx2 = find(pseudo2);
    int res = 2; //already friend
    if (idx1 != -1 && idx2 != -1){
        if(_data[idx1].findFriend(pseudo2) != -1){
            _data[idx1].removeFriend(pseudo2);
            _data[idx2].removeFriend(pseudo1);
            res = 0; //bien supp
        }
        else
            res = 1;
    }
    if (idx1 == -1){std::cout << pseudo1 << " does not exist" << std::endl;}
    if (idx2 == -1){std::cout << pseudo2 << " does not exist" << std::endl;}
    if (idx1 == idx2){std::cout << pseudo1 << " can not delete him/herself" << std::endl; res = 3;}
    return res;
}

// File management
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
    std::cout << "\n------------Save------------\n";
    FILE* out = fopen(_path.c_str(),"wb");
    for (Account &acc : _data){
        fwrite(&acc,sizeof(Account),1,out);
    }
    display();
    fclose(out);
    std::cout << "\nSAVE FINNISH\n";
}

void Database::display(){
    if(_data.size()==0){
        std::cout << "pas d'element \n";
        return;
    }
    for (int i = 0; i < _data.size(); i++){
        std::cout << _data[i] << std::endl;
    }
}

//destructor
Database::~Database(){
    _data.clear();
}
