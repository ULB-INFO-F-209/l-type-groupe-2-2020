#ifndef LABEL
#define LABEL

void ClickableLabel::mousePressEvent(QMouseEvent* event) override {
    emit clicked();
};


#include "label.moc"
#endif 