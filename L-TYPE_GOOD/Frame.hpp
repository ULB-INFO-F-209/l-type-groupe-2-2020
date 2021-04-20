#ifndef FRAME_HPP
#define FRAME_HPP

#include <QtWidgets>
#include <QFrame>
#include <QLabel>
#include <iostream>
#include <QVariant>
#include <QAction>
#include <QLabel>
#include <Qt>

#include "Label.hpp"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class Frame : public QFrame{
	std::vector<ClickableLabel*> enemy{};
	std::vector<ClickableLabel*> obs{};
public:
    explicit Frame(QWidget *parent = nullptr):QFrame(parent){
    	this->setAcceptDrops(true);
    }

    void add_enemy(ClickableLabel* e){enemy.push_back(e);}
    void add_obs(ClickableLabel* o){obs.push_back(o);}
    ClickableLabel* get_enemy(int i){
    	return enemy[static_cast<size_t>(i)];
    }
    ClickableLabel* get_obs(int i){
    	return obs[static_cast<size_t>(i)];
    }


protected:
    void dragEnterEvent(QDragEnterEvent *event) override{
    	if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
	        if (event->source() == this){
	            event->setDropAction(Qt::MoveAction);
	            event->accept();
	        }
	        else{
	            event->acceptProposedAction();
	        }
	    } 
	    else{
	    	event->ignore();
	    }
	}

    void dragMoveEvent(QDragMoveEvent *event) override{
		if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
			if (event->source() == this) {
	            event->setDropAction(Qt::MoveAction);
	            event->accept();
	        } 
	        else{
	        	event->acceptProposedAction();
		     }
	    } 
	    else{
	    	event->ignore();
	    }
    }
    void dropEvent(QDropEvent *event) override{
    	if(event->mimeData()->hasFormat("application/x-dnditemdata")) {
	        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
	        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

	        int i, type;
	        QPoint offset;
	        dataStream >> i >> type >> offset;
	        QPoint pos(event->pos() - offset);
	        size_t idx = static_cast<size_t>(i);
	        if(type==0){
	        	enemy[idx]->move(pos);
	        	enemy[idx]->setPos(pos.rx(), pos.ry());
	        	enemy[idx]->show();
	        	enemy[idx]->change_pos();
	        }
	        else{
	        	obs[idx]->move(pos);
	        	obs[idx]->setPos(pos.rx(), pos.ry());
	        	obs[idx]->show();
	        	obs[idx]->change_pos();
	        }

	        if (event->source() == this) {
	            event->setDropAction(Qt::MoveAction);
	            event->accept();
	        } 
	        else{
	            event->acceptProposedAction();
	        }
	    } else {
	    	event->ignore();
	    }
	}
public:
    void mousePressEvent(QMouseEvent *event) override{
		ClickableLabel *child = dynamic_cast<ClickableLabel*>(childAt(event->pos()));
		if (!child)
			return;
		int idx = child->index();
		int type = child->get_type();
		if(event->button() == Qt::LeftButton){
			QPixmap pixmap = *(child->pixmap());
			QByteArray itemData;
			QDataStream dataStream(&itemData, QIODevice::WriteOnly);
			dataStream << idx << type<< QPoint(event->pos() - child->pos());
			

			QMimeData *mimeData = new QMimeData;
			mimeData->setData("application/x-dnditemdata", itemData);

			QDrag *drag = new QDrag(this);
			drag->setMimeData(mimeData);
			drag->setPixmap(pixmap);
			drag->setHotSpot(event->pos() - child->pos());

			if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
			} else {
				child->show();
			}
			
		}
		else if(event->button() == Qt::RightButton){
            if(type==0)
            	enemy[static_cast<size_t>(idx)]->click();
            else
            	obs[static_cast<size_t>(idx)]->click();
        }

	}
};

#endif // FRAME_HPP


