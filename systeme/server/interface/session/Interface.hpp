#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include "parsing.hpp"



class Interface final
{
	int _yMax, _xMax; //taille terminal
	WINDOW *_menuWin;
public:
	Interface(){
		initscr(); 
        noecho(); //affiche pas les inputs sur le stdout
        keypad(stdscr,TRUE);
        getmaxyx(stdscr,_yMax,_xMax);
        _menuWin = newwin(4,2,1,1);
	}

	int print_menu(size_t size, std::string *choices){
		int res=0 ;
		box(_menuWin,10,10); //par defaut autour de win
		
		int highlight = 0;
		while(1){
			for (int i = 0; i < size; ++i)
			{
				if(i==highlight){
					wattron(_menuWin, A_REVERSE);
				}
				mvwprintw(_menuWin, i+1, 1, choices[i].c_str());
				wattroff(_menuWin, A_REVERSE);
			}
			res = wgetch(_menuWin);

			switch(res){
				case KEY_UP:
					highlight --;
					break;
				case KEY_DOWN:
					highlight++;
					break; 
				default:
					break;
			}
			if(res==10){break;}
		}

		refresh();
		wrefresh(_menuWin);
		keypad(_menuWin,true);


		return res;
	}

	bool get_connexion(char *pseudo, char *pswd, char *error);
	void print_friends(std::vector<char*> vect);
	void print_leaderboard(std::vector<Profile*> vect);
	void print_profile(Profile *prof);
	int print_invitation(char *pseudo);
	int get_pseudo(char *res, char *error); //recupere le pseudo de l amis a supp ou à ajouter
	void print_alert(char *alert);
	

	~Interface(){
		getch();
		endwin();
	}
	
};




#endif // INTERFACE_HPP