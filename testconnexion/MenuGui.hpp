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
	void set_background(QWidget *centralwidget);
	void set_title(QWidget *parent, std::string image);
	QLabel *create_label(QWidget *parent, std::string value,QRect pos);
	QPushButton *create_button(QWidget *parent,std::string image, int width, int height);
	QPushButton *create_button(QWidget *parent,std::string image, QRect size);
	QComboBox *create_box(QWidget *parent, std::vector<std::string> values, QRect pos);
	QLineEdit *create_line(QWidget *parent,QRect rect, bool pswd);
	QTableWidget * create_table_widget(QWidget *parent,int col, int row,std::string title[],QRect rect);
	QLabel *print_error(QWidget *parent, int error, QRect pos);

private slots:
	void connexion(bool sign_in=true);
	int check_data( QLineEdit *pseudo_line, QLineEdit *pswd_line,bool sign_in=true);
	void print_profile();
	void print_leaderboard();
	int verif_friend(std::string pseudo);
	void save_level(Parsing::Level my_level);
	void custom_enemy(Parsing::Level my_level, int idx);
	void custom_obstacle(Parsing::Level my_level, int idx);
	void custom_player(Parsing::Level my_level);
	void view_level(bool mine=true);
	void launch_level(std::string my_level,bool from_lead=true);
};

#endif //MENU_HPP