#include "general.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QAxObject>
#include <QDebug>
#include <QList>
general::general()
{

}

QList<QList<QVariant> > general::readExcel(QString path)
{
    QVariant var;
    QAxObject *excel = new QAxObject("Excel.Application");//连接Excel控件
    excel->setProperty("Visible", false);
    QAxObject *workbooks = excel->querySubObject("WorkBooks");
    workbooks->dynamicCall("Open (const QString&)", path);
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
    QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
    QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1
    QAxObject *usedRange = worksheet->querySubObject("UsedRange");//获取用户区域范围
    if(NULL != usedRange && !usedRange->isNull()) {
        var = usedRange->dynamicCall("Value");//读取区域内所有值
    }
    QList<QList<QVariant>> list;
    auto rows = var.toList();
    for(auto row:rows) {
        list.append(row.toList());
    }
    delete usedRange;
    workbooks->dynamicCall("Close(Boolean)",false);
    excel->dynamicCall("Quit(void)");
    delete excel;
    return list;
}
