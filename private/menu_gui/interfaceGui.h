/********************************************************************************
** Form generated from reading UI file 'interfaceGui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef INTERFACEGUI_H
#define INTERFACEGUI_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE


class Ui_InterafaceGui{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *buttonsVerticalLayout;
    QPushButton *SignIn;
    QPushButton *SignUp;
    QPushButton *Quit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *interafaceGui)
    {
        // setup de l'interface 
        if (interafaceGui->objectName().isEmpty())
            interafaceGui->setObjectName(QString::fromUtf8("interafaceGui"));
        interafaceGui->resize(1000, 600);
        interafaceGui->setAutoFillBackground(false);
        interafaceGui->setStyleSheet(QString::fromUtf8("background-color:lightsalmon"));

        centralWidget = new QWidget(interafaceGui);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(390, 210, 241, 301));
        
        // creation et settings de la layout pour les bouttons
        buttonsVerticalLayout = new QVBoxLayout(verticalLayoutWidget);
        buttonsVerticalLayout->setSpacing(8);
        buttonsVerticalLayout->setContentsMargins(11, 11, 11, 11);
        buttonsVerticalLayout->setObjectName(QString::fromUtf8("buttonsVerticalLayout"));
        buttonsVerticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        buttonsVerticalLayout->setContentsMargins(40, 20, 2, 20);
        
        //Creations PushButton
        
        SignIn = new QPushButton(verticalLayoutWidget);
        SignIn->setObjectName(QString::fromUtf8("SignIn"));
        SignIn->setMaximumSize(QSize(165, 61));
        
        buttonsVerticalLayout->addWidget(SignIn);

        SignUp = new QPushButton(verticalLayoutWidget);
        SignUp->setObjectName(QString::fromUtf8("SignUp"));
        SignUp->setMaximumSize(QSize(165, 61));

        buttonsVerticalLayout->addWidget(SignUp);

        Quit = new QPushButton(verticalLayoutWidget);
        Quit->setObjectName(QString::fromUtf8("Quit"));
        Quit->setMaximumSize(QSize(165, 61));

        buttonsVerticalLayout->addWidget(Quit);

        // layout vertical pour le texte je pense 
        horizontalLayoutWidget = new QWidget(centralWidget); // creation d'un widget qui sera occuper par un layout le widget ce trouve lui meme dans le widget centrale
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(50, 20, 851, 80));
        
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);


        interafaceGui->setCentralWidget(centralWidget); // setup du widget centrale qui contient tout 
        statusBar = new QStatusBar(interafaceGui);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        interafaceGui->setStatusBar(statusBar);

        retranslateUi(interafaceGui);

        QMetaObject::connectSlotsByName(interafaceGui);
    } // setupUi

    void retranslateUi(QMainWindow *interafaceGui)
    {
        interafaceGui->setWindowTitle(QApplication::translate("interafaceGui", "Interface", nullptr));
        SignIn->setText(QApplication::translate("interafaceGui", "Sign in", nullptr));
        SignUp->setText(QApplication::translate("interafaceGui", "Sign up", nullptr));
        Quit->setText(QApplication::translate("interafaceGui", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {

    class InterafaceGui: public QMainWindow{

    private:
        Q_OBJECT
        Ui_InterafaceGui *ui;
    public:
        InterafaceGui();
        ~InterafaceGui();

    };

} // namespace Ui


QT_END_NAMESPACE

#endif // INTERFACEGUI_H
