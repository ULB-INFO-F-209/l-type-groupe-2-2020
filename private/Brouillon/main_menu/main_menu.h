/********************************************************************************
** Form generated from reading UI file 'main_menu.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Main_menu
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Main_menu)
    {
        if (Main_menu->objectName().isEmpty())
            Main_menu->setObjectName(QStringLiteral("Main_menu"));
        Main_menu->resize(800, 600);
        centralwidget = new QWidget(Main_menu);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 30, 591, 61));
        label->setFrameShape(QFrame::WinPanel);
        label->setTextFormat(Qt::RichText);
        label->setAlignment(Qt::AlignCenter);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(80, 160, 651, 351));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(100, 0, 100, 0);
        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(25, 50));

        verticalLayout->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(pushButton_3);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(pushButton);

        pushButton_5 = new QPushButton(verticalLayoutWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(pushButton_5);

        Main_menu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Main_menu);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        Main_menu->setMenuBar(menubar);
        statusbar = new QStatusBar(Main_menu);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Main_menu->setStatusBar(statusbar);

        retranslateUi(Main_menu);

        QMetaObject::connectSlotsByName(Main_menu);
    } // setupUi

    void retranslateUi(QMainWindow *Main_menu)
    {
        Main_menu->setWindowTitle(QApplication::translate("Main_menu", "Main_menu", Q_NULLPTR));
        label->setText(QApplication::translate("Main_menu", "MAIN MENU", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Main_menu", "New Game", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("Main_menu", "Friends", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Main_menu", "Leaderboard", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Main_menu", "Profile", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("Main_menu", "Log Out", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Main_menu: public Ui_Main_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAIN_MENU_H
