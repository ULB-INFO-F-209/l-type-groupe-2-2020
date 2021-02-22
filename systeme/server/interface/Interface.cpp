#include "Interface.hpp"

/*********NOTES*****************************
	- Proportionaliser tous les dimensions
	- Lancer un thread d'ecoute en cas de 
		changement de la taille du terminale
	-Arranger le code et les fênetre
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

	std::string msg1= "Your pseudo and password must be at least 7 characters long";
	std::string msg2 = "and maximum 15. Only letters, numbers and the";
	std::string msg3= "underscore character are allowed.";
	std::string msg[] = {msg1,msg2,msg3};
	init_connexion();
	print_message(_menuWin, 3,msg, WIN_X, (WIN_Y*2)-1);
	if(error)
		print_error(_menuWin, error,WIN_X+4, (WIN_Y*4)+1);
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
			case 10: //enter
				if(nbp < 6 and nbm < 6){
					char e[] = "Your pseudo and password are too short!";
					print_error(_menuWin, e,WIN_X+4, (WIN_Y*4)+1);
				}
				else if(nbm < 6){
					char e[] = "Your password is too short!";
					print_error(_menuWin, e,WIN_X+4, (WIN_Y*4)+1);
				}
				else if(nbp < 6){
					char e[] = "Your pseudo is too short!";
					print_error(_menuWin, e,WIN_X+4, (WIN_Y*4)+1);
				}
				else{
					choice = 0;
				}
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
	return not res;
}

void Interface::print_error(WINDOW *win, char *error , int x, int y){
	start_color();
	init_pair(2, COLOR_RED, COLOR_BLACK);
	wattron(win, COLOR_PAIR(2));
	print_cara(win, error,x,y);
	wattroff(win, COLOR_PAIR(2));
	wrefresh(win);
}

void Interface::print_message(WINDOW *win, size_t size, std::string *tab, int x, int y){
	for(size_t i=0; i < size; i++){
		print_cara(_menuWin, tab[i].c_str(),x,y);
		y++;
	}
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

void Interface::print_cara(WINDOW *win , const char *c, int x, int y){
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

void Interface::print_profile(Profile *prof){
	keypad(stdscr,TRUE);
    box(_menuWin,0,0);
    box(_msgWin,0,0);
	refresh();
	wrefresh(_menuWin);
	wrefresh(_msgWin);
	char title[] = "    YOUR PROFILE   ";
	char proverbe[] = "BE PROUD OF YOUR SCORE!";
	print_cara(_msgWin, title, (WIN_X*3)-7, WIN_Y /2); 
	print_cara(_msgWin, proverbe, (WIN_X*3)-8, (WIN_Y /2)+2); 
	char name[30];
	char score[30];
	sprintf(name,  "Pseudo : %s", prof->pseudo);
	sprintf(score, "Score : %d", prof->score);
	print_cara(_menuWin,name, WIN_X+4, WIN_Y*4);
	print_cara(_menuWin,score, WIN_X+4, (WIN_Y*4)+3);
}

void Interface::print_profile(std::vector<Profile*> vect){
	keypad(stdscr,TRUE);
	int choice = 1;
	int MIN = 0,  MAX = vect.size() -1;
	int focus = 0; int nb_elem = 12; //on peut afficher que 12 
	int idx_min = 0, idx_max;
	if(MAX < 12){idx_max = MAX;}
	else{idx_max = idx_min + nb_elem;}
	while(choice){
		print_friends(_menuWin, vect, focus, idx_min, idx_max);
		choice = getch();
		switch(choice){
			case KEY_UP:
				if(focus > MIN){
					if(focus == idx_min){
						idx_min --;
						idx_max--;
					}
					focus--;
				}
				break;
			case KEY_DOWN:
				if(focus < MAX){
					if(focus == idx_max-1){
						idx_min++;
						idx_max++;
					}
					focus++;
				}
				break;
			case KEY_RIGHT: //retour?
				break;
			default:
				break;
		}
	}


}

void Interface::print_friends(WINDOW *win, std::vector<Profile*> vect, int highlight, int min, int max){
	wclear(win);
    box(win,0,0);
    box(_msgWin,0,0);
	refresh();
	wrefresh(win);
	wrefresh(_msgWin);
	char title[] = "    YOUR FRIENDS  ";
	char proverbe[] = "Making new friends shouldn't mean losing old ones.";
	char regle[64];
	sprintf(regle, "But you can only have 100 friends, you have already %lu!",vect.size());
	print_cara(_msgWin, title, (WIN_X*3)-7, WIN_Y /2); 
	print_cara(_msgWin, proverbe, (WIN_X*2)-15, (WIN_Y /2)+1);
	print_cara(_msgWin, regle, (WIN_X*2)-15, (WIN_Y /2)+2);
	int x = (WIN_X*2)-15, y = (WIN_Y /2)+7;
	char score[10]; char pseudo[30];
	char titre_pseudo[20] = "Pseudo", titre_score[] = "Score";
	print_cara(_menuWin, titre_pseudo, (WIN_X*2)-15,(WIN_Y /2)+5);
	print_cara(_menuWin, titre_score, ((WIN_X*2)-15)*6,(WIN_Y /2)+5);
	for (int i = min; i < max; ++i){
		sprintf(score, "%d",vect[i]->score);
		sprintf(pseudo, "%s", vect[i]->pseudo);
		int x_prime = x*6;
		if(i == highlight)
		{
			wattron(win, A_REVERSE);
			print_cara(win,pseudo,x,y);
			print_cara(win, score,x_prime,y);
			wattroff(win, A_REVERSE);
		}
		else{
			print_cara(win, pseudo,x,y);
			print_cara(win, score,x_prime,y);
		}
		y++;
	}
}

int Interface::get_pseudo(char *res, char *error){
	int ret=0;
	box(_menuWin,0,0);
    box(_msgWin,0,0);
	box(_pseudoWin,0,0);

	refresh();
	wrefresh(_menuWin);
	wrefresh(_msgWin);
	wrefresh(_pseudoWin);
	char id[] = "PSEUDO :";
	print_cara(_pseudoWin, id, 5, WIN_Y /2);
	char title[] = "    ADD FRIEND ";
	char proverbe[] = "Making new friends shouldn't mean losing old ones.";
	char regle[64];
	sprintf(regle, "But you can only have 100 friends, you have already");
	print_cara(_msgWin, title, (WIN_X*3)-7, WIN_Y /2); 
	print_cara(_msgWin, proverbe, (WIN_X*2)-15, (WIN_Y /2)+1);
	print_cara(_msgWin, regle, (WIN_X*2)-15, (WIN_Y /2)+2);

	int py = (WIN_Y /2), px = 15, choice=1, nbp=0;
	char cara;

	if(error)
		print_error(_menuWin, error,WIN_X+4, (WIN_Y*4)+1);
	move_cursor(_pseudoWin, px, py);

	while(choice){
		choice = getch();
		switch(choice){
			case 10: //enter
				if(nbp < 6){
					char e[] = "Pseudo is too short!";
					print_error(_menuWin, e,WIN_X+4, (WIN_Y*4)+1);
				}
				else{
					choice = 0;
				}
				break;
			case KEY_LEFT: //retour | 
				choice = 0; 
				ret = 1; 
				break;
			case KEY_BACKSPACE:
				if(nbp > 0){
					move_cursor(_pseudoWin, px, py, true);
					move_cursor(_pseudoWin, --px, py);
					nbp--;
					res[nbp] = '\0'; //fin de ligne
				}
				break;
			default:
				cara = static_cast<char>(choice);
				if(nbp < 15 and verify_cara(&cara)){
					print_cara(_pseudoWin, &cara, px, py);
					move_cursor(_pseudoWin, ++px, py);
					res[nbp] = cara;
					nbp ++;
				}
				break;
		}
	}
	return ret;
}

Interface::~Interface(){
		getch();
		endwin();
}

