#include "controldialog.h"
#include "ui_controldialog.h"
#include "imagewin.h"
ControlDialog::ControlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlDialog)
{
    ui->setupUi(this);
    ui->LabelSlider->setValue(10);
    ui->LabelSlider->setRange(5,20);
    imageWin *image = (imageWin *)this->parent();
    ui->eventCheckBox->setChecked(true);
    QIntValidator *validator = new QIntValidator(-100, 1000, this);
    ui->beforPreLineEdit->setValidator(validator);
    ui->afterPreLineEdit->setValidator(validator);
    ui->beforPreLineEdit->setText("0");
    ui->afterPreLineEdit->setText("100");
    connect(ui->LabelSlider,SIGNAL(sliderMoved(int)),image,SLOT(tickLabelValueChange(int)));
    connect(ui->eventCheckBox,SIGNAL(stateChanged(int)),image,SLOT(eventHideShow(int)));
    connect(ui->pushButton,&QPushButton::clicked,image,SLOT(eventHideShow(int)));
}

ControlDialog::~ControlDialog()
{
    delete ui;
}




