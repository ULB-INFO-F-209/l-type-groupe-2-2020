#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include <QApplication>
#include <QPushButton>

class  Button final : public QPushButton{
	int _id;
public:
	Button(const QString& name, int id, QWidget* parent=nullptr);

};

#endif