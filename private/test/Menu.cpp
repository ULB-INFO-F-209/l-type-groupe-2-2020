#include "Menu.hpp"


Menu::Menu(): QMainWindow(){
	if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("L-Type"));
     this->setWindowTitle(QApplication::translate("L-Type", "L-Type", nullptr));
    this->resize(1000, 600);
    this->setStyleSheet(QString::fromUtf8("background-color:lightsalmon"));

}

void Menu::start_session(){
	home();
	this->show();
}

Menu::~Menu(){}

void Menu::home(){
	QWidget *centralWidget = new QWidget(this);
	QVBoxLayout *buttonsVerticalLayout = new QVBoxLayout();
	QPushButton *home_button[SIZE_HOME];
	for (int i = 0; i < SIZE_HOME; ++i)
	{
		home_button[i] = new QPushButton(QString::fromStdString(connexion_menu[i]));
		buttonsVerticalLayout->addWidget(home_button[i]);
	}
	centralWidget->setLayout(buttonsVerticalLayout);
	this->setCentralWidget(centralWidget);
}
/*Menu::~Menu(){}

void Menu::start_session(){}

int  Menu::main_m(){}
int Menu::Menu::friends(){}
int Menu::lobby(){}
*/