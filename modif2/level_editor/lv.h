/********************************************************************************
** Form generated from reading UI file 'leveleditor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LV_H
#define LV_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
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
    QPushButton *theme_label;
    QPushButton *save;
    QPushButton *cancel;
    QFrame *game_zone;
    QLabel *label;
    QSlider *tick_label;
    QLCDNumber *tick_lcd;

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
        verticalLayoutWidget->setGeometry(QRect(620, 100, 172, 421));
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

        theme_label = new QPushButton(verticalLayoutWidget);
        theme_label->setObjectName(QStringLiteral("theme_label"));
        theme_label->setMaximumSize(QSize(150, 45));

        objet_label->addWidget(theme_label);

        save = new QPushButton(verticalLayoutWidget);
        save->setObjectName(QStringLiteral("save"));
        save->setMinimumSize(QSize(0, 45));
        save->setMaximumSize(QSize(150, 45));

        objet_label->addWidget(save);

        cancel = new QPushButton(verticalLayoutWidget);
        cancel->setObjectName(QStringLiteral("cancel"));
        cancel->setMinimumSize(QSize(150, 45));
        cancel->setMaximumSize(QSize(150, 45));

        objet_label->addWidget(cancel);

        game_zone = new QFrame(centralwidget);
        game_zone->setObjectName(QStringLiteral("game_zone"));
        game_zone->setGeometry(QRect(10, 100, 601, 421));
        game_zone->setStyleSheet(QStringLiteral("background-color: rgb(136, 138, 133);"));
        game_zone->setFrameShape(QFrame::WinPanel);
        game_zone->setFrameShadow(QFrame::Plain);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 546, 67, 31));
        label->setFrameShape(QFrame::WinPanel);
        label->setAlignment(Qt::AlignCenter);
        tick_label = new QSlider(centralwidget);
        tick_label->setObjectName(QStringLiteral("tick_label"));
        tick_label->setGeometry(QRect(100, 550, 561, 31));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tick_label->sizePolicy().hasHeightForWidth());
        tick_label->setSizePolicy(sizePolicy);
        tick_label->setMaximumSize(QSize(16777215, 16777213));
        QFont font;
        font.setFamily(QStringLiteral("TeX Gyre Termes Math"));
        font.setBold(true);
        font.setWeight(75);
        tick_label->setFont(font);
        tick_label->setMouseTracking(false);
        tick_label->setContextMenuPolicy(Qt::DefaultContextMenu);
        tick_label->setMaximum(20);
        tick_label->setPageStep(3);
        tick_label->setTracking(false);
        tick_label->setOrientation(Qt::Horizontal);
        tick_label->setInvertedAppearance(false);
        tick_label->setInvertedControls(false);
        tick_label->setTickPosition(QSlider::TicksBothSides);
        tick_label->setTickInterval(1);
        tick_lcd = new QLCDNumber(centralwidget);
        tick_lcd->setObjectName(QStringLiteral("tick_lcd"));
        tick_lcd->setGeometry(QRect(680, 550, 64, 31));
        tick_lcd->setFrameShape(QFrame::WinPanel);
        tick_lcd->setFrameShadow(QFrame::Plain);
        tick_lcd->setLineWidth(3);
        tick_lcd->setDigitCount(2);
        tick_lcd->setSegmentStyle(QLCDNumber::Flat);
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
        theme_label->setText(QApplication::translate("LevelEditor", "Theme", Q_NULLPTR));
        save->setText(QApplication::translate("LevelEditor", "Save", Q_NULLPTR));
        cancel->setText(QApplication::translate("LevelEditor", "Cancel", Q_NULLPTR));
        label->setText(QApplication::translate("LevelEditor", "Tick :", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LevelEditor: public Ui_LevelEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LV_H
