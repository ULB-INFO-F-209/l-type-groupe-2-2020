#include "Interface.hpp"


Interface::Interface(){
	initscr(); 
    noecho(); //affiche pas les inputs sur le stdout
    curs_set(0);
    getmaxyx(stdscr,_yMax,_xMax);
    WIN_HEIGHT = _yMax-(_yMax/4);
    WIN_WIDTH = _xMax-(_xMax/5);
    WIN_Y = _yMax/7;
    WIN_X = _xMax/8;
    _menuWin = newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X); //hauteur;longueur;y;x
    _pseudoWin = newwin(WIN_HEIGHT/5, (WIN_WIDTH/2)+5, WIN_Y+3, WIN_X+5);
    _mdpWin = newwin(WIN_HEIGHT/5, (WIN_WIDTH/2)+5, WIN_Y+10, WIN_X+5);

}

int Interface::print_menu(size_t size, std::string *choices){
		int res = 0, choice=1;
		keypad(_menuWin,TRUE); //active clavier
		box(_menuWin,0,0);
		wrefresh(_menuWin);
		while(choice){
			update_menu(size,choices,res);
			choice = wgetch(_menuWin);
			switch(choice){
				case KEY_UP:
					if(res > 0){res--;} //tu peux monter plus haut que le ciel
					break;
				case KEY_DOWN:
					if(static_cast<size_t>(res) < size-1){res++;} //tu peux pas descendre plus bas que terre
					break;
				case KEY_RIGHT:
					choice = 0; //quit menu
					break;
				default: //any other
					break;
			}
		}
		wrefresh(_menuWin);
		return res;
}


void Interface::update_menu(size_t size,  std::string *choices, int highlight){
	int x = WIN_WIDTH/4, y= WIN_HEIGHT/(size);
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	wattron(_menuWin, COLOR_PAIR(1));
	for(size_t i = 0; i < size; ++i){
		if(i  == static_cast<size_t>(highlight)){
			wattron(_menuWin, A_BLINK);
			wattron(_menuWin, A_REVERSE);
			mvwprintw(_menuWin, y, x, choices[i].c_str());
			wattroff(_menuWin, A_REVERSE);
			wattroff(_menuWin, A_BLINK);
		}
		else{mvwprintw(_menuWin, y, x, choices[i].c_str());}
		y+=3;
	}
	wattroff(_menuWin, COLOR_PAIR(1));
}

bool Interface::get_connexion(char *pseudo, char *pswd, char *error){
	bool res = false; int cara=1, focus=0;
    keypad(stdscr,TRUE); //all windows not only pseudo or mdp
	box(_pseudoWin,0,0);
	box(_mdpWin,0,0);
	refresh();
	wrefresh(_pseudoWin);
	wrefresh(_mdpWin);

	while(cara){
		cara = getch();
		switch(cara){
			case KEY_UP:
				if(focus > 0){focus--;}
				break;
			case KEY_DOWN:
				if(focus < 1){focus++;}
				break;
			case KEY_RIGHT: //enter 
				break;
			case KEY_LEFT: //retour
				break;
			default:
    			echo(); //affiche pas les inputs sur le stdout
    			keypad(stdscr,FALSE); //all windows not only pseudo or mdp
				if(focus){
					keypad(_pseudoWin,TRUE); 
					wgetstr(_pseudoWin, pseudo);
					keypad(_pseudoWin,FALSE); 
				}
				else{
    				keypad(_mdpWin,TRUE);
					wgetstr(_mdpWin, pswd);
    				keypad(_mdpWin,FALSE);
				}
    			noecho(); //affiche pas les inputs sur le stdout
    			keypad(stdscr,FALSE); //all windows not only pseudo or mdp
				break;
    			//keypad(stdscr,FALSE); //all windows not only pseudo or mdp
		}
	}


	return res;
}

bool Interface::verify_cara(char *c){
	bool isNum  = (strcmp(c,"0")>=0) and (strcmp(c,"9") <=0);
	bool isMaj = (strcmp(c,"A")>=0) and (strcmp(c,"Z") <=0);
	bool isMin = (strcmp(c,"a")>=0) and (strcmp(c,"z") <=0);
	bool isSpecial = (strcmp(c,"_")==0);

	return isNum || isMaj || isMin || isSpecial;
}


Interface::~Interface(){
		getch();
		endwin();
	}

