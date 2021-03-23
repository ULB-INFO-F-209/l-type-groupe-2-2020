/********************************************************************************
** Form generated from reading UI file 'interface.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef HOME_H
#define HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Interface
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *buuton_v_layout;
    QPushButton *signIn;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QLabel *saying_label;

    void setupUi(QMainWindow *Interface)
    {
        if (Interface->objectName().isEmpty())
            Interface->setObjectName(QStringLiteral("Interface"));
        Interface->resize(800, 600);
        Interface->setAutoFillBackground(false);
        Interface->setStyleSheet(QStringLiteral("background-color: salmon"));
        centralwidget = new QWidget(Interface);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(240, 240, 321, 301));
        buuton_v_layout = new QVBoxLayout(verticalLayoutWidget);
        buuton_v_layout->setObjectName(QStringLiteral("buuton_v_layout"));
        buuton_v_layout->setContentsMargins(11, 11, 11, 11);
        signIn = new QPushButton(verticalLayoutWidget);
        signIn->setObjectName(QStringLiteral("signIn"));
        signIn->setMinimumSize(QSize(165, 65));

        buuton_v_layout->addWidget(signIn);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(165, 65));

        buuton_v_layout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(165, 65));

        buuton_v_layout->addWidget(pushButton_2);

        saying_label = new QLabel(centralwidget);
        saying_label->setObjectName(QStringLiteral("saying_label"));
        saying_label->setEnabled(true);
        saying_label->setGeometry(QRect(190, 20, 401, 78));
        saying_label->setMouseTracking(true);
        saying_label->setFrameShape(QFrame::WinPanel);
        saying_label->setTextFormat(Qt::MarkdownText);
        saying_label->setAlignment(Qt::AlignCenter);
        Interface->setCentralWidget(centralwidget);

        retranslateUi(Interface);

        QMetaObject::connectSlotsByName(Interface);
    } // setupUi

    void retranslateUi(QMainWindow *Interface)
    {
        Interface->setWindowTitle(QApplication::translate("Interface", "Interface", Q_NULLPTR));
        signIn->setText(QApplication::translate("Interface", "Sign In", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Interface", "Sign Up", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Interface", "Quit", Q_NULLPTR));
        saying_label->setText(QApplication::translate("Interface", "HOME", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Interface: public Ui_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // HOME_H

