/*
	Ajouter:
		titre aux menu
		option quitter pour venir au précédent menu
		option log out dans le menu principale
	Bugs:
		verifier les entrée (user met une lettre dans int ..faut gérer)
		LE BOUTONNNNN EXITTT  du programme

	commentaire:
		_Utiliser les thread evite de faire full stack. Sans thread y'aura trop 
		d'appelle de menu successive sur le stack, et même de la réentrance de code
		_DECOMMENTER POUR UTILISER CLIENT

*/

#ifndef Menu_HPP
#define Menu_HPP


#include <iostream>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QApplication>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

class Menu : public QMainWindow{

	//who
	//Client _client{};

	//size menu
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

	//Button 
	QPushButton *home_button[SIZE_HOME];
	QPushButton *main_button[SIZE_MAIN_MENU];
	QPushButton *settings_button[SIZE_SETTINGS];
	QPushButton *friends_button[SIZE_FRIENDS_MENU];

	//widget
	QWidget *centralWidget;

public:
	Menu();
	~Menu();

	void start_session();
	void home();
	int  main_m();
	int friends();
	int lobby();
	
};



#endif //MENU_HPP