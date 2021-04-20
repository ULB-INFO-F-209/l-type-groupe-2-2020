#ifndef PROFILE_H
#define PROFILE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Profile; }
QT_END_NAMESPACE

class Profile : public QMainWindow
{
    Q_OBJECT

public:
    Profile(QWidget *parent = nullptr);
    ~Profile();

private:
    Ui::Profile *ui;
};
#endif // PROFILE_H
