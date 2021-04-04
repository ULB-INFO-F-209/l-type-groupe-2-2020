#include "account.hpp"

Account::Account(char* pseudo, char* pswd): _bestScore(0){
	// remplissage des champs pseudo et pswd + nettoyer les champs amis et demandes d'amis
    strcpy(_pseudo, pseudo);
    strcpy(_pswd, pswd);
}

void Account::setScore(int score){    
    if(_bestScore < score)
        _bestScore = score; 
}  

std::ostream& operator<<(std::ostream& out, const Account& obj){
	// outputting pseudo, pswd and bestScore,
    out << obj._pseudo << ", " << obj._pswd << ", " << obj._bestScore;
    return out;
}

std::istream& operator>>(std::istream& in, Account& obj){
	// inputting bestScore, pseudo et pswd
    in >> obj._pseudo; in >> obj._pswd; in >> obj._bestScore;
    return in;
}