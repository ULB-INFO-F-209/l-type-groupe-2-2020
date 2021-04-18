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
    set_background(centralWidget);

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

void MenuGui::check_data(QLineEdit *pseudo_line, QLineEdit *pswd_line, bool sign_in){
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

void MenuGui::set_background(QWidget *centralwidget){
    QLabel *lbl = new QLabel(centralwidget);
    QMovie *mv = new QMovie("images/background/ciel.gif");
    mv->setScaledSize(QSize(800,600));
    lbl->setGeometry(QRect(0, 0, 800, 600));
    mv->start();
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    lbl->setMovie(mv);
}

QComboBox *MenuGui::create_box(QWidget *parent, std::vector<std::string> values,QRect pos){
    QComboBox *box = new QComboBox(parent);
    box->setGeometry(pos);
    box->clear();
    for(auto val: values)
        box->addItem(QString::fromStdString(val));
    return box;
}

QLabel *MenuGui::create_label(QWidget *parent, std::string value, QRect pos){
    QLabel *label = new QLabel(QString::fromStdString(value),parent);
    label->setGeometry(pos);
    label->setStyleSheet("QLabel { background-color : black; color : white; }");
    return label;
}

QPushButton *MenuGui::create_button(QWidget *parent,std::string image, int width, int height){
    QPushButton * button = new QPushButton(parent);
    button->setMinimumSize(QSize(width, height));
    QPixmap pix(QString::fromStdString(image));
    pix = pix.scaled(button->size(),Qt::KeepAspectRatio);
    QIcon icon(pix);
    button->setIcon(icon);
    button->setIconSize(QSize(width, height));
    button->setFlat(true);
    return button;
}

QPushButton *MenuGui::create_button(QWidget *parent,std::string image, int width, int height, QRect size){
    QPushButton * button = new QPushButton(parent);
    button->setGeometry(size);
    QPixmap pix(QString::fromStdString(image));
    pix = pix.scaled(button->size(),Qt::KeepAspectRatio);
    QIcon icon(pix);
    button->setIcon(icon);
    button->setIconSize(QSize(width, height));
    button->setFlat(true);
    return button;
}

void MenuGui::set_title(QWidget *parent, std::string image){
    QLabel *title_label = new QLabel(parent);
    title_label->setGeometry(QRect(110, 10, 600, 150));
    QPixmap pix_home_title(QString::fromStdString(image));
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);
    title_label->setPixmap( pix_home_title);
    title_label->setAlignment(Qt::AlignCenter);
}

QLineEdit *MenuGui::create_line(QWidget *parent,QRect rect, bool pswd){
    QRegExp re("[a-z-A-Z-0-9]+");
    QRegExpValidator *validator = new QRegExpValidator(re, this);
    QLineEdit *line = new QLineEdit(parent);
    line->setGeometry(rect);
    line->setMaxLength(15);
    line->setValidator(validator);
    /**********/
    line->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
                                            "font: 75 13pt \"Tlwg Typo\";\n"
                                            "border-color: rgb(0, 0, 0);\n"
                                            "gridline-color: rgb(238, 238, 236);"));
    if(pswd)
        line->setEchoMode(QLineEdit::Password);
    return line;
}

QTableWidget * MenuGui::create_table_widget(QWidget *parent,int col, int row,std::string title[],QRect rect){

    QTableWidget *table = new QTableWidget(parent);
    table->setColumnCount(col);
    table->setRowCount(row);
    table->setGeometry(rect);

    for(int i=0; i < col; i++){
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem(QString::fromStdString(title[i]));
        __qtablewidgetitem->setBackground(QColor(255, 255, 255));
        table->setHorizontalHeaderItem(i, __qtablewidgetitem);
    }
    table->setStyleSheet(QStringLiteral("background-color:white;"));
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    
    return table;
}

void MenuGui::connexion(bool sign_in){
    QWidget *centralWidget = new QWidget(this);
    set_background(centralWidget);

    QLineEdit *pseudo_line = create_line(centralWidget,QRect(230, 270, 400, 45),false);
    QLineEdit *pswd_line = create_line(centralWidget,QRect(230, 370, 400, 45),true);

    QLabel *pseudo_label = create_label(centralWidget, "Username : ", QRect(140, 270, 91, 45));
    QLabel *pswd_label = create_label(centralWidget, "Password : ", QRect(130, 370, 101, 45));

    QWidget *horizontalLayoutWidget = new QWidget(centralWidget);
    horizontalLayoutWidget->setGeometry(QRect(110, 440, 680, 200));
    horizontalLayoutWidget->setAttribute(Qt::WA_TranslucentBackground);

    QHBoxLayout *horizontalLayout =  new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setSpacing(50);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);

    QPushButton *ok_button =  create_button(horizontalLayoutWidget,"images/buttons/ok", 150,150 );
    horizontalLayout->addWidget(ok_button);

    QPushButton *cancel_button = create_button(horizontalLayoutWidget,"images/buttons/back", 150,150 );
    horizontalLayout->addWidget(cancel_button);
    
    /****************************DESIGN*****************************************************/
    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(110, 50, 600, 150));
    QPixmap pix_home_title = QPixmap();
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet(QStringLiteral("background-color:black;"));

    if(sign_in)
        pix_home_title.load("images/titles/signIn");
    else
        pix_home_title.load("images/titles/signUp");

    /****************************CONNECTIONS*****************************************************/
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);
    title_label->setPixmap( pix_home_title);
    connect(ok_button, &QPushButton::clicked, this, [this,sign_in,pseudo_line,pswd_line]() {
            check_data(pseudo_line,pswd_line,sign_in);
    });
    connect(cancel_button, &QPushButton::clicked, this,&MenuGui::home);

    this->setCentralWidget(centralWidget);
    this->show();

}

void MenuGui::main_m(){
    QWidget *centralWidget = new QWidget(this);
    set_background(centralWidget);
    set_title(centralWidget,"images/titles/mainMenu");

    QPushButton *button[SIZE_MAIN_MENU];
    std::string pix_main[SIZE_MAIN_MENU] = {"images/buttons/game","images/buttons/friends","images/buttons/lead",
    										   "images/buttons/profile","images/buttons/level","images/buttons/logout"};
    int ngame = 0, friends=1, lead=2, prof=3, level=4, logout=5;
    QRect rects[SIZE_MAIN_MENU] = {QRect(280, 280, 241, 100), QRect(540, 370, 241, 100), QRect(20, 190, 241, 100), QRect(540, 190, 241, 100), QRect(20, 370, 241, 100), QRect(280, 470, 241, 100)};

    for (size_t i = 0; i < SIZE_MAIN_MENU; ++i){
       button[i] = create_button(centralWidget,pix_main[i],241,100, rects[i]);
       button[i]->setStyleSheet(QString::fromUtf8("border-radius:20;"));
    }

    connect(button[friends], &QPushButton::clicked, this, &MenuGui::print_friends);
    connect(button[lead], &QPushButton::clicked, this,&MenuGui::print_leaderboard);
    connect(button[prof], &QPushButton::clicked, this, &MenuGui::print_profile);
    connect(button[logout], &QPushButton::clicked, this,&MenuGui::home);
    connect(button[ngame], &QPushButton::clicked, this,[this](){
        lobby();
    });
    connect(button[level], &QPushButton::clicked, this, &MenuGui::level_menu);
    this->setCentralWidget(centralWidget);
    this->show();
}

void MenuGui::print_profile(){
    Profile profile; char buffer[Constante::CHAR_SIZE];
    _client.get_profile(buffer);
    Parsing::profile_from_str(buffer, &profile);
    std::string pseudo = profile.pseudo, score =  std::to_string(profile.score);

    QWidget *centralWidget = new QWidget(this);
    set_background(centralWidget);

    QLabel *username = create_label(centralWidget, "USERNAME :", QRect(40, 250, 150, 21));
    username->setStyleSheet("QLabel { background-color : black; color : white; }");
    QLabel *score_l = create_label(centralWidget, "SCORE :", QRect(40, 320, 150, 21));
    score_l->setStyleSheet("QLabel { background-color : black; color : white; }");

    QFont font1;
    font1.setFamily(QStringLiteral("Ubuntu"));
    font1.setPointSize(16);
    font1.setBold(false);
    font1.setWeight(50);
    username->setFont(font1);
    score_l->setFont(font1);

    QPushButton* back = create_button(centralWidget, "images/buttons/back2", 270, 470, QRect(270, 470, 261, 61));
    connect(back, &QPushButton::clicked, this,&MenuGui::main_m);

    QFont font2;
    font2.setFamily(QStringLiteral("aakar"));
    font2.setPointSize(16);

    QLabel *pseudo_label = create_label(centralWidget, pseudo, QRect(250, 250, 71, 21));
    pseudo_label->setFont(font2);
    pseudo_label->setStyleSheet("QLabel { background-color : black; color : white; }");

    QLabel *score_label = create_label(centralWidget, score, QRect(250, 320, 71, 21));
    score_label->setFont(font2);
    score_label->setStyleSheet("QLabel { background-color : black; color : white; }");

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
    set_background(centralWidget);

    QTableWidget* tableWidget = new QTableWidget(centralWidget);
    tableWidget->setGeometry(QRect(300, 190, 201, 211));
    tableWidget->setColumnCount(2);
    tableWidget->setMaximumSize(QSize(300, 200));
    tableWidget->setRowCount(profile_list.size());

    QPushButton* back = create_button(centralWidget, "images/buttons/back2", 270, 470, QRect(270, 470, 261, 61));
    connect(back, &QPushButton::clicked, this,&MenuGui::main_m);

    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem("Pseudo");
    __qtablewidgetitem->setBackground(QColor(255, 255, 255));
    tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);

    QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem("Score");
    __qtablewidgetitem2->setBackground(QColor(255, 255, 255));
    tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem2);

    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setShowGrid(false);
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

    tableWidget->setStyleSheet(QStringLiteral("background-color:white;"));
    /****** DESIGN SECTION ****************************/
    //this->setStyleSheet("background-color:rgb(148, 62, 8);");
    QLabel *title_label = new QLabel(centralWidget);
    title_label->setGeometry(QRect(170, 30, 500, 100));
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
    set_background(centralwidget);
    set_title(centralwidget,"images/titles/levelEditor");

    QPushButton * button[4]; 
    int create = 0, ranking=1, my_levels = 2, back=3;
    std::string name[4] = {"Create level", "Level ranking", "My levels", "Back"};
    QRect rects[] = {QRect(300, 220, 181, 41), QRect(300, 300, 181, 41), QRect(300, 380, 181, 41), QRect(300, 460, 181, 41)};
    for( int i = 0; i < 4; i++){
        button[i] = new QPushButton(QString::fromStdString(name[i]),centralwidget);
        button[i]->setGeometry(rects[i]);
        //button[i] = create_button(centralwidget, );
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
    //friends 
	char buffer[Constante::CHAR_SIZE];
	std::vector<Profile> friendlist;
	_client.getFriendList(buffer);
	Parsing::profile_list_from_str(buffer, &friendlist);
    //requetes
    char buffer2[Constante::CHAR_SIZE];
	std::vector<Profile> requestlist;
	_client.getFriendRequest(buffer2);
	Parsing::profile_list_from_str(buffer2, &requestlist);
   
    this->setFixedSize(923, 758);

    QWidget *centralwidget = new QWidget(this);
    set_background(centralwidget);
    set_title(centralwidget, "images/titles/friends");
    //this->setStyleSheet("background-color: white");
    QPushButton *ok_button_a = new QPushButton("OK",centralwidget); //add
    ok_button_a->setGeometry(QRect(690, 580, 91, 41));

    QLineEdit *pseudo_line = create_line(centralwidget,QRect(220, 580, 441, 41),false);
    QLabel *user_label = create_label(centralwidget, "USERNAME",QRect(100, 580, 101, 41));
    
    pseudo_line->hide();
    user_label->hide();
    ok_button_a->hide();

    QPushButton *back_button =  new QPushButton("BACK",centralwidget);
    back_button->setGeometry(QRect(100, 660, 721, 51));
    back_button->setStyleSheet("color: black; background-color: white");

    std::string titles_friends[] = {"USERNAME", "SCORE", "DELETE"};
    std::string titles_request[] = {"USERNAME", "SCORE", "ACCEPT", "DECLINE"};
    QTableWidget *friends_table = create_table_widget(centralwidget,3,friendlist.size(), titles_friends,QRect(0, 170, 402, 371));
    QTableWidget *request_table = create_table_widget(centralwidget,4,requestlist.size(), titles_request,QRect(529, 170,380, 371));
    
    friends_table->horizontalHeader()->setMinimumSectionSize(133);
    friends_table->horizontalHeader()->setMaximumSectionSize(133);
    request_table->horizontalHeader()->setMinimumSectionSize(125);

    request_table->horizontalHeader()->setDefaultSectionSize(133);
    friends_table->horizontalHeader()->setDefaultSectionSize(133);

    QPushButton *add_button = new QPushButton("ADD",centralwidget);
    add_button->setGeometry(QRect(410, 300, 111, 41));
    add_button->setStyleSheet("color: black; background-color: white");
    
    QLabel *friends_title =  create_label(centralwidget,"FRIENDS", QRect(30, 120, 321, 41));
    friends_title->setFrameShape(QFrame::WinPanel);
    friends_title->setAlignment(Qt::AlignCenter);
    QLabel *request_label = create_label(centralwidget,"REQUESTS",QRect(560, 120, 321, 41) );
    request_label->setFrameShape(QFrame::WinPanel);
    request_label->setAlignment(Qt::AlignCenter);

    for (size_t i = 0; i < friendlist.size(); i++){
        QTableWidgetItem *item;
        friends_table->setItem(i, 0, new QTableWidgetItem(friendlist[i].pseudo)); //pseudo
        item = friends_table->item(i, 0);
        item->setTextAlignment(Qt::AlignCenter);

        int score = friendlist[i].score;
        friends_table->setItem(i, 1, new QTableWidgetItem(std::to_string(score).c_str())); //score
        item = friends_table->item(i, 1);
        item->setTextAlignment(Qt::AlignCenter);

        friends_table->setItem(i, 2, new QTableWidgetItem("DEL")); //delete
        item = friends_table->item(i, 2);
        item->setTextAlignment(Qt::AlignCenter);
    }
    for (size_t i = 0; i < requestlist.size(); i++){
        QTableWidgetItem *item;
        request_table->setItem(i, 0, new QTableWidgetItem(requestlist[i].pseudo)); //pseudo
        item = request_table->item(i, 0);
        item->setTextAlignment(Qt::AlignCenter);

        int score = requestlist[i].score;
        request_table->setItem(i, 1, new QTableWidgetItem(std::to_string(score).c_str())); //score
        item = request_table->item(i, 1);
        item->setTextAlignment(Qt::AlignCenter);

        request_table->setItem(i, 2, new QTableWidgetItem("ACCEPT")); //delete
        item = request_table->item(i, 2);
        item->setTextAlignment(Qt::AlignCenter);

        request_table->setItem(i, 3, new QTableWidgetItem("DECLINE")); //delete
        item = request_table->item(i, 3);
        item->setTextAlignment(Qt::AlignCenter);
    }
    //connections
    connect(back_button,  &QPushButton::clicked, this, [this](){
        this->setFixedSize(800, 600);
        main_m();
    });
    connect(add_button,  &QPushButton::clicked, this,[this,pseudo_line, user_label,ok_button_a](){
        pseudo_line->show();
        user_label->show();
        ok_button_a->show();
    });
    connect(ok_button_a, &QPushButton::clicked, this,[this,pseudo_line, user_label,ok_button_a](){
        std::string pseudo = (pseudo_line->text()).toUtf8().constData();
        std::string error = verif_friend(pseudo);
        if(error == "null"){
            pseudo_line->hide();
            user_label->hide();
            ok_button_a->hide();
        }
    });
    connect(friends_table,&QAbstractItemView::clicked,this,[this,friendlist](const QModelIndex& idx){
        if(idx.column()==2){ //del
            int i = idx.row();
            char* pseudo2 = const_cast<char*>(friendlist[i].pseudo);
            _client.delFriend(pseudo2);
            print_friends();
        }
    });
    connect(request_table,&QAbstractItemView::clicked,this,[this,requestlist](const QModelIndex& idx){
        if(idx.column()==2){ //accept
            int i = idx.row();
            char* pseudo2 = const_cast<char*>(requestlist[i].pseudo);
            _client.addFriend(pseudo2);
        }
        else if(idx.column()==3){ //decline
            int i = idx.row();
            char* pseudo2 = const_cast<char*>(requestlist[i].pseudo);
           _client.delFriendRequest(pseudo2);
        }
        print_friends();
    });
    this->setCentralWidget(centralwidget);
    this->show();
}

std::string MenuGui::verif_friend(std::string pseudo, bool adding){
    //Aissa: all error are already in screen ==> c'est pas écrit pour decorer :-)
    char* pseudo2 = const_cast<char*>(pseudo.c_str());
    std::string error;
    int success; 
    if(adding){
        success = _client.sendFriendRequest(pseudo2);
        if(success==1)
        error = ALREADY_REQUESTED;
        else if (success==2)
            error = ALREADY_FRIENDS;
        else if(success==3)
            error = NO_USER_MSG;
        else if(success==4)
            error = YOURSEL_MSG;
        else
            error = "null";
    }
    else
        success = _client.delFriend(pseudo2);
        if(success==1)
            error = NOT_FRIENDS;
        else if (success==2)
           error = NO_USER_MSG;
        else if(success==3)
            error = YOURSEL_MSG;
        else
           error = "null";

    return error;
}


void MenuGui::lobby(std::string my_level, bool from_lead){
    QWidget *centralwidget =  new QWidget(this);
    set_background(centralwidget);
    set_title(centralwidget, "images/titles/lobby");

    QLabel *players_label;
    QComboBox *players_combo;
    QLabel *ally_label;
    QComboBox *ally_combo;
    QLabel *difficulty_label;
    QComboBox *difficulty_combo;
    QLabel *lives_label;
    QLabel *droprate_label;
    QSpinBox *lives_spin;
    QSpinBox *droprate_spin;
    QPushButton *play_button;
    QPushButton *cancel_button;
    std::vector<std::string> players_str{"1", "2"};
    std::vector<std::string> ally_str{"YES", "NO"};
    std::vector<std::string> difficulty_str{"EASY", "NORMAL", "HARD"};

    QLabel *label[7];

    std::string legende[7] = {"Username", "Password","players", "Ally shot", "Difficulty","Lives","Droprate"};
    int user=0, pass=1, player=2, ally=3, diff=4, live=5, drop=6;

    int posx[7]= {40, 40,40, 310,550,550,550};
    int posy[7]={290,370,200,200,200,290,380};
    int width = 91 , height = 17;

    for (int i = 0; i < 7; ++i){
        label[i] = create_label(centralwidget,legende[i], QRect(posx[i], posy[i], width, height));
    }

    QLineEdit *pseudo_lineEdit = create_line(centralwidget,QRect(160, 270, 341, 41),false);

    QLineEdit *password_lineEdit = create_line(centralwidget,QRect(160, 360, 341, 41),true);
    //password_lineEdit->setStyleSheet("color: black; background-color: white");
    players_combo = create_box(centralwidget, players_str, QRect(160, 200, 111, 21));
    players_combo->setStyleSheet("color: black; background-color: white");

    ally_combo = create_box(centralwidget, ally_str, QRect(390, 200, 111, 21));
    ally_combo->setStyleSheet("color: black; background-color: white");
    
    difficulty_combo = create_box(centralwidget, difficulty_str, QRect(660, 200, 111, 21));
    difficulty_combo->setStyleSheet("color: black; background-color: white");
    
    lives_spin = new QSpinBox(centralwidget);
    lives_spin->setGeometry(QRect(660, 280, 111, 26));
    lives_spin->setMaximum(3); 
    lives_spin->setMinimum(1);
    lives_spin->setStyleSheet("color: black; background-color: white");
    
    droprate_spin = new QSpinBox(centralwidget);
    droprate_spin->setGeometry(QRect(660, 370, 111, 26));
    droprate_spin->setMaximum(100); 
    droprate_spin->setSuffix(" %"); //fait pas att à la surbrillance : juste une fail
    droprate_spin->setStyleSheet("color: black; background-color: white");

    play_button = create_button(centralwidget, "images/buttons/play", 140, 470, QRect(140, 470, 201, 51));
    cancel_button = create_button(centralwidget, "images/buttons/back2", 480, 470, QRect(480, 470, 201, 51));

    pseudo_lineEdit->hide();
    password_lineEdit->hide();
    label[pass]->hide();
    label[user]->hide();

    connect(players_combo, QOverload<int>::of(&QComboBox::currentIndexChanged),[this,pseudo_lineEdit,password_lineEdit,pass,user,label](int idx){
         if(idx==1){
            pseudo_lineEdit->show();
            password_lineEdit->show();
            label[user]->show();
            label[pass]->show();
        }
        else{
            pseudo_lineEdit->hide();
            password_lineEdit->hide();
            label[pass]->hide();
            label[user]->hide();
        }
    });
    //connections
    connect(cancel_button, &QPushButton::clicked, this,[this, my_level, from_lead](){
        if(my_level=="0")
            main_m();
        else if(from_lead)
            view_level(!from_lead);
        else
            view_level(from_lead);
    });
    connect(play_button, &QPushButton::clicked, this,[this, players_combo, lives_spin, ally_combo, droprate_spin, difficulty_combo, my_level,from_lead,pseudo_lineEdit,password_lineEdit](){
        Parsing::Game_settings setting; 
        _client.get_pseudo(setting.pseudo_hote);
        
        std::string difficulty = (difficulty_combo->currentText()).toStdString();
        strcpy(setting.difficulty_str, difficulty.c_str());

        setting.diff = !strcmp(setting.difficulty_str,"easy")? easy: !strcmp(setting.difficulty_str,"medium")? medium :hard;
        setting.drop_rate =  droprate_spin->value();
        setting.nb_lives = lives_spin->value();
        setting.ally_shot = ((ally_combo->currentText()).toStdString()).compare("Yes") == 0;
        setting.nb_player = (players_combo->currentText()).toInt();

        char game_sett_char[Constante::CHAR_SIZE];
        if(setting.nb_player==2){
            std::string pseudo = (password_lineEdit->text()).toUtf8().constData();
            std::string pswd = (pseudo_lineEdit->text()).toUtf8().constData();
            bool success =0;
    
            if(pseudo.compare(std::string(setting.pseudo_hote)) != 0)
                success = _client.signIn(pseudo.c_str(), pswd.c_str(), false);

            if(not success)
                return;
        }

        Parsing::create_game_to_str(game_sett_char,&setting);
        if(my_level=="0")
            _client.createGame(game_sett_char);
        else
            _client.playLevel(my_level,game_sett_char);

        std::cout << "level a jouer = "<<my_level<<std::endl;
        std::cout << "settings lobby  = "<<game_sett_char<<std::endl;
        launch_game();
       
    });
    
    this->setCentralWidget(centralwidget);
    this->show();
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
    QPixmap pix_title("images/titles/level_lab");
    pix_title = pix_title.scaled(title_label->size(),Qt::KeepAspectRatio);
    title_label->setPixmap( pix_title);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setAttribute(Qt::WA_TranslucentBackground);

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
        copy_level.obs_list[idx].x = spin_box[0]->value();
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


