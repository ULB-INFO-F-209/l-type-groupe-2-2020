#ifndef STRUCT
#define STRUCT

#include "account.hpp"

struct Profile{
	char pseudo[20];
	int score;
	Profile()=default;
	Profile(const char *p, int s):score(s){sprintf(pseudo,"%s", p);}
	Profile(Account acc):score(acc.getScore()){acc.getPseudo(pseudo);}
};

struct DatabaseLevel{
	std::string pseudo;
   	std::string level;
   	std::string name;
   	int vote;
	DatabaseLevel(std::string p,std::string l, std::string n, int v):pseudo(p),level(l),name(n),vote(v){};
	DatabaseLevel():pseudo(),level(),name(),vote(){};
};

#endif