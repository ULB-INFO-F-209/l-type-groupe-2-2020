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

#include "Client.hpp"
#include "screen.hpp"
#include "parsing.hpp"


#include <iostream>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QListWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QSignalMapper>
//#include <QObject>


using namespace Screen;
using namespace Parsing;

class Menu : public QMainWindow{

	Client _client{};

	//size menu
	static const size_t SIZE_HOME = 3;
	static const size_t SIZE_FRIENDS_MENU = 5; 
	static const size_t SIZE_MAIN_MENU = 6;				// ajout de LEVEL EDITOR
	static const size_t SIZE_SETTINGS = 7;

	//choices
	std::string connexion_menu[SIZE_HOME] = {"Sign in", "Sign up", "Quit"};
	std::string friends_menu[SIZE_FRIENDS_MENU] = {"Friends list", "Friends requests", "Add friend",
								   "Remove friend", "Back"};
	std::string main_menu[SIZE_MAIN_MENU] = {"New game", "Friends", "Leaderboard",
								   "Profile", "Level Editor", "Log out"};
	std::string settings_menu[SIZE_SETTINGS] = {"Players", "Drop rate","Ally shot",\
									 "Lives", "Difficulty", "Play", "Quit lobby"};	
	//Q_OBJECT;
	QLineEdit *pseudo_line;
	QLineEdit *pswd_line;
	QLabel *error;

public:
	Menu();
	virtual ~Menu(){}

	void start_session();
private:
	//menu
	void home();
	void  main_m();
	void print_friends();
	int lobby();


private slots:
	void connexion(bool sign_in=true);
	void check_data(bool sign_in=true);
	void print_profile();
	void print_leaderboard();
	void add_friend();
	void verif_friend(QDialog*);
	void request_list(const QModelIndex &index);
	void accepte_friend_request(Profile,QDialog *Dialog);
	void delete_friend_request(Profile,QDialog *Dialog);
};


#endif //MENU_HPP