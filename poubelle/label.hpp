#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel { 

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags()): QLabel(parent){}
    ~ClickableLabel(){};

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override {emit clicked();}

};

#endif // CLICKABLELABEL_H