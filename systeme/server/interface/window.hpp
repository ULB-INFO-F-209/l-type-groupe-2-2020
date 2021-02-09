#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <ncurses.h>

#include "Menu.hpp"
#include "Client.hpp"

/* Ici on va tout géré*/

class Interface
{
	WINDOW *_mainWindow;

	Client client{};

	ConnexionMenu _acceuil{};
    ConnexionMenu _menu{};
    FriendMenu _friend_menu{};
public:
	//constructor
	Interface(){
		if((_mainWindow = initscr() )== NULL){
			perror("Une erreur s'est produit au lancement\n");
			exit(EXIT_FAILURE);
		}
		start_color();                    /*  Initialize colours  */
	}
	void start_session(){
		//lancer l'accueil
		_acceuil.print(_mainWindow);
		refresh();
	}

	//destructor
	~Interface(){
		delwin(_mainWindow);
		endwin();
		refresh();
	}
	


};

#endif