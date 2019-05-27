#include "imagedisplay.h"
#include "ui_imagedisplay.h"

imageDisplay::imageDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imageDisplay)
{
    ui->setupUi(this);
}

imageDisplay::~imageDisplay()
{
    delete ui;
}
