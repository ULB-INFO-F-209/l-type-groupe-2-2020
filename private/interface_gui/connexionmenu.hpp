#ifndef CONNEXIONMENU_HPP
#define CONNEXIONMENU_HPP

#include <QMainWindow>

namespace Ui {
  class ConnexionMenu;
}

class ConnexionMenu : public QMainWindow
{
  Q_OBJECT

public:
  explicit ConnexionMenu(QWidget *parent = nullptr);
  ~ConnexionMenu();

private slots:
  void on_SignIn_clicked();

private:
  Ui::ConnexionMenu *ui;
};

#endif // CONNEXIONMENU_HPP
