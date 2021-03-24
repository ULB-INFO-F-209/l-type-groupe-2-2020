#include "Menu.hpp"

/******************** TODO ********************************************
        *  23/03 : Reunir sign in, sign up using lambda function
        *    
        *
 ***********************************************************************/


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
    //button clicked connect (lambda statement)
   /* connect(&home_button[0],SIGNAL(clicked()), SIGNAL([this]() {
       connexion(true);
   }));*/
    //connect(*home_button[0], SIGNAL(clicked()), this, SLOT(connexion()));
    //connect(home_button[0],  SIGNAL(clicked()), this, SLOT(connexion()));
    connect(home_button[0], &QPushButton::clicked, this, [this]() {
       connexion(true);
   });
    connect(home_button[1], &QPushButton::clicked, this, [this]() {
       connexion(false);
   });
    connect(home_button[2], &QPushButton::clicked, this,  &Menu::close);


    //title section
    QLabel *title_label = new QLabel(QString::fromStdString(HOME_TITLE),centralwidget);
    title_label->setGeometry(QRect(110, 20, 579, 78));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setAlignment(Qt::AlignCenter);
    this->setCentralWidget(centralwidget);
}

void Menu::check_data(bool sign_in){
    std::string pseudo = (pseudo_line->text()).toUtf8().constData();
    std::string pswd = (pswd_line->text()).toUtf8().constData();
    std::cout<<"is sign in = "<<sign_in<<std::endl;
    int success;
    if(sign_in){
        success = _client.signIn(pseudo.c_str(), pswd.c_str());
        if(success)
            main_m();
    }
    else{
        success = _client.signUp(pseudo.c_str(), pswd.c_str());
        if(success)
            main_m();
    }
}

void Menu::connexion(bool sign_in){
    QWidget *centralwidget = new QWidget(this);

    pseudo_line = new QLineEdit(centralwidget);
    pseudo_line->setGeometry(QRect(230, 270, 400, 45));
    pseudo_line->setMaxLength(15);

    pswd_line = new QLineEdit(centralwidget);
    pswd_line->setGeometry(QRect(230, 370, 400, 45));
    pswd_line->setMaxLength(15);

    QLabel *title_label = new QLabel(QString::fromStdString("CONNEXION"), centralwidget);
    title_label->setGeometry(QRect(70, 47, 691, 81));
    title_label->setFrameShape(QFrame::WinPanel);
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
    if(sign_in)
        connect(ok_button, &QPushButton::clicked, this,  [this]() {
            check_data(true);});
    else
        connect(ok_button, &QPushButton::clicked, this, [this]() {
            check_data(false);});
    

    QPushButton *cancel_button = new QPushButton(QString::fromStdString("Cancel"),horizontalLayoutWidget);
    cancel_button->setMinimumSize(QSize(25, 50));
    connect(cancel_button, &QPushButton::clicked, this, [this](){
        home();
    });
    horizontalLayout->addWidget(cancel_button);

    this->setCentralWidget(centralwidget);
    //this->update();
    this->show();

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
    QPushButton *new_game = (main_button[0]);
    QPushButton *friends = (main_button[1]);
    QPushButton *leaderboard = (main_button[2]);
    QPushButton *profile = (main_button[3]);
    QPushButton *level = (main_button[4]);
    QPushButton *log_out = (main_button[5]);
    connect(profile, &QPushButton::clicked, this,  [this]() {
           print_profile();});
    connect(log_out, &QPushButton::clicked, this,  [this]() {
           home();});
    connect(leaderboard, &QPushButton::clicked, this,  [this]() {
           print_leaderboard();});
}

void Menu::print_profile(){
    Profile profile; char buffer[Constante::CHAR_SIZE];
    _client.get_profile(buffer);
    profile_from_str(buffer, &profile);
    std::string pseudo = profile.pseudo, score =  std::to_string(profile.score);
    
    QWidget *centralwidget = new QWidget(this);
    QLabel *title = new QLabel(QString::fromStdString(PROFILE),centralwidget);
    title->setGeometry(QRect(40, 20, 721, 61));
    QFont font;
    font.setPointSize(24);
    title->setFont(font);
    title->setFrameShape(QFrame::WinPanel);
    title->setTextFormat(Qt::RichText);
    title->setAlignment(Qt::AlignCenter);

    QWidget *gridLayoutWidget = new QWidget(centralwidget);
    gridLayoutWidget->setGeometry(QRect(40, 110, 731, 431));
    QGridLayout *gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *username = new QLabel((QString::fromStdString("USERNAME :")),gridLayoutWidget);
    QFont font1;
    font1.setFamily(QStringLiteral("Ubuntu"));
    font1.setPointSize(16);
    font1.setBold(false);
    font1.setWeight(50);
    username->setFont(font1);
    gridLayout->addWidget(username, 0, 0, 1, 1);

    QPushButton *back = new QPushButton((QString::fromStdString("Back")),gridLayoutWidget);
    back->setMinimumSize(QSize(0, 45));
    connect(back, &QPushButton::clicked, this,&Menu::main_m);

    gridLayout->addWidget(back, 3, 0, 1, 3);

    QLabel *pseudo_label= new QLabel(QString::fromStdString(pseudo),gridLayoutWidget);
    QFont font2;
    font2.setFamily(QStringLiteral("aakar"));
    font2.setPointSize(16);
    pseudo_label->setFont(font2);

    gridLayout->addWidget(pseudo_label, 0, 1, 1, 1);

    QLabel *score_label = new QLabel(QString::fromStdString(score),gridLayoutWidget);
    score_label->setFont(font2);

    gridLayout->addWidget(score_label, 2, 1, 1, 1);

    QLabel *label_3 = new QLabel(QString::fromStdString("SCORE :"),gridLayoutWidget);
    QFont font3;
    font3.setPointSize(16);
    label_3->setFont(font3);
    gridLayout->addWidget(label_3, 2, 0, 1, 1);

    this->setCentralWidget(centralwidget);
    //this->update();
    this->show();
}
void Menu::print_leaderboard(){
    std::vector<Profile> profile_list;
    char buffer[Constante::CHAR_SIZE];
    _client.checkLeaderboard(buffer);
    profile_list_from_str(buffer, &profile_list);

    QWidget *centralwidget = new QWidget(this);
    QLabel *title = new QLabel(QString::fromStdString(LEADERBOARD),centralwidget);
    title->setGeometry(QRect(40, 20, 721, 61));
    QFont font;
    font.setPointSize(24);
    title->setFont(font);
    title->setFrameShape(QFrame::WinPanel);
    title->setTextFormat(Qt::RichText);
    title->setAlignment(Qt::AlignCenter);
    QTableWidget* tableWidget = new QTableWidget(centralWidget);
    if (tableWidget->columnCount() < 2)
        tableWidget->setColumnCount(2);
    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem)->setText(QApplication::translate("Lead", "Caligula", nullptr));;
    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem);
    if (tableWidget->rowCount() < 12)
            tableWidget->setRowCount(12);
    

    QStringList m_TableHeader;
    m_TableHeader <<"#"<<"Name"<<"Text";
    tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setShowGrid(false);
    //tableWidget->setGeometry(QApplication::desktop()->screenGeometry());
    tableWidget->setGeometry(QRect(115, 200, 661, 351));
    for(auto prof:profile_list) {
        new QListWidgetItem(QString::fromStdString(prof.pseudo),listWidget);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem11);

        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(1, 1);
        ___qtablewidgetitem10->setText(QApplication::translate("Lead", "80", nullptr));
    }
    this->setCentralWidget(centralwidget);
    //this->update();
    this->show();
}

/*

void Menu::start_session(){}


int Menu::Menu::friends(){}
int Menu::lobby(){}
*/