#include "InterfaceGUI.hpp"

InterfaceGUI::InterfaceGUI():QMainWindow(){
    setupInitUi();
}

void InterfaceGUI::setupInitUi(){
    // setup de la fenetre
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("L-Type"));
    this->resize(1000, 600);
    this->setStyleSheet(QString::fromUtf8("background-color:lightsalmon"));
    
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    verticalLayoutWidget = new QWidget(centralWidget);
    verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(380, 180, 241, 301));
    buttonsVerticalLayout = new QVBoxLayout(verticalLayoutWidget);
    buttonsVerticalLayout->setSpacing(8);
    buttonsVerticalLayout->setContentsMargins(11, 11, 11, 11);
    buttonsVerticalLayout->setObjectName(QString::fromUtf8("buttonsVerticalLayout"));
    buttonsVerticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    buttonsVerticalLayout->setContentsMargins(40, 20, 2, 20);
    SignIn = new QPushButton(verticalLayoutWidget);
    SignIn->setObjectName(QString::fromUtf8("SignIn"));
    SignIn->setMaximumSize(QSize(165, 61));
    QIcon icon;
    QString iconThemeName = QString::fromUtf8("image/sign_in");
    if (QIcon::hasThemeIcon(iconThemeName)) {
        icon = QIcon::fromTheme(iconThemeName);
    } else {
        icon.addFile(QString::fromUtf8("../../../../../../media/sf_Partage_Ubuntu"), QSize(), QIcon::Normal, QIcon::Off);
    }
    SignIn->setIcon(icon);
    SignIn->setFlat(false);

    buttonsVerticalLayout->addWidget(SignIn);

    SignUp = new QPushButton(verticalLayoutWidget);
    SignUp->setObjectName(QString::fromUtf8("SignUp"));
    SignUp->setMaximumSize(QSize(165, 61));

    buttonsVerticalLayout->addWidget(SignUp);

    Quit = new QPushButton(verticalLayoutWidget);
    Quit->setObjectName(QString::fromUtf8("Quit"));
    Quit->setMaximumSize(QSize(165, 61));

    buttonsVerticalLayout->addWidget(Quit);

    horizontalLayoutWidget = new QWidget(centralWidget);
    horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
    horizontalLayoutWidget->setGeometry(QRect(80, 30, 851, 80));
    horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    this->setCentralWidget(centralWidget);

    retranslateUi();
    QObject::connect(Quit, SIGNAL(clicked()), this, SLOT(close()));

    
} // setupUi

void InterfaceGUI::retranslateUi(){
    this->setWindowTitle(QApplication::translate("L-Type", "L-Type", nullptr));
    SignIn->setText(QApplication::translate("L-Type", "Sign in", nullptr));
    SignUp->setText(QApplication::translate("L-Type", "Sign up", nullptr));
    Quit->setText(QApplication::translate("L-Type", "Quit", nullptr));
}

void InterfaceGUI::setupConnectetUi(){

    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *name_pwd_layout;
    QGridLayout *gridLayout;
    QPushButton *quit_button;
    QLabel *titre_label_connct_screen;
    QVBoxLayout *name_layout;
    QLabel *name_label;
    QLineEdit *lineEdit_2;
    QLabel *error_label;
    QVBoxLayout *pwd_layout;
    QLabel *pwd_label;
    QLineEdit *lineEdit_3;
    QMainWindow *connection_screen = new QMainWindow();

    if (connection_screen->objectName().isEmpty())
            connection_screen->setObjectName(QString::fromUtf8("connection_screen"));
        connection_screen->resize(1000, 600);
        connection_screen->setStyleSheet(QString::fromUtf8("background-color:lightblue"));
        centralwidget = new QWidget(connection_screen);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 20, 969, 569));
        name_pwd_layout = new QVBoxLayout(verticalLayoutWidget_3);
        name_pwd_layout->setSpacing(8);
        name_pwd_layout->setObjectName(QString::fromUtf8("name_pwd_layout"));
        name_pwd_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        name_pwd_layout->setContentsMargins(20, 20, 20, 20);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        quit_button = new QPushButton(verticalLayoutWidget_3);
        quit_button->setObjectName(QString::fromUtf8("quit_button"));
        quit_button->setMaximumSize(QSize(50, 30));
        quit_button->setFlat(true);

        gridLayout->addWidget(quit_button, 0, 0, 1, 1);

        titre_label_connct_screen = new QLabel(verticalLayoutWidget_3);
        titre_label_connct_screen->setObjectName(QString::fromUtf8("titre_label_connct_screen"));
        titre_label_connct_screen->setMaximumSize(QSize(900, 50));
        QFont font;
        font.setPointSize(20);
        titre_label_connct_screen->setFont(font);
        titre_label_connct_screen->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(titre_label_connct_screen, 1, 0, 1, 2);


        name_pwd_layout->addLayout(gridLayout);

        name_layout = new QVBoxLayout();
        name_layout->setSpacing(8);
        name_layout->setObjectName(QString::fromUtf8("name_layout"));
        name_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        name_layout->setContentsMargins(40, 20, 2, 20);
        name_label = new QLabel(verticalLayoutWidget_3);
        name_label->setObjectName(QString::fromUtf8("name_label"));
        name_label->setMaximumSize(QSize(800, 40));
        name_label->setCursor(QCursor(Qt::ArrowCursor));
        name_label->setLayoutDirection(Qt::LeftToRight);
        name_label->setAlignment(Qt::AlignCenter);

        name_layout->addWidget(name_label);

        lineEdit_2 = new QLineEdit(verticalLayoutWidget_3);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setMaximumSize(QSize(800, 40));

        name_layout->addWidget(lineEdit_2);


        name_pwd_layout->addLayout(name_layout);

        error_label = new QLabel(verticalLayoutWidget_3);
        error_label->setObjectName(QString::fromUtf8("error_label"));
        error_label->setMaximumSize(QSize(800, 40));

        name_pwd_layout->addWidget(error_label);

        pwd_layout = new QVBoxLayout();
        pwd_layout->setSpacing(8);
        pwd_layout->setObjectName(QString::fromUtf8("pwd_layout"));
        pwd_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        pwd_layout->setContentsMargins(40, 20, 2, 20);
        pwd_label = new QLabel(verticalLayoutWidget_3);
        pwd_label->setObjectName(QString::fromUtf8("pwd_label"));
        pwd_label->setMaximumSize(QSize(800, 30));
        pwd_label->setTextFormat(Qt::AutoText);
        pwd_label->setAlignment(Qt::AlignCenter);

        pwd_layout->addWidget(pwd_label);

        lineEdit_3 = new QLineEdit(verticalLayoutWidget_3);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setMaximumSize(QSize(800, 40));

        pwd_layout->addWidget(lineEdit_3);


        name_pwd_layout->addLayout(pwd_layout);

        connection_screen->setCentralWidget(centralwidget);

        connection_screen->setWindowTitle(QApplication::translate("connection_screen", "MainWindow", nullptr));
        quit_button->setText(QApplication::translate("connection_screen", "Quit", nullptr));
        titre_label_connct_screen->setText(QApplication::translate("connection_screen", "CONNECTION", nullptr));
        name_label->setText(QApplication::translate("connection_screen", "Name :", nullptr));
        error_label->setText(QApplication::translate("connection_screen", "Future erreur", nullptr));
        pwd_label->setText(QApplication::translate("connection_screen", "Passeword  : ", nullptr));
}

void InterfaceGUI::on_SignIn_clicked(){
    
}


