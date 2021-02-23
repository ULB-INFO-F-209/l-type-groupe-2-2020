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
    PS_HEIGHT = WIN_HEIGHT/5;
    PS_WIDTH = (WIN_WIDTH/2)+10;
    PS_Y = WIN_Y*4;
    PS_X = (WIN_X*2)+3;
    PA_HEIGHT = WIN_HEIGHT/5;
    PA_WIDTH = (WIN_WIDTH/2)+10;
    PA_Y = WIN_Y*6;
    PA_X = (WIN_X*2)+3;
    S_HEIGHT =  WIN_HEIGHT/4;
    S_WIDTH = WIN_WIDTH;
    S_Y = WIN_Y;
    S_X = WIN_X ;

    //other postions (a readapater selon la fenetre)
    _menu_x = WIN_WIDTH/4;
	_menu_y =  WIN_HEIGHT/3;
	_title_x = (WIN_X*3)-7;
	_title_y =  WIN_Y /2;
	_ps_x = 15;  //pas la legende
	_ps_y = (WIN_Y /2); //readapatation
	_pa_x = 15;
	_pa_y =(WIN_Y /2);
	_saying_x =  WIN_X;
	_saying_y = (WIN_Y*2)-1;
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
void Interface::set_screen(char *title, int nb_saying,char*saying1, char*saying2, char*saying3){
	clear();
	resize_win(); //maybe do the resize only if terminal change
	box(_main_win,0,0);
    box(_saying_win,0,0);
    refresh();
	wrefresh(_main_win);
	wrefresh(_saying_win);
	print_cara(_saying_win, title, _title_x, _title_y); 
	print_cara(_saying_win, saying1, _saying_x, _saying_y);
	if(nb_saying > 1){
		print_cara(_saying_win, saying2, _saying_x, _saying_y+1);
		if(nb_saying > 2){
			print_cara(_saying_win, saying3, _saying_x, _saying_y+2);
		}
	}
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

