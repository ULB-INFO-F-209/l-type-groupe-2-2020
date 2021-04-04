/********************************************************************************
** Form generated from reading UI file 'leveleditor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEVELEDITOR_H
#define UI_LEVELEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LevelEditor
{
public:
    QWidget *centralwidget;
    QLabel *title_label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *objet_label;
    QPushButton *ennemy_button;
    QPushButton *obstacle_button;
    QPushButton *difficulty_label;
    QPushButton *bonus_label;
    QPushButton *theme_label;
    QFrame *game_zone;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QMainWindow *LevelEditor)
    {
        if (LevelEditor->objectName().isEmpty())
            LevelEditor->setObjectName(QStringLiteral("LevelEditor"));
        LevelEditor->resize(800, 600);
        centralwidget = new QWidget(LevelEditor);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        title_label = new QLabel(centralwidget);
        title_label->setObjectName(QStringLiteral("title_label"));
        title_label->setGeometry(QRect(80, 10, 641, 51));
        title_label->setFrameShape(QFrame::WinPanel);
        title_label->setAlignment(Qt::AlignCenter);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(610, 100, 160, 421));
        objet_label = new QVBoxLayout(verticalLayoutWidget);
        objet_label->setObjectName(QStringLiteral("objet_label"));
        objet_label->setContentsMargins(11, 0, 11, 0);
        ennemy_button = new QPushButton(verticalLayoutWidget);
        ennemy_button->setObjectName(QStringLiteral("ennemy_button"));
        ennemy_button->setMaximumSize(QSize(150, 45));

        objet_label->addWidget(ennemy_button);

        obstacle_button = new QPushButton(verticalLayoutWidget);
        obstacle_button->setObjectName(QStringLiteral("obstacle_button"));
        obstacle_button->setMaximumSize(QSize(150, 45));

        objet_label->addWidget(obstacle_button);

        difficulty_label = new QPushButton(verticalLayoutWidget);
        difficulty_label->setObjectName(QStringLiteral("difficulty_label"));
        difficulty_label->setMaximumSize(QSize(150, 45));

        objet_label->addWidget(difficulty_label);

        bonus_label = new QPushButton(verticalLayoutWidget);
        bonus_label->setObjectName(QStringLiteral("bonus_label"));
        bonus_label->setMaximumSize(QSize(150, 45));

        objet_label->addWidget(bonus_label);

        theme_label = new QPushButton(verticalLayoutWidget);
        theme_label->setObjectName(QStringLiteral("theme_label"));
        theme_label->setMaximumSize(QSize(150, 45));

        objet_label->addWidget(theme_label);

        game_zone = new QFrame(centralwidget);
        game_zone->setObjectName(QStringLiteral("game_zone"));
        game_zone->setGeometry(QRect(30, 100, 551, 421));
        game_zone->setStyleSheet(QStringLiteral("background-color: rgb(136, 138, 133);"));
        game_zone->setFrameShape(QFrame::StyledPanel);
        game_zone->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 530, 551, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(11, 0, 11, 0);
        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 45));
        pushButton_2->setMaximumSize(QSize(250, 45));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(250, 45));
        pushButton->setMaximumSize(QSize(250, 45));

        horizontalLayout->addWidget(pushButton);

        LevelEditor->setCentralWidget(centralwidget);

        retranslateUi(LevelEditor);

        QMetaObject::connectSlotsByName(LevelEditor);
    } // setupUi

    void retranslateUi(QMainWindow *LevelEditor)
    {
        LevelEditor->setWindowTitle(QApplication::translate("LevelEditor", "LevelEditor", Q_NULLPTR));
        title_label->setText(QApplication::translate("LevelEditor", "Level Editor", Q_NULLPTR));
        ennemy_button->setText(QApplication::translate("LevelEditor", "Ennemy", Q_NULLPTR));
        obstacle_button->setText(QApplication::translate("LevelEditor", "Obstacle", Q_NULLPTR));
        difficulty_label->setText(QApplication::translate("LevelEditor", "Difficulty", Q_NULLPTR));
        bonus_label->setText(QApplication::translate("LevelEditor", "Bonus", Q_NULLPTR));
        theme_label->setText(QApplication::translate("LevelEditor", "Theme", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("LevelEditor", "Save", Q_NULLPTR));
        pushButton->setText(QApplication::translate("LevelEditor", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LevelEditor: public Ui_LevelEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVELEDITOR_H
