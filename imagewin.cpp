#include "imagewin.h"
#include "ui_imagewin.h"
#include "general.h"
#include "cevents.h"
#include "Pressurelog.h"
#include <QDebug>
#include <QPen>
imageWin::imageWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::imageWin),mTag1(0)
{
    ui->setupUi(this);
}

imageWin::~imageWin()
{
    delete ui;
}

void imageWin::imagePlot(QString eventPath, QString logPath)
{
    QProgressDialog *progressDialog=new QProgressDialog(this);
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->setMinimumDuration(5);
    progressDialog->setWindowTitle("请稍等");
    progressDialog->setLabelText("读取数据中......");
    progressDialog->setCancelButtonText("Cancel");

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
//            qDebug()<<event.getNumber()<<" "<<event.getDate()<<"  "<<event.getQTime()<<"  "<<event.getNorth()<<"  "<<event.getEnergy();
            eList<<event;
        }
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
        progressDialog->setRange(0,eList.size()+lList.size()-1);
        int progressNum=0;
        //作图
        this->resize(1300,700);
        this->setWindowTitle("压裂曲线与事件点匹配(包含震级、能量)");
        QPen pen;
        pCustomPlot = new QCustomPlot(this);
        this->setCentralWidget(pCustomPlot);
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
        //  QVector<double> enegyVector(eList.size());
        for(int i = 0; i < lList.size(); i++){
            Pressurelog pl = lList.at(i);
            preVector[i] = pl.getPressure();
            disVector[i] = pl.getDisplacement();
            sandconVector[i] = pl.getSand_concentration();
            QDateTime dt(pl.getDate(),pl.getQTime());
            dtVector[i] = QDateTime::fromString(dt.toString("yyyy-MM-dd hh:mm:ss"),"yyyy-MM-dd hh:mm:ss").toTime_t();
            progressDialog->setValue(progressNum);
            progressNum++;
        }

        for(int i = 0; i<eList.size(); i++){
            CEvents e = eList.at(i);
            momVector[i] = e.getMom_mag();
            double power = e.getMom_mag()*1.5+4.8;
            enegyVector[i] = qPow(10,power);
            //            enegyVector[i] = e.getEnergy();
            QDateTime edt(e.getDate(),e.getQTime());
            edtVector[i] = QDateTime::fromString(edt.toString("yyyy-MM-dd hh:mm:ss"),"yyyy-MM-dd hh:mm:ss").toTime_t();
//            qDebug()<<QDateTime::fromString(edt.toString("yyyy-MM-dd hh:mm:ss"),"yyyy-MM-dd hh:mm:ss");
//            qDebug()<<enegyVector[i];
            progressDialog->setValue(progressNum);
            progressNum++;
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
        //        mGraph1->valueAxis()->setTickLabelFont(QFont("雅黑",14));
        //        mGraph1->valueAxis()->setLabelFont(QFont("雅黑",14));
        mGraph1->valueAxis()->setLabel("施工压力");
        mGraph2->valueAxis()->setLabel("排量");
        mGraph3->valueAxis()->setLabel("砂浓度");
        mGraph4->valueAxis()->setLabel("震级");

        volumeAxisRect = new QCPAxisRect(pCustomPlot);
        pCustomPlot->plotLayout()->addElement(1, 0, volumeAxisRect);
        volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 150));
        volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
        volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
        pCustomPlot->plotLayout()->setRowSpacing(0);
        volumeAxisRect->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
        volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));
        pCustomPlot->setAutoAddPlottableToLegend(false);
        QCPBars *volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
        volumePos->valueAxis()->setLabel("地震波能量(N·m)");
        volumePos->setWidth(30);
        volumePos->setPen(Qt::NoPen);
        volumePos->setBrush(QColor(Qt::red));
        connect(pCustomPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
        connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), pCustomPlot->xAxis, SLOT(setRange(QCPRange)));
        volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(timer);
        volumePos->setData(edtVector,enegyVector);
        volumePos->rescaleAxes();

        QCPMarginGroup *group = new QCPMarginGroup(pCustomPlot);
        pCustomPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
        volumeAxisRect->setMarginGroup(QCP::msLeft|QCP::msRight, group);

        QList<QCPAxis*> axes;
        axes <<pCustomPlot->xAxis <<pCustomPlot->axisRect()->axis(QCPAxis::atRight, 0) << pCustomPlot->axisRect()->axis(QCPAxis::atRight, 1) << pCustomPlot->axisRect()->axis(QCPAxis::atLeft, 0) << pCustomPlot->axisRect()->axis(QCPAxis::atLeft, 1);
        pCustomPlot->axisRect()->setRangeZoomAxes(axes);
        pCustomPlot->axisRect()->setRangeDragAxes(axes);
        pCustomPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom| QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
        pCustomPlot->axisRect()->setRangeZoomFactor(0.9);

        mTag1 = new AxisTag(mGraph1->valueAxis());
        mTag1->setPen(mGraph1->pen());

        mTag2 = new AxisTag(mGraph4->valueAxis());
        mTag2->setPen(mGraph4->pen());

        connect(this->pCustomPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));

        this->show();
    }
}

void imageWin::on_action_triggered()
{
    qDebug()<<"action triggered";

    this->pCustomPlot->rescaleAxes();
    this->pCustomPlot->graph(0)->valueAxis()->setRange(0,100);
    this->pCustomPlot->graph(1)->valueAxis()->setRange(0,20);
    this->pCustomPlot->graph(2)->valueAxis()->setRange(0,400);
    this->pCustomPlot->graph(3)->valueAxis()->setRange(-5,0);
    this->pCustomPlot->replot();

}

void imageWin::on_action_2_triggered()
{
    QString path = QFileDialog::getSaveFileName(this,"保存图片",".","png files (*.png)");
    this->pCustomPlot->savePng(path);
}

void imageWin::on_action_3_triggered()
{
    this->Cdialog = new ControlDialog(this);
    this->Cdialog->setGeometry(100,100,100,100);
    int x= this->geometry().x();
    int y= this->geometry().y();
    int width = this->geometry().width();
    int height = this->geometry().height();
    this->Cdialog->setGeometry(x+width+1,y+1,300,500);
    this->Cdialog->show();
}

void imageWin::tickLabelValueChange(int value)
{
    this->pCustomPlot->graph(0)->valueAxis()->setTickLabelFont(QFont("雅黑",value));
    this->pCustomPlot->graph(1)->valueAxis()->setTickLabelFont(QFont("雅黑",value));
    this->pCustomPlot->graph(2)->valueAxis()->setTickLabelFont(QFont("雅黑",value));
    this->pCustomPlot->graph(3)->valueAxis()->setTickLabelFont(QFont("雅黑",value));
    this->pCustomPlot->xAxis->setTickLabelFont(QFont("雅黑",value));
    volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelFont(QFont("雅黑",value));
    volumeAxisRect->axis(QCPAxis::atLeft)->setTickLabelFont(QFont("雅黑",value));


    this->pCustomPlot->graph(0)->valueAxis()->setLabelFont(QFont("雅黑",value));
    this->pCustomPlot->graph(1)->valueAxis()->setLabelFont(QFont("雅黑",value));
    this->pCustomPlot->graph(2)->valueAxis()->setLabelFont(QFont("雅黑",value));
    this->pCustomPlot->graph(3)->valueAxis()->setLabelFont(QFont("雅黑",value));
    this->pCustomPlot->xAxis->setLabelFont(QFont("雅黑",value));
    volumeAxisRect->axis(QCPAxis::atBottom)->setLabelFont(QFont("雅黑",value));
    volumeAxisRect->axis(QCPAxis::atLeft)->setLabelFont(QFont("雅黑",value));

    this->pCustomPlot->replot();


}

void imageWin::eventHideShow(int value)
{
    if(value>0){
        this->pCustomPlot->graph(3)->setVisible(true);
    }else{
        this->pCustomPlot->graph(3)->setVisible(false);
    }
    this->pCustomPlot->replot();
}

void imageWin::preHideShow(int value)
{
    qDebug()<<"value"<<value;
    if(value>0){
        this->pCustomPlot->graph(0)->setVisible(true);
    }else{
        this->pCustomPlot->graph(0)->setVisible(false);
    }
    this->pCustomPlot->replot();
}

void imageWin::disHideShow(int value)
{
    qDebug()<<"value"<<value;
    if(value>0){
        this->pCustomPlot->graph(1)->setVisible(true);
    }else{
        this->pCustomPlot->graph(1)->setVisible(false);
    }
    this->pCustomPlot->replot();
}

void imageWin::sandHideShow(int value)
{
    qDebug()<<"value"<<value;
    if(value>0){
        this->pCustomPlot->graph(2)->setVisible(true);
    }else{
        this->pCustomPlot->graph(2)->setVisible(false);
    }
    this->pCustomPlot->replot();
}

void imageWin::rangeChanged(int num , QString value1 , QString value2)
{
    if(value1.isNull()||value2.isNull()){
        QMessageBox::information(this,"error","非法输入!");
    }else{
        if(value1.toInt()<value2.toInt())
        this->pCustomPlot->graph(num)->valueAxis()->setRange(value1.toInt(),value2.toInt());
    }
    this->pCustomPlot->replot();
}

void imageWin::mouseMove(QMouseEvent *event)
{
    // calculate and add a new data point to each graph:
    QPointer<QCPGraph> mGraph1 = this->pCustomPlot->graph(0);
    QPointer<QCPGraph> mGraph4 = this->pCustomPlot->graph(3);

    int x_pos = event->pos().x();
    int y_pos = event->pos().y();

    int x_val = this->pCustomPlot->xAxis->pixelToCoord(x_pos);
    double y_val_pre = mGraph1->data()->findBegin(x_val)->value;
    double y_val_event = mGraph4->data()->findBegin(x_val)->value;
//    double y_val = mGraph1->valueAxis()->pixelToCoord(y_pos);

    qDebug()<<"x:"<<QString::number(x_val, 10, 4)<<" "<<"y:"<<y_val_event;


    mTag1->updatePosition(x_val,y_val_pre);
    mTag2->updatePosition(x_val,y_val_event);

    mTag1->setText(QString::number(y_val_pre, 'f', 2));
    mTag2->setText(QString::number(y_val_event, 'f', 2));






      //make key axis range scroll with the data:
//    this->pCustomPlot->xAxis->rescale();
//    mGraph1->rescaleValueAxis(false, true);
//    mGraph2->rescaleValueAxis(false, true);
//    this->pCustomPlot->xAxis->setRange(this->pCustomPlot->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
//    double graph1Value = mGraph1->dataMainValue(mGraph1->dataCount()-1);
//    qDebug()<<graph1Value;
//    double graph2Value = mGraph2->dataMainValue(mGraph2->dataCount()-1);
//    mTag1->updatePosition(graph1Value);
//    mTag2->updatePosition(graph2Value);
//    mTag1->setText(QString::number(graph1Value, 'f', 2));
//    mTag2->setText(QString::number(graph2Value, 'f', 2));

    this->pCustomPlot->replot();
}
