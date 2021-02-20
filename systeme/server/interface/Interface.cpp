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
    _pseudoWin = newwin(WIN_HEIGHT/5, (WIN_WIDTH/2)+10, WIN_Y*4, (WIN_X*2)+3);
    _mdpWin = newwin(WIN_HEIGHT/5, (WIN_WIDTH/2)+10, WIN_Y*6, (WIN_X*2)+3);
    _msgWin = newwin(WIN_HEIGHT/4, (WIN_WIDTH), WIN_Y, WIN_X);

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
    keypad(stdscr,TRUE); //all windows not only pseudo or mdp
    box(_menuWin,0,0);
    box(_msgWin,0,0);
	box(_pseudoWin,0,0);
	box(_mdpWin,0,0);
	refresh();
	wrefresh(_menuWin);
	wrefresh(_msgWin);
	wrefresh(_pseudoWin);
	wrefresh(_mdpWin);

	//legends
	char title[] = "SIGN IN";
	char id[] = "PSEUDO :";
	char mdp[] = "PASSWORD :";

	wattron(_msgWin, A_BOLD);
	mvwprintw(_msgWin, WIN_Y /2, (WIN_X*3), title);
	wattroff(_msgWin, A_BOLD);
	wrefresh(_msgWin);

	wattron(_pseudoWin, A_BOLD);
	mvwprintw(_pseudoWin, WIN_Y /2, 5, id);
	wattroff(_pseudoWin, A_BOLD);
	wrefresh(_pseudoWin);

	wattron(_mdpWin, A_BOLD);
	mvwprintw(_mdpWin, WIN_Y /2, 5, mdp);
	wattroff(_mdpWin, A_BOLD);
	wrefresh(_mdpWin);

	bool res = false; char cara; int choice = 1,  focus=0;
	int py = (WIN_Y /2), px = 15, my=(WIN_Y /2), mx=15;
	int nbp = 0, nbm=0;
	while(choice){
		choice = getch();
		switch(choice){
			case KEY_UP:
				if(focus > 0){focus--;}
				break;
			case KEY_DOWN:
				if(focus < 1){focus++;}
				break;
			case KEY_RIGHT: //enter 
				break;
			case KEY_LEFT: //retour |  
				break;
			default:
				cara = static_cast<char>(choice);
				echo();
				if(focus and nbp < 15 and verify_cara(&cara)){
					wattron(_pseudoWin, A_BOLD);
					mvwprintw(_pseudoWin, py, px++, &cara);
					wrefresh(_pseudoWin);
					wattroff(_pseudoWin, A_BOLD);
				}
				else if(not focus and nbm < 15 and verify_cara(&cara)){
					wattron(_mdpWin, A_BOLD);
    				//mvwprintw(_mdpWin, my, mx++, &cara);
					wrefresh(_mdpWin);
					wattroff(_mdpWin, A_BOLD);
				}
				noecho();
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

