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
	Interface(){
		initscr(); 
        noecho(); //affiche pas les inputs sur le stdout
        curs_set(0);
        keypad(stdscr,TRUE);
        getmaxyx(stdscr,_yMax,_xMax);
        _menuWin = newwin(_yMax/2, _xMax/2, _yMax/4, _xMax/4); //hauteur;longueur;y;x
	}

	int print_menu(size_t size, std::string *choices){
		int res = 0;
		box(_menuWin,0,0); int x = 25, y=3;
		for (size_t i = 0; i < size; ++i)
		{
			mvwprintw(_menuWin, y,x, choices[i].c_str());
			y+=3;
		}

		wgetch(_menuWin);
		refresh();
		return res;
	}

	bool get_connexion(char *pseudo, char *pswd, char *error);
	void print_profile(std::vector<Profile*> vect); //n oublie pas le titre
	void print_profile(Profile *prof);
	int print_invitation(Profile *pseudo);
	int get_pseudo(char *res, char *error); //for sendrequest/add/del
	void print_alert(char *alert); //signaux
	

	~Interface(){
		getch();
		endwin();
	}
	
};




#endif // INTERFACE_HPP