#include "account.hpp"

Account::Account(char* pseudo, char* pswd): _bestScore(0){
	// remplissage des champs pseudo et pswd + nettoyer les champs amis et demandes d'amis
    strcpy(_pseudo, pseudo);
    strcpy(_pswd, pswd);
    for (size_t i = 0; i < _max_friend_nb; i++) {
        std::fill(std::begin(*_friends), std::end(*_friends), '\0');
    }
    for (size_t i = 0; i < _max_request_nb; i++) {
        std::fill(std::begin(*_friend_requests), std::end(*_friend_requests), '\0');
    }
}

// retourne l'indice de pseudo dans la liste d'amis si il est ami, -1 sinon
std::ptrdiff_t Account::findFriend(char pseudo[20]){
    std::ptrdiff_t idx = 0;
    bool continuer = true;
    while(idx < _max_friend_nb && continuer){
        continuer = !(strcmp(pseudo, _friends[idx]) == 0);
        if (continuer){idx++;}
    }
    return !continuer ? idx : -1;
}

// retourne l'indice de pseudo dans la liste des requetes si elle existe, -1 sinon
std::ptrdiff_t Account::findRequest(char pseudo[20]){
    std::ptrdiff_t idx = 0;
    bool continuer = true;
    while(idx < _max_request_nb && continuer){
        continuer = !(strcmp(pseudo, _friend_requests[idx]) == 0);
        if (continuer){idx++;}
    }
    return !continuer ? idx : -1;
}

int Account::addRequest(char pseudo[20]){
	// ajout de la requete si pseudo n'est pas deja ami ou n'a pas deja envoyé une demande d'amis
    int res;
    std::ptrdiff_t idxFriend = findFriend(pseudo);
    if (idxFriend == -1){
        std::ptrdiff_t idxRequest = findRequest(pseudo);
        if (idxRequest == -1) {
            strcpy(_friend_requests[_curr_request_nb], pseudo);
            _curr_request_nb++;
            res = 0;
        } else {	// pseudo is already in friend requests of _pseudo
            res = 1;
        }
    }else{	//pseudo is already friends with _pseudo
        res = 2;
    }
    return res;
}

// rearrangement de la liste de requetes et suppression de la requete de pseudo si elle existe
void Account::removeRequest(char pseudo[20]){
    std::ptrdiff_t idx = findRequest(pseudo);
    if (idx != -1) {
        _curr_request_nb--;
        // rearrangement
        for (std::ptrdiff_t i = idx; i < _max_request_nb; i++) {
            if (i == _max_request_nb-1){
                strcpy(_friend_requests[i], "\0");
            } else{
                strcpy(_friend_requests[i], _friend_requests[i+1]);
            }
        }
    }
}

// ajout de pseudo dans la liste d'amis si il n'y est pas deja
void Account::addFriend(char pseudo[20]){
    std::ptrdiff_t idx = findFriend(pseudo);
    if (idx == -1) {
        strcpy(_friends[_curr_friend_nb], pseudo);
        _curr_friend_nb++;
    }
}

// rearrangement de la liste d'amis et suppression de l'ami pseudo si il existe
void Account::removeFriend(char pseudo[20]){
    std::ptrdiff_t idx = findFriend(pseudo);
    if (idx != -1) {
        _curr_friend_nb--;
        // rearrangement
        for (std::ptrdiff_t i = idx; i < _max_friend_nb; i++) {
            if (i == _max_friend_nb-1){
                strcpy(_friends[i], "\0");
            } else{
                strcpy(_friends[i], _friends[i+1]);
            }
        }
    }
}

std::ostream& operator<<(std::ostream& out, const Account& obj){
	// outputting bestScore, pseudo et pswd
    out << obj._bestScore << ", " << obj._pseudo << ", " << obj._pswd << ", ";
    // outputting _friends
    out << "[ ";
    for (size_t i = 0; i < obj._max_friend_nb; i++) {
        out << obj._friends[i] << ' ';
    }
    out << "]" << " , ";
    // outputting _friend_requests
    out << "[ ";
    for (size_t i = 0; i < obj._max_request_nb; i++) {
        out << obj._friend_requests[i] << ' ';
    }
    out << "]" << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Account& obj){
	// inputting bestScore, pseudo et pswd
    in >> obj._bestScore; in >> obj._pseudo; in >> obj._pswd;
    // inputting _friends
    for (size_t i = 0; i < obj._max_friend_nb; i++) {
        in >> obj._friends[i];
    }
    // inputting _friend_requests
    for (size_t i = 0; i < obj._max_request_nb; i++) {
        in >> obj._friend_requests[i];
    }
    return in;
}