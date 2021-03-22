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
    QWidget *centralwidget = new QWidget(this);

    QLineEdit *pseudo_line = new QLineEdit(centralwidget);
    pseudo_line->setGeometry(QRect(230, 270, 400, 45));
    pseudo_line->setMaxLength(15);

    QLineEdit *pswd_line = new QLineEdit(centralwidget);
    pswd_line->setGeometry(QRect(230, 370, 400, 45));
    pswd_line->setMaxLength(15);

    QLabel *title_label = new QLabel(QString::fromStdString("CONNEXION"), centralwidget);
    title_label->setGeometry(QRect(70, 47, 691, 81));
    title_label->setFrameShape(QFrame::WinPanel);
    //title_label->setTextFormat(Qt::MarkdownText);
    title_label->setAlignment(Qt::AlignCenter);

    QLabel *pseudo_label = new QLabel(QString::fromStdString("USERNAME : "),centralwidget);
    pseudo_label->setGeometry(QRect(140, 270, 91, 45));

    QLabel *pswd_label = new QLabel(QString::fromStdString("PASSWORD : "),centralwidget);
    pswd_label->setGeometry(QRect(130, 370, 101, 45));

    QWidget *horizontalLayoutWidget = new QWidget(centralwidget);
    horizontalLayoutWidget->setGeometry(QRect(110, 470, 641, 80));
    QHBoxLayout *horizontalLayout =  new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setSpacing(50);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);

    QPushButton *ok_button =  new QPushButton(QString::fromStdString("Ok"),horizontalLayoutWidget);
    ok_button->setMinimumSize(QSize(25, 50));
    horizontalLayout->addWidget(ok_button);


    QPushButton *cancel_button = new QPushButton(QString::fromStdString("Cancel"),horizontalLayoutWidget);
    cancel_button->setMinimumSize(QSize(25, 50));
    horizontalLayout->addWidget(cancel_button);

    this->setCentralWidget(centralwidget);

}
void Menu::main_m(){
    QWidget *centralwidget = new QWidget(this);

    QLabel *label = new QLabel(QString::fromStdString("MAIN MENU"),centralwidget);
    label->setGeometry(QRect(100, 30, 591, 61));
    label->setFrameShape(QFrame::WinPanel);
    label->setTextFormat(Qt::RichText);
    label->setAlignment(Qt::AlignCenter);

    QWidget *verticalLayoutWidget  = new QWidget(centralwidget);
    verticalLayoutWidget->setGeometry(QRect(80, 160, 651, 351));

    QVBoxLayout *verticalLayout  = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setContentsMargins(100, 0, 100, 0);

    QPushButton *main_button[SIZE_MAIN_MENU];
    for (size_t i = 0; i < SIZE_MAIN_MENU; ++i){
       main_button[i] = new QPushButton(QString::fromStdString(main_menu[i]),verticalLayoutWidget);
       main_button[i]->setMinimumSize(QSize(25, 50));
       verticalLayout->addWidget(main_button[i]);
    }

    this->setCentralWidget(centralwidget);

}
/*

void Menu::start_session(){}


int Menu::Menu::friends(){}
int Menu::lobby(){}
*/