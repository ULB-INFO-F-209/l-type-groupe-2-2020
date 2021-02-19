#include "Interface.hpp"


Interface::Interface(){
	initscr(); 
    noecho(); //affiche pas les inputs sur le stdout
    curs_set(0);
    keypad(stdscr,TRUE);
    getmaxyx(stdscr,_yMax,_xMax);
    _menuWin = newwin(_yMax/2, _xMax/2, _yMax/4, _xMax/4); //hauteur;longueur;y;x
}

int Interface::print_menu(size_t size, std::string *choices){
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

Interface::~Interface(){
		getch();
		endwin();
	}

