#include "MenuGui.hpp"

/********************* TODO ********************************************
        *  23/03 : Reunir sign in, sign up using lambda function
        *  23/03 : Maybe mettre tous les widget important en attribut?
        *  26/03 : Design fade like r-type or fun like neon?   
        *
 ***********************************************************************/


MenuGui::MenuGui(): QMainWindow(){
    this->setWindowTitle(QApplication::translate("L-Type", "L-Type", nullptr));
    this->resize(800, 600);
    this->setFixedSize(size());
    this->setStyleSheet(QStringLiteral("background-color:white;"));
}

void MenuGui::start_session(){
    home();
	this->show();
}


void MenuGui::home(){	
    this->setStyleSheet(QStringLiteral("background-color:black;"));
    QWidget *centralWidget = new QWidget(this);

    //exageration
    QLabel *lbl = new QLabel(centralWidget);
    QMovie *mv = new QMovie("images/background/ciel.gif");
    mv->setScaledSize(QSize(800,600));
    lbl->setGeometry(QRect(0, 0, 800, 600));
    mv->start();
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    lbl->setMovie(mv);


    //layout box
    QWidget *verticalLayoutWidget = new QWidget(centralWidget);
    verticalLayoutWidget->setGeometry(QRect(50, 150, 700, 450));
    verticalLayoutWidget->setAttribute(Qt::WA_TranslucentBackground);
    //layout button
    QHBoxLayout *button_v_layout = new QHBoxLayout(verticalLayoutWidget);
    button_v_layout->setContentsMargins(11, 0, 0, 11);
    //home button
    QPushButton *home_button[SIZE_HOME];
    int signIn = 0, signUp = 1, quit = 2;
    QPixmap pix_home_button[SIZE_HOME] = {QPixmap("images/buttons/signIn"),QPixmap("images/buttons/signUp"),QPixmap("images/buttons/quit")};
    QIcon icon_home[SIZE_HOME];
    for (size_t i = 0; i < SIZE_HOME; ++i){
       home_button[i] = new QPushButton(verticalLayoutWidget);
       home_button[i]->setMinimumSize(QSize(200, 200));
       icon_home[i] = QIcon(pix_home_button[i]);
       home_button[i]->setIcon(icon_home[i]);
       home_button[i]->setIconSize(QSize(200, 200));
       home_button[i]->setFlat(true);
       button_v_layout->addWidget(home_button[i]);
   }
   /*************************CONNECTIONS***********************************/
    connect(home_button[signIn], &QPushButton::clicked, this, [this]() {
       connexion(true);
   });
    connect(home_button[signUp], &QPushButton::clicked, this, [this]() {
       connexion(false);
   });
    connect(home_button[quit], &QPushButton::clicked, this,  &MenuGui::close);


    /************************DESIGN SECTION *****************************/
    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(110, 50, 600, 150));
    QPixmap pix_home_title("images/titles/home");
    title_label->setPixmap( pix_home_title);
    title_label->setAlignment(Qt::AlignCenter);
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);


    this->setCentralWidget(centralWidget);

}

void MenuGui::check_data(bool sign_in){
    std::string pseudo = (pseudo_line->text()).toUtf8().constData();
    std::string pswd = (pswd_line->text()).toUtf8().constData();
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

void MenuGui::connexion(bool sign_in){
    QWidget *centralWidget = new QWidget(this);
    QLabel *lbl = new QLabel(centralWidget);
    QMovie *mv = new QMovie("images/background/ciel.gif");
    mv->setScaledSize(QSize(800,600));
    lbl->setGeometry(QRect(0, 0, 800, 600));
    mv->start();
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    lbl->setMovie(mv);

    pseudo_line = new QLineEdit(centralWidget);
    pseudo_line->setGeometry(QRect(230, 270, 400, 45));
    pseudo_line->setMaxLength(15);
    /**********/
    pseudo_line->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
                                            "font: 75 13pt \"Tlwg Typo\";\n"
                                            "border-color: rgb(0, 0, 0);\n"
                                            "gridline-color: rgb(238, 238, 236);"));
    /*********/

    pswd_line = new QLineEdit(centralWidget);
    pswd_line->setGeometry(QRect(230, 370, 400, 45));
    pswd_line->setMaxLength(15);
    pswd_line->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
                                            "font: 75 13pt \"Tlwg Typo\";\n"
                                            "border-color: rgb(0, 0, 0);\n"
                                            "gridline-color: rgb(238, 238, 236);"));

    QLabel *pseudo_label = new QLabel(QString::fromStdString("USERNAME : "),centralWidget);
    pseudo_label->setGeometry(QRect(140, 270, 91, 45));
    pseudo_label->setStyleSheet("QLabel { background-color : black; color : white; }");

    QLabel *pswd_label = new QLabel(QString::fromStdString("PASSWORD : "),centralWidget);
    pswd_label->setGeometry(QRect(130, 370, 101, 45));
    pswd_label->setStyleSheet("QLabel { background-color : black; color : white; }");

    QWidget *horizontalLayoutWidget = new QWidget(centralWidget);
    horizontalLayoutWidget->setGeometry(QRect(110, 440, 680, 200));
    horizontalLayoutWidget->setAttribute(Qt::WA_TranslucentBackground);

    QHBoxLayout *horizontalLayout =  new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setSpacing(50);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);

    QPushButton *ok_button =  new QPushButton(QString::fromStdString("Ok"),horizontalLayoutWidget);
    ok_button->setMinimumSize(QSize(150, 150));
    horizontalLayout->addWidget(ok_button);
    QPixmap pix_ok("images/buttons/ok");
    QIcon icon_ok(pix_ok);
    pix_ok = pix_ok.scaled(ok_button->size(),Qt::KeepAspectRatio);
    ok_button->setIcon(icon_ok);
    ok_button->setIconSize(QSize(150, 150));
    ok_button->setFlat(true);


    /****************************DESIGN*****************************************************/
    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(110, 50, 600, 150));
    QPixmap pix_home_title = QPixmap();
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet(QStringLiteral("background-color:black;"));

    /****************************CONNECTIONS*****************************************************/
    
    if(sign_in){
        //this->setStyleSheet(QStringLiteral("background-color:rgb(183, 110, 34);"));
        pix_home_title.load("images/titles/signIn");
        title_label->setPixmap( pix_home_title);
        pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);
        connect(ok_button, &QPushButton::clicked, this,  [this]() {
            check_data(true);});

    }
    else{
        //this->setStyleSheet(QStringLiteral("background-color:rgb(19, 43, 15);"));
        pix_home_title.load("images/titles/signUp");
        title_label->setPixmap( pix_home_title);
        pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);
        connect(ok_button, &QPushButton::clicked, this, [this]() {
            check_data(false);});
    }
    /*************************************************/
    QPushButton *cancel_button = new QPushButton(QString::fromStdString("Cancel"),horizontalLayoutWidget);
    cancel_button->setMinimumSize(QSize(150, 150));
    QPixmap pix_cancel("images/buttons/back");
    QIcon icon_cancel(pix_cancel);
    cancel_button->setIcon(icon_cancel);
    cancel_button->setIconSize(QSize(150, 1500));
    pix_cancel = pix_cancel.scaled(cancel_button->size(),Qt::KeepAspectRatio);
    cancel_button->setFlat(true);
    connect(cancel_button, &QPushButton::clicked, this, [this](){
        home();
    });
    horizontalLayout->addWidget(cancel_button);

    this->setCentralWidget(centralWidget);
    this->show();

}
void MenuGui::main_m(){
    QWidget *centralWidget = new QWidget(this);

    //exageration
    QLabel *lbl = new QLabel(centralWidget);
    QMovie *mv = new QMovie("images/background/ciel.gif");
    mv->setScaledSize(QSize(800,600));
    lbl->setGeometry(QRect(0, 0, 800, 600));
    mv->start();
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    lbl->setMovie(mv);

    QWidget *horizontalLayoutWidget  = new QWidget(centralWidget);
    horizontalLayoutWidget->setGeometry(QRect(80, 150, 651, 450));

    QVBoxLayout *HLayout  = new QVBoxLayout(horizontalLayoutWidget);
    HLayout->setContentsMargins(100, 0, 100, 0);

    QPushButton *button[SIZE_MAIN_MENU];
    QPixmap pix_main_button[SIZE_MAIN_MENU] = {QPixmap("images/buttons/game"),QPixmap("images/buttons/friends"),QPixmap("images/buttons/lead"),
    										   QPixmap("images/buttons/profile"),QPixmap("images/buttons/level"),QPixmap("images/buttons/logout")};
    QIcon icon_main[SIZE_MAIN_MENU];
    int ngame = 0, friends=1, lead=2, prof=3, level=4, logout=5;
    for (size_t i = 0; i < SIZE_MAIN_MENU; ++i){
       button[i] = new QPushButton(horizontalLayoutWidget);
       button[i]->setMinimumSize(QSize(400,100 ));
       icon_main[i] = QIcon(pix_main_button[i]);
       button[i]->setIcon(icon_main[i]);
       button[i]->setIconSize(QSize(400, 100));
       button[i]->setFlat(true);
       HLayout->addWidget(button[i]);
    }

    connect(button[friends], &QPushButton::clicked, this, &MenuGui::print_friends);
    connect(button[lead], &QPushButton::clicked, this,&MenuGui::print_leaderboard);
    connect(button[prof], &QPushButton::clicked, this, &MenuGui::print_profile);
    connect(button[logout], &QPushButton::clicked, this,&MenuGui::home);
    connect(button[ngame], &QPushButton::clicked, this,[this](){
        lobby();
    });
    connect(button[level], &QPushButton::clicked, this, &MenuGui::level_menu);

    /****** DESIGN SECTION ****************************/
    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(110, 30, 600, 150));
    QPixmap pix_home_title("images/titles/mainMenu");
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);
    title_label->setPixmap( pix_home_title);
    title_label->setAlignment(Qt::AlignCenter);
    /*********END DESIGN SECTION*****************************************/
    this->setCentralWidget(centralWidget);
    this->show();
}

void MenuGui::print_profile(){
    Profile profile; char buffer[Constante::CHAR_SIZE];
    _client.get_profile(buffer);
    Parsing::profile_from_str(buffer, &profile);
    std::string pseudo = profile.pseudo, score =  std::to_string(profile.score);

    QWidget *centralWidget = new QWidget(this);
    QLabel *lbl = new QLabel(centralWidget);
    QMovie *mv = new QMovie("images/background/ciel.gif");
    mv->setScaledSize(QSize(800,600));
    lbl->setGeometry(QRect(0, 0, 800, 600));
    mv->start();
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    lbl->setMovie(mv);


    QWidget *gridLayoutWidget = new QWidget(centralWidget);
    gridLayoutWidget->setGeometry(QRect(40, 110, 731, 431));
    gridLayoutWidget->setAttribute(Qt::WA_TranslucentBackground);

    QGridLayout *gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *username = new QLabel((QString::fromStdString("USERNAME :")),gridLayoutWidget);
    username->setStyleSheet("QLabel { background-color : black; color : white; }");
    QLabel *score_l = new QLabel(QString::fromStdString("SCORE :"),gridLayoutWidget);
    score_l->setStyleSheet("QLabel { background-color : black; color : white; }");

    
    QFont font1;
    font1.setFamily(QStringLiteral("Ubuntu"));
    font1.setPointSize(16);
    font1.setBold(false);
    font1.setWeight(50);
    username->setFont(font1);
    score_l->setFont(font1);
    gridLayout->addWidget(username, 0, 0, 1, 1);
    gridLayout->addWidget(score_l, 2, 0, 1, 1);

    QPushButton *back = new QPushButton((QString::fromStdString("Back")),gridLayoutWidget);
    back->setMinimumSize(QSize(0, 45));
    back->setStyleSheet("QLabel { background-color : black; color : white; }");
    connect(back, &QPushButton::clicked, this,&MenuGui::main_m);

    gridLayout->addWidget(back, 3, 0, 1, 3);

    QLabel *pseudo_label= new QLabel(QString::fromStdString(pseudo),gridLayoutWidget);
    QFont font2;
    font2.setFamily(QStringLiteral("aakar"));
    font2.setPointSize(16);
    pseudo_label->setFont(font2);
    pseudo_label->setStyleSheet("QLabel { background-color : black; color : white; }");
    
    gridLayout->addWidget(pseudo_label, 0, 1, 1, 1);

    QLabel *score_label = new QLabel(QString::fromStdString(score),gridLayoutWidget);
    score_label->setFont(font2);
    score_label->setStyleSheet("QLabel { background-color : black; color : white; }");


    gridLayout->addWidget(score_label, 2, 1, 1, 1);


    /****** DESIGN SECTION ****************************/
    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(110, 30, 600, 150));
    QPixmap pix_home_title("images/titles/profile");
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);
    title_label->setPixmap( pix_home_title);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setAttribute(Qt::WA_TranslucentBackground);
    /*********END DESIGN SECTION*****************************************/

    this->setCentralWidget(centralWidget);
    //this->update();
    this->show();
}

void MenuGui::print_leaderboard(){
    std::vector<Profile> profile_list;
    char buffer[Constante::CHAR_SIZE];
    _client.checkLeaderboard(buffer);
    Parsing::profile_list_from_str(buffer, &profile_list);

    QWidget *centralWidget = new QWidget(this);
    QLabel *lbl = new QLabel(centralWidget);
    QMovie *mv = new QMovie("images/background/ciel.gif");
    mv->setScaledSize(QSize(800,600));
    lbl->setGeometry(QRect(0, 0, 800, 600));
    mv->start();
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    lbl->setMovie(mv);

    QWidget * verticalLayoutWidget = new QWidget(centralWidget);
    verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(80, 110, 620, 500));
    QVBoxLayout* verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout* verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    QHBoxLayout* horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    QTableWidget* tableWidget = new QTableWidget(verticalLayoutWidget);
    tableWidget->setColumnCount(2);
    tableWidget->setMaximumSize(QSize(300, 200));
    tableWidget->setRowCount(profile_list.size());

    horizontalLayout->addWidget(tableWidget);

    verticalLayout_2->addLayout(horizontalLayout);

    verticalLayout->addLayout(verticalLayout_2);

    QPushButton* back = new QPushButton((QString::fromStdString("Back")), verticalLayoutWidget);
    back->setMaximumSize(QSize(1000, 45));
    connect(back, &QPushButton::clicked, this,&MenuGui::main_m);

    verticalLayout->addWidget(back);

    QStringList m_TableHeader;
    m_TableHeader <<"Pseudo"<<"Score";
    tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setShowGrid(false);
    //tableWidget->setGeometry(QApplication::desktop()->screenGeometry());
    tableWidget->setGeometry(QRect(300, 300, 500, 300));
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setShowGrid(false);
    for (size_t i = 0; i < profile_list.size(); i++){
        tableWidget->setItem(i, 0, new QTableWidgetItem(profile_list[i].pseudo));
        int score = profile_list[i].score;
        char buff[20];
        sprintf(buff, "%d", score);
        tableWidget->setItem(i, 1, new QTableWidgetItem(buff));
    }

    /****** DESIGN SECTION ****************************/
    //this->setStyleSheet("background-color:rgb(148, 62, 8);");
    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(0, 30, 800, 150));
    QPixmap pix_home_title("images/titles/leaderboard");
    title_label->setPixmap( pix_home_title);
    title_label->setAlignment(Qt::AlignCenter);
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);
    /*********END DESIGN SECTION*****************************************/


    this->setCentralWidget(centralWidget);
    //this->update();
    this->show();
}

void MenuGui::level_menu(){
    QWidget *centralwidget = new QWidget(this);
    //exageration
    QLabel *lbl = new QLabel(centralwidget);
    QMovie *mv = new QMovie("images/background/ciel.gif");
    mv->setScaledSize(QSize(800,600));
    lbl->setGeometry(QRect(0, 0, 800, 600));
    mv->start();
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    lbl->setMovie(mv);


    QLabel *title_label = new QLabel("LEVEL EDITOR",centralwidget);
    title_label->setGeometry(QRect(90, 20, 631, 71));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setLineWidth(2);
    title_label->setTextFormat(Qt::PlainText);
    title_label->setAlignment(Qt::AlignCenter);
    QWidget *verticalLayoutWidget = new QWidget(centralwidget);
    verticalLayoutWidget->setGeometry(QRect(300, 190, 241, 301));
    QVBoxLayout *verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setContentsMargins(10, 0, 10, 0);

    QPushButton * button[4]; 
    int create = 0, ranking=1, my_levels = 2, back=3;
    std::string name[4] = {"Create level", "Level ranking", "My levels", "Back"};
    for( int i = 0; i < 4; i++){
        button[i] = new QPushButton(QString::fromStdString(name[i]),verticalLayoutWidget);
        button[i]->setMinimumSize(QSize(150, 45));
        button[i]->setMaximumSize(QSize(200, 45));
        verticalLayout->addWidget( button[i]);

    }

    connect(button[create], &QPushButton::clicked, this, [this](){
        Parsing::Level my_level;
        level_editor(my_level);
    });
    connect(button[ranking], &QPushButton::clicked, this,[this](){
        view_level(false);
    });
    connect(button[my_levels], &QPushButton::clicked, this, [this](){
        view_level(true);
    });
    connect(button[back], &QPushButton::clicked, this, &MenuGui::main_m);



    this->setCentralWidget(centralwidget);
    this->show();

}

void MenuGui::print_friends(){
	char buffer[Constante::CHAR_SIZE];
	std::vector<Profile> friendlist;
	_client.getFriendList(buffer);
	Parsing::profile_list_from_str(buffer, &friendlist);

    char buffer2[Constante::CHAR_SIZE];
	std::vector<Profile> requestlist;
	_client.getFriendRequest(buffer2);
	Parsing::profile_list_from_str(buffer2, &requestlist);

    QWidget *centralWidget = new QWidget(this);    
    QLabel *lbl = new QLabel(centralWidget);
    QMovie *mv = new QMovie("images/background/ciel.gif");
    mv->setScaledSize(QSize(800,600));
    lbl->setGeometry(QRect(0, 0, 800, 600));
    mv->start();
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    lbl->setMovie(mv);

    QWidget *gridLayoutWidget = new QWidget(centralWidget);
    gridLayoutWidget->setGeometry(QRect(60, 150, 800, 350));
    QGridLayout *gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    QListWidget *listWidget = new QListWidget(gridLayoutWidget);

    gridLayout->addWidget(listWidget, 1, 1, 1, 1, Qt::AlignHCenter);

    QPushButton* back = new QPushButton((QString::fromStdString("Back")), gridLayoutWidget);
    back->setMinimumSize(QSize(0, 50));
    back->setMaximumSize(QSize(16777215, 50));
    gridLayout->addWidget(back, 2, 0, 1, 3);
    connect(back, &QPushButton::clicked, this, &MenuGui::main_m);

    QTableWidget* tableWidget = new QTableWidget(gridLayoutWidget);
    tableWidget->setColumnCount(2);
    tableWidget->setMaximumSize(QSize(220, 190));
    tableWidget->setRowCount(friendlist.size());
    tableWidget->setMinimumSize(QSize(0, 500));

    gridLayout->addWidget(tableWidget, 1, 0, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);

    QLabel *label = new QLabel(QString::fromStdString("Friends"),gridLayoutWidget);
    label->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(label, 0, 0, 1, 1);

    QLabel *request_label = new QLabel(QString::fromStdString("Requests"),gridLayoutWidget);
    request_label->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(request_label, 0, 1, 1, 1);

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(7);
    QPushButton* add_button = new QPushButton((QString::fromStdString("Add Friend")), gridLayoutWidget);
    add_button->setMinimumSize(QSize(200, 50));
    add_button->setMaximumSize(QSize(200, 50));
    connect(add_button, &QPushButton::clicked, this, [this]() {
           add_del_friend(true);});

    QPushButton* del_button = new QPushButton((QString::fromStdString("Del Friend")), gridLayoutWidget);
    del_button->setMinimumSize(QSize(200, 50));
    del_button->setMaximumSize(QSize(200, 50));
    connect(del_button, &QPushButton::clicked, this, [this]() {
           add_del_friend(false);});

    QVBoxLayout *vLayout = new QVBoxLayout(gridLayoutWidget);
    gridLayout->addLayout(vLayout, 1, 2, 1, 1);
    vLayout->addWidget(add_button);
    vLayout->addWidget(del_button);

    gridLayout->addLayout(verticalLayout, 0, 2, 1, 1);

    QStringList m_TableHeader;
    m_TableHeader <<"Pseudo"<<"Score";
    tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setShowGrid(false);
    //tableWidget->setGeometry(QApplication::desktop()->screenGeometry());
    tableWidget->setGeometry(QRect(300, 150, 22, 190));
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setShowGrid(false);
    tableWidget->setMinimumSize(QSize(255, 500));
    for (size_t i = 0; i < friendlist.size(); i++){
        QTableWidgetItem *item;
        tableWidget->setItem(i, 0, new QTableWidgetItem(friendlist[i].pseudo));
        item = tableWidget->item(i, 0);
        item->setTextAlignment(Qt::AlignCenter);
        int score = friendlist[i].score;
        char buff[20];
        sprintf(buff, "%d", score);
        tableWidget->setItem(i, 1, new QTableWidgetItem(buff));
        item = tableWidget->item(i, 1);
        item->setTextAlignment(Qt::AlignCenter);
    }
    for (size_t i = 0; i < requestlist.size(); i++){
        listWidget->addItem(requestlist[i].pseudo);
        QListWidgetItem *item;
        item = listWidget->item(i);      
        item->setTextAlignment(Qt::AlignCenter);
    }
    QFont font;
    font.setPointSize(13);
    listWidget->setFont(font);
    connect(listWidget,&QAbstractItemView::doubleClicked,this,&MenuGui::request_list);

    /****** DESIGN SECTION ****************************/
    /*this->setStyleSheet("background-color:rgb(8, 82, 40);");

    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(110, 30, 600, 150));
    QPixmap pix_home_title("images/titles/friends");
    title_label->setPixmap( pix_home_title);
    title_label->setAlignment(Qt::AlignCenter);
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);*/
    /*********END DESIGN SECTION*****************************************/


    this->setCentralWidget(centralWidget);
    this->show();
}

void MenuGui::request_list(const QModelIndex &index){
    //this->setStyleSheet(QStringLiteral("background-color:grey;"));
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *pseudo;
    QLabel *score;
    QDialogButtonBox *action_button;
    QDialog *Dialog;

    char buffer2[Constante::CHAR_SIZE]; // Peut etre a modifier ...
	std::vector<Profile> requestlist;
	_client.getFriendRequest(buffer2);
	Parsing::profile_list_from_str(buffer2, &requestlist);

    Dialog = new QDialog;
    Dialog->setModal(true);
    Dialog->resize(400, 300);
    horizontalLayoutWidget = new QWidget(Dialog);
    horizontalLayoutWidget->setGeometry(QRect(38, 26, 351, 251));
    horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout = new QVBoxLayout();

    QFont font1;
    font1.setPointSize(13);

    char pseudo_char[25];
    char pseudo_char2[25];
    strcpy(pseudo_char2,requestlist.at(index.row()).pseudo); //to use later
    sprintf(pseudo_char,"Pseudo : %s",requestlist.at(index.row()).pseudo);
    pseudo = new QLabel(QString::fromStdString(pseudo_char),horizontalLayoutWidget);
    pseudo->setFont(font1);
    verticalLayout->addWidget(pseudo);


    char score_char[25];
    sprintf(score_char,"Score   : %d",requestlist.at(index.row()).score);
    score = new QLabel(QString::fromStdString(score_char),horizontalLayoutWidget);
    
    score->setFont(font1);
    verticalLayout->addWidget(score);


    horizontalLayout->addLayout(verticalLayout);

    action_button = new QDialogButtonBox(horizontalLayoutWidget);
    QFont font;
    font.setPointSize(12);
    action_button->setFont(font);
    action_button->setOrientation(Qt::Vertical);
    action_button->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::No|QDialogButtonBox::Yes);

    action_button->setCenterButtons(true);

    //connect(action_button, SIGNAL(rejected()), Dialog, SLOT(reject()));
    connect(action_button, SIGNAL(rejected()), Dialog, SLOT(reject()));
    connect(action_button, &QDialogButtonBox::accepted,this, [this,pseudo_char2,action_button]{
        char* pseudo2 = const_cast<char*>(pseudo_char2);
        _client.addFriend(pseudo2); 
        action_button->rejected();
        print_friends();
    });

    QPushButton *okButton =  action_button->button(QDialogButtonBox::No);
    connect(okButton, &QPushButton::clicked, this, [this,pseudo_char2, action_button]{
        char* pseudo2 = const_cast<char*>(pseudo_char2);
        _client.delFriendRequest(pseudo2); 
        action_button->rejected();
        print_friends();
    });

    horizontalLayout->addWidget(action_button);
    Dialog->show();
}


void MenuGui::add_del_friend(bool adding){
    this->setStyleSheet(QStringLiteral("background-color:grey;"));
    QDialog *Dialog = new QDialog(this);
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    Dialog->resize(400, 300);
    Dialog->setModal(true);
    verticalLayoutWidget = new QWidget(Dialog);
    verticalLayoutWidget->setGeometry(QRect(20, 20, 361, 261));
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    if(adding)
        label = new QLabel(QString::fromStdString("ADD YOUR FRIEND"),verticalLayoutWidget);
    else
        label = new QLabel(QString::fromStdString("DEL A FRIEND"),verticalLayoutWidget);

    QFont font;
    font.setPointSize(17);
    font.setBold(true);
    font.setItalic(false);
    font.setUnderline(false);
    font.setWeight(75);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    verticalLayout->addWidget(label);

    pseudo_line = new QLineEdit(verticalLayoutWidget);

    verticalLayout->addWidget(pseudo_line);

    error = new QLabel(QString::fromStdString(""),verticalLayoutWidget);
    QFont font1;
    font1.setPointSize(11);
    font1.setBold(true);
    font1.setWeight(75);
    error->setFont(font1);
    error->setStyleSheet(QString::fromUtf8("color: rgb(239, 41, 41);"));
    error->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(error);

    buttonBox = new QDialogButtonBox(verticalLayoutWidget);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);


    connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));
    if(adding)
        connect(buttonBox, &QDialogButtonBox::accepted,this, [this,Dialog]{
            verif_friend(Dialog);});
    else
        connect(buttonBox, &QDialogButtonBox::accepted,this, [this,Dialog]{
            verif_friend(Dialog,false);});

    verticalLayout->addWidget(buttonBox);
    Dialog->show();

}


void MenuGui::verif_friend(QDialog* dialog, bool adding){
    //Aissa: all error are already in screen ==> c'est pas écrit pour decorer :-)
    const char* pseudo = (pseudo_line->text()).toUtf8().constData(); 
    char* pseudo2 = const_cast<char*>(pseudo);

	int success; 
    if(adding){
        success = _client.sendFriendRequest(pseudo2);
        if(success==1)
        error->setText(QString::fromStdString(ALREADY_REQUESTED));
        else if (success==2)
            error->setText(QString::fromStdString(ALREADY_FRIENDS));
        else if(success==3)
            error->setText(QString::fromStdString(NO_USER_MSG));
        else if(success==4)
            error->setText(QString::fromStdString(YOURSEL_MSG));
        else
            dialog->hide();
    }
    else
        success = _client.delFriend(pseudo2);
        if(success==1)
        error->setText(QString::fromStdString(NOT_FRIENDS));
        else if (success==2)
            error->setText(QString::fromStdString(NO_USER_MSG));
        else if(success==3)
            error->setText(QString::fromStdString(YOURSEL_MSG));
        else{
            dialog->hide();
            print_friends();
        }


}


void MenuGui::lobby(std::string my_level, bool from_lead){
    QWidget *centralWidget =  new QWidget(this);

    this->setStyleSheet(QStringLiteral("background-color:white;"));

    QWidget *gridLayoutWidget = new QWidget(centralWidget);
    /*QLabel *lbl = new QLabel(centralWidget);
    QMovie *mv = new QMovie("images/background/ciel.gif");
    mv->setScaledSize(QSize(800,600));
    lbl->setGeometry(QRect(0, 0, 800, 600));
    mv->start();
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    lbl->setMovie(mv);*/

    gridLayoutWidget->setGeometry(QRect(20, 120, 771, 311));
    QGridLayout *gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    QComboBox *players_box  = new QComboBox(gridLayoutWidget);
    players_box->clear();
    players_box->addItem(QString::fromStdString("1"));
    players_box->addItem(QString::fromStdString("2"));

    QLabel *lives_label = new QLabel(QString::fromStdString("Lives : "),gridLayoutWidget);
    QLabel *dropRate_label  = new QLabel(QString::fromStdString("Drop rate : "),gridLayoutWidget);
    QSpinBox *lives_spin  = new QSpinBox(gridLayoutWidget);
    lives_spin->setMaximum(3); 
    lives_spin->setMinimum(1);

    QComboBox *Ally_shot_box  = new QComboBox(gridLayoutWidget);
    Ally_shot_box->clear();
    Ally_shot_box->addItem(QString::fromStdString("No"));
    Ally_shot_box->addItem(QString::fromStdString("Yes"));

    QLabel *allyShot_label = new QLabel(QString::fromStdString("Ally shot : "),gridLayoutWidget);;
    QLabel *playersLabel = new QLabel(QString::fromStdString("Player's number : "),gridLayoutWidget);
    QSpinBox *droprate_spin = new QSpinBox(gridLayoutWidget);
    droprate_spin->setMaximum(100); 
    droprate_spin->setSuffix(" %"); //fait pas att à la surbrillance : juste une fail
    QLabel *difficulty_label  = new QLabel(QString::fromStdString("Difficulty"),gridLayoutWidget);

    QLabel *space_label = new QLabel(gridLayoutWidget);

    QComboBox *difficulty_box =  new QComboBox(gridLayoutWidget);
    difficulty_box->clear();
    difficulty_box->addItem(QString::fromStdString("Easy"));
    difficulty_box->addItem(QString::fromStdString("Normal"));
    difficulty_box->addItem(QString::fromStdString("Hard"));

    QWidget *horizontalLayoutWidget = new QWidget(centralWidget);
    horizontalLayoutWidget->setGeometry(QRect(60, 450, 681, 80));
    QHBoxLayout *horizontalLayout  = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setContentsMargins(3, 0, 3, 0);
    horizontalLayout->setSpacing(36);
    
    QPushButton *play_button = new QPushButton(QString::fromStdString("Play"),horizontalLayoutWidget);;
    play_button->setMinimumSize(QSize(300, 45));
    play_button->setMaximumSize(QSize(300, 45));
    QPushButton *back_button = new QPushButton(QString::fromStdString("Back"),horizontalLayoutWidget);
    back_button->setMinimumSize(QSize(300, 45));
    back_button->setMaximumSize(QSize(300, 45));

    //players label
    QLabel *player1Title_label = new QLabel(QString::fromStdString("Player 1 :"),gridLayoutWidget);;
    char pseudo[15];
    _client.get_pseudo(pseudo);
    QLabel *player1Name = new QLabel(pseudo,gridLayoutWidget);

    //hlayout adding
    horizontalLayout->addWidget(play_button);
    horizontalLayout->addWidget(back_button);

    //operations
    gridLayout->addWidget(players_box, 0, 1, 1, 1);
    gridLayout->addWidget(lives_label, 4, 3, 1, 1);
    gridLayout->addWidget(dropRate_label, 4, 0, 1, 1);
    gridLayout->addWidget(lives_spin, 4, 4, 1, 1); 
    gridLayout->addWidget(Ally_shot_box, 0, 4, 1, 1);
    gridLayout->addWidget(allyShot_label, 0, 3, 1, 1);
    gridLayout->addWidget(playersLabel, 0, 0, 1, 1);
    gridLayout->addWidget(droprate_spin, 4, 1, 1, 1);
    gridLayout->addWidget(difficulty_label, 2, 3, 1, 1);
    gridLayout->addWidget(difficulty_box, 2, 4, 1, 1);
    gridLayout->addWidget(space_label, 2, 2, 1, 1); //invisible
    gridLayout->addWidget(player1Title_label, 2, 0, 1, 1);
    gridLayout->addWidget(player1Name, 2, 1, 1, 1);
    //connections
    connect(back_button, &QPushButton::clicked, this,[this, my_level, from_lead](){
        if(my_level=="0")
            main_m();
        else if(from_lead)
            view_level(!from_lead);
        else
            view_level(from_lead);
    });
    connect(play_button, &QPushButton::clicked, this,[this, players_box, lives_spin, Ally_shot_box,droprate_spin, difficulty_box, my_level,from_lead](){
        int drop_rate = droprate_spin->value() , lives = lives_spin->value(); 
        int players = (players_box->currentText()).toInt();
        std::string difficulty = (difficulty_box->currentText()).toStdString();
        bool ally_shot = ((Ally_shot_box->currentText()).toStdString()).compare("Yes") == 0;
        launch_game(players, drop_rate, lives, difficulty,ally_shot, my_level, from_lead);
       
    });

    /****** DESIGN SECTION ***********************************************/
    //this->setStyleSheet("background-color:black;");
    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(110, 30, 600, 150));
    QPixmap pix_home_title("images/titles/lobby");
    title_label->setPixmap( pix_home_title);
    title_label->setAlignment(Qt::AlignCenter);
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);
    /****************END DESIGN SECTION*************************/
    
    this->setCentralWidget(centralWidget);
    this->show();

}

/*void MenuGui::launch_level(std::string my_level, bool from_lead){
    QDialog * Dialog = new QDialog(this);
    Dialog->setModal(true);
    Dialog->resize(741, 527);
    QLabel *player_label;
    QComboBox *player_box;
    QLabel *name_label;
    QLabel *pswd_label;
    QLabel *title_label;
    QLineEdit *username_line;
    QLineEdit *pass_line;
    QPushButton *play_button;
    QPushButton *cancel_button;
    player_label = new QLabel("NB PLAYER : ",Dialog);
    player_label->setGeometry(QRect(70, 150, 85, 25));
    player_box = new QComboBox(Dialog);
    player_box->setGeometry(QRect(210, 150, 378, 25));
    player_box->clear();
    player_box->addItem("1 player");
    player_box->addItem("2 players");
    name_label = new QLabel("USERNAME : ",Dialog);
    name_label->setGeometry(QRect(70, 260, 86, 17));
    name_label->hide();
    pswd_label = new QLabel("PASSWORD : ",Dialog);
    pswd_label->setGeometry(QRect(70, 326, 91, 31));
    pswd_label->hide();
    title_label = new QLabel("RUN LEVEL",Dialog);
    title_label->setGeometry(QRect(30, 20, 681, 61));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setAlignment(Qt::AlignCenter);
    username_line = new QLineEdit(Dialog);
    username_line->setGeometry(QRect(210, 260, 371, 30));
    username_line->hide();
    pass_line = new QLineEdit(Dialog);
    pass_line->setGeometry(QRect(210, 330, 371, 30));
    pass_line->hide();
    play_button = new QPushButton("PLAY",Dialog);
    play_button->setGeometry(QRect(150, 430, 100, 45));
    cancel_button = new QPushButton("CANCEL",Dialog);
    cancel_button->setGeometry(QRect(490, 430, 100, 45));
    connect(player_box, QOverload<int>::of(&QComboBox::currentIndexChanged),[this,player_box, username_line,pass_line,pswd_label, name_label](int idx){
         if(idx==1){
            username_line->show();
            pass_line->show();
            pswd_label->show();
            name_label->show();
        }
        else{
            username_line->hide();
            pass_line->hide();
            pswd_label->hide();
            name_label->hide();
        }
    });


    connect(play_button, &QPushButton::clicked, this,[this,player_box,username_line,pass_line, my_level](){
        int nb_player = player_box->currentIndex() + 1;
        char y_pseudo[Constante::SIZE_PSEUDO]; 
        _client.get_pseudo(y_pseudo);
        if(nb_player == 2){
            std::string pseudo = (username_line->text()).toUtf8().constData();
            std::string pswd = (pass_line->text()).toUtf8().constData();
            std::cout <<"Player = " << pseudo<<std::endl;
            bool success =0;
            if(pseudo.compare(std::string(y_pseudo)) != 0)
                success= _client.signIn(pseudo.c_str(), pswd.c_str(), false);
            if(success){
                //TODO :LAUNCH GAME 
            }

        }
        else{
            std::cout << "voila le level = " << my_level<< std::endl;
            _client.playLevel(my_level);
            this->hide();
            launch_game();
            this->show();
            std::cout << "salut bg je suis de retoure pour te jouer de mauvais tour";
        }


    });
    connect(cancel_button, &QPushButton::clicked, this,[this, from_lead, Dialog](){
        Dialog->hide();
        if(from_lead)
            view_level(false);
        view_level(true);
    });
    

    Dialog->show();

}
*/

void MenuGui::launch_game(int players, int drop_rate, int lives, std::string difficulty, bool ally_shot, std::string my_level, bool from_lead){
    Parsing::Game_settings setting; char my_pseudo[Constante::SIZE_PSEUDO];
    _client.get_pseudo(my_pseudo);
    strcpy(setting.difficulty_str, difficulty.c_str());
    strcpy(setting.pseudo_hote,my_pseudo);
    setting.diff = !strcmp(setting.difficulty_str,"easy")? easy: !strcmp(setting.difficulty_str,"medium")? medium :hard;
    setting.drop_rate = drop_rate;
    setting.nb_lives = lives;
    setting.ally_shot = ally_shot;
    setting.nb_player = players;

    if(players==2){
        QDialogButtonBox *buttonBox;
        QLabel *label;
        QLabel *pseudo;
        QLabel *pswd;
        QLineEdit *pseudoLine;
        QLineEdit *pswdLine;
        QDialog *Dialog = new QDialog(this);
        Dialog->resize(400, 300);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel("CONNEXION",Dialog);
        label->setGeometry(QRect(30, 20, 331, 31));
        label->setFrameShape(QFrame::WinPanel);
        label->setAlignment(Qt::AlignCenter);
        pseudo = new QLabel("Username: ",Dialog);
        pseudo->setGeometry(QRect(25, 100, 91, 31));
        pswd = new QLabel("Password : ",Dialog);
        pswd->setGeometry(QRect(25, 170, 81, 31));
        pseudoLine = new QLineEdit(Dialog);
        pseudoLine->setGeometry(QRect(125, 100, 231, 25));
        pswdLine = new QLineEdit(Dialog);
        pswdLine->setGeometry(QRect(125, 170, 231, 25));


        //connection 
        connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));
        connect(buttonBox, &QDialogButtonBox::accepted,this, [this,buttonBox,pseudoLine,pswdLine,setting,my_level](){
            Parsing::Game_settings& sett_ref = const_cast<Parsing::Game_settings&>(setting);
            
            std::string pseudo = (pseudoLine->text()).toUtf8().constData();
            std::string pswd = (pswdLine->text()).toUtf8().constData();
            char y_pseudo[Constante::SIZE_PSEUDO]; bool success =0;
            _client.get_pseudo(y_pseudo);
            if(pseudo.compare(std::string(y_pseudo)) != 0)
                success= _client.signIn(pseudo.c_str(), pswd.c_str(), false);
                
            if(success){
                char game_sett_char[Constante::CHAR_SIZE];
                strcpy(sett_ref.pseudo_hote,y_pseudo);
                Parsing::create_game_to_str(game_sett_char,&sett_ref);
                if(my_level=="0")
                    _client.createGame(game_sett_char);
                else
                    _client.playLevel(my_level,game_sett_char);
                std::cout << "level a jouer = "<<my_level<<std::endl;
                std::cout << "settings lobby  = "<<game_sett_char<<std::endl;
                launch_game();
                buttonBox->rejected();
                
            }
            
    });
        Dialog->show();

    }
    else{ // joueur solo
        char game_sett_char[Constante::CHAR_SIZE];
        Parsing::create_game_to_str(game_sett_char,&setting);
        std::cout << "voila le str = " << game_sett_char<< std::endl;
        if(my_level=="0")
            _client.createGame(game_sett_char);
        else{
            _client.playLevel(my_level,game_sett_char);
            std::cout << "level a jouer = "<<my_level<<std::endl;
        }
        std::cout << "settings lobby  = "<<game_sett_char<<std::endl;
        this->hide();
        launch_game();
        this->show();
        std::cout << "salut bg je suis de retoure pour te jouer de mauvais tour";
    }
}


void MenuGui::level_editor(Parsing::Level my_level){

	this->setStyleSheet(QStringLiteral("background-color:white;"));
    this->setFixedSize(1500,800);


    QWidget *centralwidget = new QWidget(this);

    Frame *game_zone = new Frame(centralwidget);
    game_zone->setGeometry(QRect(100, 150, 1000, 480));;
    game_zone->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));
    game_zone->setFrameShape(QFrame::WinPanel);
    game_zone->setFrameShadow(QFrame::Plain);
    game_zone->setLineWidth(3);
    
    QLabel *lbl = new QLabel(game_zone);
    lbl->setGeometry(QRect(0, 0, 1000, 480));
    QMovie *mv = new QMovie("images/background/ciel.gif");
    mv->setScaledSize(lbl->size());
    mv->start();
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    lbl->setMovie(mv);

    QLabel *title_label = new QLabel(centralwidget);
    title_label->setGeometry(QRect(400, 10, 621, 81));
    QPixmap pix_title("images/titles/levelEditor");
    pix_title = pix_title.scaled(title_label->size(),Qt::KeepAspectRatio);
    title_label->setPixmap( pix_title);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setAttribute(Qt::WA_TranslucentBackground);

    /*ClickableLabel *dragTest = new ClickableLabel(0,0,game_zone); //index, type
    //dragTest->setGeometry(QRect(0, 0, 100, 100));

    dragTest->setPixmap(QPixmap("images/custom/e1"));
    dragTest->move(10, 10);
    dragTest->setAttribute(Qt::WA_DeleteOnClose);
    game_zone->add_enemy(dragTest);
    connect(dragTest, &ClickableLabel::clicked, this,[this](){
        std::cout << "on m'appelle l'ovni"<<std::endl;
    });
    */
    QWidget *verticalLayoutWidget = new QWidget(centralwidget);
    verticalLayoutWidget->setGeometry(QRect(1260, 150, 160, 591));
    QVBoxLayout *verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setContentsMargins(10, 0, 10, 0);

    int enemy=0, obs=1, player=2, save=3, cancel =4;
    QPixmap pix[] = {QPixmap("images/custom/e1"),QPixmap("images/custom/o2"),QPixmap("images/custom/p1"),QPixmap("images/custom/save"),QPixmap("images/custom/cancel")};
    QIcon icon[5];
    QPushButton * button[5];
    for (int i = 0; i < 5; ++i){
        icon[i] = QIcon(pix[i]);
        button[i] = new QPushButton(verticalLayoutWidget);
        button[i]->setMinimumSize(QSize(100, 100));
        button[i]->setMaximumSize(QSize(100, 100));
        button[i]->setIcon(icon[i]);
        button[i]->setIconSize(QSize(100, 100));
        button[i]->setFlat(true);
        verticalLayout->addWidget(button[i]);
    }
    QWidget *horizontalLayoutWidget = new QWidget(centralwidget);
    horizontalLayoutWidget->setGeometry(QRect(10, 649, 1231, 91));
    QHBoxLayout *horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *tick_label = new QLabel("Tick : ",horizontalLayoutWidget);
    tick_label->setMinimumSize(QSize(80, 0));
    //tick_label->setFrameShape(QFrame::WinPanel);
    //tick_label->setLineWidth(3);
    tick_label->setTextFormat(Qt::RichText);
    tick_label->setAlignment(Qt::AlignCenter);
    tick_label->setStyleSheet("QLabel { background-color : black; color : white; }");
    tick_label->setAttribute(Qt::WA_TranslucentBackground);
    QSlider *tick_slider = new QSlider(horizontalLayoutWidget);
    tick_slider->setMaximum(20);
    tick_slider->setPageStep(1);
    tick_slider->setOrientation(Qt::Horizontal);
    tick_slider->setTickPosition(QSlider::TicksBothSides);
    tick_slider->setTickInterval(150);
    tick_slider->setMaximum(3000);
    tick_slider->setSingleStep(150);
    tick_slider->setPageStep(300);
    tick_slider->setStyleSheet("color: black; background-color: white");
    tick_slider->setAttribute(Qt::WA_TranslucentBackground);
    QLCDNumber *tick_lcd = new QLCDNumber(horizontalLayoutWidget);
    tick_lcd->setFrameShape(QFrame::WinPanel);
    tick_lcd->setFrameShadow(QFrame::Plain);
    tick_lcd->setLineWidth(3);
    tick_lcd->setDigitCount(4);
    tick_lcd->setStyleSheet("color: black; background-color: white");

    horizontalLayout->addWidget(tick_label);
    horizontalLayout->addWidget(tick_slider);
    horizontalLayout->addWidget(tick_lcd);

    //placer sur la frame:
    for(int i = 0; i < my_level.enemy_list.size(); i++){
        ClickableLabel * e = new ClickableLabel(i,0,game_zone);
        QPixmap pix("images/custom/e1");
        pix = pix.scaled(QSize(button_size,button_size));
        e->setPixmap(pix);
        e->setGeometry(QRect(X_MIN + my_level.enemy_list[i].x , my_level.enemy_list[i].y, button_size, button_size));
        game_zone->add_enemy(e);
        if(my_level.enemy_list[i].tick != tick_lcd->intValue())
           e->hide();

        connect(e, &ClickableLabel::clicked, this,[this, my_level,i](){
            custom_enemy(my_level, i);});

        connect(e, &ClickableLabel::changedPos, this,[this, my_level,i, game_zone](){
            auto lev = my_level;
            lev.enemy_list[i].x = (game_zone->get_enemy(i))->posx();
            lev.enemy_list[i].y = (game_zone->get_enemy(i))->posy();

            level_editor(lev);

        });
    }

    for(int i = 0; i < my_level.obs_list.size(); i++){
        ClickableLabel * e = new ClickableLabel(i,1,game_zone);
        QPixmap pix("images/custom/o2");
        pix = pix.scaled(QSize(button_size,button_size));
        e->setPixmap(pix);
        e->setGeometry(QRect(X_MIN + my_level.obs_list[i].x ,  my_level.obs_list[i].y, button_size, button_size));
        game_zone->add_obs(e);
        if(my_level.obs_list[i].tick != tick_lcd->intValue())
           e->hide();

        connect(e, &ClickableLabel::clicked, this,[this, my_level,i](){
            custom_obstacle(my_level, i);
        });

        connect(e, &ClickableLabel::changedPos, this,[this, my_level,i, game_zone](){
            std::cout << "je fonctionne avant "<<std::endl;
            auto lev = my_level;
            lev.obs_list[i].x = (game_zone->get_obs(i))->posx();
            lev.obs_list[i].y = (game_zone->get_obs(i))->posy();
            level_editor(lev);
            

        });
    }

    //connect section
    connect(button[cancel], &QPushButton::clicked, this,[this](){
        this->setFixedSize(800,600);
        level_menu();
    });
    connect(button[save], &QPushButton::clicked, this,[this, my_level](){
            save_level(my_level);
        });
    connect(button[enemy], &QPushButton::clicked, this,[this, my_level](){
            Parsing::Enemy_template newE{}; Parsing::Level level_copy = my_level; //probleme de constance
            level_copy.enemy_list.push_back(newE);
            custom_enemy(level_copy, level_copy.enemy_list.size()-1);
        });
    connect(button[obs], &QPushButton::clicked, this,[this, my_level](){
            Parsing::Obstacle_template newO{}; Parsing::Level level_copy = my_level; //probleme de constance
            level_copy.obs_list.push_back(newO);
            custom_obstacle(level_copy, level_copy.obs_list.size()-1);
        });
    connect(button[player], &QPushButton::clicked, this,[this, my_level](){
            Parsing::Level level_copy = my_level; //probleme de constance
            custom_player(level_copy);
        });
    connect(tick_slider, SIGNAL(valueChanged(int)),tick_lcd, SLOT(display(int)));
    connect(tick_slider, &QSlider::valueChanged,this, [this,tick_lcd, my_level, game_zone](){
        for(int i = 0; i < my_level.enemy_list.size(); i++){
            if(my_level.enemy_list[i].tick != tick_lcd->intValue()){
               game_zone->get_enemy(i)->hide();
            }
            else{
                game_zone->get_enemy(i)->show();
            }
        }
        for(int i = 0; i < my_level.obs_list.size(); i++){
            if(my_level.obs_list[i].tick != tick_lcd->intValue()){
                game_zone->get_obs(i)->hide();
            }
            else{
                game_zone->get_obs(i)->show();
            }
        }
       
    });

    this->setCentralWidget(centralwidget);
    this->show();
}

void MenuGui::save_level(Parsing::Level my_level){
	 this->setStyleSheet(QStringLiteral("background-color:white;"));
    QDialog * Dialog = new QDialog(this);
    Dialog->resize(452, 345);
    Dialog->setModal(true);

    QLabel *title_label = new QLabel("SAVE YOUR LEVEL",Dialog);
    title_label->setGeometry(QRect(50, 10, 350, 71));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setAlignment(Qt::AlignCenter);

    QWidget *horizontalLayoutWidget = new QWidget(Dialog);
    horizontalLayoutWidget->setGeometry(QRect(30, 250, 381, 80));
    QHBoxLayout *horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    QPushButton *ok = new QPushButton("OK",horizontalLayoutWidget);
    ok->setMinimumSize(QSize(100, 45));
    ok->setMaximumSize(QSize(100, 45));

    QPushButton *cancel = new QPushButton("Cancel",horizontalLayoutWidget);
    cancel->setMinimumSize(QSize(100, 45));
    cancel->setMaximumSize(QSize(100, 45));

    QWidget *horizontalLayoutWidget_2  = new QWidget(Dialog);
    horizontalLayoutWidget_2->setGeometry(QRect(40, 120, 361, 81));
    QHBoxLayout *horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
    QLabel *name_label = new QLabel("Name : ",horizontalLayoutWidget_2);
    QLineEdit *name_edit = new QLineEdit(horizontalLayoutWidget_2);
    name_edit->setMaxLength(15);
    horizontalLayout_2->addWidget(name_label);
    horizontalLayout_2->addWidget(name_edit);

    horizontalLayout->addWidget(ok);
    horizontalLayout->addWidget(cancel);

    connect(ok, &QPushButton::clicked, this, [this, Dialog, my_level, name_edit](){
        std::string level_name = (name_edit->text()).toUtf8().constData();
        Parsing::Level copy_level = my_level;
        std::string string_level = Parsing::level_to_str(&copy_level, level_name);
        
        _client.createLevel(string_level.c_str());
        Dialog->hide();
        this->setFixedSize(800,600);
        level_menu();
    });
    connect(cancel, &QPushButton::clicked, this, [this, Dialog](){
        Dialog->hide();
        level_menu();
    });

    Dialog->show();


}

void MenuGui::custom_enemy(Parsing::Level my_level, int idx){
	this->setStyleSheet(QStringLiteral("background-color:white;"));
    QDialog * Dialog = new QDialog(this);
    Dialog->resize(859, 665);
    Dialog->setModal(true);

    QLabel * title_label = new QLabel("CUSTOM ENEMY", Dialog);
    title_label->setGeometry(QRect(70, 20, 701, 71));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setAlignment(Qt::AlignCenter);

    /*************SPIN AND THEIR LEGENDE ZONE********************/
    QWidget *formLayoutWidget = new QWidget(Dialog);
    formLayoutWidget->setGeometry(QRect(590, 160, 258, 275));
     QFormLayout *formLayout = new QFormLayout(formLayoutWidget);
    int position = 0, hp=1, tick=2, damage=3; 
    std::string legende[] = {"POSITION :","HP :","TICK :","DAMAGE :"};
    QLabel *label[4];
    int spin_value[4]; my_level.enemy_list[idx].get_values(spin_value);
    QSpinBox * spin_box[4];
    for (int i = 0; i < 4; ++i){
        //legende
        label[i] = new QLabel(legende[i].c_str(), formLayoutWidget);
        formLayout->setWidget(i, QFormLayout::LabelRole, label[i] );
        label[i]->setMinimumSize(QSize(100, 45));
        label[i]->setMaximumSize(QSize(100, 45));
        label[i]->setAlignment(Qt::AlignCenter);

        //value
        spin_box[i] = new QSpinBox(formLayoutWidget);
        spin_box[i]->setMinimumSize(QSize(100, 45));
        spin_box[i]->setMaximumSize(QSize(100, 45));
        spin_box[i]->setValue(spin_value[i]);
        formLayout->setWidget(i, QFormLayout::FieldRole, spin_box[i]);
    }
    spin_box[position]->setMaximum(X_MAX);
    spin_box[position]->setValue(spin_value[position]);
    spin_box[tick]->setMaximum(3000);
    spin_box[tick]->setSingleStep(150);
    spin_box[tick]->setValue(spin_value[tick]);
    spin_box[tick]->findChild<QLineEdit*>()->setReadOnly(true);

    /*************BUTTON_ZONE********************/
    QWidget *horizontalLayoutWidget = new QWidget(Dialog);
    horizontalLayoutWidget->setGeometry(QRect(40, 540, 771, 80));
    QHBoxLayout* horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    int ok = 0, del=1;
    std::string button_name[] = {"OK","DELETE"};
    QPushButton * button[2];
    for (int i = 0; i < 2; ++i){
        button[i] = new QPushButton(button_name[i].c_str(), horizontalLayoutWidget);
        button[i]->setMinimumSize(QSize(100, 45));
        button[i]->setMaximumSize(QSize(100, 45));
        horizontalLayout->addWidget( button[i]);
    }

    /*************SKIN_ZONE********************/
    QWidget * widget = new QWidget(Dialog);
    widget->setGeometry(QRect(60, 150, 181, 281));
    QVBoxLayout *verticalLayout = new QVBoxLayout(widget);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    QLabel * skin_label = new QLabel("SKIN", widget);
    verticalLayout->addWidget(skin_label);

    std::string skin_name[] = {"skin1","skin2", "skin3"};
    QRadioButton * skin[3];

    for (int i = 0; i < 3; ++i){
        skin[i] = new QRadioButton(skin_name[i].c_str(), widget);
        skin[i]->setMinimumSize(QSize(100, 45));
        skin[i]->setMaximumSize(QSize(100, 45));
        if(i == my_level.enemy_list[idx].skin)
             skin[i]->setChecked(true);
        verticalLayout->addWidget(skin[i]);
    }


    /*************BONUS_ZONE********************/
    QWidget *widget1 = new QWidget(Dialog);
    widget1->setGeometry(QRect(330, 140, 191, 291));
    QVBoxLayout *verticalLayout_2 = new QVBoxLayout(widget1);
    verticalLayout_2->setContentsMargins(0, 0, 0, 0);

    QLabel *Bonus_label = new QLabel("BONUS", widget1);
    verticalLayout_2->addWidget(Bonus_label);

    std::string bonus_name[] = {"Damage","Triple Shot", "Life Steal", "Minigun"};
    QRadioButton * bonus[4];

    for (int i = 0; i < 4; ++i){
        bonus[i] = new QRadioButton(bonus_name[i].c_str(), widget1);
        if(i == my_level.enemy_list[idx].bonus)
            bonus[i]->setChecked(true);
        verticalLayout_2->addWidget(bonus[i]);
    }


    /*************SAME SIZE LABEL********************/
    QLabel * label_legend[] ={skin_label,Bonus_label};
    for(auto lbl : label_legend){
        lbl->setMinimumSize(QSize(100, 45));
        lbl->setMaximumSize(QSize(100, 45));
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setFrameShape(QFrame::WinPanel);
        lbl->setLineWidth(3);
    }

    /***************CONNECTION********************/
    connect(button[ok], &QPushButton::clicked, this, [this, my_level,Dialog, spin_box, idx, bonus, skin](){
        Parsing::Level copy_level = my_level;
        copy_level.enemy_list[idx].x = spin_box[0]->value();
        copy_level.enemy_list[idx].hp = spin_box[1]->value();
        copy_level.enemy_list[idx].tick = spin_box[2]->value();
        copy_level.enemy_list[idx].damage = spin_box[3]->value();
        for (int i = 0; i < 4; ++i){
            if(bonus[i]->isChecked())
                copy_level.enemy_list[idx].bonus = i;
        }

        for (int i = 0; i < 3; ++i){
            if(skin[i]->isChecked())
                copy_level.enemy_list[idx].skin = i;
        }

        Dialog->hide();
        level_editor(copy_level);
    });
    connect(button[del], &QPushButton::clicked, this, [this, my_level,idx, Dialog](){
        Dialog->hide();
        Parsing::Level copy_level = my_level;
        copy_level.enemy_list.erase(copy_level.enemy_list.begin()+idx);
        level_editor(copy_level);
    });

    Dialog->show();
}

void MenuGui::custom_obstacle(Parsing::Level my_level, int idx){
	this->setStyleSheet(QStringLiteral("background-color:white;"));
    QDialog * Dialog = new QDialog(this);
    Dialog->resize(859, 665);
    Dialog->setModal(true);

    QLabel * title_label = new QLabel("CUSTOM OBSTACLE", Dialog);
    title_label->setGeometry(QRect(70, 20, 701, 71));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setAlignment(Qt::AlignCenter);

    /*************SPIN AND THEIR LEGENDE ZONE********************/
    QWidget *formLayoutWidget = new QWidget(Dialog);
    formLayoutWidget->setGeometry(QRect(590, 160, 258, 275));
     QFormLayout *formLayout = new QFormLayout(formLayoutWidget);
    int position = 0, hp=1, tick=2, damage=3; 
    std::string legende[] = {"POSITION :","HP :","TICK :","DAMAGE :"};
    QLabel *label[4];
    int spin_value[4]; my_level.obs_list[idx].get_values(spin_value);
    QSpinBox * spin_box[4];
    for (int i = 0; i < 4; ++i){
        //legende
        label[i] = new QLabel(legende[i].c_str(), formLayoutWidget);
        formLayout->setWidget(i, QFormLayout::LabelRole, label[i] );
        label[i]->setMinimumSize(QSize(100, 45));
        label[i]->setMaximumSize(QSize(100, 45));
        label[i]->setAlignment(Qt::AlignCenter);

        //value
        spin_box[i] = new QSpinBox(formLayoutWidget);
        spin_box[i]->setMinimumSize(QSize(100, 45));
        spin_box[i]->setMaximumSize(QSize(100, 45));
        spin_box[i]->setValue(spin_value[i]);
        formLayout->setWidget(i, QFormLayout::FieldRole, spin_box[i]);
    }
    spin_box[position]->setMaximum(X_MAX);
    spin_box[position]->setValue(spin_value[position]);
    spin_box[tick]->setMaximum(3000);
    spin_box[tick]->setSingleStep(150);
    spin_box[tick]->setValue(spin_value[tick]);
    spin_box[tick]->findChild<QLineEdit*>()->setReadOnly(true);

    /*************BUTTON_ZONE********************/
    QWidget *horizontalLayoutWidget = new QWidget(Dialog);
    horizontalLayoutWidget->setGeometry(QRect(40, 540, 771, 80));
    QHBoxLayout* horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    int ok = 0, del=1;
    std::string button_name[] = {"OK","DELETE"};
    QPushButton * button[2];
    for (int i = 0; i < 2; ++i){
        button[i] = new QPushButton(button_name[i].c_str(), horizontalLayoutWidget);
        button[i]->setMinimumSize(QSize(100, 45));
        button[i]->setMaximumSize(QSize(100, 45));
        horizontalLayout->addWidget( button[i]);
    }

    /*************SKIN_ZONE********************/
    QWidget * widget = new QWidget(Dialog);
    widget->setGeometry(QRect(60, 150, 181, 281));
    QVBoxLayout *verticalLayout = new QVBoxLayout(widget);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    QLabel * skin_label = new QLabel("SKIN", widget);
    verticalLayout->addWidget(skin_label);

    std::string skin_name[] = {"skin1","skin2", "skin3"};
    QRadioButton * skin[3];

    for (int i = 0; i < 3; ++i){
        skin[i] = new QRadioButton(skin_name[i].c_str(), widget);
        skin[i]->setMinimumSize(QSize(100, 45));
        skin[i]->setMaximumSize(QSize(100, 45));
        if(i == my_level.obs_list[idx].skin)
             skin[i]->setChecked(true);
        verticalLayout->addWidget(skin[i]);
    }

    /*************SKIN LABEL********************/
    skin_label->setMinimumSize(QSize(100, 45));
    skin_label->setMaximumSize(QSize(100, 45));
    skin_label->setAlignment(Qt::AlignCenter);
    skin_label->setFrameShape(QFrame::WinPanel);
    skin_label->setLineWidth(3);

    /***************CONNECTION********************/
    connect(button[ok], &QPushButton::clicked, this, [this, my_level,Dialog, spin_box, idx,skin](){
        Parsing::Level copy_level = my_level;
        //copy_level.obs_list[idx].x = spin_box[0]->value();
        copy_level.obs_list[idx].hp = spin_box[1]->value();
        copy_level.obs_list[idx].tick = spin_box[2]->value();
        copy_level.obs_list[idx].damage = spin_box[3]->value();

        for (int i = 0; i < 3; ++i){
            if(skin[i]->isChecked())
                copy_level.obs_list[idx].skin = i;
        }

        Dialog->hide();
        level_editor(copy_level);
    });
    connect(button[del], &QPushButton::clicked, this, [this, my_level,idx, Dialog](){
        Dialog->hide();
        Parsing::Level copy_level = my_level;
        copy_level.obs_list.erase(copy_level.obs_list.begin()+idx);
        level_editor(copy_level);
    });

    Dialog->show();
}

void MenuGui::custom_player(Parsing::Level my_level){
	this->setStyleSheet(QStringLiteral("background-color:white;"));
    QDialog * Dialog = new QDialog(this);
    Dialog->resize(859, 665);
    Dialog->setModal(true);

    QLabel * title_label = new QLabel("CUSTOM PLAYER", Dialog);
    title_label->setGeometry(QRect(70, 20, 701, 71));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setAlignment(Qt::AlignCenter);

    /*************SPIN AND THEIR LEGENDE ZONE********************/
    QWidget *formLayoutWidget = new QWidget(Dialog);
    formLayoutWidget->setGeometry(QRect(590, 160, 258, 275));
    QFormLayout *formLayout = new QFormLayout(formLayoutWidget);
    int hp=0, damage=1, drop=2; 
    std::string legende[] = {"HP :","DAMAGE :"};
    QLabel *label[2];
    int spin_value[2] = {my_level.player.hp, my_level.player.damage};
    QSpinBox * spin_box[2];
    for (int i = 0; i < 2; ++i){
        //legende
        label[i] = new QLabel(legende[i].c_str(), formLayoutWidget);
        formLayout->setWidget(i, QFormLayout::LabelRole, label[i] );
        label[i]->setMinimumSize(QSize(100, 45));
        label[i]->setMaximumSize(QSize(100, 45));
        label[i]->setAlignment(Qt::AlignCenter);

        //value
        spin_box[i] = new QSpinBox(formLayoutWidget);
        spin_box[i]->setMinimumSize(QSize(100, 45));
        spin_box[i]->setMaximumSize(QSize(100, 45));
        spin_box[i]->setMaximum(100);
        spin_box[i]->setValue(spin_value[i]);
        formLayout->setWidget(i, QFormLayout::FieldRole, spin_box[i]);
    }

    QComboBox *speed_box = new QComboBox(formLayoutWidget);
    speed_box->setMinimumSize(QSize(100, 45));
    speed_box->setMaximumSize(QSize(100, 45));
    formLayout->setWidget(3, QFormLayout::FieldRole, speed_box);
    speed_box->clear();
    QLabel *speed_label = new QLabel("SPEED :");
    formLayout->setWidget(3, QFormLayout::LabelRole, speed_label );
    speed_label->setMinimumSize(QSize(100, 45));
    speed_label->setMaximumSize(QSize(100, 45));
    speed_label->setAlignment(Qt::AlignCenter);
    std::string box_value[] = {"SLUG", "TURTLE", "HUMAN", "HORSE","CHEETAHS"};
    for(auto val :box_value){
        speed_box->addItem(QString::fromStdString(val));
    }
    speed_box->setCurrentIndex(my_level.player.speed);
    /*************BUTTON_ZONE********************/
    QWidget *horizontalLayoutWidget = new QWidget(Dialog);
    horizontalLayoutWidget->setGeometry(QRect(40, 540, 771, 80));
    QHBoxLayout* horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    int ok = 0, cancel=1;
    std::string button_name[] = {"OK","CANCEL"};
    QPushButton * button[2];
    for (int i = 0; i < 2; ++i){
        button[i] = new QPushButton(button_name[i].c_str(), horizontalLayoutWidget);
        button[i]->setMinimumSize(QSize(100, 45));
        button[i]->setMaximumSize(QSize(100, 45));
        horizontalLayout->addWidget( button[i]);
    }

    /*************PLAYER1_ZONE********************/
    QWidget * widget = new QWidget(Dialog);
    widget->setGeometry(QRect(60, 150, 181, 281));
    QVBoxLayout *verticalLayout = new QVBoxLayout(widget);

    QLabel * player1_label = new QLabel("PLAYER 1", widget);
    verticalLayout->addWidget(player1_label);

    std::string skin_name[] = {"skin1","skin2", "skin3"};
    QRadioButton * skin_player1[3];

    for (int i = 0; i < 3; ++i){
        skin_player1[i] = new QRadioButton(skin_name[i].c_str(), widget);
        skin_player1[i]->setMinimumSize(QSize(100, 45));
        skin_player1[i]->setMaximumSize(QSize(100, 45));
        if(i == my_level.player.skin)
             skin_player1[i]->setChecked(true);
        verticalLayout->addWidget(skin_player1[i]);
    }


    /*************PLAYER2_ZONE********************/
    QWidget *widget1 = new QWidget(Dialog);
    widget1->setGeometry(QRect(330, 140, 191, 291));
    QVBoxLayout *verticalLayout_2 = new QVBoxLayout(widget1);
    verticalLayout_2->setContentsMargins(0, 0, 0, 0);

    QLabel * player2_label = new QLabel("PLAYER 2", widget);
    verticalLayout_2->addWidget(player2_label);

    QRadioButton * skin_player2[3];

    for (int i = 0; i < 3; ++i){
        skin_player2[i] = new QRadioButton(skin_name[i].c_str(), widget1);
        skin_player2[i]->setMinimumSize(QSize(100, 45));
        skin_player2[i]->setMaximumSize(QSize(100, 45));
        if(i == my_level.player.skin2)
             skin_player2[i]->setChecked(true);
        verticalLayout_2->addWidget(skin_player2[i]);
    }

    /*************SAME SIZE LABEL********************/
    QLabel * label_legend[] ={player1_label,player2_label};
    for(auto lbl : label_legend){
        lbl->setMinimumSize(QSize(100, 45));
        lbl->setMaximumSize(QSize(100, 45));
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setFrameShape(QFrame::WinPanel);
        lbl->setLineWidth(3);
    }

    /***************CONNECTION********************/
    connect(button[ok], &QPushButton::clicked, this, [this, my_level,Dialog, spin_box, skin_player1, skin_player2, speed_box](){
        Parsing::Level copy_level = my_level;
        copy_level.player.speed = speed_box->currentIndex();
        copy_level.player.hp = spin_box[0]->value();
        copy_level.player.damage = spin_box[1]->value();
        for (int i = 0; i < 3; ++i){
            if(skin_player1[i]->isChecked())
                copy_level.player.skin = i;
        }

        for (int i = 0; i < 3; ++i){
            if(skin_player2[i]->isChecked())
                copy_level.player.skin2 = i;
        }

        Dialog->hide();
        level_editor(copy_level);
    });
    connect(button[cancel], &QPushButton::clicked, this, [this, my_level,Dialog](){
        Dialog->hide();
        Parsing::Level copy_level = my_level;
        level_editor(copy_level);
    });

    Dialog->show();

}

void MenuGui::view_level(bool mine){
	this->setStyleSheet(QStringLiteral("background-color:white;"));
    std::string res; 
    if(mine)
       res =  _client.myLevels();
    else
        res = _client.viewLevels();
    std::vector<Parsing::Creator> creator_list = Parsing::creator_list_from_str(res);

    QWidget *centralWidget = new QWidget(this);

    QPushButton* back = new QPushButton("Back", centralWidget);
    back->setGeometry(QRect(330, 504, 151, 41));
    connect(back, &QPushButton::clicked, this, &MenuGui::level_menu);

    QTableWidget* tableWidget = new QTableWidget(centralWidget);
    if(mine)
        tableWidget->setColumnCount(4);
    else
        tableWidget->setColumnCount(5);

    tableWidget->setRowCount(creator_list.size());

    QLabel *label = new QLabel("MY LEVELS", centralWidget);
    label->setAlignment(Qt::AlignCenter);
    label->setGeometry(QRect(100, 10, 601, 71));
    label->setFrameShape(QFrame::WinPanel);
    label->setAlignment(Qt::AlignCenter);

    QStringList m_TableHeader;
    m_TableHeader <<"Title"<<"Author"<<"Vote"<<"Play"<<"Like";
    tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setShowGrid(false);
    //tableWidget->setGeometry(QApplication::desktop()->screenGeometry());
    tableWidget->setGeometry(QRect(100, 140, 621, 341));
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    /*QPalette palette = tableWidget->palette();
    palette.setBrush(QPalette::Highlight,QBrush(Qt::white));
    palette.setBrush(QPalette::HighlightedText,QBrush(Qt::black));
    tableWidget->setPalette(palette);*/

    connect(tableWidget,&QAbstractItemView::clicked,this,[this,creator_list,mine](const QModelIndex& idx){
        if(idx.column()==3){ //run
            int i = idx.row();
            std::string level = _client.getLevel(creator_list[i].name, std::string(creator_list[i].pseudo));
            std::cout << "level to play : "<< level<<std::endl;
            lobby(level, mine);
        }
        else if(idx.column()==4){ //like
            int i = idx.row();
            _client.voteLevel(creator_list[i].name, std::string(creator_list[i].pseudo));
            view_level(mine);
        }
    });
    
    for (size_t i = 0; i < creator_list.size(); i++){
        QTableWidgetItem *item;
        tableWidget->setItem(i, 0, new QTableWidgetItem((creator_list[i].name).c_str()));
        item = tableWidget->item(i, 0);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled);
        item->setSizeHint(QSize(100, 100));

        int vote = creator_list[i].vote;
        std::string author = creator_list[i].pseudo;
        tableWidget->setItem(i, 1, new QTableWidgetItem(author.c_str()));
        item = tableWidget->item(i, 1);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled);
        item->setSizeHint(QSize(100, 100));

        tableWidget->setItem(i, 2, new QTableWidgetItem(std::to_string(vote).c_str()));
        item = tableWidget->item(i, 2);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled);

        tableWidget->setItem(i, 3, new QTableWidgetItem("run"));
        item = tableWidget->item(i, 3);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled);

        if(not mine){
            QPixmap pix("images/thumb");
            QIcon icon(pix);
            QTableWidgetItem *item;
            tableWidget->setItem(i, 4, new QTableWidgetItem());
            item = tableWidget->item(i, 4);
            tableWidget->setIconSize(QSize(50, 50));
            item->setIcon(icon);
            item->setTextAlignment(Qt::AlignCenter);
            item->setSizeHint(QSize(100, 100));
            //connect(tableWidget->item(i, 3), &QTableWidget::itemClicked, this, &Menu::main_m);
            /*connect(tableWidget->item(i, 3), &QTableWidget::itemSelectionChanged,this, [this, creator_list, i](){
                _client.voteLevel(creator_list[i].name, std::string(creator_list[i].pseudo));

            });*/
        }
    }

    /****** DESIGN SECTION ****************************/
    /*this->setStyleSheet("background-color:rgb(8, 82, 40);");

    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(110, 30, 600, 150));
    QPixmap pix_home_title("images/titles/friends");
    title_label->setPixmap( pix_home_title);
    title_label->setAlignment(Qt::AlignCenter);
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);*/
    /*********END DESIGN SECTION*****************************************/


    this->setCentralWidget(centralWidget);
    this->show();

}

void MenuGui::launch_game(){
	DisplayGameGui display_game;
	display_game.initGraphics();
    std::cout << "on est la bg"<< std::endl;
	sf::RenderWindow* window = display_game.getWindow();

    bool gameOn = true;
    std::vector<int> inp;
	std::string string_game_to_display;
	std::string string_previous_game_to_display;

    while(gameOn && window->isOpen()){ 

		sf::Event event; // TODO PQ TT CA C'EST PAS DANS GET INPUT WINDOW !!!!!!
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
			if (event.type == sf::Event::KeyPressed)
				display_game.getInputWindow(&inp);
        }
	
		window->clear();
		_client.send_game_input(inp);
		inp.clear();

		string_game_to_display = _client.read_game_pipe();
		if (string_game_to_display != Constante::GAME_END)
			string_previous_game_to_display = string_game_to_display;
		if (string_game_to_display == Constante::GAME_END)
		
			break;
		display_game.parse_instruction(string_game_to_display);
		window->display();

    }
	
	//Last background
	display_game.parse_instruction(string_previous_game_to_display);
	window->display();

	//Final Score
	string_game_to_display = _client.read_game_pipe();
	display_game.drawEndGame(string_game_to_display);
	window->display();
	sf::Event event;
	
	while(true){ // CELA N'A RIEN A FAIRE LA TODO
		char in_char = -1;
		while (window->pollEvent(event))
        {
			if (event.type == sf::Event::KeyPressed)
				in_char = display_game.getInputWindow(&inp);
        }
        if(in_char == 'p')break;
    }

	window->close();
}


