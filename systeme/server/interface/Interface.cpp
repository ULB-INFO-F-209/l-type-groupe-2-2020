#include "Interface.hpp"

/*********NOTES*****************************
	- Proportionaliser tous les dimensions
	- Lancer un thread d'ecoute en cas de 
		changement de la taille du terminale
*******************************************/

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

bool Interface::get_connexion(char pseudo[20], char pswd[20], char *error){
	char mask = '*'; char cara; int choice = 1,  focus=0;
	int py = (WIN_Y /2), px = 15, my=(WIN_Y /2), mx=15;
	int nbp = 0, nbm=0; 
	bool res = false; //si tu met vrai , il affiche qqchose . WHYYYY?

	init_connexion();
	move_cursor(_pseudoWin, px, py);
	while(choice){
		choice = getch();
		switch(choice){
			case KEY_UP:
				if(focus > 0){
					focus--;
					move_cursor(_mdpWin, mx, my, true);
					move_cursor(_pseudoWin, px, py);
				}
				break;
			case KEY_DOWN:
				if(focus < 1){
					focus++;
					move_cursor(_pseudoWin, px, py, true);
					move_cursor(_mdpWin, mx, my);
				}
				break;
			case KEY_ENTER: //enter
				choice = 0;
				break;
			case KEY_LEFT: //retour | 
				choice = 0;
				res = true; 
				break;
			case KEY_BACKSPACE:
				if(focus and nbm > 0){ //mdp_zone
					move_cursor(_mdpWin, mx, my, true); //rendre invsible le curseur
					move_cursor(_mdpWin, --mx, my); //reculer le cursor
					nbm--;
					pswd[nbm] = '\0';
				}
				else if(not focus and nbp > 0){
					move_cursor(_pseudoWin, px, py, true);
					move_cursor(_pseudoWin, --px, py);
					nbp--;
					pseudo[nbp] = '\0'; //fin de ligne
				}
				break;
			default:
				cara = static_cast<char>(choice);
				if(not focus and nbp < 15 and verify_cara(&cara)){
					print_cara(_pseudoWin, &cara, px, py);
					move_cursor(_pseudoWin, ++px, py);
					pseudo[nbp] = cara;
					nbp ++;
				}
				else if(focus and nbm < 15 and verify_cara(&cara)){
					print_cara(_mdpWin, &mask, mx, my);
					move_cursor(_mdpWin, ++mx, my);
					pswd[nbm] = cara;
					nbm++;
				}
				break;
		}
	}
	//verif 
	print_cara(_menuWin, pseudo, WIN_X*2, WIN_Y*2);
	print_cara(_menuWin, pswd, WIN_X*2, (WIN_Y*2)+5); //verif
	return not res;
}

void Interface::init_connexion(){
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

	print_cara(_msgWin, title, (WIN_X*3), WIN_Y /2); 
	print_cara(_pseudoWin, id, 5, WIN_Y /2);
	print_cara(_mdpWin, mdp, 5, WIN_Y /2);
}

void Interface::print_cara(WINDOW *win , char *c, int x, int y){
	wattron(win, A_BOLD);
    mvwprintw(win, y, x, c);
	wrefresh(win);
	wattroff(win, A_BOLD);
}

void Interface::move_cursor(WINDOW *win, int x, int y, bool invisible){
	char cursor = '|';
	if(invisible){
		wattron(win, A_INVIS);
		mvwprintw(win, y, x, &cursor);
		wrefresh(win);
		wattroff(win, A_INVIS);
	}
	else{
		wattron(win, A_BLINK | A_BOLD);
		mvwprintw(win, y, x, &cursor);
		wrefresh(win);
		wattroff(win, A_BLINK | A_BOLD);
	}
	
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

