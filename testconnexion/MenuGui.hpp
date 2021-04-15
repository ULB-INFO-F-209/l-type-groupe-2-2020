/*
	Ajouter:
		titre aux MenuGui
		option quitter pour venir au précédent MenuGui
		option log out dans le MenuGui principale
	Bugs:
		verifier les entrée (user met une lettre dans int ..faut gérer)
		LE BOUTONNNNN EXITTT  du programme

	commentaire:
		_Utiliser les thread evite de faire full stack. Sans thread y'aura trop 
		d'appelle de MenuGui successive sur le stack, et même de la réentrance de code
		_DECOMMENTER POUR UTILISER CLIENT

*/

#ifndef Menu_HPP
#define Menu_HPP

#include "Client.hpp"
#include "screen.hpp"
#include "game_test/parsing.hpp"
#include "Frame.hpp"
//#include "label.hpp"


#include <iostream>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QLabel>
#include <QMovie>
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
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QStringListModel>
#include <QFrame>
#include <QLCDNumber>
#include <QSlider>
#include <QRadioButton>
#include <QFormLayout>
#include <QPalette>


#include "DisplayGameGui.hpp"
#include <SFML/Graphics.hpp>


using namespace Screen;
//using namespace Parsing;

class MenuGui : public QMainWindow{

	Client _client{};

	//size MenuGui
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

    QListWidget* list_of_all_modif = nullptr;
    QListWidget* list_setup_level = nullptr;

    QAction* m_pActAdd = nullptr;
    QAction* m_pActRemove = nullptr;

	int button_size = 60;

	//game area
	int X_MIN = 0;
	int X_MAX = 1000-button_size; // ASK PQ ENLEVER CA !!!


public:
	MenuGui();
	virtual ~MenuGui(){}
	void start_session();
private:
	//MenuGui
	void level_menu();
	void home();
	void main_m();
	void print_friends();
	void lobby(std::string my_level="0",bool from_lead=false);
	void level_editor(Parsing::Level my_level);
	void launch_game();
	void view_level();

private slots:
	void connexion(bool sign_in=true);
	void check_data(bool sign_in=true);
	void print_profile();
	void print_leaderboard();
	void add_del_friend(bool adding=true);
	void verif_friend(QDialog*, bool adding=true);
	void request_list(const QModelIndex &index);
	void accept_friend();
	void launch_game(int players, int drop_rate, int lives, std::string difficulty, bool ally_shot, std::string my_level="0",bool from_lead=false);
	void save_level(Parsing::Level my_level);
	void custom_enemy(Parsing::Level my_level, int idx);
	void custom_obstacle(Parsing::Level my_level, int idx);
	void custom_player(Parsing::Level my_level);
	void view_level(bool mine=true);
	void launch_level(std::string my_level,bool from_lead=true);
};

#endif //MENU_HPP