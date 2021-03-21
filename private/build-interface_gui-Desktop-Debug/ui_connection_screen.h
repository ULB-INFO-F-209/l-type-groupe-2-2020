/********************************************************************************
** Form generated from reading UI file 'connection_screen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTION_SCREEN_H
#define UI_CONNECTION_SCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_connection_screen
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *name_pwd_layout;
    QLabel *error_label;
    QVBoxLayout *name_layout;
    QHBoxLayout *phrase_de_aissa_layout;
    QLabel *name_label;
    QLineEdit *lineEdit_2;
    QLabel *titre_label_connct_screen;
    QVBoxLayout *pwd_layout;
    QLabel *pwd_label;
    QLineEdit *lineEdit_3;

    void setupUi(QMainWindow *connection_screen)
    {
        if (connection_screen->objectName().isEmpty())
            connection_screen->setObjectName(QString::fromUtf8("connection_screen"));
        connection_screen->resize(1000, 600);
        connection_screen->setStyleSheet(QString::fromUtf8("background-color:lightblue"));
        centralwidget = new QWidget(connection_screen);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 30, 971, 551));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        name_pwd_layout = new QVBoxLayout();
        name_pwd_layout->setSpacing(8);
        name_pwd_layout->setObjectName(QString::fromUtf8("name_pwd_layout"));
        name_pwd_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        name_pwd_layout->setContentsMargins(20, 20, 20, 20);
        error_label = new QLabel(widget);
        error_label->setObjectName(QString::fromUtf8("error_label"));

        name_pwd_layout->addWidget(error_label);

        name_layout = new QVBoxLayout();
        name_layout->setSpacing(8);
        name_layout->setObjectName(QString::fromUtf8("name_layout"));
        name_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        name_layout->setContentsMargins(40, 20, 2, 20);
        phrase_de_aissa_layout = new QHBoxLayout();
        phrase_de_aissa_layout->setObjectName(QString::fromUtf8("phrase_de_aissa_layout"));

        name_layout->addLayout(phrase_de_aissa_layout);

        name_label = new QLabel(widget);
        name_label->setObjectName(QString::fromUtf8("name_label"));
        name_label->setCursor(QCursor(Qt::ArrowCursor));
        name_label->setLayoutDirection(Qt::LeftToRight);
        name_label->setAlignment(Qt::AlignCenter);

        name_layout->addWidget(name_label);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setMaximumSize(QSize(800, 40));

        name_layout->addWidget(lineEdit_2);


        name_pwd_layout->addLayout(name_layout);

        titre_label_connct_screen = new QLabel(widget);
        titre_label_connct_screen->setObjectName(QString::fromUtf8("titre_label_connct_screen"));
        titre_label_connct_screen->setMaximumSize(QSize(800, 40));
        QFont font;
        font.setPointSize(20);
        titre_label_connct_screen->setFont(font);
        titre_label_connct_screen->setAlignment(Qt::AlignCenter);

        name_pwd_layout->addWidget(titre_label_connct_screen);

        pwd_layout = new QVBoxLayout();
        pwd_layout->setSpacing(8);
        pwd_layout->setObjectName(QString::fromUtf8("pwd_layout"));
        pwd_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        pwd_layout->setContentsMargins(40, 20, 2, 20);
        pwd_label = new QLabel(widget);
        pwd_label->setObjectName(QString::fromUtf8("pwd_label"));
        pwd_label->setMaximumSize(QSize(800, 30));
        pwd_label->setTextFormat(Qt::AutoText);
        pwd_label->setAlignment(Qt::AlignCenter);

        pwd_layout->addWidget(pwd_label);

        lineEdit_3 = new QLineEdit(widget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setMaximumSize(QSize(800, 40));

        pwd_layout->addWidget(lineEdit_3);


        name_pwd_layout->addLayout(pwd_layout);


        verticalLayout->addLayout(name_pwd_layout);

        connection_screen->setCentralWidget(centralwidget);

        retranslateUi(connection_screen);

        QMetaObject::connectSlotsByName(connection_screen);
    } // setupUi

    void retranslateUi(QMainWindow *connection_screen)
    {
        connection_screen->setWindowTitle(QApplication::translate("connection_screen", "MainWindow", nullptr));
        error_label->setText(QApplication::translate("connection_screen", "Future erreur", nullptr));
        name_label->setText(QApplication::translate("connection_screen", "Name :", nullptr));
        titre_label_connct_screen->setText(QApplication::translate("connection_screen", "Conncetion", nullptr));
        pwd_label->setText(QApplication::translate("connection_screen", "Passeword  : ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class connection_screen: public Ui_connection_screen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTION_SCREEN_H
