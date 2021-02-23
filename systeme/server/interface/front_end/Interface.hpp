#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include <ncurses.h>
#include "parsing.hpp"
class Interface final
{
	//Terminale state
	int YMAX=0, XMAX=0;

	//all window sizes
	int WIN_HEIGHT=0, WIN_WIDTH=0, WIN_Y=0, WIN_X=0;
	int PS_HEIGHT=0, PS_WIDTH=0, PS_Y =0, PS_X=0; 	//pseudo win
	int PA_HEIGHT=0, PA_WIDTH=0, PA_Y=0, PA_X=0; 	//password win
	int S_HEIGHT=0, S_WIDTH=0, S_Y=0, S_X=0; 		//saying win

	//positions
	int _menu_x=0 , _menu_y=0; 			//where menu begin to be printed
	int _ps_x=0, _ps_y=0, _pa_x=0, _pa_y=0; //where the pseudo and password begin
	int _saying_x=0, _saying_y=0;
	int _error_x=0, _error_y=0;
	int _prof_x=0, _prof_p_y=0, _prof_s_y=0;
	int _title_x=0, _title_y=0;

	//different window
	WINDOW * _main_win;
	WINDOW* _pseudo_win;
	WINDOW*_pass_win;
	WINDOW*_saying_win;
public:
	//constructor
	Interface();
	void resize_win();
	//communication with screen
	int print_menu(size_t size, std::string *choices);
	bool get_connexion(char *pseudo, char *pswd, char *error);
	void print_profile(std::vector<Parsing::Profile*> vect); //n oublie pas le titre
	void print_profile(Parsing::Profile *prof);
	int print_invitation(Parsing::Profile *pseudo);
	int get_pseudo(char *res, char *error); //for sendrequest|add|del
	void print_alert(char *alert); //signaux

	//destructor
	~Interface();
	void set_screen(std::string *title,std::string *saying1, std::string *saying2, std::string *saying3);
	void update_menu(size_t size,  std::string *choices, int highlight);
	bool verify_cara(char *c);
	void print_cara(WINDOW *win , const char *c, int x, int y);
	void move_cursor(WINDOW *win, int x, int y, bool invisible=false);
	void init_connexion();
	void print_message(WINDOW *win, size_t size, std::string *tab, int x, int y);
	void print_error(WINDOW *win, char *error , int x, int y);
	void print_friends(WINDOW *win, std::vector<Parsing::Profile*> vect, int highlight, int min, int max);
};




#endif // INTERFACE_HPP