#include "getplayer.h"
#include "ui_getplayer.h"

GetPlayer::GetPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GetPlayer)
{
    ui->setupUi(this);
}

GetPlayer::~GetPlayer()
{
    delete ui;
}

