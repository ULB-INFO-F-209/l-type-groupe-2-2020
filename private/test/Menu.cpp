#include "Menu.hpp"


Menu::Menu(): QMainWindow(){
    this->setWindowTitle(QApplication::translate("L-Type", "L-Type", nullptr));
    this->resize(800, 600);
    this->setStyleSheet(QStringLiteral("background-color:salmon;"));
}

void Menu::start_session(){
	home();
	this->show();
}


void Menu::home(){	
    QWidget *centralwidget = new QWidget(this);

    //layout box
    QWidget *verticalLayoutWidget = new QWidget(centralwidget);
    verticalLayoutWidget->setGeometry(QRect(240, 230, 321, 301));
    //layout button
    QVBoxLayout *button_v_layout = new QVBoxLayout(verticalLayoutWidget);
    button_v_layout->setContentsMargins(11, 11, 11, 11);
    //home button
    QPushButton *home_button[SIZE_HOME];
    for (size_t i = 0; i < SIZE_HOME; ++i)
    {
       home_button[i] = new QPushButton(QString::fromStdString(connexion_menu[i]),verticalLayoutWidget);
       home_button[i]->setMinimumSize(QSize(165, 65));
       button_v_layout->addWidget(home_button[i]);
    }
    QLabel *title_label = new QLabel(QString::fromStdString("HOME"),centralwidget);
    title_label->setGeometry(QRect(110, 20, 579, 78));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setAlignment(Qt::AlignCenter);
    this->setCentralWidget(centralwidget);
}

void Menu::connexion(){
    /*QString conn("CONNEXION");
    QString psd("pseudo");
    QString psw("password");
    QGroupBox* box = new QGroupBox(conn, centralWidget);
    QLineEdit* pseudo = new QLineEdit(psd, box);
    QLineEdit* pswd = new QLineEdit(psw, box);*/



}
/*

void Menu::start_session(){}

int  Menu::main_m(){}
int Menu::Menu::friends(){}
int Menu::lobby(){}
*/