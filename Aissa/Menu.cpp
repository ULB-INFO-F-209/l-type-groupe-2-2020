#include "Menu.hpp"

/********************* TODO ********************************************
        *  23/03 : Reunir sign in, sign up using lambda function
        *  23/03 : Maybe mettre tous les widget important en attribut?
        *  26/03 : Design fade like r-type or fun like neon?   
        *
 ***********************************************************************/


Menu::Menu(): QMainWindow(){
    this->setWindowTitle(QApplication::translate("L-Type", "L-Type", nullptr));
    this->resize(800, 600);
    this->setStyleSheet(QStringLiteral("background-color:white;"));

}

void Menu::start_session(){
	home();
	this->show();
}


void Menu::home(){	
    this->setStyleSheet(QStringLiteral("background-color:black;"));
    QWidget *centralWidget = new QWidget(this);


    //layout box
    QWidget *verticalLayoutWidget = new QWidget(centralWidget);
    verticalLayoutWidget->setGeometry(QRect(50, 140, 700, 450));
    //layout button
    QHBoxLayout *button_v_layout = new QHBoxLayout(verticalLayoutWidget);
    button_v_layout->setContentsMargins(11, 11, 11, 11);
    //home button
    QPushButton *home_button[SIZE_HOME];
    QPixmap pix_home_button[SIZE_HOME] = {QPixmap("images/buttons/signIn"),QPixmap("images/buttons/signUp"),QPixmap("images/buttons/quit")};
    QIcon icon_home[SIZE_HOME];
    for (size_t i = 0; i < SIZE_HOME; ++i)
    {
       home_button[i] = new QPushButton(verticalLayoutWidget);
       home_button[i]->setMinimumSize(QSize(200, 200));
       icon_home[i] = QIcon(pix_home_button[i]);
       home_button[i]->setIcon(icon_home[i]);
       home_button[i]->setIconSize(QSize(165, 165));
       home_button[i]->setFlat(true);
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


    /****** DESIGN SECTION ****************************/
    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(110, 50, 600, 150));
    QPixmap pix_home_title("images/titles/home");
    title_label->setPixmap( pix_home_title);
    title_label->setAlignment(Qt::AlignCenter);
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);

    /*********END DESIGN SECTION*****************************************/

        //exageration
    /*QLabel *lbl = new QLabel(centralWidget);
    QMovie *mv = new QMovie("images/stars_rain.gif");
    lbl->setGeometry(QRect(70, 0, 1000, 1000));
    mv->start();
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    lbl->setMovie(mv);*/


    this->setCentralWidget(centralWidget);

}

void Menu::check_data(bool sign_in){
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

void Menu::connexion(bool sign_in){
    QWidget *centralWidget = new QWidget(this);

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
    horizontalLayoutWidget->setGeometry(QRect(110, 440, 680, 100));
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


    /****** DESIGN SECTION ****************************/
    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(110, 50, 600, 150));
    QPixmap pix_home_title = QPixmap();
    title_label->setAlignment(Qt::AlignCenter);
    this->setStyleSheet(QStringLiteral("background-color:black;"));

    
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
    //this->update();
    this->show();

}
void Menu::main_m(){
    QWidget *centralWidget = new QWidget(this);

    QWidget *verticalLayoutWidget  = new QWidget(centralWidget);
    verticalLayoutWidget->setGeometry(QRect(80, 210, 651, 351));

    QVBoxLayout *verticalLayout  = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setContentsMargins(100, 0, 100, 0);

    QPushButton *main_button[SIZE_MAIN_MENU];
    for (size_t i = 0; i < SIZE_MAIN_MENU; ++i){
       main_button[i] = new QPushButton(QString::fromStdString(main_menu[i]),verticalLayoutWidget);
       main_button[i]->setMinimumSize(QSize(25, 50));
       verticalLayout->addWidget(main_button[i]);
    }
    QPushButton *new_game = (main_button[0]);
    QPushButton *friends = (main_button[1]);
    QPushButton *leaderboard = (main_button[2]);
    QPushButton *profile = (main_button[3]);
    QPushButton *level = (main_button[4]);
    QPushButton *log_out = (main_button[5]);

    connect(friends, &QPushButton::clicked, this, &Menu::print_friends);
    connect(leaderboard, &QPushButton::clicked, this,&Menu::print_leaderboard);
    connect(profile, &QPushButton::clicked, this, &Menu::print_profile);
    connect(level, &QPushButton::clicked, this, &Menu::level);
    connect(log_out, &QPushButton::clicked, this,&Menu::home);
    connect(new_game, &QPushButton::clicked, this,&Menu::lobby);

    /****** DESIGN SECTION ****************************/
    //this->setStyleSheet("background-color:rgb(123, 22, 22);");
    this->setStyleSheet(QStringLiteral("background-color:white;"));
    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(110, 30, 600, 150));
    QPixmap pix_home_title("images/titles/mainMenu");
    title_label->setPixmap( pix_home_title);
    title_label->setAlignment(Qt::AlignCenter);
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);
    /*********END DESIGN SECTION*****************************************/
    this->setCentralWidget(centralWidget);
    this->show();
}

void Menu::print_profile(){
    Profile profile; char buffer[Constante::CHAR_SIZE];
    _client.get_profile(buffer);
    profile_from_str(buffer, &profile);
    std::string pseudo = profile.pseudo, score =  std::to_string(profile.score);

    QWidget *centralWidget = new QWidget(this);
    QWidget *gridLayoutWidget = new QWidget(centralWidget);
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

    /****** DESIGN SECTION ****************************/
    //this->setStyleSheet("background-color:rgb(62, 153, 150);");
    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(110, 30, 600, 150));
    QPixmap pix_home_title("images/titles/profile");
    title_label->setPixmap( pix_home_title);
    title_label->setAlignment(Qt::AlignCenter);
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);
    /*********END DESIGN SECTION*****************************************/

    this->setCentralWidget(centralWidget);
    //this->update();
    this->show();
}
void Menu::print_leaderboard(){
    std::vector<Profile> profile_list;
    char buffer[Constante::CHAR_SIZE];
    _client.checkLeaderboard(buffer);
    profile_list_from_str(buffer, &profile_list);

    QWidget *centralWidget = new QWidget(this);

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
    tableWidget->setMaximumSize(QSize(220, 190));
    tableWidget->setRowCount(profile_list.size());

    horizontalLayout->addWidget(tableWidget);

    verticalLayout_2->addLayout(horizontalLayout);

    verticalLayout->addLayout(verticalLayout_2);

    QPushButton* back = new QPushButton((QString::fromStdString("Back")), verticalLayoutWidget);
    back->setMaximumSize(QSize(1000, 45));
    connect(back, &QPushButton::clicked, this,&Menu::main_m);

    verticalLayout->addWidget(back);

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

void Menu::print_friends(){
	char buffer[Constante::CHAR_SIZE];
	std::vector<Profile> friendlist;
	_client.getFriendList(buffer);
	profile_list_from_str(buffer, &friendlist);

    char buffer2[Constante::CHAR_SIZE];
	std::vector<Profile> requestlist;
	_client.getFriendRequest(buffer2);
	profile_list_from_str(buffer2, &requestlist);

    QWidget *centralWidget = new QWidget(this);
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
    connect(back, &QPushButton::clicked, this, &Menu::main_m);

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
    connect(listWidget,&QAbstractItemView::doubleClicked,this,&Menu::request_list);

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

void Menu::request_list(const QModelIndex &index){
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
	profile_list_from_str(buffer2, &requestlist);

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


void Menu::add_del_friend(bool adding){
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


void Menu::verif_friend(QDialog* dialog, bool adding){
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


void Menu::lobby(){
    QWidget *centralWidget =  new QWidget(this);

    QWidget *gridLayoutWidget = new QWidget(centralWidget);
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

    QComboBox *Ally_shot_box  = new QComboBox(gridLayoutWidget);
    Ally_shot_box->clear();
    Ally_shot_box->addItem(QString::fromStdString("Yes"));
    Ally_shot_box->addItem(QString::fromStdString("No"));

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
    connect(back_button, &QPushButton::clicked, this,&Menu::main_m);
    connect(play_button, &QPushButton::clicked, this,[this, players_box, lives_spin, Ally_shot_box,droprate_spin, difficulty_box](){
        int drop_rate = droprate_spin->value() , lives = lives_spin->value(); 
        int players = (players_box->currentText()).toInt();
        std::string difficulty = (difficulty_box->currentText()).toStdString();
        bool ally_shot = ((Ally_shot_box->currentText()).toStdString()).compare("Yes") == 0;
        launch_game(players, drop_rate, lives, difficulty,ally_shot);
       
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


void Menu::launch_game(int players, int drop_rate, int lives, std::string difficulty, bool ally_shot){
    Game_settings setting;
    strcpy(setting.difficulty_str, difficulty.c_str());
    setting.diff = !strcmp(setting.difficulty_str,"easy")? easy: !strcmp(setting.difficulty_str,"medium")? medium :hard;
    setting.drop_rate = drop_rate;
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
        connect(buttonBox, &QDialogButtonBox::accepted,this, [this,buttonBox,pseudoLine,pswdLine](){
            std::string pseudo = (pseudoLine->text()).toUtf8().constData();
            std::string pswd = (pswdLine->text()).toUtf8().constData();
            char y_pseudo[15]; bool success =0;
            _client.get_pseudo(y_pseudo);
            if(pseudo.compare(std::string(y_pseudo)) != 0)
                success= _client.signIn(pseudo.c_str(), pswd.c_str(), false); 
            if(success)
                buttonBox->rejected();
    });
        Dialog->show();

    }
}


void Menu::level(){
    //faire des boucle pour les rept de code
    QWidget *centralwidget = new QWidget(this);
    QFrame *game_zone = new QFrame(centralwidget);
    game_zone->setGeometry(QRect(20, 130, 551, 371));
    game_zone->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));
    game_zone->setFrameShape(QFrame::WinPanel);
    game_zone->setFrameShadow(QFrame::Plain);
    game_zone->setLineWidth(3);

    QLabel *title_label = new QLabel("LEVEL EDITOR",centralwidget);
    title_label->setGeometry(QRect(120, 30, 571, 81));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setAlignment(Qt::AlignCenter);

    QWidget *verticalLayoutWidget = new QWidget(centralwidget);
    verticalLayoutWidget->setGeometry(QRect(580, 130, 170, 361));
    QVBoxLayout *verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setContentsMargins(10, 0, 10, 0);
    QPushButton *ennemy_button = new QPushButton("Ennemy", verticalLayoutWidget);
    ennemy_button->setMinimumSize(QSize(150, 45));
    ennemy_button->setMaximumSize(QSize(150, 45));
    QPushButton *obstacle_button = new QPushButton("Obstacle",verticalLayoutWidget);
    obstacle_button->setMinimumSize(QSize(150, 45));
    obstacle_button->setMaximumSize(QSize(150, 45));
    QPushButton *save = new QPushButton("Save",verticalLayoutWidget);
    save->setMinimumSize(QSize(150, 45));
    save->setMaximumSize(QSize(150, 45));
    QPushButton *cancel = new QPushButton("Cancel",verticalLayoutWidget);
    cancel->setMinimumSize(QSize(150, 45));
    cancel->setMaximumSize(QSize(150, 45));
    QWidget *horizontalLayoutWidget = new QWidget(centralwidget);
    horizontalLayoutWidget->setGeometry(QRect(20, 515, 771, 81));
    QHBoxLayout *horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *tick_label = new QLabel("Tick : ",horizontalLayoutWidget);
    tick_label->setMinimumSize(QSize(80, 0));
    tick_label->setFrameShape(QFrame::WinPanel);
    tick_label->setLineWidth(3);
    tick_label->setTextFormat(Qt::RichText);
    tick_label->setAlignment(Qt::AlignCenter);
    QSlider *tick_slider = new QSlider(horizontalLayoutWidget);
    tick_slider->setMaximum(20);
    tick_slider->setPageStep(1);
    tick_slider->setOrientation(Qt::Horizontal);
    tick_slider->setTickPosition(QSlider::TicksBothSides);
    tick_slider->setTickInterval(1);
    QLCDNumber *tick_lcd = new QLCDNumber(horizontalLayoutWidget);
    tick_lcd->setFrameShape(QFrame::WinPanel);
    tick_lcd->setFrameShadow(QFrame::Plain);
    tick_lcd->setLineWidth(3);
    tick_lcd->setDigitCount(2);

    verticalLayout->addWidget(ennemy_button);
    verticalLayout->addWidget(obstacle_button);
    verticalLayout->addWidget(save);
    verticalLayout->addWidget(cancel);

    horizontalLayout->addWidget(tick_label);
    horizontalLayout->addWidget(tick_slider);
    horizontalLayout->addWidget(tick_lcd);

    //connect section
    connect(cancel, &QPushButton::clicked, this,&Menu::main_m);
    connect(save, &QPushButton::clicked, this,&Menu::save_level);
    connect(ennemy_button, &QPushButton::clicked, this,&Menu::custom_ennemy);
    connect(obstacle_button, &QPushButton::clicked, this,&Menu::custom_obstacle);
    connect(tick_slider, SIGNAL(valueChanged(int)),tick_lcd, SLOT(display(int)));

    this->setCentralWidget(centralwidget);
    this->show();



}

void Menu::save_level(){
    QDialog * Dialog = new QDialog();
    Dialog->resize(452, 345);

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
    Dialog->show();


}
void Menu::custom_ennemy(){
    QDialog * Dialog = new QDialog();
    Dialog->resize(800, 600);

    QWidget *gridLayoutWidget = new QWidget(Dialog);
    gridLayoutWidget->setGeometry(QRect(20, 100, 761, 331));

    QGridLayout *gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *position_label = new QLabel("Position : ",gridLayoutWidget);
    position_label->setMinimumSize(QSize(100, 45));
    position_label->setMaximumSize(QSize(100, 45));
    position_label->setFrameShape(QFrame::WinPanel);
    position_label->setAlignment(Qt::AlignCenter);

    //separator
    QLabel *invisible = new QLabel(gridLayoutWidget);
    QLabel *invisible2 = new QLabel(gridLayoutWidget);

    //bonus
    QRadioButton *bonus1 = new QRadioButton("Bonus1",gridLayoutWidget);
    QRadioButton *bonus2 = new QRadioButton("Bonus2",gridLayoutWidget);
    QRadioButton *bonus3 = new QRadioButton("Bonus3",gridLayoutWidget);
    QRadioButton *bonus4 = new QRadioButton("Bonus4",gridLayoutWidget);

    //skin
    QRadioButton *skin1 = new QRadioButton("skin1",gridLayoutWidget);
    skin1->setMinimumSize(QSize(100, 45));
    skin1->setMaximumSize(QSize(100, 45));
    QRadioButton *skin2 = new QRadioButton("skin2",gridLayoutWidget);
    skin2->setMinimumSize(QSize(100, 45));
    skin2->setMaximumSize(QSize(100, 45));
    QRadioButton *skin3 = new QRadioButton("skin3",gridLayoutWidget);
    skin3->setMinimumSize(QSize(100, 45));
    skin3->setMaximumSize(QSize(100, 45));

    QLabel *skin_label = new QLabel("SKIN",gridLayoutWidget);
    skin_label->setFrameShape(QFrame::WinPanel);
    skin_label->setAlignment(Qt::AlignCenter);

    QLabel *Bonus_label = new QLabel("Bonus",gridLayoutWidget);
    Bonus_label->setMinimumSize(QSize(100, 45));
    Bonus_label->setMaximumSize(QSize(100, 45));
    Bonus_label->setFrameShape(QFrame::WinPanel);
    Bonus_label->setAlignment(Qt::AlignCenter);

    QLabel *tick_label = new QLabel("Tick :",gridLayoutWidget);
    tick_label->setFrameShape(QFrame::WinPanel);
    tick_label->setAlignment(Qt::AlignCenter);

    QSpinBox *tick_spin = new QSpinBox(gridLayoutWidget);
    tick_spin->setMinimumSize(QSize(100, 45));
    tick_spin->setMaximumSize(QSize(100, 45));
    tick_spin->setMaximum(20);

    QSpinBox *position_spin = new QSpinBox(gridLayoutWidget);
    position_spin->setMinimumSize(QSize(100, 45));
    position_spin->setMaximumSize(QSize(100, 45));
    position_spin->setMaximum(100);

    QLabel *hp_label = new QLabel("HP : ",gridLayoutWidget);
    hp_label->setFrameShape(QFrame::WinPanel);
    hp_label->setMidLineWidth(3);
    hp_label->setAlignment(Qt::AlignCenter);

    QLabel *damage_label  = new QLabel("Damage : ",gridLayoutWidget);
    damage_label->setFrameShape(QFrame::WinPanel);
    damage_label->setAlignment(Qt::AlignCenter);

    QSpinBox *hp_spin = new QSpinBox(gridLayoutWidget);
    hp_spin->setMinimumSize(QSize(100, 45));
    hp_spin->setMaximumSize(QSize(100, 45));
    hp_spin->setMaximum(100);

    QSpinBox *damage_spin = new QSpinBox(gridLayoutWidget);
    damage_spin->setMinimumSize(QSize(100, 45));
    damage_spin->setMaximumSize(QSize(100, 45));
    damage_spin->setMaximum(50);

    QLabel *vitesse_label = new QLabel("Speed",gridLayoutWidget);
    vitesse_label->setMinimumSize(QSize(100, 45));
    vitesse_label->setMaximumSize(QSize(100, 45));
    vitesse_label->setFrameShape(QFrame::WinPanel);
    vitesse_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    QSpinBox *vitesse_spin  = new QSpinBox(gridLayoutWidget);
    vitesse_spin->setMinimumSize(QSize(100, 45));
    vitesse_spin->setMaximumSize(QSize(100, 45));

    QLabel *title_label = new QLabel("CUSTOM ENNEMY",Dialog);
    title_label->setGeometry(QRect(60, 9, 701, 71));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setAlignment(Qt::AlignCenter);

    QWidget *horizontalLayoutWidget = new QWidget(Dialog);
    horizontalLayoutWidget->setGeometry(QRect(20, 460, 771, 80));
    QHBoxLayout *horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton *ok = new QPushButton("OK",horizontalLayoutWidget);
    ok->setMinimumSize(QSize(100, 45));
    ok->setMaximumSize(QSize(100, 45));
    QPushButton *delete_button = new QPushButton("Delete",horizontalLayoutWidget);
    delete_button->setMinimumSize(QSize(100, 45));
    delete_button->setMaximumSize(QSize(100, 45));
    QPushButton *cancel = new QPushButton("Cancel",horizontalLayoutWidget);
    cancel->setMinimumSize(QSize(100, 45));
    cancel->setMaximumSize(QSize(100, 45));

    horizontalLayout->addWidget(ok);
    horizontalLayout->addWidget(delete_button);
    horizontalLayout->addWidget(cancel);

    //grid
    gridLayout->addWidget(skin2, 5, 0, 1, 1);
    gridLayout->addWidget(skin_label, 0, 0, 1, 1);
    gridLayout->addWidget(invisible2, 4, 3, 1, 1);
    gridLayout->addWidget(Bonus_label, 0, 2, 1, 1);
    gridLayout->addWidget(skin3, 7, 0, 1, 1);
    gridLayout->addWidget(skin1, 2, 0, 1, 1);
    gridLayout->addWidget(invisible, 4, 1, 1, 1);
    gridLayout->addWidget(damage_label, 7, 4, 1, 1);
    gridLayout->addWidget(damage_spin, 7, 5, 1, 1);
    gridLayout->addWidget(tick_label, 6, 4, 1, 1);
    gridLayout->addWidget(tick_spin, 6, 5, 1, 1);
    gridLayout->addWidget(hp_label, 5, 4, 1, 1);
    gridLayout->addWidget(hp_spin, 5, 5, 1, 1);
    gridLayout->addWidget(position_label, 4, 4, 1, 1);
    gridLayout->addWidget(position_spin, 4, 5, 1, 1);
    gridLayout->addWidget(vitesse_spin, 2, 5, 1, 1);
    gridLayout->addWidget(vitesse_label, 2, 4, 1, 1);
    gridLayout->addWidget(bonus1, 2, 2, 1, 1);
    gridLayout->addWidget(bonus2, 4, 2, 1, 1);
    gridLayout->addWidget(bonus3, 5, 2, 1, 1);
    gridLayout->addWidget(bonus4, 6, 2, 1, 1);


    Dialog->show();

}
void Menu::custom_obstacle(){
        QDialog * Dialog = new QDialog();
    Dialog->resize(800, 600);

    QWidget *gridLayoutWidget = new QWidget(Dialog);
    gridLayoutWidget->setGeometry(QRect(20, 100, 761, 331));

    QGridLayout *gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *position_label = new QLabel("Position : ",gridLayoutWidget);
    position_label->setMinimumSize(QSize(100, 45));
    position_label->setMaximumSize(QSize(100, 45));
    position_label->setFrameShape(QFrame::WinPanel);
    position_label->setAlignment(Qt::AlignCenter);

    //separator
    QLabel *invisible = new QLabel(gridLayoutWidget);
    QLabel *invisible2 = new QLabel(gridLayoutWidget);

    //bonus
    QRadioButton *bonus1 = new QRadioButton("Bonus1",gridLayoutWidget);
    QRadioButton *bonus2 = new QRadioButton("Bonus2",gridLayoutWidget);
    QRadioButton *bonus3 = new QRadioButton("Bonus3",gridLayoutWidget);
    QRadioButton *bonus4 = new QRadioButton("Bonus4",gridLayoutWidget);

    //skin
    QRadioButton *skin1 = new QRadioButton("skin1",gridLayoutWidget);
    skin1->setMinimumSize(QSize(100, 45));
    skin1->setMaximumSize(QSize(100, 45));
    QRadioButton *skin2 = new QRadioButton("skin2",gridLayoutWidget);
    skin2->setMinimumSize(QSize(100, 45));
    skin2->setMaximumSize(QSize(100, 45));
    QRadioButton *skin3 = new QRadioButton("skin3",gridLayoutWidget);
    skin3->setMinimumSize(QSize(100, 45));
    skin3->setMaximumSize(QSize(100, 45));

    QLabel *skin_label = new QLabel("SKIN",gridLayoutWidget);
    skin_label->setFrameShape(QFrame::WinPanel);
    skin_label->setAlignment(Qt::AlignCenter);

    QLabel *Bonus_label = new QLabel("Bonus",gridLayoutWidget);
    Bonus_label->setMinimumSize(QSize(100, 45));
    Bonus_label->setMaximumSize(QSize(100, 45));
    Bonus_label->setFrameShape(QFrame::WinPanel);
    Bonus_label->setAlignment(Qt::AlignCenter);

    QLabel *tick_label = new QLabel("Tick :",gridLayoutWidget);
    tick_label->setFrameShape(QFrame::WinPanel);
    tick_label->setAlignment(Qt::AlignCenter);

    QSpinBox *tick_spin = new QSpinBox(gridLayoutWidget);
    tick_spin->setMinimumSize(QSize(100, 45));
    tick_spin->setMaximumSize(QSize(100, 45));
    tick_spin->setMaximum(20);

    QSpinBox *position_spin = new QSpinBox(gridLayoutWidget);
    position_spin->setMinimumSize(QSize(100, 45));
    position_spin->setMaximumSize(QSize(100, 45));
    position_spin->setMaximum(100);

    QLabel *damage_label  = new QLabel("Damage : ",gridLayoutWidget);
    damage_label->setFrameShape(QFrame::WinPanel);
    damage_label->setAlignment(Qt::AlignCenter);

    QSpinBox *damage_spin = new QSpinBox(gridLayoutWidget);
    damage_spin->setMinimumSize(QSize(100, 45));
    damage_spin->setMaximumSize(QSize(100, 45));
    damage_spin->setMaximum(50);

    QLabel *vitesse_label = new QLabel("Speed",gridLayoutWidget);
    vitesse_label->setMinimumSize(QSize(100, 45));
    vitesse_label->setMaximumSize(QSize(100, 45));
    vitesse_label->setFrameShape(QFrame::WinPanel);
    vitesse_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    QSpinBox *vitesse_spin  = new QSpinBox(gridLayoutWidget);
    vitesse_spin->setMinimumSize(QSize(100, 45));
    vitesse_spin->setMaximumSize(QSize(100, 45));

    QLabel *title_label = new QLabel("CUSTOM ENNEMY",Dialog);
    title_label->setGeometry(QRect(60, 9, 701, 71));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setAlignment(Qt::AlignCenter);

    QWidget *horizontalLayoutWidget = new QWidget(Dialog);
    horizontalLayoutWidget->setGeometry(QRect(20, 460, 771, 80));
    QHBoxLayout *horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton *ok = new QPushButton("OK",horizontalLayoutWidget);
    ok->setMinimumSize(QSize(100, 45));
    ok->setMaximumSize(QSize(100, 45));
    QPushButton *delete_button = new QPushButton("Delete",horizontalLayoutWidget);
    delete_button->setMinimumSize(QSize(100, 45));
    delete_button->setMaximumSize(QSize(100, 45));
    QPushButton *cancel = new QPushButton("Cancel",horizontalLayoutWidget);
    cancel->setMinimumSize(QSize(100, 45));
    cancel->setMaximumSize(QSize(100, 45));

    horizontalLayout->addWidget(ok);
    horizontalLayout->addWidget(delete_button);
    horizontalLayout->addWidget(cancel);

    //grid
    gridLayout->addWidget(skin2, 5, 0, 1, 1);
    gridLayout->addWidget(skin_label, 0, 0, 1, 1);
    gridLayout->addWidget(invisible2, 4, 3, 1, 1);
    gridLayout->addWidget(Bonus_label, 0, 2, 1, 1);
    gridLayout->addWidget(skin3, 7, 0, 1, 1);
    gridLayout->addWidget(skin1, 2, 0, 1, 1);
    gridLayout->addWidget(invisible, 4, 1, 1, 1);
    gridLayout->addWidget(damage_label,  6, 4, 1, 1);
    gridLayout->addWidget(damage_spin, 6, 5, 1, 1);
    gridLayout->addWidget(tick_label, 5, 4, 1, 1);
    gridLayout->addWidget(tick_spin, 5, 5, 1, 1);
    gridLayout->addWidget(position_label, 4, 4, 1, 1);
    gridLayout->addWidget(position_spin, 4, 5, 1, 1);
    gridLayout->addWidget(vitesse_spin, 2, 5, 1, 1);
    gridLayout->addWidget(vitesse_label, 2, 4, 1, 1);
    gridLayout->addWidget(bonus1, 2, 2, 1, 1);
    gridLayout->addWidget(bonus2, 4, 2, 1, 1);
    gridLayout->addWidget(bonus3, 5, 2, 1, 1);
    gridLayout->addWidget(bonus4, 6, 2, 1, 1);


    Dialog->show();
}



