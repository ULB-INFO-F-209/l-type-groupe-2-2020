#ifndef FRAME_HPP
#define FRAME_HPP

#include <QtWidgets>
#include <QFrame>
#include <QLabel>
#include <iostream>
#include <QVariant>
#include <QAction>
#include <QLabel>
#include "label.hpp"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class Frame : public QFrame{
public:
    explicit Frame(QWidget *parent = nullptr):QFrame(parent){
    	this->setAcceptDrops(true);
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

	        QPixmap pixmap;
	        QPoint offset;
	        dataStream >> pixmap >> offset;

	        ClickableLabel *newIcon = new ClickableLabel(this);
	        newIcon->setPixmap(pixmap);
	        newIcon->move(event->pos() - offset);
	        newIcon->show();
	        newIcon->setAttribute(Qt::WA_DeleteOnClose);
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
    void mousePressEvent(QMouseEvent *event) override{
    	ClickableLabel *child = static_cast<ClickableLabel*>(childAt(event->pos()));
    	if (!child)
        	return;

	    QPixmap pixmap = *(child->pixmap());
	    QByteArray itemData;
	    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
	    dataStream << pixmap << QPoint(event->pos() - child->pos());
	    
	    QMimeData *mimeData = new QMimeData;
    	mimeData->setData("application/x-dnditemdata", itemData);

    	QDrag *drag = new QDrag(this);
	    drag->setMimeData(mimeData);
	    drag->setPixmap(pixmap);
	    drag->setHotSpot(event->pos() - child->pos());

	    QPixmap tempPixmap = pixmap;
	    QPainter painter;
	    painter.begin(&tempPixmap);
	    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
	    painter.end();

	    child->setPixmap(tempPixmap);

	    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
	        child->close();
	    } else {
	        child->show();
	        child->setPixmap(pixmap);
	    }
	}
};

#endif // FRAME_HPP


