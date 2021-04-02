#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LevelEditor; }
QT_END_NAMESPACE

class LevelEditor : public QMainWindow
{
    Q_OBJECT

public:
    LevelEditor(QWidget *parent = nullptr);
    ~LevelEditor();

private:
    Ui::LevelEditor *ui;
};
#endif // LEVELEDITOR_H
