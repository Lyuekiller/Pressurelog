#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QWidget>

namespace Ui {
class imageDisplay;
}

class imageDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit imageDisplay(QWidget *parent = nullptr);
    ~imageDisplay();

private:
    Ui::imageDisplay *ui;
};

#endif // IMAGEDISPLAY_H
