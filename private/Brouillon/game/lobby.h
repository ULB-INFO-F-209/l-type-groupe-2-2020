#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class lobby; }
QT_END_NAMESPACE

class lobby : public QMainWindow
{
    Q_OBJECT

public:
    lobby(QWidget *parent = nullptr);
    ~lobby();

private:
    Ui::lobby *ui;
};
#endif // LOBBY_H
