#include "Interface.hpp"

/*****************NOTE*************************
	- Proportionaliser tous les dimensions
	- Lancer un thread d'ecoute en cas de 
		changement de la taille du terminale
	-Arranger le code et les fênetre
	_ 24/02 : Trouver pourquoi la cosntante	
			 KEY_ENTER  n'est pas recconnu

	_24/02 : Suprress all french comment

	_24/02 : voir comment géré les invitation
				a) affcher 1 par 1
				b) tout afficher , laisser l user
					naviguer et apuyer sur enter 
				c) lui proposer d'accepter ou non, ou quitter


*******************************************/

Interface::Interface(){
	initscr(); 
    noecho(); //affiche pas les inputs sur le stdout
    keypad(stdscr, true);
    curs_set(0);
    resize_win();
}

void Interface::resize_win(){

    getmaxyx(stdscr,YMAX,XMAX);

    //size and positions
    WIN_HEIGHT = YMAX-(YMAX/4);
    WIN_WIDTH = XMAX-(XMAX/5);
    WIN_Y = YMAX/7;
    WIN_X = XMAX/8;

    //Saying
    S_HEIGHT =  WIN_HEIGHT/3;
    S_WIDTH = WIN_WIDTH;
    S_Y = WIN_Y;
    S_X = WIN_X ;

    PS_HEIGHT = WIN_HEIGHT/5;
    PS_WIDTH = (WIN_WIDTH/5)*3;

    PS_Y = WIN_Y + (WIN_HEIGHT/3) + (WIN_HEIGHT-S_HEIGHT)/6;
    PS_X = (WIN_WIDTH/2) - (PS_WIDTH/4);


    PA_HEIGHT = WIN_HEIGHT/5;
    PA_WIDTH = PS_WIDTH;
    PA_Y = PS_Y + 3*PS_HEIGHT/2;
    PA_X = PS_X;

    

    //other postions (a readapater selon la fenetre)
    _menu_x = WIN_WIDTH/4;
	_menu_y =  WIN_HEIGHT/3;

	_title_x = WIN_WIDTH/2;			//(WIN_X*3)-7;
	_title_y =  (WIN_Y /2) +1;

	_ps_caption_x=	3;  //caption of pseudo and pass win
	_ps_caption_y= (PS_HEIGHT/2)- 1;
	_pa_caption_y= _ps_caption_y;

	_saying_x =  _title_x;
	_saying_y = _title_y+1;

	_error_x = WIN_WIDTH/2;
	_error_y= PS_Y -1 + (PA_HEIGHT/2);
	_prof_x = WIN_X+4; //afficher ton profile
	_prof_p_y = WIN_Y*4;
	_prof_s_y = (WIN_Y*4)+3;
 
    _main_win = newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X); //hauteur;longueur;y;x
    _pseudo_win = newwin(PS_HEIGHT, PS_WIDTH, PS_Y, PS_X);
    _pass_win = newwin(PA_HEIGHT, PA_WIDTH, PA_Y, PA_X);
    _saying_win = newwin(S_HEIGHT, S_WIDTH, S_Y, S_X);

    wrefresh(_main_win);
    wrefresh(_pseudo_win);
    wrefresh(_pass_win);
    wrefresh(_saying_win);
}

// PUBLIC METHODES
int Interface::print_menu(size_t size, std::string *choices, int type){
	int res =0, choice = 1;
	
	keypad(stdscr,TRUE); //active clavier
	while(choice){
		update_menu(size,choices,res, type);
		choice = getch();
		switch(choice){
			case KEY_UP:
				if(res > 0){res--;} //tu peux monter plus haut que le ciel
				break;
			case KEY_DOWN:
				if(static_cast<size_t>(res) < size-1)
					res++; //tu peux pas descendre plus bas que terre
				break;
			case KEY_LEFT:
				choice = 0; //quit menu
				res = -1;
				break;
			case 10:
				choice = 0;
				break;
			default: //any other
				break;
		}
	}
	return res;
}
bool Interface::get_connexion(char pseudo[20], char pswd[20], int error, int type){
	bool res = false; //si tu met vrai , il affiche qqchose (letrre apres) . WHYYYY?
	char cara; int choice = 1,  focus=0;
	int py = _ps_caption_y, px = _ps_caption_x + PSEUDO_ZONE.size() + 1,
		my=_pa_caption_y, mx=_ps_caption_x + PSWD_ZONE.size() + 1;
	int idx_ps = 0, idx_pa=0; 

	keypad(stdscr, true);
	init_connexion(type);
	if(error != NO_ERROR)
		print_error(error);
	move_cursor(_pseudo_win, px, py);
	while(choice){
		choice = getch();
		switch(choice){
			case KEY_UP:
				if(focus > 0){
					focus--; //focus on pseudo win
					move_cursor(_pass_win, mx, my, true); //supress cursor from pswd win
					move_cursor(_pseudo_win, px, py); 
				}
				break;
			case KEY_DOWN:
				if(focus < 1){
					focus++;
					move_cursor(_pseudo_win, px, py, true);
					move_cursor(_pass_win, mx, my); //put cursor to pswd win
				}
				break;
			case 10: //enter 
				if(idx_ps + 1 < NB_MIN_CARA and idx_pa+1 < NB_MIN_CARA){
					print_error(LEN_ERROR);
				}
				else if(idx_pa + 1 < NB_MIN_CARA){
					print_error(LEN_PSWD);
				}
				else if(idx_ps +1 < NB_MIN_CARA){
					print_error(LEN_PSEUDO);
				}
				else{
					choice = 0; //stop loop
					pswd[idx_pa] = '\0';
					pseudo[idx_ps] = '\0'; //end of line to supress letters

				}
				break;
			case KEY_LEFT: //retour 
				choice = 0; 
				res = true;  //quit
				break;
			case KEY_BACKSPACE:
				if(focus and idx_pa > 0){ //pswd_zone
					move_cursor(_pass_win, mx, my, true); //rendre invsible le curseur
					move_cursor(_pass_win, --mx, my); //reculer le cursor
					idx_pa--;
					pswd[idx_pa] = '\0';
				}
				else if(not focus and idx_ps > 0){
					move_cursor(_pseudo_win, px, py, true);
					move_cursor(_pseudo_win, --px, py);
					idx_ps--;
					pseudo[idx_ps] = '\0'; //end of line to supress letters
				}
				break;
			default:
				cara = static_cast<char>(choice);
				if(not focus and idx_ps < NB_MAX_CARA and verify_cara(&cara)){
					print_cara(_pseudo_win, &cara, px, py);
					move_cursor(_pseudo_win, ++px, py);
					pseudo[idx_ps] = cara;
					idx_ps ++;
				}
				else if(focus and idx_pa < NB_MAX_CARA and verify_cara(&cara)){
					print_cara(_pass_win, &cara, mx, my);
					move_cursor(_pass_win, ++mx, my);
					pswd[idx_pa] = cara;
					idx_pa++;
				}
				break;
		}
	}
	return res;
}

int  Interface::print_profile(Profile *prof, int type){
	int res = 0;
	if(type==PROF)
		set_screen(&PROFILE, nullptr, &PROFILE_SAYING, nullptr); 
	else if (type==REQ)
		set_screen(&PROFILE2, nullptr, &PROFILE2_SAYING, nullptr); 
	char name[30];
	char score[30];
	sprintf(name,  "Pseudo : %s", prof->pseudo);
	sprintf(score, "Score : %d", prof->score);
	int x = WIN_WIDTH/4, y = WIN_HEIGHT/2;

	print_cara(_main_win,name,x , y);
	if(type==REQ)
		print_cara(_main_win,score,x, y+2);
	else
		print_cara(_main_win,score,x, 3*y/2);

	refresh();
	wrefresh(_main_win);
	if(type==REQ){
		int focus = 0; 
		int choice = 1;
		while(choice){
			set_request(focus);
			choice = getch();
			switch(choice){
				case KEY_RIGHT:
					if(focus < 2)
						focus++;
					break;
				case KEY_LEFT:
					if(focus > 0)
						focus--;
					break;
				case 10:
					res = focus;
					choice = 0;
					break;
				default:
					break;
			}
		}
	}
	else{
		getch(); //sto
	}
	return res;
}



bool Interface::print_profile(std::vector<Profile*> vect, int type, int *answer){
	keypad(stdscr,TRUE);
	bool res=false;
	int choice = 1, accepted=-1,
		MIN = 0,  MAX = vect.size() -1,
		focus = 0; int nb_elem = 10, //on peut afficher que 10
		idx_min = 0, idx_max;

	if(MAX < nb_elem)
		idx_max = MAX; //no scroll
	else
		idx_max = idx_min + nb_elem;

	while(choice){
		print_users(vect, focus, idx_min, idx_max,type);
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
			case 10:
				if(type==REQ){
					accepted = print_profile(vect[focus], REQ);
					print_users(vect, focus, idx_min, idx_max,type);

					if(accepted==1){
						answer[0] = focus;
						answer[1] = 1; //accepted friends
						choice = 0;
						res = true; //juste prevenir qu il y a une reponse
					}

					else if(accepted==-1){
						answer[0] = focus;
						answer[1] = 0; //not accepted
						choice =0; 
						res = true;
					}
				}

				break;
			case KEY_LEFT: //retour?
				choice = 0;
				break;
			default:
				break;
		}
	}
	return res;
}

int Interface::get_pseudo(char *res, int error,int type){
	int ret=0; int py = _ps_caption_y, px =  _ps_caption_x + PSEUDO_ZONE.size() +1;
	char cara; int choice=1, idx=0; //ret doit être ici sinon fonctionne pas
	if(type == ADD)
		set_screen(&ADD_FRIEND, nullptr, &ADD_SAYING, &ADD_SAYING2);
	else
		set_screen(&DEL_FRIEND, nullptr, &DEL_SAYING, &DEL_SAYING2);

	init_pseudo_win();
	keypad(stdscr, true);
	

	if(error != NO_ERROR)
		print_error(error);
	move_cursor(_pseudo_win, px, py);
	while(choice){
		choice = getch();
		switch(choice){
			case 10: //enter
				if(idx + 1 < NB_MIN_CARA)
					print_error(LEN_PSEUDO);
				else
					choice = 0;
					res[idx] = '\0'; //fin de ligne	
				break;
			case KEY_LEFT: //retour | 
				choice = 0; 
				ret = 1;  
				break;
			case KEY_BACKSPACE:
				if(idx > 0){
					move_cursor(_pseudo_win, px, py, true);
					move_cursor(_pseudo_win, --px, py);
					idx--;
					res[idx] = '\0'; //fin de ligne
				}
				break;
			default:
				cara = static_cast<char>(choice);
				if(idx < NB_MAX_CARA and verify_cara(&cara)){
					print_cara(_pseudo_win, &cara, px, py);
					move_cursor(_pseudo_win, ++px, py);
					res[idx] = cara;
					idx ++;
				}
				break;
		}
	}
	return ret;
}

//PRIVATE METHODES 
void Interface::set_screen(std::string *title,std::string *saying1, std::string *saying2, std::string *saying3){
	clear(); wclear(_main_win);
	wclear(_pseudo_win); wclear(_pass_win); wclear(_saying_win);
	resize_win(); //maybe do the resize only if terminal change
	box(_main_win,0,0);
    box(_saying_win,0,0);
    refresh();
	wrefresh(_main_win);
	wrefresh(_saying_win);
	int t_x =_title_x - (title->size() / 2);
	int s_x;
	print_cara(_saying_win, title->c_str(), t_x, _title_y);
 
	if(saying1 != nullptr){
		s_x = _saying_x - (saying1->size()/2);
		print_cara(_saying_win, saying1->c_str(),s_x, _saying_y);
	}
	if(saying2 != nullptr){
		s_x = _saying_x - (saying2->size()/2);
		print_cara(_saying_win, saying2->c_str(), s_x, _saying_y+1);
	}
	if(saying3 != nullptr){
		s_x = _saying_x - (saying3->size()/2);
		print_cara(_saying_win, saying3->c_str(), s_x, _saying_y+2);
	}
}
void Interface::init_pseudo_win(){
	wclear(_pseudo_win);
	print_cara(_pseudo_win, PSEUDO_ZONE.c_str(), _ps_caption_x, _ps_caption_y);
	box(_pseudo_win,0,0);
	refresh();
	wrefresh(_pseudo_win);
}
void Interface::init_connexion(int choice){

	switch(choice){
		case S_IN:
			set_screen(&SIGN_IN, nullptr,&SIGN_IN_SAYING,&SIGN_IN_SAYING2);
			break;
		case S_UP:
			set_screen(&SIGN_UP, nullptr,&SIGN_UP_SAYING,nullptr);
			break;
		case GAME:
			set_screen(&CHECK_USER, nullptr,&CHECK_USER_SAYING,&CHECK_USER_SAYING2);
			break;
		default:
			break;
	}
	init_pseudo_win();
	wclear(_pass_win);
	print_cara(_pass_win, PSWD_ZONE.c_str(),_ps_caption_x, _pa_caption_y);
	box(_pass_win,0,0);
	refresh();
	wrefresh(_pass_win);

}
void Interface::update_menu(size_t size,  std::string *choices, int highlight, int type){
	clear();
	if(type==HOME)
		set_screen(&HOME_TITLE, nullptr, &HOME_SAYING, nullptr);
	else if(type==MAIN)
		set_screen(&MAIN_TITLE, nullptr, &MAIN_SAYING, &MAIN_SAYING2);
	else if(type==FRIENDS)
		set_screen(&FRIENDS_TITLE, nullptr, &FRIENDS_SAYING, nullptr);

	int x = WIN_WIDTH/2, y= (WIN_HEIGHT/2) - (size+1)/2;
	start_color(); int x_courant;
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	wattron(_main_win, COLOR_PAIR(1));
	for(size_t i = 0; i < size; ++i){
		x_courant = x- (choices[i] .size()/2);
		if(i  == static_cast<size_t>(highlight)){
			wattron(_main_win, A_STANDOUT);
			print_cara(_main_win,choices[i].c_str(), x_courant, y);
			wattroff(_main_win, A_STANDOUT);
		}
		else
			print_cara(_main_win,choices[i].c_str(), x_courant, y);
		y+=3;
	}
	wattroff(_main_win, COLOR_PAIR(1));
}

void Interface::print_error(int error){ //a effacer la zone erreur 
	start_color(); int caption_score_x;
	init_pair(2, COLOR_RED, COLOR_BLACK);
	wattron(_main_win, COLOR_PAIR(2));
	switch(error){
		case LEN_ERROR:
			caption_score_x = _error_x - (SHORT_ALL.size()/2);
			print_cara(_main_win, SHORT_ALL.c_str(),caption_score_x, _error_y);
			break;
		case LEN_PSEUDO:
			caption_score_x = _error_x - (SHORT_PSEUDO.size()/2);
			print_cara(_main_win, SHORT_PSEUDO.c_str(),_error_x, _error_y);
			break;
		case LEN_PSWD:
			caption_score_x = _error_x - (SHORT_PSWD.size()/2);
			print_cara(_main_win, SHORT_PSWD.c_str(),_error_x, _error_y);
			break;
		case NO_USER:
			caption_score_x = _error_x - (NO_USER_MSG.size()/2);
			print_cara(_main_win, NO_USER_MSG.c_str(),_error_x, _error_y);
			break;
		case TAKEN_PSEUDO:
			caption_score_x = _error_x - (TAKEN_PSEUDO_MSG.size()/2);
			print_cara(_main_win,TAKEN_PSEUDO_MSG.c_str(),_error_x, _error_y);
			break;
		default:
			caption_score_x = _error_x - (DEFAULT_ERROR.size()/2);
			print_cara(_main_win,DEFAULT_ERROR.c_str(),_error_x, _error_y);
			break; 
	}
	wattroff(_main_win,COLOR_PAIR(2));
	wrefresh(_main_win);
}


void Interface::set_request(int highlight){
	char vect[3][6] = {"YES", "NO", "BACK"};
	int x = WIN_WIDTH * 1/5, y = WIN_HEIGHT*4/5;
	for (int i = 0; i < 3; ++i){
		if(i==highlight){
			wattron(_main_win, A_STANDOUT);
			print_cara(_main_win, vect[i], x, y);
			wattroff(_main_win, A_STANDOUT);
		}
		else{
			print_cara(_main_win, vect[i], x, y);
		}
		x += (x/2);
	}
}

void Interface::print_cara(WINDOW *win , const char *c, int x, int y){
	wattron(win, A_BOLD);
    mvwprintw(win, y, x, c);
	wrefresh(win);
	wattroff(win, A_BOLD);
}

void Interface::move_cursor(WINDOW *win, int x, int y, bool invisible){
	if(invisible){ //suprresing a charactere
		wattron(win, A_INVIS);
		mvwprintw(win, y, x, &CURSOR);
		wrefresh(win);
		wattroff(win, A_INVIS);
	}
	else{
		wattron(win, A_BLINK | A_BOLD);
		mvwprintw(win, y, x, &CURSOR);
		wrefresh(win);
		wattroff(win, A_BLINK | A_BOLD);
	}
	
}

void Interface::print_users(std::vector<Profile*> vect, int highlight, int min, int max, int type){
	clear();
	resize_win();
	if(type == Y_FRIENDS) 
		set_screen(&YOUR_FRIENDS, nullptr, &Y_FRIENDS_SAYING, &Y_FRIENDS_SAYING2);
	else if(type==LEADB) //lead_board
		set_screen(&LEADERBOARD, nullptr, &LEADBOARD_SAYING, nullptr);
	else if(type==REQ)
		set_screen(&REQUEST, nullptr, &REQUEST_SAYING, nullptr);
 
	int caption_x  = (WIN_WIDTH/4),caption_y = (WIN_HEIGHT-PS_HEIGHT)/2;

	int x =caption_x, y=caption_y+2, caption_score_x =caption_x*3;

	char score[10]; char pseudo[30];
	char pseudo_title[20] = "PSEUDO", score_title[] = "SCORE";

	print_cara(_main_win, pseudo_title,caption_x,caption_y);
	print_cara(_main_win, score_title, caption_score_x,caption_y);
	
	for (int i = min; i < max; ++i){
		sprintf(score, "%d",vect[i]->score);
		sprintf(pseudo, "%s", vect[i]->pseudo);
		if(i == highlight)
		{
			wattron(_main_win, A_REVERSE);
			print_cara(_main_win,pseudo,x,y);
			print_cara(_main_win, score,caption_score_x,y);
			wattroff(_main_win, A_REVERSE);
		}
		else{
			print_cara(_main_win, pseudo,x,y);
			print_cara(_main_win, score,caption_score_x,y);
		}
		y++;
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
