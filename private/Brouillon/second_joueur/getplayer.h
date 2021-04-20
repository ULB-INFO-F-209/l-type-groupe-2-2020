#ifndef GETPLAYER_H
#define GETPLAYER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GetPlayer; }
QT_END_NAMESPACE

class GetPlayer : public QMainWindow
{
    Q_OBJECT

public:
    GetPlayer(QWidget *parent = nullptr);
    ~GetPlayer();

private:
    Ui::GetPlayer *ui;
};
#endif // GETPLAYER_H
