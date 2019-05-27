#include "cevents.h"

CEvents::CEvents()
{

}

void CEvents::setNumber(int number)
{
    this->number = number;
}

void CEvents::setComponent(QString component)
{
    this->component = component;
}

void CEvents::setDate(QDate date)
{
    this->date = date;
}

void CEvents::setTime(QTime time)
{
    this->time = time;
}

void CEvents::setLabel(QString label)
{
    this->label = label;
}

void CEvents::setNorth(double north)
{
    this->north = north;
}

void CEvents::setEast(double east)
{
    this->east = east;
}

void CEvents::setDown(double down)
{
    this->down = down;
}

void CEvents::setMom_mag(double mom_mag)
{
    this->mom_mag = mom_mag;
}

void CEvents::setEnergy(double energy)
{
    this->energy = energy;
}

int CEvents::getNumber()
{
    return this->number;
}

QString CEvents::getComponent()
{
    return this->component;
}

QDate CEvents::getDate()
{
    return this->date;
}

QTime CEvents::getQTime()
{
    return this->time;
}

QString CEvents::getLabel()
{
    return this->label;
}

double CEvents::getNorth()
{
    return this->north;
}

double CEvents::getEast()
{
    return this->east;
}

double CEvents::getDown()
{
    return this->down;
}

double CEvents::getMom_mag()
{
    return this->mom_mag;
}

double CEvents::getEnergy()
{
    return this->energy;
}



