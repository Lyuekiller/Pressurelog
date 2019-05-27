#ifndef CEVENTS_H
#define CEVENTS_H
#include <QDate>
#include <QTime>

class CEvents
{
public:
    CEvents();
    void setNumber(int number);
    void setComponent(QString component);
    void setDate(QDate date);
    void setTime(QTime time);
    void setLabel(QString label);
    void setNorth(double north);
    void setEast(double east);
    void setDown(double down);
    void setMom_mag(double mom_mag);
    void setEnergy(double energy);
    int getNumber();
    QString getComponent();
    QDate getDate();
    QTime getQTime();
    QString getLabel();
    double getNorth();
    double getEast();
    double getDown();
    double getMom_mag();
    double getEnergy();

private:
    int number;
    QString component;
    QDate date;
    QTime time;
    QString label;
    double north;
    double east;
    double down;
    double mom_mag;
    double energy;


};

#endif // CEVENTS_H
