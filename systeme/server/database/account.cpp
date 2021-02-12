#include "account.hpp"

Account::Account(char* pseudo, char* pswd): _bestScore(0){
    strcpy(_pseudo, pseudo);
    strcpy(_pswd, pswd);
    for (size_t i = 0; i < _max_friend_nb; i++) {
        std::fill(std::begin(*_friends), std::end(*_friends), '\0');
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

void Account::addFriend(char pseudo[20]){
    strcpy(_friends[_curr_friend_nb], pseudo);
    _curr_friend_nb++;
}

std::ostream& operator<<(std::ostream& out, const Account& obj){
    out << obj._bestScore << "\n" << obj._pseudo << "\n" << obj._pswd << "\n";
    out << "[ ";
    for (size_t i = 0; i < obj._max_friend_nb; i++) {
        out << obj._friends[i] << ' ';
    }
    out << "]" << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Account& obj){
    in >> obj._bestScore; in >> obj._pseudo; in >> obj._pswd;
    for (size_t i = 0; i < obj._max_friend_nb; i++) {
        in >> obj._friends[i];
    }
    return in;
}