/*
	Ajouter:
		titre aux MenuTerminal
		option quitter pour venir au précédent MenuTerminal
		option log out dans le MenuTerminal principale
	Bugs:
		verifier les entrée (user met une lettre dans int ..faut gérer)
		LE BOUTONNNNN EXITTT  du programme

	commentaire:
		_Utiliser les thread evite de faire full stack. Sans thread y'aura trop 
		d'appelle de MenuTerminal successive sur le stack, et même de la réentrance de code
		_DECOMMENTER POUR UTILISER CLIENT

*/

#ifndef Menu_HPP
#define Menu_HPP

#include <iostream>
#include <sys/types.h>
#include <vector>
#include "Client.hpp"
#include "Interface.hpp"
#include "game/parsing.hpp"
#include "DisplayGame.hpp"
#include "SFML/Graphics.hpp"

using namespace Parsing; //utilities
using namespace Screen;

class MenuTerminal{

	//who
	Client _client{};

	//all MenuTerminal
	static const int HOME = 0;
	static const int MAIN  = 1;
	static const int FRIENDS = 2; 
	static const int SETTINGS = 3;

	//size MenuTerminal
	static const size_t SIZE_HOME = 3;
	static const size_t SIZE_FRIENDS_MENU = 5; 
	static const size_t SIZE_MAIN_MENU = 5;
	static const size_t SIZE_SETTINGS = 7;

	//choices
	std::string connexion_menu[SIZE_HOME] = {"Sign in", "Sign up", "Quit"};
	std::string friends_menu[SIZE_FRIENDS_MENU] = {"Friends list", "Friends requests", "Add friend",
								   "Remove friend", "Back"};
	std::string main_menu[SIZE_MAIN_MENU] = {"New game", "Friends", "Leaderboard",
								   "Profile", "Log out"};
	std::string settings_menu[SIZE_SETTINGS] = {"Players", "Drop rate","Ally shot",
									 "Lives", "Difficulty", "Play", "Quit lobby"};				   
	//console
	static Interface window;
	
public:
	MenuTerminal()=default;
	void start_session();
	~MenuTerminal()=default;

private:
	//all MenuTerminal
	int home();
	int  main_m();
	int friends();
	int lobby();

	//format
	bool verify_pseudo_format(char *pseudo);
	bool verify_pswd_format(char*pswd);

	//Home utilities
	int connexion(bool sign_in=true);

	//Friends utilities
	void afficher_friends();
	void request_management();
	void add_del_friends(bool add=true);

	//Game utilities
	void get_players(Game_settings *set);
	void launch_game();

	static void handle_SIGINT(int sig);

	
};



#endif //MENU_HPP