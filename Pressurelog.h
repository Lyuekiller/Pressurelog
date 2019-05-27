#ifndef LOG_H
#define LOG_H

#include <QDate>
#include <QTime>
class Pressurelog
{
public:
    Pressurelog();
    void setDate(QDate date);
    void setTime(QTime time);
    void setSand_ratio(double sand_ratio);
    void setSand_concentration(double sand_concentration);
    void setPressure(double pressure);
    void setDisplacement(double displacement);
    QDate getDate();
    QTime getQTime();
    double getSand_ratio();
    double getSand_concentration();
    double getPressure();
    double getDisplacement();

private:
    QDate date;
    QTime time;
    double sand_ratio;
    double sand_concentration;
    double pressure;
    double displacement;
};

#endif // LOG_H
