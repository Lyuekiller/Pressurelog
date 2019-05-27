#include "imagewin.h"
#include "ui_imagewin.h"

imageWin::imageWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::imageWin)
{
    ui->setupUi(this);
}

imageWin::~imageWin()
{
    delete ui;
}
