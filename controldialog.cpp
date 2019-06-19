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

    ui->disBeforeLineEdit->setValidator(validator);
    ui->disAfterLineEdit->setValidator(validator);
    ui->disBeforeLineEdit->setText("0");
    ui->disAfterLineEdit->setText("20");

    ui->sandBeforeLineEdit->setValidator(validator);
    ui->sandAfterLineEdit->setValidator(validator);
    ui->sandBeforeLineEdit->setText("0");
    ui->sandAfterLineEdit->setText("400");

    ui->magBeforeLineEdit->setValidator(validator);
    ui->magAfterLineEdit->setValidator(validator);
    ui->magBeforeLineEdit->setText("-5");
    ui->magAfterLineEdit->setText("0");

    connect(ui->LabelSlider,SIGNAL(sliderMoved(int)),image,SLOT(tickLabelValueChange(int)));
    connect(ui->eventCheckBox,SIGNAL(stateChanged(int)),image,SLOT(eventHideShow(int)));

    connect(ui->beforPreLineEdit,&QLineEdit::textChanged,image, [=](){image->rangeChanged(0,ui->beforPreLineEdit->text(),ui->afterPreLineEdit->text());});
    connect(ui->afterPreLineEdit,&QLineEdit::textChanged,image, [=](){image->rangeChanged(0,ui->beforPreLineEdit->text(),ui->afterPreLineEdit->text());});

    connect(ui->disBeforeLineEdit,&QLineEdit::textChanged,image, [=](){image->rangeChanged(1,ui->disBeforeLineEdit->text(),ui->disAfterLineEdit->text());});
    connect(ui->disAfterLineEdit,&QLineEdit::textChanged,image, [=](){image->rangeChanged(1,ui->disBeforeLineEdit->text(),ui->disAfterLineEdit->text());});

    connect(ui->sandBeforeLineEdit,&QLineEdit::textChanged,image, [=](){image->rangeChanged(2,ui->sandBeforeLineEdit->text(),ui->sandAfterLineEdit->text());});
    connect(ui->sandAfterLineEdit,&QLineEdit::textChanged,image, [=](){image->rangeChanged(2,ui->sandBeforeLineEdit->text(),ui->sandAfterLineEdit->text());});

    connect(ui->magBeforeLineEdit,&QLineEdit::textChanged,image, [=](){image->rangeChanged(3,ui->magBeforeLineEdit->text(),ui->magAfterLineEdit->text());});
    connect(ui->magAfterLineEdit,&QLineEdit::textChanged,image, [=](){image->rangeChanged(3,ui->magBeforeLineEdit->text(),ui->magAfterLineEdit->text());});
}

ControlDialog::~ControlDialog()
{
    delete ui;
}
