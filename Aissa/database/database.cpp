#include "database.hpp"

void Database::add(Account account){
    AccountAndVectors acc(account);
    _data.push_back(acc);
}

void Database::add(Friend frnd){
    std::ptrdiff_t idx = find(frnd._pseudo);
    if (idx != -1){
        _data[idx]._friends_vector.push_back(frnd._friend);
    }
}

void Database::add(Request request){
    std::ptrdiff_t idx = find(request._pseudo);
    if (idx != -1)
        _data[idx]._requests_vector.push_back(request._request);
}

void Database::add(std::string pseudo, std::string level, std::string nameLevel, int vote){
    std::ptrdiff_t idx = find(pseudo.c_str());
    if (idx != -1)
        _data[idx]._levels_vector.push_back(DatabaseLevel{level, nameLevel, vote});

    else
        std::cout << "[ERROR DATABASE] PSEUDO NOT FOUND : "<< pseudo <<std::endl;
}

//getters

// retourne -1 si pseudo n'existe pas, l'indice dans _data sinon
std::ptrdiff_t Database::find(const char* pseudo){
    std::ptrdiff_t idx = 0;
	bool continuer = true;
	while(idx < _data.size() && continuer){
		continuer = !(strcmp(pseudo, _data[idx].acc._pseudo) == 0);
        if (continuer){idx++;}
	}
 	return !continuer ? idx : -1;
}

bool Database::verifyLogin(char* pseudo, char* pswd){
    std::ptrdiff_t idx = find(pseudo);
    bool res = false;
    if (idx == -1){
        std::cout << pseudo << " does not exist" << std::endl;
    } else{
        res = strcmp(pseudo, _data[idx].acc._pseudo) == 0 && strcmp(pswd, _data[idx].acc._pswd) == 0;
    }
    return res;
}

// retourne le Profile (pseudo+score) associé a pseudo
Profile Database::getProfile(char* pseudo){
    std::ptrdiff_t idx = find(pseudo);
    Profile res;
    if (idx == -1){
        std::cout << pseudo << " does not exist" << std::endl;
    } else{
        Profile ret_val{_data[idx].acc};
        res = ret_val;
    }
    return res;
}

// retourne les requetes de pseudo sous forme de vecteur de Profile 
std::vector<Profile> Database::getFriendRequest(char* pseudo){
    std::vector<Profile> requests;
    std::ptrdiff_t idx = find(pseudo);
    if (idx == -1){
        std::cout << pseudo << " does not exist" << std::endl;
    } else{
        for (auto req : _data[idx]._requests_vector){
            idx = find(req.c_str());
            Profile prof{_data[idx].acc};
            requests.push_back(prof);
        }
    }
    return requests;
}

// retourne les amis de pseudo sous forme de vecteur de Profile 
std::vector<Profile> Database::getFriendList(char* pseudo){
    std::vector<Profile> friends;
    std::ptrdiff_t idx = find(pseudo);
    if (idx == -1){
        std::cout << pseudo << " does not exist" << std::endl;
    } else{ 
        for (auto frnd : _data[idx]._friends_vector){
            if (frnd[0] != '\0'){
                idx = find(frnd.c_str());
                Profile f{_data[idx].acc};
                friends.push_back(f);
            }
        }
    }
    return friends;
}

// retourne le leaderboard sous forme de vecteur de Profile 
std::vector<Profile> Database::checkLeaderboard(){
	// on parcourt la base de données et on ajoute chaque account sous forme de Profile dans le vect
    _profiles.clear();
    for (AccountAndVectors &acc_vect : _data){
        _profiles.push_back(Profile{acc_vect.acc});
    }
    // tri du vecteur dans l'ordre decroissant des scores
    std::sort(_profiles.begin(), _profiles.end(), [](Profile a, Profile b) {
        return a.score > b.score;
    });
    // affichage
    for (auto x : _profiles)
        std::cout << x.pseudo << " -> " << x.score << std::endl;
    std::cout << "-----------------" << std::endl;
    return _profiles;
}

// retourne les levels de tous les accounts
std::vector<DatabaseLevel> Database::checkLevels(){
	// on parcourt la base de données et on ajoute level
    _levels.clear();
    for (AccountAndVectors &acc_vect : _data){
        for (auto level: acc_vect._levels_vector){
            _levels.push_back(level);
        }
    }
    // affichage
    for (auto x : _levels)
        std::cout << x.level << "-> " << x.vote << ", ";

    std::cout << "-----------------" << std::endl;
    return _levels;
}

//setter
bool Database::createAccount(char* pseudo, char* pswd){
    std::ptrdiff_t exists = find(pseudo);
    bool res = false;
    if (exists == -1){
        Account account(pseudo, pswd);
        add(account);
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
        _data[idx].acc.setScore(score);
        res = true;
    }
    return res;
}

int Database::friendRequest(char* pseudoSrc, char* pseudoDest){
    int res;
    std::ptrdiff_t idxSrc = find(pseudoSrc);
    std::ptrdiff_t idxDest = find(pseudoDest);
    if (idxSrc != -1 && idxDest != -1 && idxSrc != idxDest){
        int already_req = _data[idxSrc].findRequest(pseudoDest);
        if (already_req == -1){
            res = _data[idxDest].addRequest(pseudoSrc);     // res=0 if request is sent, res=1 if already requested
        }
        else{
            _data[idxSrc].addFriend(pseudoDest);
            _data[idxDest].addFriend(pseudoSrc);
            _data[idxSrc]._requests_vector.erase(_data[idxSrc]._requests_vector.begin()+already_req);
            res = 0;
        }
    }                                                   // res=2 if already friends
    if (idxSrc == -1){std::cout << pseudoSrc << " does not exist" << std::endl; res = 3;}  // res=3 if pseudo doesn't exist
    if (idxDest == -1){std::cout << pseudoDest << " does not exist" << std::endl; res = 3;}
    else if (idxSrc == idxDest){std::cout << pseudoSrc << " can not add him/herself :  "<< std::endl; res = 4;}
    return res;
}

bool Database::addFriend(char* pseudo1, char* pseudo2){
    std::ptrdiff_t idx1 = find(pseudo1);
    std::ptrdiff_t idx2 = find(pseudo2);
    bool res = false;
    if (idx1 != -1 && idx2 != -1){
        _data[idx1].addFriend(pseudo2);
        _data[idx2].addFriend(pseudo1);
        _data[idx1].removeRequest(pseudo2);             // supprimer la requete de la liste
        res = true;
    }
    if (idx1 == -1){std::cout << pseudo1 << " does not exist" << std::endl;}
    if (idx2 == -1){std::cout << pseudo2 << " does not exist" << std::endl;}
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
            res = 0; //bien supprimé
        }
        else
            res = 1;
    }
    if (idx1 == -1){std::cout << pseudo1 << " does not exist" << std::endl;}
    if (idx2 == -1){std::cout << pseudo2 << " does not exist" << std::endl;}
    if (idx1 == idx2){std::cout << pseudo1 << " can not delete him/herself" << std::endl; res = 3;}
    return res;
}

void incrementVote(std::string pseudo, std::string level){

}

// File management

// chargement de la base de données à partir d'un fichier .bin
void Database::dbLoad(){
    FILE* accounts;
    FILE* friends;
    FILE* requests;

    const char* c_path = _path.c_str();
    const char* c_path_frnd = _path_frnd.c_str();
    const char* c_path_req = _path_req.c_str();


    // verif existence du fichier
    struct stat buffer;
    if (!(stat (c_path, &buffer) == 0)){
    	accounts = fopen(c_path, "wb");
    	if (accounts == nullptr){
            throw "Could not create accounts file!";
        }
        fclose(accounts);
    }
    if (!(stat (c_path_frnd, &buffer) == 0)){
    	friends = fopen(c_path_frnd, "wb");
    	if (friends == nullptr){
            throw "Could not create friends file!";
        }
        fclose(friends);
    }
    if (!(stat (c_path_req, &buffer) == 0)){
    	requests = fopen(c_path_req, "wb");
    	if (requests == nullptr){
            throw "Could not create requests file!";
        }
        fclose(requests);
    } 

    accounts = fopen(c_path, "rb");
    if (accounts == nullptr){
        throw "Could not open accounts file!";
    }

    friends = fopen(c_path_frnd, "rb");
    if (friends == nullptr){
        throw "Could not open friends file!";
    }

    requests = fopen(c_path_req, "rb");
    if (requests == nullptr){
        throw "Could not open requests file!";
    }

    std::cout << "------------Load------------\n\n";
    // chargement accounts
    Account account;
    while(fread(&account,sizeof(Account),1,accounts)){
        add(account);
    }
    // chargement friends
    Friend frnd;
    while(fread(&frnd,sizeof(Friend),1,friends)){
        add(frnd);
    }
    // chargement requests
    Request req;
    while(fread(&req,sizeof(Request),1,requests)){
        add(req);
    }

    // chargement levels
    std::ifstream levels;
    levels.open(_path_level, std::ios::in | std::ios::binary);
    if(!levels){
        std::cout << "Levels empty"<<std::endl;
    }
    else{
        size_t size1, size2, size3;
        char read_size1, read_size2, read_size3;
        while (levels.read(&read_size1, sizeof(size1))){        
            std::string read_pseudo, read_level, read_name;

            size1 = read_size1;
            read_pseudo.resize(size1);
            levels.read(&read_pseudo[0], size1);

            levels.read(&read_size2, sizeof(size2));
            size2 = read_size2;
            read_level.resize(size2);
            levels.read(&read_level[0], size2);

            levels.read(&read_size3, sizeof(size3));
            size3 = read_size3;
            read_name.resize(size3);
            levels.read(&read_name[0], size3);

            int vote;
	        levels.read(reinterpret_cast<char *>(&vote), sizeof(vote));

            add(read_pseudo, read_level, read_name, vote);
        }
    }

    display(); 
    fclose(accounts);
    fclose(friends);
    fclose(requests);
    levels.close();
}

// ecriture des accounts dans le fichier _path
void Database::dbSave(){
    std::cout << "\n------------Save------------\n";
    FILE* out = fopen(_path.c_str(),"wb");
    FILE* out_frnd = fopen(_path_frnd.c_str(),"wb");
    FILE* out_req = fopen(_path_req.c_str(),"wb");
    FILE* out_lev = fopen(_path_level.c_str(),"wb");
    std::fstream levels;
    levels.open(_path_level, std::ios::out | std::ios::binary);

    for (auto account : _data){
        char* pseudo = account.acc._pseudo;
        fwrite(&account.acc ,sizeof(Account),1,out);

        for (auto friend_in_vect : account._friends_vector){
            Friend frnd(pseudo, friend_in_vect.c_str());
            fwrite(&frnd,sizeof(Friend),1,out_frnd);
        }
        for (auto req_in_vect : account._requests_vector){
            Request req(pseudo, req_in_vect.c_str());
            fwrite(&req,sizeof(Request),1,out_req);
        }

        for (auto lev : account._levels_vector)
            if (levels.is_open()){
                std::string str(pseudo);
                size_t size = str.size();
                char char_size = char(size);
                levels.write(&char_size,sizeof(size));
                levels.write(&str[0],size);

                size_t size2 = lev.level.size();
                char char_size2 = char(size2);
                levels.write(&char_size2,sizeof(size2));
                levels.write(&lev.level[0],size2);

                size_t size3=lev.name.size();
                char char_size3 = char(size3);
                levels.write(&char_size3,sizeof(size3));
                levels.write(&lev.name[0],size3);

                int vote = lev.vote;
                levels.write(reinterpret_cast<const char *>(&vote), sizeof(vote));
            }
    }
    fclose(out);
    fclose(out_frnd);
    fclose(out_req);
    fclose(out_lev);
    levels.close();
    display();
    std::cout << "\nSAVE FINNISH\n";
}

void Database::display(){
    if(_data.size()==0){
        std::cout << "pas d'element \n";
        return;
    }
    for (int i = 0; i < _data.size(); i++){
        std::cout << _data[i].acc;

        std::cout << "\nfriends : [";
        for (auto frnd: _data[i]._friends_vector){
            std::cout << (frnd) << ", ";
        }
        std::cout << "]" << std::endl;

        std::cout << "requests : [";
        for (auto req: _data[i]._requests_vector){
            std::cout << (req) << ", ";
        }
        std::cout << "]" << std::endl;
        
        std::cout << "levels : [";
        for (auto level: _data[i]._levels_vector){
            std::cout << level.level << "-> " << level.vote << "|" << level.name << ", ";
        }
        std::cout << "]" << std::endl << std::endl;
    }
}

//destructor
Database::~Database(){
    _data.clear();
}
