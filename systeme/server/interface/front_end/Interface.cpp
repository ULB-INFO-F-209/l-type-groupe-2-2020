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

	_ps_x = 15;  //pas la legende
	_ps_y = (WIN_Y /2); //readapatation
	_pa_x = 15;
	_pa_y =(WIN_Y /2);

	_saying_x =  _title_x;
	_saying_y = _title_y+1;

	_error_x = WIN_X+4;
	_error_y= (WIN_Y*4)+1;
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

//PRIVATE METHODES 
void Interface::set_screen(std::string *title,std::string *saying1, std::string *saying2, std::string *saying3){
	clear();
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

void Interface::init_connexion(){
	set_screen(&HOME_TITLE, nullptr, &HOME_SAYING, nullptr);
	box(_pseudo_win,0,0);
	box(_pass_win,0,0);
	refresh();
	wrefresh(_pseudo_win);
	wrefresh(_pass_win);

}


void Interface::print_cara(WINDOW *win , const char *c, int x, int y){
	wattron(win, A_BOLD);
    mvwprintw(win, y, x, c);
	wrefresh(win);
	wattroff(win, A_BOLD);
}

Interface::~Interface(){
		getch();
		endwin();
}

