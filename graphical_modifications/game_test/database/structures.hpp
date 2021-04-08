#ifndef STRUCT
#define STRUCT

#include "account.hpp"

struct Profile{
	char pseudo[20];
	int score;
	Profile()=default;
	Profile(const char *p, int s){sprintf(pseudo,"%s", p); score=s;}
	Profile(Account acc){acc.getPseudo(pseudo); score = acc.getScore();}
};

struct DatabaseLevel{
   std::string level;
   std::string name;
   int vote;
};

#endif