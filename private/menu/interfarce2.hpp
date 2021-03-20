#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include "game_test/parsing.hpp"
#include "screen.hpp"

using Parsing::Game_settings;
using namespace Screen;

class Interface final{
	
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
private:
	void set_screen(std::string *title,std::string *saying1, std::string *saying2);
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
	void print_message(std::string *msg1, bool up=true );

};




#endif // INTERFACE_HPP