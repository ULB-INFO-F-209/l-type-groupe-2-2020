/*
	Ajouter:
		titre aux menu
		option quitter pour venir au précédent menu
	Bugs:
		Entrez autre chose qu un nombre dans get_user_choice casse la machine!
*/

#ifndef Menu_HPP
#define Menu_HPP

#include <iostream>
#include <sys/types.h>
#include <pthread.h>  
#include <signal.h>
#include <semaphore.h>
#include "Client.hpp"



class Menu{
	Client *_client;
	static const int HOME = 0;
	static const int MAIN  = 1;
	static const int FRIENDS = 2; 
public:
	Menu(Client *client):_client(client){}

	//DIFERRENT MENUUU(threads)
	void *home(void *arg){}
	void *main(void *arg){}
	void *friends(void *arg);
	void start_menu(int menu){
		switch(menu){
			case HOME:
				break;
			case MAIN:
				break;
			case FRIENDS:
				break;
			default:
				break;
		}

	}
	void start_session(){
		start_menu(HOME);
	}

	//getters & setters
	
	//destructor
	~Menu()=default;
};




#endif //MENU_HPP