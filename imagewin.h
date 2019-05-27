#ifndef IMAGEWIN_H
#define IMAGEWIN_H

#include <QMainWindow>

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
};

#endif // IMAGEWIN_H
