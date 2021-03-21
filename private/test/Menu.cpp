#include "Menu.hpp"


Menu::Menu(): QMainWindow(){
	if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("L-Type"));
     this->setWindowTitle(QApplication::translate("L-Type", "L-Type", nullptr));
    this->resize(1000, 600);
    this->setStyleSheet(QString::fromUtf8("background-color:lightsalmon"));

    //Widget 
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    //Home button initializing	
	for (int i = 0; i < SIZE_HOME; ++i){
		home_button[i] = new QPushButton(QString::fromStdString(connexion_menu[i]));
	}
}

void Menu::start_session(){
	home();
	this->show();
}

Menu::~Menu(){}

void Menu::home(){	
	QWidget *horizontalLayoutWidget = new QWidget(centralWidget);
	QWidget *verticalLayoutWidget = new QWidget(centralWidget);
 
    /*horizontalLayoutWidget->setGeometry(QRect(80, 30, 851, 80));
    QHBoxLayout *horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
	*/


   	verticalLayoutWidget->setGeometry(QRect(370,300,80, 80));
	QVBoxLayout *button_VLayout = new QVBoxLayout(verticalLayoutWidget);
	button_VLayout->setSpacing(8);
    button_VLayout->setContentsMargins(11, 11, 11, 11);
    button_VLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    button_VLayout->setContentsMargins(40, 20, 2, 20);
	
	for (int i = 0; i < SIZE_HOME; ++i){
		button_VLayout->addWidget(home_button[i]);
	}

}
/*Menu::~Menu(){}

void Menu::start_session(){}

int  Menu::main_m(){}
int Menu::Menu::friends(){}
int Menu::lobby(){}
*/