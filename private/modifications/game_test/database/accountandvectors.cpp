#include "accountandvectors.hpp"

// retourne l'indice de pseudo dans la liste d'amis si il est ami, -1 sinon
int AccountAndVectors::findFriend(char pseudo[20]){
    int index = 0;
    bool found = false;
    while (index < _friends_vector.size() && !found){
        found = (strcmp(pseudo, _friends_vector.at(index).c_str()) == 0);
        if (!found){index++;}
    }
    return found ? index : -1;
}

// retourne l'indice de pseudo dans la liste des requetes si elle existe, -1 sinon
int AccountAndVectors::findRequest(char pseudo[20]){
    int index = 0;
    bool found = false;
    while (index < _requests_vector.size() && !found){
        std::cout << "pseudo=" << pseudo << " pseudo_req=" << _requests_vector.at(index) << std::endl;
        found = (strcmp(pseudo, _requests_vector.at(index).c_str()) == 0);
        if (!found){index++;}
    }
    std::cout << "found=" << found << std::endl;
    return found ? index : -1;
}

int AccountAndVectors::addRequest(char pseudo[20]){
	// ajout de la requete si pseudo n'est pas deja ami ou n'a pas deja envoyé une demande d'amis
    int res = 3;
    int idxFriend = findFriend(pseudo);
    if (idxFriend == -1){
        int idxRequest = findRequest(pseudo);
        if (idxRequest == -1) {
            _requests_vector.push_back(pseudo);
            res = 0;
        } else          	// pseudo is already in friend requests of _pseudo
            res = 1;
    } else	                // pseudo is already friends with _pseudo
        res = 2;

    return res;
}

// suppression de la requete de pseudo si elle existe
void AccountAndVectors::removeRequest(char pseudo[20]){
    std::ptrdiff_t idx = findRequest(pseudo);
    if (idx != -1)
        _requests_vector.erase(_requests_vector.begin()+idx);
}

// ajout de pseudo dans la liste d'amis s'il n'y est pas deja
void AccountAndVectors::addFriend(char pseudo[20]){
    _friends_vector.push_back(pseudo);
}

// suppression de l'ami pseudo s'il existe
void AccountAndVectors::removeFriend(char pseudo[20]){
    std::ptrdiff_t idx = findFriend(pseudo);
    if (idx != -1)
        _friends_vector.erase(_friends_vector.begin()+idx);
}