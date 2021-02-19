#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include "parsing.hpp"

using namespace Parsing;


class Interface final
{
	int _yMax, _xMax; //taille terminal
	WINDOW *_menuWin;
public:
	//constructor
	Interface();

	//communication with screen
	int print_menu(size_t size, std::string *choices);
	bool get_connexion(char *pseudo, char *pswd, char *error);
	void print_profile(std::vector<Profile*> vect); //n oublie pas le titre
	void print_profile(Profile *prof);
	int print_invitation(Profile *pseudo);
	int get_pseudo(char *res, char *error); //for sendrequest|add|del
	void print_alert(char *alert); //signaux

	//destructor
	~Interface();
	
};




#endif // INTERFACE_HPP