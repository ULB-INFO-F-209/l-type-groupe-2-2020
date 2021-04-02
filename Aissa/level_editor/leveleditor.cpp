#include "leveleditor.h"
#include "ui_leveleditor.h"

LevelEditor::LevelEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LevelEditor)
{
    ui->setupUi(this);
}

LevelEditor::~LevelEditor()
{
    delete ui;
}

