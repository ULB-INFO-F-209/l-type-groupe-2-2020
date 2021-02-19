/*
	Ajouter:
		titre aux menu
		option quitter pour venir au précédent menu
		option log out dans le menu principale
	Bugs:
		verifier les entrée (user met une lettre dans int ..faut gérer)

	commentaire:
		Utiliser les thread evite de faire full stack. Sans thread y'aura trop 
		d'appelle de menu successive sur le stack, et même de la réentrance de code

*/

#ifndef Menu_HPP
#define Menu_HPP

#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include "Client.hpp"
#include "Interface.hpp"
#include "parsing.hpp"
#include "namespaceMenu.hpp"

using namespace Parsing; //utilities

class Menu{

	//who
	Client *_client;

	//all menu
	static const int HOME = 0;
	static const int MAIN  = 1;
	static const int FRIENDS = 2; 

	//size menu
	static const size_t SIZE_HOME = 3;
	static const size_t SIZE_FRIENDS_MENU = 5; 
	static const size_t SIZE_MAIN_MENU = 5;

	//choices
	std::string connexion_menu[SIZE_HOME] = {"Sign in", "Sign up", "Quit"};
	std::string friends_menu[SIZE_FRIENDS_MENU] = {"Friends list", "Friends requests", "Add friend",
								   "Remove friend", "Back"};
	std::string main_menu[ SIZE_MAIN_MENU] = {"New game", "Friends", "Leaderboard",
								   "Profile", "Log out"};
	//console
	Interface window{};
public:
	Menu(Client *client):_client(client){}

	void start_session();
	
	//destructor
	~Menu()=default;

private:
	//all menu
	int home();
	int  main_m();
	int friends();

	//format
	bool verify_pseudo_format(char *pseudo);
	bool verify_pswd_format(char*pswd);

	//Home utilities
	int connexion(bool sign_in=true);

	//Friends utilities
	void afficher_friends();
	void request_management();
	void add_del_friends(bool add=true);
	void get_msg(char * pseudo, char *res,int msg, bool invitation);

};


#endif //MENU_HPP