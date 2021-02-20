#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include <ncurses.h>
#include "parsing.hpp"

using namespace Parsing;


class Interface final
{
	//Terminale state
	int _yMax, _xMax; //size
	int WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X;

	//different window
	WINDOW *_menuWin;
	WINDOW* _pseudoWin;
	WINDOW*_mdpWin;
	WINDOW*_msgWin;
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
private:
	void update_menu(size_t size,  std::string *choices, int highlight);
	bool verify_cara(char *c);
};




#endif // INTERFACE_HPP