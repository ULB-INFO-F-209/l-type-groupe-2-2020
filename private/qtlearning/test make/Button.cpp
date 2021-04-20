#include "Button.hpp"


Button::Button(const QString& name, int id , QWidget* parent): QPushButton( name, parent ), _id(id){}


