#ifndef IMAGEWIN_H
#define IMAGEWIN_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "controldialog.h"

namespace Ui {
class imageWin;
}

class imageWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit imageWin(QWidget *parent = nullptr);
    ~imageWin();

private:
    Ui::imageWin *ui;
    QCustomPlot *pCustomPlot;
    QCPAxisRect *volumeAxisRect;
    ControlDialog *Cdialog;

public slots:
    void imagePlot(QString eventPath , QString logPath);
    void tickLabelValueChange(int value);
    void eventHideShow(int value);
    void rangeChanged(int num , QString value1 , QString value2);
private slots:
    void on_action_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();

};

#endif // IMAGEWIN_H
