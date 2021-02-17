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

using namespace Parsing; //utilities

class Menu{

	//who
	Client *_client;

	//all menu
	static const int HOME = 0;
	static const int MAIN  = 1;
	static const int FRIENDS = 2; 

	//choices
	std::string connexion_menu[3] = {"Sign in", "Sign up", "Quit"};
	std::string friends_menu[5] = {"Friends list", "Friends requests", "Add friend",
								   "Remove friend", "Back"};
	std::string main_menu[5] = {"New game", "Friends", "Leaderboard",
								   "Profile", "Log out"};
	//console
	Interface window{};
public:
	Menu(Client *client):_client(client){}

	//DIFERRENT MENUUU(threads)
	int home();
	int  main_m();
	int friends();
	void start_session();
	
	//destructor
	~Menu()=default;

private:
	bool verify_pseudo_format(char *pseudo);
	bool verify_pswd_format(char*pswd);

};


#endif //MENU_HPP