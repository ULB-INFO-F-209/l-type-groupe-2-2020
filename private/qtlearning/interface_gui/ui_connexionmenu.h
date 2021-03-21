/********************************************************************************
** Form generated from reading UI file 'connexionmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNEXIONMENU_H
#define UI_CONNEXIONMENU_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnexionMenu
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *buttonsVerticalLayout;
    QPushButton *SignIn;
    QPushButton *SignUp;
    QPushButton *Quit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;

    void setupUi(QMainWindow *ConnexionMenu)
    {
        if (ConnexionMenu->objectName().isEmpty())
            ConnexionMenu->setObjectName(QString::fromUtf8("ConnexionMenu"));
        ConnexionMenu->resize(1000, 600);
        ConnexionMenu->setStyleSheet(QString::fromUtf8("background-color:lightsalmon"));
        centralWidget = new QWidget(ConnexionMenu);
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
        ConnexionMenu->setCentralWidget(centralWidget);

        retranslateUi(ConnexionMenu);
        QObject::connect(Quit, SIGNAL(clicked()), ConnexionMenu, SLOT(close()));

        QMetaObject::connectSlotsByName(ConnexionMenu);
    } // setupUi

    void retranslateUi(QMainWindow *ConnexionMenu)
    {
        ConnexionMenu->setWindowTitle(QApplication::translate("ConnexionMenu", "ConnexionMenu", nullptr));
        SignIn->setText(QApplication::translate("ConnexionMenu", "Sign in", nullptr));
        SignUp->setText(QApplication::translate("ConnexionMenu", "Sign up", nullptr));
        Quit->setText(QApplication::translate("ConnexionMenu", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnexionMenu: public Ui_ConnexionMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNEXIONMENU_H
