#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QtWidgets>
#include <QVariant>
#include <QLabel>
#include <QWidget>
#include <Qt>
#include <iostream>

class ClickableLabel : public QLabel{ 
    int idx;
    int type;
    int x = 10;
    int y = 10;
    Q_OBJECT 

public:
    explicit ClickableLabel(int i=0,int t=0, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags()): idx{i},type(t),QLabel(parent){}
    ~ClickableLabel(){};
    int index(){return idx;}
    int get_type(){return type;}
    void click(){emit clicked();}
    void change_pos(){emit changedPos();}
    void setPos(int a, int b){x=a; y=b;}
    int posx(){return x;}
    int posy(){return y;}

signals:
    void clicked();
    void changedPos();

/*protected:
    void mouseReleaseEvent(QMouseEvent* event)override{
        if(event->button() == Qt::RightButton){
            std::cout << " Clique sur le bouton droit"<<std::endl;
            emit clicked(); 
        }

       } 
        else if(event->button() == Qt::LeftButton){
        	childAt(event->pos())->mousePressEvent(event);
        	std::cout << " Clique sur le bouton gauche"<<std::endl;
        	par->mousePressEvent(event);
        }
}*/


};

#endif // CLICKABLELABEL_H