#include "account.hpp"

Account::Account(char* pseudo, char* pswd): _bestScore(0){
    strcpy(_pseudo, pseudo);
    strcpy(_pswd, pswd);
    for (size_t i = 0; i < _max_friend_nb; i++) {
        std::fill(std::begin(*_friends), std::end(*_friends), '\0');
    }
    for (size_t i = 0; i < _max_request_nb; i++) {
        std::fill(std::begin(*_friend_requests), std::end(*_friend_requests), '\0');
    }
}

std::ptrdiff_t Account::findFriend(char pseudo[20]){
    std::ptrdiff_t idx = 0;
    bool continuer = true;
    while(idx < _max_friend_nb && continuer){
        continuer = !(strcmp(pseudo, _friends[idx]) == 0);
        if (continuer){idx++;}
    }
    return !continuer ? idx : -1;
}

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
    int res;
    std::ptrdiff_t idxFriend = findFriend(pseudo);
    if (idxFriend == -1){
        std::ptrdiff_t idxRequest = findRequest(pseudo);
        if (idxRequest == -1) {
            strcpy(_friend_requests[_curr_request_nb], pseudo);
            _curr_request_nb++;
            res = 0;
        } else {
            std::cout << pseudo << " is already in friend requests of " << _pseudo << std::endl;
            res = 1;
        }
    }else{
        std::cout << pseudo << " is already friends with " << _pseudo << std::endl;
        res = 2;
    }
    return res;
}

void Account::removeRequest(char pseudo[20]){
    std::ptrdiff_t idx = findRequest(pseudo);
    if (idx != -1) {
        _curr_request_nb--;
        for (std::ptrdiff_t i = idx; i < _max_request_nb; i++) {
            if (i == _max_request_nb-1){
                strcpy(_friend_requests[i], "\0");
            } else{
                strcpy(_friend_requests[i], _friend_requests[i+1]);
            }
        }
    }else{
        std::cout << pseudo << " was not friends with " << _pseudo << std::endl;
    }
}

void Account::addFriend(char pseudo[20]){
    std::ptrdiff_t idx = findFriend(pseudo);
    if (idx == -1) {
        strcpy(_friends[_curr_friend_nb], pseudo);
        _curr_friend_nb++;
    }else{
        std::cout << pseudo << " is already friends with " << _pseudo << std::endl;
    }
}

void Account::removeFriend(char pseudo[20]){
    std::ptrdiff_t idx = findFriend(pseudo);
    if (idx != -1) {
        _curr_friend_nb--;
        for (std::ptrdiff_t i = idx; i < _max_friend_nb; i++) {
            if (i == _max_friend_nb-1){
                strcpy(_friends[i], "\0");
            } else{
                strcpy(_friends[i], _friends[i+1]);
            }
        }
    }else{
        std::cout << pseudo << " was not friends with " << _pseudo << std::endl;
    }
}

std::ostream& operator<<(std::ostream& out, const Account& obj){
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
    in >> obj._bestScore; in >> obj._pseudo; in >> obj._pswd;
    for (size_t i = 0; i < obj._max_friend_nb; i++) {
        in >> obj._friends[i];
    }
    for (size_t i = 0; i < obj._max_request_nb; i++) {
        in >> obj._friend_requests[i];
    }
    return in;
}