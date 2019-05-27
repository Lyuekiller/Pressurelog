#include "Pressurelog.h"

Pressurelog::Pressurelog()
{

}

void Pressurelog::setDate(QDate date)
{
    this->date = date;
}

void Pressurelog::setTime(QTime time)
{
    this->time = time;
}

void Pressurelog::setSand_ratio(double sand_ratio)
{
    this->sand_ratio = sand_ratio;
}

void Pressurelog::setSand_concentration(double sand_concentration)
{
    this->sand_concentration = sand_concentration;
}

void Pressurelog::setPressure(double pressure)
{
    this->pressure = pressure;
}

void Pressurelog::setDisplacement(double displacement)
{
    this->displacement = displacement;
}

QDate Pressurelog::getDate()
{
    return this->date;
}

QTime Pressurelog::getQTime()
{
    return this->time;
}

double Pressurelog::getSand_ratio()
{
    return this->sand_ratio;
}

double Pressurelog::getSand_concentration()
{
    return this->sand_concentration;
}

double Pressurelog::getPressure()
{
    return this->pressure;
}

double Pressurelog::getDisplacement()
{
    return this->displacement;
}

