#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <iostream>
#include <QtWidgets>
#include <QVariant>
//#include "Frame.hpp"

class ClickableLabel : public QLabel { 
public:
    explicit ClickableLabel(QFrame* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags()): QLabel(parent){}
    ~ClickableLabel(){};

signals:
    void clicked();

protected:
    

    void mousePressEvent(QMouseEvent* event) override {
        if(event->button() == Qt::RightButton){
            std::cout << " jje suis pas ici bg"<<std::endl;
            emit clicked(); 

        }
        else if(event->button() == Qt::LeftButton){
            //dynamic_cast<Frame*>(parentWidget())->mousePressEvent(event); 

        }
        
         
    }

};

#endif // CLICKABLELABEL_H