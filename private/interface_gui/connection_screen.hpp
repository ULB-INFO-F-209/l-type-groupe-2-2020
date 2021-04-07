#ifndef CONNECTION_SCREEN_HPP
#define CONNECTION_SCREEN_HPP

#include <QMainWindow>

namespace Ui {
  class connection_screen;
}

class connection_screen : public QMainWindow
{
  Q_OBJECT

public:
  explicit connection_screen(QWidget *parent = nullptr);
  ~connection_screen();

private:
  Ui::connection_screen *ui;
};

#endif // CONNECTION_SCREEN_HPP
