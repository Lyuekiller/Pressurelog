#include "widget.h"
#include "ui_widget.h"
#include "qcustomplot.h"
#include "general.h"
#include "cevents.h"
#include "Pressurelog.h"
#include <QFileDialog>
#include <QDebug>
#include "imagedisplay.h"
#include "imagewin.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->eventEdit->setText("D:\\微地震项目\\2019曲致X1\\transform\\stage01.xlsx");
    ui->logEdit->setText("D:\\微地震项目\\2019曲致X1\\transform\\压裂曲线.xlsx");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_openButton_clicked()
{
    QString eventPath = QFileDialog::getOpenFileName(this,"事件点文件",".","Excel(*.xls *.xlsx)");
    ui->eventEdit->setText(eventPath);

}

void Widget::on_pushButton_clicked()
{
    QString logPath = QFileDialog::getOpenFileName(this,"压裂曲线",".","Excel(*.xls *.xlsx)");
    ui->logEdit->setText(logPath);
}

void Widget::on_displayButton_clicked()
{
    QString eventPath = ui->eventEdit->text();
    QString logPath = ui->logEdit->text();
    if(!eventPath.isNull()&&!eventPath.isEmpty()&&!logPath.isNull()&&!logPath.isEmpty()){
        general gen;
        QList<CEvents> eList;
        QList<Pressurelog> lList;
        QList<QList<QVariant>> eventList = gen.readExcel(eventPath);
        QList<QList<QVariant>> logList = gen.readExcel(logPath);
        for(int i = 1; i<eventList.size();i++){
            CEvents event;
            event.setNumber(eventList.at(i).at(0).toInt());
            event.setComponent(eventList.at(i).at(1).toString());
            event.setDate(eventList.at(i).at(2).toDate());
            event.setTime(eventList.at(i).at(3).toTime());
            event.setLabel(eventList.at(i).at(4).toString());
            event.setNorth(eventList.at(i).at(5).toDouble());
            event.setEast(eventList.at(i).at(6).toDouble());
            event.setDown(eventList.at(i).at(7).toDouble());
            event.setMom_mag(eventList.at(i).at(8).toDouble());
            event.setEnergy(eventList.at(i).at(9).toDouble());
//            qDebug()<<event.getNumber()<<" "<<event.getComponent()<<"  "<<event.getLabel()<<"  "<<event.getNorth()<<"  "<<event.getEnergy();
            eList<<event;
        }
        qDebug()<<eList.size();
        for(int i = 2; i < logList.size(); i++){
            Pressurelog log;
            log.setDate(logList.at(i).at(0).toDate());
            log.setTime(logList.at(i).at(1).toTime());
            log.setSand_ratio(logList.at(i).at(2).toDouble());
            log.setSand_concentration(logList.at(i).at(3).toDouble());
            log.setPressure(logList.at(i).at(4).toDouble());
            log.setDisplacement(logList.at(i).at(5).toDouble());
//            qDebug()<<log.getDate()<<"  "<<log.getQTime()<<"  "<<log.getSand_concentration();
            lList<<log;
        }
        qDebug()<<lList.size();
        //作图
        imageWin *iWin = new imageWin();
        iWin->resize(1200,600);
        QPen pen;
        QCustomPlot *pCustomPlot = new QCustomPlot(iWin);
        iWin->setCentralWidget(pCustomPlot);
        pCustomPlot->legend->setVisible(true);

        pCustomPlot->yAxis->setTickLabels(true);
        pCustomPlot->yAxis2->setVisible(true);
        pCustomPlot->yAxis->setVisible(true);
        pCustomPlot->axisRect()->addAxis(QCPAxis::atRight);
        pCustomPlot->axisRect()->addAxis(QCPAxis::atLeft);
        pCustomPlot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(15); // add some padding to have space for tags
        pCustomPlot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(15);
        pCustomPlot->axisRect()->axis(QCPAxis::atLeft, 0)->setPadding(15);// add some padding to have space for tags

        QVector<double> preVector(lList.size());
        QVector<double> dtVector(lList.size());
        QVector<double> disVector(lList.size());
        QVector<double> sandconVector(lList.size());
        QVector<double> edtVector(eList.size());
        QVector<double> momVector(eList.size());
        QVector<double> enegyVector(eList.size());
        for(int i = 0; i < lList.size(); i++){
            Pressurelog pl = lList.at(i);
            preVector[i] = pl.getPressure();
            disVector[i] = pl.getDisplacement();
            sandconVector[i] = pl.getSand_concentration();
            QDateTime dt(pl.getDate(),pl.getQTime());
            dtVector[i] = QDateTime::fromString(dt.toString("yyyy-MM-dd hh:mm:ss"),"yyyy-MM-dd hh:mm:ss").toTime_t();
        }

        for(int i = 0; i<eList.size(); i++){
            CEvents e = eList.at(i);
            momVector[i] = e.getMom_mag();
            enegyVector[i] = e.getEnergy()*100;
            QDateTime edt(e.getDate(),e.getQTime());
            edtVector[i] = QDateTime::fromString(edt.toString("yyyy-MM-dd hh:mm:ss"),"yyyy-MM-dd hh:mm:ss").toTime_t();
        }
        QSharedPointer<QCPAxisTickerDateTime> timer(new QCPAxisTickerDateTime);
        timer->setDateTimeFormat("yyyy-MM-dd hh:mm:ss");
        timer->setTickCount(5);
        pCustomPlot->xAxis->setTicker(timer);

        QPointer<QCPGraph> mGraph1 = pCustomPlot->addGraph(pCustomPlot->xAxis, pCustomPlot->axisRect()->axis(QCPAxis::atRight, 0));
        QPointer<QCPGraph> mGraph2 = pCustomPlot->addGraph(pCustomPlot->xAxis, pCustomPlot->axisRect()->axis(QCPAxis::atRight, 1));
        QPointer<QCPGraph> mGraph3 = pCustomPlot->addGraph(pCustomPlot->xAxis, pCustomPlot->axisRect()->axis(QCPAxis::atLeft, 0));
        QPointer<QCPGraph> mGraph4 = pCustomPlot->addGraph(pCustomPlot->xAxis, pCustomPlot->axisRect()->axis(QCPAxis::atLeft, 1));
        mGraph1->setPen(QPen(QColor(250, 120, 0)));
        mGraph2->setPen(QPen(QColor(0, 180, 60)));
        mGraph4->setPen(QPen(QColor(0, 180, 180)));

        mGraph1->addData(dtVector,preVector);
        mGraph1->setName("施工压力");
        mGraph2->addData(dtVector,disVector);
        mGraph2->setName("排量");
        mGraph3->addData(dtVector,sandconVector);
        mGraph3->setName("砂浓度");
        mGraph4->addData(edtVector,momVector);
        mGraph4->setName("事件点震级");
        pCustomPlot->xAxis->rescale();
        mGraph1->rescaleValueAxis(false, true);
        mGraph2->rescaleValueAxis(false, true);
        mGraph3->rescaleValueAxis(false, true);
        mGraph4->rescaleValueAxis(false, true);
        mGraph1->valueAxis()->setRange(0,100);
        mGraph2->valueAxis()->setRange(0,20);
        mGraph3->valueAxis()->setRange(0,400);
        mGraph4->valueAxis()->setRange(-5,0);
        mGraph4->setLineStyle(QCPGraph::lsNone);
        mGraph4->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 9));
        mGraph1->valueAxis()->setLabel("施工压力");
        mGraph2->valueAxis()->setLabel("排量");
        mGraph3->valueAxis()->setLabel("砂浓度");
        mGraph4->valueAxis()->setLabel("震级");

//        QCPAxisRect *volumeAxisRect = new QCPAxisRect(pCustomPlot);
//        pCustomPlot->plotLayout()->addElement(1, 0, volumeAxisRect);
//        volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 150));
//        volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
//        volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
//        pCustomPlot->plotLayout()->setRowSpacing(0);
//        volumeAxisRect->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
//        volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));
//        pCustomPlot->setAutoAddPlottableToLegend(false);
//        QCPBars *volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
//        volumePos->setWidth(30);
//        volumePos->setPen(Qt::NoPen);
//        volumePos->setBrush(QColor(200, 70, 90));
//        connect(pCustomPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
//        connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), pCustomPlot->xAxis, SLOT(setRange(QCPRange)));
//        volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(timer);
//        volumePos->setData(edtVector,enegyVector);
//        volumeAxisRect->setupFullAxesBox(true);
//        volumePos->rescaleAxes();

//        QCPMarginGroup *group = new QCPMarginGroup(pCustomPlot);
//        pCustomPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
//        volumeAxisRect->setMarginGroup(QCP::msLeft|QCP::msRight, group);

        QList<QCPAxis*> axes;
        axes <<pCustomPlot->xAxis <<pCustomPlot->axisRect()->axis(QCPAxis::atRight, 0) << pCustomPlot->axisRect()->axis(QCPAxis::atRight, 1) << pCustomPlot->axisRect()->axis(QCPAxis::atLeft, 0) << pCustomPlot->axisRect()->axis(QCPAxis::atLeft, 1);
        pCustomPlot->axisRect()->setRangeZoomAxes(axes);
        pCustomPlot->axisRect()->setRangeDragAxes(axes);
        pCustomPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom| QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);

        iWin->show();
    }
}


