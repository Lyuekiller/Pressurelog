#ifndef GENERAL_H
#define GENERAL_H

#include <QList>
#include <QVariant>
class general
{
public:
    general();
    QList<QList<QVariant>> readExcel(QString path);
};

#endif // GENERAL_H
