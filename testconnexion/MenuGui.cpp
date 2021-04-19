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
    QWidget *centralWidget = new QWidget(this);
    set_background(centralWidget);
    set_title(centralWidget, "images/titles/home");

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
    std::string home_buttons[SIZE_HOME] = {"images/buttons/signIn", "images/buttons/signUp", "images/buttons/quit"};
    for (size_t i = 0; i < SIZE_HOME; ++i){
       home_button[i] = create_button(verticalLayoutWidget, home_buttons[i], 200, 200);
       button_v_layout->addWidget(home_button[i]);
   }
    connect(home_button[signIn], &QPushButton::clicked, this, [this]() {
       connexion(true);
   });
    connect(home_button[signUp], &QPushButton::clicked, this, [this]() {
       connexion(false);
   });
    connect(home_button[quit], &QPushButton::clicked, this,  &MenuGui::close);

    this->setCentralWidget(centralWidget);
}

QLabel * MenuGui::print_error(QWidget *parent, int error, QRect pos){
    std::cout << " ERROR "<<error<<std::endl;
    QLabel *error_label; 
    switch(error){
        case LEN_ERROR:
            error_label = create_label(parent,SHORT_ALL , pos);
            break;
        case LEN_PSEUDO:
            error_label = create_label(parent, SHORT_PSEUDO, pos);
            break;
        case LEN_PSWD:
            error_label = create_label(parent, SHORT_PSWD, pos);
            break;
        case NO_USER_ERROR:
            error_label = create_label(parent, NO_USER_MSG, pos);
            break;
        case TAKEN_PSEUDO:
            error_label = create_label(parent, TAKEN_PSEUDO_MSG, pos);
            break;
        case FRIENDS_ALREADY:
            error_label = create_label(parent,ALREADY_FRIENDS , pos);
            break;
        case FRIENDS_YET:
            error_label = create_label(parent, NOT_FRIENDS, pos);
            break;
        case REQ_ALREADY:
            error_label = create_label(parent, ALREADY_REQUESTED, pos);
            break;
        case YOURSELF_ERROR:
            error_label = create_label(parent, YOURSEL_MSG, pos);
            break;
        case NO_ERROR:
            error_label = create_label(parent, "", pos);
            break;
        default:
            error_label = create_label(parent, DEFAULT_ERROR, pos);
            break; 
    }
    error_label->setStyleSheet("QLabel { background-color : black; color : red; }");
    error_label->show();
    return error_label;
}

int MenuGui::check_data(QLineEdit *pseudo_line, QLineEdit *pswd_line, bool sign_in){
    std::string pseudo = (pseudo_line->text()).toUtf8().constData();
    std::string pswd = (pswd_line->text()).toUtf8().constData();
    int error = NO_ERROR;
    int success;

    if(pswd.size() < NB_MIN_CARA and pseudo.size() < NB_MIN_CARA)
        return LEN_ERROR;
    if(pseudo.size() < NB_MIN_CARA)
        return LEN_PSEUDO;
    if(pswd.size() < NB_MIN_CARA)
        return LEN_PSWD;

    if(sign_in){
        success = _client.signIn(pseudo.c_str(), pswd.c_str());
        if(success)
            main_m();
        else
            error = NO_USER_ERROR;
    }
    else{
        success = _client.signUp(pseudo.c_str(), pswd.c_str());
        if(success)
            main_m();
        else
            error = TAKEN_PSEUDO;
    }

    return error;
}

void MenuGui::set_background(QWidget *centralwidget){
    centralwidget->setStyleSheet(QStringLiteral("background-color:black;"));
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

QPushButton *MenuGui::create_button(QWidget *parent,std::string image, QRect size){
    QPushButton * button = new QPushButton(parent);
    button->setGeometry(size);
    QPixmap pix(QString::fromStdString(image));
    pix = pix.scaled(button->size(),Qt::KeepAspectRatio);
    QIcon icon(pix);
    button->setIcon(icon);
    button->setIconSize(QSize(size.width(), size.height()));
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

    create_label(centralWidget, "Username : ", QRect(140, 270, 91, 45));
    create_label(centralWidget, "Password : ", QRect(130, 370, 101, 45));

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

    if(sign_in)
        set_title(centralWidget, "images/titles/signIn");
    else
        set_title(centralWidget, "images/titles/signUp");

    connect(ok_button, &QPushButton::clicked, this, [this,sign_in,pseudo_line,pswd_line,centralWidget]() {
           int error = check_data(pseudo_line,pswd_line,sign_in);
           if(error != NO_ERROR)
                print_error(centralWidget, error, QRect(230, 325, 400, 45));
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
       button[i] = create_button(centralWidget,pix_main[i],rects[i]);
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
    set_title(centralWidget, "images/titles/profile");

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

    QPushButton* back = create_button(centralWidget, "images/buttons/back2", QRect(270, 470, 261, 61));
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
    set_title(centralWidget, "images/titles/leaderboard");

    std::string titles[] = {"USERNAME", "SCORE"};
    QTableWidget *tableWidget = create_table_widget(centralWidget, 2, profile_list.size(), titles, QRect(275, 180, 250, 300));
    
    tableWidget->horizontalHeader()->setMinimumSectionSize(106);
    tableWidget->horizontalHeader()->setMaximumSectionSize(106);
    tableWidget->horizontalHeader()->setDefaultSectionSize(106);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setShowGrid(false);

    QPushButton* back = create_button(centralWidget, "images/buttons/back2", QRect(270, 510, 261, 61));
    connect(back, &QPushButton::clicked, this,&MenuGui::main_m);

    for (size_t i = 0; i < profile_list.size(); i++){
        tableWidget->setItem(i, 0, new QTableWidgetItem(profile_list[i].pseudo));
        int score = profile_list[i].score;
        char buff[20];
        sprintf(buff, "%d", score);
        tableWidget->setItem(i, 1, new QTableWidgetItem(buff));
    }
    
    this->setCentralWidget(centralWidget);
    this->show();
}

void MenuGui::level_menu(){
    QWidget *centralwidget = new QWidget(this);
    set_background(centralwidget);
    set_title(centralwidget,"images/titles/levelEditor");

    QPushButton * button[4]; 
    int create = 0, ranking=1, my_levels = 2, back=3;
    std::string path = "images/buttons/editor/";
    std::string pathIcon[] = { path+"create_level", path+"level_ranking", path+"my_levels", path+"back"};
    QRect rects[] = {QRect(30, 260, 180, 150), QRect(300, 260, 180, 150), QRect(560, 260, 180, 150), QRect(310, 460, 170,120)};
   
    for( int i = 0; i < 4; i++){
        button[i] = create_button(centralwidget, pathIcon[i], rects[i]);
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
    centralwidget->setStyleSheet(QStringLiteral("background-color:black;"));

    QLabel *lbl = new QLabel(centralwidget);
    QMovie *mv = new QMovie("images/background/ciel.gif");
    mv->setScaledSize(QSize(923, 758));
    lbl->setGeometry(QRect(0, 0, 923, 758));
    mv->start();
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    lbl->setMovie(mv);

    QLabel *title_label = new QLabel(centralwidget);
    title_label->setGeometry(QRect(161, 0, 600, 150));
    QPixmap pix_home_title(QString::fromStdString("images/titles/friends"));
    pix_home_title = pix_home_title.scaled(title_label->size(),Qt::KeepAspectRatio);
    title_label->setPixmap( pix_home_title);
    title_label->setAlignment(Qt::AlignCenter);

    QPushButton *ok_button_a = new QPushButton("OK",centralwidget); //add
    ok_button_a->setGeometry(QRect(690, 580, 91, 41));
    ok_button_a->setStyleSheet("color: black; background-color: white");

    QLineEdit *pseudo_line = create_line(centralwidget,QRect(220, 580, 441, 41),false);
    QLabel *user_label = create_label(centralwidget, "USERNAME",QRect(100, 580, 101, 41));
    
    pseudo_line->hide();
    user_label->hide();
    ok_button_a->hide();

    QPushButton *back_button = create_button(centralwidget, "images/buttons/editor/back", QRect(380, 620, 180, 150));

    std::string titles_friends[] = {"USERNAME", "SCORE", "DELETE"};
    std::string titles_request[] = {"USERNAME", "SCORE", "ACCEPT", "DECLINE"};
    QTableWidget *friends_table = create_table_widget(centralwidget,3,friendlist.size(), titles_friends,QRect(0, 170, 402, 371));
    QTableWidget *request_table = create_table_widget(centralwidget,4,requestlist.size(), titles_request,QRect(530, 170, 392, 371));
    
    friends_table->horizontalHeader()->setMinimumSectionSize(129);
    friends_table->horizontalHeader()->setMaximumSectionSize(129);
    friends_table->horizontalHeader()->setDefaultSectionSize(129);

    request_table->horizontalHeader()->setMinimumSectionSize(94);
    request_table->horizontalHeader()->setMaximumSectionSize(94);
    request_table->horizontalHeader()->setDefaultSectionSize(94);

    QPushButton *add_button = new QPushButton("ADD",centralwidget);
    add_button->setGeometry(QRect(410, 300, 111, 41));
    add_button->setStyleSheet("color: black; background-color: white");
    
    QLabel *friends_title =  create_label(centralwidget,"FRIENDS", QRect(40, 120, 321, 41));
    friends_title->setFrameShape(QFrame::WinPanel);
    friends_title->setAlignment(Qt::AlignCenter);
    QLabel *request_label = create_label(centralwidget,"REQUESTS",QRect(570, 120, 321, 41) );
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
    connect(ok_button_a, &QPushButton::clicked, this,[this,pseudo_line, user_label,ok_button_a,centralwidget](){
        std::string pseudo = (pseudo_line->text()).toUtf8().constData();
        int  error = verif_friend(pseudo);
        if(error == NO_ERROR){
            pseudo_line->setText("");
            pseudo_line->hide();
            user_label->hide();
            ok_button_a->hide();
            print_error(centralwidget, error, QRect(220, 620, 441, 41));
        }
        else{
            print_error(centralwidget, error, QRect(220, 620, 441, 41));
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

int MenuGui::verif_friend(std::string pseudo){
    //Aissa: all error are already in screen ==> c'est pas écrit pour decorer :-)
    char* pseudo2 = const_cast<char*>(pseudo.c_str());
    int error = NO_ERROR;
    int success = 0; 
    if(pseudo.size() < NB_MIN_CARA)
        return LEN_PSEUDO;

    success = _client.sendFriendRequest(pseudo2);
    if(success==1)
        error = REQ_ALREADY;
    else if (success==2)
        error = FRIENDS_ALREADY;
    else if(success==3)
        error = NO_USER_ERROR;
    else if(success==4)
        error = YOURSELF_ERROR;

    return error;
}


void MenuGui::lobby(std::string my_level, bool from_lead){
    QWidget *centralwidget =  new QWidget(this);
    set_background(centralwidget);
    set_title(centralwidget, "images/titles/lobby");

    QComboBox *players_combo;
    QComboBox *ally_combo;
    QComboBox *difficulty_combo;
    QSpinBox *lives_spin;
    QSpinBox *droprate_spin;
    QPushButton *play_button;
    QPushButton *cancel_button;
    std::vector<std::string> players_str{"1", "2"};
    std::vector<std::string> ally_str{"YES", "NO"};
    std::vector<std::string> difficulty_str{"EASY", "MEDIUM", "HARD"};

    QLabel *label[7];

    std::string legende[7] = {"Username", "Password","players", "Friendly fire", "Difficulty","Lives","Droprate"};
    int user=0, pass=1, ally=3;

    int posx[7]= {40, 40,40, 295,550,550,550};
    int posy[7]={290,370,200,200,200,290,380};
    int width = 91 , height = 17;

    for (int i = 0; i < 7; ++i)
        label[i] = create_label(centralwidget,legende[i], QRect(posx[i], posy[i], width, height));

    QLineEdit *pseudo_lineEdit = create_line(centralwidget,QRect(160, 270, 341, 41),false);
    QLineEdit *password_lineEdit = create_line(centralwidget,QRect(160, 360, 341, 41),true);

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

    play_button = create_button(centralwidget, "images/buttons/play", QRect(140, 470, 201, 51));
    cancel_button = create_button(centralwidget, "images/buttons/back2", QRect(480, 470, 201, 51));

    pseudo_lineEdit->hide();
    password_lineEdit->hide();
    ally_combo->hide();
    label[pass]->hide();
    label[user]->hide();
    label[ally]->hide();

    connect(players_combo, QOverload<int>::of(&QComboBox::currentIndexChanged),[this,pseudo_lineEdit,password_lineEdit,ally_combo,pass,user,ally,label,centralwidget](int idx){
         if(idx==1){
            pseudo_lineEdit->show();
            password_lineEdit->show();
            ally_combo->show();
            label[user]->show();
            label[pass]->show();
            label[ally]->show();
        }
        else{
            pseudo_lineEdit->hide();
            password_lineEdit->hide();
            ally_combo->hide();
            label[pass]->hide();
            label[user]->hide();
            label[ally]->hide();
            print_error(centralwidget,NO_ERROR, QRect(160, 400, 341, 41));
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
    connect(play_button, &QPushButton::clicked, this,[this, players_combo, lives_spin, ally_combo, droprate_spin, difficulty_combo, my_level,from_lead,pseudo_lineEdit,password_lineEdit,centralwidget](){
        Parsing::Game_settings setting; 
        _client.get_pseudo(setting.pseudo_hote);
        
        std::string difficulty = (difficulty_combo->currentText()).toStdString();

        std::for_each(difficulty.begin(), difficulty.end(), [](char & c){
            c = ::tolower(c);
        });
        strcpy(setting.difficulty_str, difficulty.c_str());

        setting.diff = !strcmp(setting.difficulty_str,"easy")? easy: !strcmp(setting.difficulty_str,"medium")? medium :hard;
        std::cout << "la diff : " << setting.difficulty_str << std::endl;
        setting.drop_rate =  droprate_spin->value();
        setting.nb_lives = lives_spin->value();
        setting.ally_shot = ally_combo->currentIndex() == 0? 1:0;
        setting.nb_player = (players_combo->currentText()).toInt();

        char game_sett_char[Constante::CHAR_SIZE];
        if(setting.nb_player==2){
            std::string pseudo = (password_lineEdit->text()).toUtf8().constData();
            std::string pswd = (pseudo_lineEdit->text()).toUtf8().constData();
                if(pswd.size() < NB_MIN_CARA and pseudo.size() < NB_MIN_CARA){
                    print_error(centralwidget,LEN_ERROR, QRect(160, 400, 341, 41));
                    return;
                }
                if(pseudo.size() < NB_MIN_CARA){
                    print_error(centralwidget,LEN_PSEUDO, QRect(160, 400, 341, 41));
                    return ;
                }
                if(pswd.size() < NB_MIN_CARA){
                    print_error(centralwidget,LEN_PSWD, QRect(160, 400, 341, 41));
                    return ;
                }
            
            bool success =0;
    
            if(pseudo.compare(std::string(setting.pseudo_hote)) == 0){
                print_error(centralwidget,YOURSELF_ERROR, QRect(160, 400, 341, 41));
                return;
            }
            else{
                success = _client.signIn(pseudo.c_str(), pswd.c_str(), false);
                if(not success){
                    print_error(centralwidget,NO_USER_ERROR, QRect(160, 400, 341, 41));
                    return;
                }
                else{
                    strcpy(setting.pseudo_other,pseudo.c_str());

                }
            }
                
        }

        Parsing::create_game_to_str(game_sett_char,&setting);
        if(my_level=="0")
            _client.createGame(game_sett_char);
        else
            _client.playLevel(my_level,game_sett_char);
        this->hide();
        launch_game();
        this->show();
        std::cout << "i'm back bg"<<std::endl;
       
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
    tick_slider->setTickInterval(10);
    tick_slider->setMaximum(200);
    tick_slider->setSingleStep(1);
    tick_slider->setPageStep(1);
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
    for(size_t i = 0; i < my_level.enemy_list.size(); i++){
        ClickableLabel * e = new ClickableLabel(static_cast<int>(i),0,game_zone);
        QPixmap pix1("images/custom/e1.png");
        pix1 = pix1.scaled(QSize(button_size,button_size));
        QPixmap pix2("images/custom/e2.png");
        pix2 = pix2.scaled(QSize(button_size,button_size));
        my_level.enemy_list[i].skin == 0 ? e->setPixmap(pix1): e->setPixmap(pix2);
        
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

    for(size_t i = 0; i < my_level.obs_list.size(); i++){
        ClickableLabel * e = new ClickableLabel(static_cast<int>(i),1,game_zone);
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
        for(size_t i = 0; i < my_level.enemy_list.size(); i++){
            if(my_level.enemy_list[i].tick != tick_lcd->intValue()){
               game_zone->get_enemy(i)->hide();
            }
            else{
                game_zone->get_enemy(i)->show();
            }
        }
        for(size_t i = 0; i < my_level.obs_list.size(); i++){
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
    //QLineEdit *name_edit = new QLineEdit(horizontalLayoutWidget_2);
    QLineEdit *name_edit = create_line(Dialog,QRect(230, 270, 400, 45),false);
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
        level_editor(my_level);
    });
    connect(cancel, &QPushButton::clicked, this, [this, Dialog, my_level](){
        Dialog->hide();
        this->setFixedSize(800,600);
        level_editor(my_level);
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
    int tick=1; 
    std::string legende[] = {"HP :","TIME :","DAMAGE :"};
    QLabel *label[3];
    int spin_value[3]; my_level.enemy_list[idx].get_values(spin_value);
    QSpinBox * spin_box[3];
    for (int i = 0; i < 3; ++i){
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
    spin_box[tick]->setMaximum(3000);
    spin_box[tick]->setSingleStep(1);
    spin_box[tick]->setValue(spin_value[tick]);
    //spin_box[tick]->findChild<QLineEdit*>()->setReadOnly(true);

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

    QRadioButton * skin[2];
    for (int i = 0; i < 2; ++i){
        skin[i] = new QRadioButton( widget);
        skin[i]->setMinimumSize(QSize(100, 100));
        skin[i]->setMaximumSize(QSize(100, 100));
        if(i == my_level.enemy_list[idx].skin)
             skin[i]->setChecked(true);
        verticalLayout->addWidget(skin[i]);
    }
    QIcon icon;
    icon.addFile(QString::fromUtf8("enemy.png"), QSize(), QIcon::Normal, QIcon::On);
    skin[0]->setIcon(icon);
    skin[0]->setIconSize(QSize(100, 100));
    icon.addFile(QString::fromUtf8("enemy2.png"), QSize(), QIcon::Normal, QIcon::On);
    skin[1]->setIcon(icon);
    skin[1]->setIconSize(QSize(100, 100));


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
        //copy_level.enemy_list[idx].x = spin_box[0]->value();
        copy_level.enemy_list[idx].hp = spin_box[0]->value();
        copy_level.enemy_list[idx].tick = spin_box[1]->value();
        copy_level.enemy_list[idx].damage = spin_box[2]->value();
        for (int i = 0; i < 4; ++i){
            if(bonus[i]->isChecked())
                copy_level.enemy_list[idx].bonus = i;
        }

        for (int i = 0; i < 2; ++i){
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
    Dialog->resize(548, 480);
    Dialog->setModal(true);

    QLabel * title_label = new QLabel("CUSTOM OBSTACLE", Dialog);
    title_label->setGeometry(QRect(160, 20, 181, 51));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setAlignment(Qt::AlignCenter);

    /*************SPIN AND THEIR LEGENDE ZONE********************/
    QWidget *formLayoutWidget = new QWidget(Dialog);
    formLayoutWidget->setGeometry(QRect(150, 99, 251, 251));
     QFormLayout *formLayout = new QFormLayout(formLayoutWidget);
    int position = 0,tick=2; 
    std::string legende[] = {"POSITION :","HP :","TIME :","DAMAGE :"};
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
    spin_box[tick]->setSingleStep(1);
    spin_box[tick]->setValue(spin_value[tick]);

    /*************BUTTON_ZONE********************/
    QWidget *horizontalLayoutWidget = new QWidget(Dialog);
    horizontalLayoutWidget->setGeometry(QRect(100, 360, 371, 50));
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

    /***************CONNECTION********************/
    connect(button[ok], &QPushButton::clicked, this, [this, my_level,Dialog, spin_box, idx](){
        Parsing::Level copy_level = my_level;
        copy_level.obs_list[idx].x = spin_box[0]->value();
        copy_level.obs_list[idx].hp = spin_box[1]->value();
        copy_level.obs_list[idx].tick = spin_box[2]->value();
        copy_level.obs_list[idx].damage = spin_box[3]->value();

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
    Dialog->resize(548, 480);
    Dialog->setModal(true);

    QLabel * title_label = new QLabel("CUSTOM PLAYER", Dialog);
    title_label->setGeometry(QRect(180, 20, 181, 51));
    title_label->setFrameShape(QFrame::WinPanel);
    title_label->setAlignment(Qt::AlignCenter);

    /*************SPIN AND THEIR LEGENDE ZONE********************/
    QWidget *formLayoutWidget = new QWidget(Dialog);
    formLayoutWidget->setGeometry(QRect(150, 99, 251, 251));
    QFormLayout *formLayout = new QFormLayout(formLayoutWidget);
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
    //boss actif ?
    QComboBox *boss_box = new QComboBox(formLayoutWidget);
    boss_box->setMinimumSize(QSize(100, 45));
    boss_box->setMaximumSize(QSize(100, 45));
    formLayout->setWidget(4, QFormLayout::FieldRole, boss_box);
    boss_box->clear();
    QLabel *boss_label = new QLabel("BOSS :");
    formLayout->setWidget(4, QFormLayout::LabelRole, boss_label );
    boss_label->setMinimumSize(QSize(100, 45));
    boss_label->setMaximumSize(QSize(100, 45));
    boss_label->setAlignment(Qt::AlignCenter);
    std::string box_value2[] = {"Disable","Enable"};
    for(auto val :box_value2){
        boss_box->addItem(QString::fromStdString(val));
    }
    boss_box->setCurrentIndex(my_level.player.boss);

    /*************BUTTON_ZONE********************/
    QWidget *horizontalLayoutWidget = new QWidget(Dialog);
    horizontalLayoutWidget->setGeometry(QRect(100, 360, 371, 50));
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
    /***************CONNECTION********************/
    connect(button[ok], &QPushButton::clicked, this, [this, my_level,Dialog, spin_box/*, skin_player1, skin_player2,*/, speed_box,boss_box](){
        Parsing::Level copy_level = my_level;
        copy_level.player.speed = speed_box->currentIndex();
        copy_level.player.hp = spin_box[0]->value();
        copy_level.player.damage = spin_box[1]->value();
        copy_level.player.boss = boss_box->currentIndex();
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
    std::string res; 
    if(mine)
       res =  _client.myLevels();
    else
        res = _client.viewLevels();
    std::vector<Parsing::Creator> creator_list = Parsing::creator_list_from_str(res);

    QWidget *centralWidget = new QWidget(this);
    set_background(centralWidget);
    QPushButton* back = create_button(centralWidget, "images/buttons/back2", QRect(330, 505, 151, 80));
    connect(back, &QPushButton::clicked, this, &MenuGui::level_menu);

    std::string titles[] = {"Title", "Author", "Vote", "Play", "Like"};
    QTableWidget* tableWidget;
    int column_width;
    if(mine){
        tableWidget = create_table_widget(centralWidget, 4, creator_list.size(), titles, QRect(100, 160, 620, 341));
        set_title(centralWidget, "images/titles/myLevels");
        column_width = 620/4 - 1;
    }
    else{
        tableWidget = create_table_widget(centralWidget, 5, creator_list.size(), titles, QRect(100, 160, 620, 341));
        set_title(centralWidget, "images/titles/levelRanking");
        column_width = 620/5 - 1;
    }
    tableWidget->horizontalHeader()->setMinimumSectionSize(column_width);
    tableWidget->horizontalHeader()->setMaximumSectionSize(column_width);
    tableWidget->horizontalHeader()->setDefaultSectionSize(column_width);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setShowGrid(false);

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
        }
    }
    this->setCentralWidget(centralWidget);
    this->show();
}

void MenuGui::launch_game(){
	DisplayGameGui display_game;
	display_game.initGraphics();
	sf::RenderWindow* window = display_game.getWindow();

    bool gameOn = true;
    std::vector<int> inp;
	std::string string_game_to_display;
	std::string string_previous_game_to_display;

    while(gameOn && window->isOpen()){ 
		sf::Event event; 
        while (window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window->close();
                return;
            }
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
	
	while(true){ 
		char in_char = -1;
		while (window->pollEvent(event)){
			if (event.type == sf::Event::KeyPressed)
				in_char = display_game.getInputWindow(&inp);
        }
        if(in_char == 'p')break;
    }
	window->close();
}
