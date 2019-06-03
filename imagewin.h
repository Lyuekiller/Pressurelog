#ifndef IMAGEWIN_H
#define IMAGEWIN_H

#include <QMainWindow>
#include "qcustomplot.h"

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

public slots:
    void imagePlot(QString eventPath , QString logPath);
private slots:
    void on_action_triggered();
};

#endif // IMAGEWIN_H
