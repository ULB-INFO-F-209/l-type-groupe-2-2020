
#ifndef InterfaceGUI_HPP
#define InterfaceGUI_HPP

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>


class InterfaceGUI: public QMainWindow
{
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *buttonsVerticalLayout;
    QPushButton *SignIn;
    QPushButton *SignUp;
    QPushButton *Quit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;

public:
    InterfaceGUI();

    void setupInitUi();

    void retranslateUi();

    void setupConnectetUi();

    void on_SignIn_clicked();
};

#endif