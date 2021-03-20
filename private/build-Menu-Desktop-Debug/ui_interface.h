/********************************************************************************
** Form generated from reading UI file 'interface.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Interface
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *SignIn;
    QPushButton *SignUp;
    QPushButton *pushButton_3;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Interface)
    {
        if (Interface->objectName().isEmpty())
            Interface->setObjectName(QStringLiteral("Interface"));
        Interface->resize(1000, 600);
        Interface->setAutoFillBackground(false);
        Interface->setStyleSheet(QStringLiteral("background-color:lightsalmon"));
        centralWidget = new QWidget(Interface);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(390, 210, 241, 301));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(8);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(40, 20, 2, 20);
        SignIn = new QPushButton(verticalLayoutWidget);
        SignIn->setObjectName(QStringLiteral("SignIn"));
        SignIn->setMaximumSize(QSize(165, 61));
        QIcon icon(QIcon::fromTheme(QStringLiteral("image/sign_in")));
        SignIn->setIcon(icon);
        SignIn->setFlat(false);

        verticalLayout->addWidget(SignIn);

        SignUp = new QPushButton(verticalLayoutWidget);
        SignUp->setObjectName(QStringLiteral("SignUp"));
        SignUp->setMaximumSize(QSize(165, 61));

        verticalLayout->addWidget(SignUp);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMaximumSize(QSize(165, 61));

        verticalLayout->addWidget(pushButton_3);

        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(50, 20, 851, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Interface->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Interface);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 22));
        Interface->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Interface);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Interface->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Interface);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Interface->setStatusBar(statusBar);

        retranslateUi(Interface);

        QMetaObject::connectSlotsByName(Interface);
    } // setupUi

    void retranslateUi(QMainWindow *Interface)
    {
        Interface->setWindowTitle(QApplication::translate("Interface", "Interface", Q_NULLPTR));
        SignIn->setText(QApplication::translate("Interface", "Sign in", Q_NULLPTR));
        SignUp->setText(QApplication::translate("Interface", "Sign up", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Interface", "Quit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Interface: public Ui_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
