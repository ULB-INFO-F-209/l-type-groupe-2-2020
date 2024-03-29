#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include <ncurses.h>
#include "game/parsing.hpp"
#include "screen.hpp"

using Parsing::Game_settings;
using namespace Screen;

class Interface final{
	//Terminale state
	int YMAX{}, XMAX{};

	//all window sizes
	int WIN_HEIGHT{}, WIN_WIDTH{}, WIN_Y{}, WIN_X{};
	int PS_HEIGHT{}, PS_WIDTH{}, PS_Y {}, PS_X{}; 	//pseudo win
	int PA_HEIGHT{}, PA_WIDTH{}, PA_Y{}, PA_X{}; 	//password win
	int S_HEIGHT{}, S_WIDTH{}, S_Y{}, S_X{}; 		//saying win
	int SET_HEIGHT{}, SET_WIDTH{}, SET_Y{}, SET_X1{}, SET_X2{}; //settings of lobby
	//positions
	int _menu_x{} , _menu_y{}; 			//where MenuTerminal begin to be printed
	int _saying_x{}, _saying_y{};
	int _error_x{}, _error_y{};
	int _prof_x{}, _prof_p_y{}, _prof_s_y{};
	int _title_x{}, _title_y{};

	int _ps_caption_x{}, _ps_caption_y{}, _pa_caption_y{};

	//different window
	WINDOW * _main_win=nullptr;
	WINDOW* _pseudo_win=nullptr;
	WINDOW*_pass_win=nullptr;
	WINDOW*_saying_win=nullptr;
	WINDOW* _settings_win1=nullptr;
	WINDOW* _settings_win2=nullptr;
public:
	//constructor
	Interface();
	void resize_win();

	//communication with screen
	int print_menu(size_t size, std::string *choices, int type, Game_settings*set=nullptr);
	bool get_connexion(char *pseudo, char *pswd,int error, int type);
	bool print_profile(std::vector<Parsing::Profile> *vect, int type,int answer[2] = nullptr); 
	int print_profile(Parsing::Profile *prof, int type);
	int get_pseudo(char *res, int error, int type);
	int range(int n, Game_settings *set, bool percent=false);
	inline void erase_win(){endwin();}
	//destructor
	~Interface();

	//other
	Interface(const Interface&)=default;
	Interface& operator=(const Interface&)=default;

private:
	void set_screen(const std::string *title,const std::string *saying1,const std::string *saying2);
	void update_menu(size_t size,  std::string *choices, int highlight, int type);
	bool verify_cara(char *c);
	void print_cara(WINDOW *win , const char *c, int x, int y);
	void move_cursor(WINDOW *win, int x, int y, bool invisible=false);
	void init_connexion(int choice);
	void print_error(int error);
	void print_users(std::vector<Parsing::Profile> *vect, int highlight, int min, int max, int type);
	void init_pseudo_win();
	void set_request(int highlight);
	void set_settings(Game_settings *set);
	void print_message(const std::string *msg1, bool up=true );

};




#endif // INTERFACE_HPP