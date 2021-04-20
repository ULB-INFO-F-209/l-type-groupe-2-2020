/********************************************************************************
** Form generated from reading UI file 'connexion.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CONNEXION_H
#define CONNEXION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Connexion
{
public:
    QWidget *centralwidget;
    QLineEdit *pseudo_line;
    QLineEdit *pswd_line;
    QLabel *title_label;
    QLabel *pseudo_label;
    QLabel *pswd_label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *ok_button;
    QPushButton *cancel_button;

    void setupUi(QMainWindow *Connexion)
    {
        if (Connexion->objectName().isEmpty())
            Connexion->setObjectName(QStringLiteral("Connexion"));
        Connexion->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Connexion->sizePolicy().hasHeightForWidth());
        Connexion->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(Connexion);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pseudo_line = new QLineEdit(centralwidget);
        pseudo_line->setObjectName(QStringLiteral("pseudo_line"));
        pseudo_line->setGeometry(QRect(230, 270, 400, 45));
        pseudo_line->setMaxLength(15);
        pseudo_line->setClearButtonEnabled(false);
        pswd_line = new QLineEdit(centralwidget);
        pswd_line->setObjectName(QStringLiteral("pswd_line"));
        pswd_line->setGeometry(QRect(230, 370, 400, 45));
        title_label = new QLabel(centralwidget);
        title_label->setObjectName(QStringLiteral("title_label"));
        title_label->setGeometry(QRect(70, 47, 691, 81));
        title_label->setFrameShape(QFrame::WinPanel);
        title_label->setTextFormat(Qt::MarkdownText);
        title_label->setAlignment(Qt::AlignCenter);
        pseudo_label = new QLabel(centralwidget);
        pseudo_label->setObjectName(QStringLiteral("pseudo_label"));
        pseudo_label->setGeometry(QRect(140, 270, 91, 45));
        pswd_label = new QLabel(centralwidget);
        pswd_label->setObjectName(QStringLiteral("pswd_label"));
        pswd_label->setGeometry(QRect(130, 370, 101, 45));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(110, 470, 641, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(50);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        ok_button = new QPushButton(horizontalLayoutWidget);
        ok_button->setObjectName(QStringLiteral("ok_button"));
        ok_button->setMinimumSize(QSize(25, 50));

        horizontalLayout->addWidget(ok_button);

        cancel_button = new QPushButton(horizontalLayoutWidget);
        cancel_button->setObjectName(QStringLiteral("cancel_button"));
        cancel_button->setMinimumSize(QSize(10, 50));

        horizontalLayout->addWidget(cancel_button);

        Connexion->setCentralWidget(centralwidget);

        retranslateUi(Connexion);

        QMetaObject::connectSlotsByName(Connexion);
    } // setupUi

    void retranslateUi(QMainWindow *Connexion)
    {
        Connexion->setWindowTitle(QApplication::translate("Connexion", "Connexion", Q_NULLPTR));
        title_label->setText(QApplication::translate("Connexion", "Connexion", Q_NULLPTR));
        pseudo_label->setText(QApplication::translate("Connexion", "USERNAME: ", Q_NULLPTR));
        pswd_label->setText(QApplication::translate("Connexion", "PASSWORD : ", Q_NULLPTR));
        ok_button->setText(QApplication::translate("Connexion", "OK", Q_NULLPTR));
        cancel_button->setText(QApplication::translate("Connexion", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Connexion: public Ui_Connexion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CONNEXION_H
