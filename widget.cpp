#include "widget.h"
#include "ui_widget.h"
#include "qcustomplot.h"
#include "general.h"
#include "cevents.h"
#include "Pressurelog.h"
#include <QFileDialog>
#include <QDebug>
#include "imagedisplay.h"
#include "imagewin.h"
#include <qmath.h>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->eventEdit->setText("D:\\微地震项目\\2019曲致X1\\transform\\stage01.xlsx");
    ui->logEdit->setText("D:\\微地震项目\\2019曲致X1\\transform\\压裂曲线.xlsx");
    this->setWindowTitle("文件输入");
    imageWin *iWin = new imageWin();
    connect(ui->displayButton,&QPushButton::clicked,iWin, [=](){iWin->imagePlot(ui->eventEdit->text(),ui->logEdit->text());});

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_openButton_clicked()
{
    QString eventPath = QFileDialog::getOpenFileName(this,"事件点文件",".","Excel(*.xls *.xlsx)");
    ui->eventEdit->setText(eventPath);

}

void Widget::on_pushButton_clicked()
{
    QString logPath = QFileDialog::getOpenFileName(this,"压裂曲线",".","Excel(*.xls *.xlsx)");
    ui->logEdit->setText(logPath);
}



