#ifndef CONNEXION_H
#define CONNEXION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Connexion; }
QT_END_NAMESPACE

class Connexion : public QMainWindow
{
    Q_OBJECT

public:
    Connexion(QWidget *parent = nullptr);
    ~Connexion();

private:
    Ui::Connexion *ui;
};
#endif // CONNEXION_H
