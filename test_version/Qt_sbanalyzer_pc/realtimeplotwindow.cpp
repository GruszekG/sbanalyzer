#include "realtimeplotwindow.h"
#include "ui_realtimeplotwindow.h"

RealTimePlotWindow::RealTimePlotWindow(QWidget *parent) :
    QMainWindow(parent),
    keyCounter(0),
    wait(0),
    MPS(0),
   // dialogWindow(0),
    measurementState(false),
    triger(false),
    ui(new Ui::RealTimePlotWindow)
{
    ui->setupUi(this);

    setWindowTitle("SkateboardAnalyzer v0.5 measuring");
    setWindowIcon(QIcon(":/skate"));

    //--------------SETS VARIABLES--------------//
    dialogWindow = new DialogWindow(this);
    instValWindow = new instValuesWindow(this);
    saveGraphWindow = new SaveGraphWindow(this);

    timer = new QTimer(this);
    timer->start(200);

    instValues = new QVector<double> (10);

    //---------------------------------------------------//
    //-----------------CONNECTS--------------------------//
    //---------------------------------------------------//
    //buttons
  //  connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->terminalButton, SIGNAL(clicked()), SLOT(onTerminalButton()));
    connect(ui->instantValuesButton, SIGNAL(clicked()), SLOT(onInstButton()));

    connect(ui->stopButton, SIGNAL(clicked()), SLOT(onStopButton()));
    connect(ui->startButton, SIGNAL(clicked()), SLOT(onStartButton()));

    connect(saveGraphWindow, SIGNAL(putGraphsAsPNG(QString)),this, SLOT(saveAsPNG(QString)));
    connect(saveGraphWindow, SIGNAL(putGraphsAsBMP(QString)),this, SLOT(saveAsBMP(QString)));
    connect(saveGraphWindow, SIGNAL(putGraphsAsPDF(QString)),this, SLOT(saveAsPDF(QString)));
    connect(saveGraphWindow, SIGNAL(putGraphsAsJPG(QString)),this, SLOT(saveAsJPG(QString)));

    connect(ui->saveGraphButton, SIGNAL(clicked()), SLOT(onSaveGraphButton()));

    //dialog window
    connect(dialogWindow, SIGNAL(dataAvaible(QByteArray)), this, SLOT(dataAvaible(QByteArray)));
    //timers
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));


    //--------------ON PLOTS-----------------//
     ui->accPlot->replot();
     ui->gyroPlot->replot();
     startGraph(ui->accPlot, ui->gyroPlot/*, ui->an_gyroPlot*/);
}

RealTimePlotWindow::~RealTimePlotWindow()
{
    delete ui;
    delete instValWindow;
    delete saveGraphWindow;
}

void RealTimePlotWindow::onTerminalButton()
{
   // dialogWindow = new DialogWindow(this);
    //dialogWindow->show();
    dialogWindow->showNormal();
}

void RealTimePlotWindow::onInstButton()
{
    instValWindow->show();
}

void RealTimePlotWindow::stopDialog()
{
    onStopButton();
    delete dialogWindow;
}

void RealTimePlotWindow::onStopButton()
{
    dialogWindow->onStopButton();
    if(dialogWindow->getMeasurementState() == false) measurementState = false;
    else measurementState = true;
}

void RealTimePlotWindow::onStartButton()
{
    dialogWindow->onStartButton();
    if(dialogWindow->getMeasurementState() == true) measurementState = true;
    else measurementState = false;
}

void RealTimePlotWindow::saveAsPNG(QString ext)
{
   ui->accPlot->savePng("fast_graphs/"+ext+"_acce.png",800,400,2,-1);
   ui->gyroPlot->savePng("fast_graphs/"+ext+"_gyro.png",800,400,2,-1);
    qDebug()<<"save_graph"<<"fast_graps/"+ext+"_acc.png";
}

void RealTimePlotWindow::saveAsPDF(QString ext)
{
    ui->accPlot->savePdf("fast_graphs/"+ext+"_acce.pdf",true,800,400);
    ui->gyroPlot->savePdf("fast_graphs/"+ext+"_gyro.pdf",true,800,400);
}

void RealTimePlotWindow::saveAsJPG(QString ext)
{
    ui->accPlot->saveJpg("fast_graphs/"+ext+"_acce.jpg",800,400,2,-1);
    ui->gyroPlot->saveJpg("fast_graphs/"+ext+"_gyro.jpg",800,400,2,-1);
}

void RealTimePlotWindow::saveAsBMP(QString ext)
{
    ui->accPlot->saveBmp("fast_graphs/"+ext+"_acce.bmp",800,400,2);
    ui->gyroPlot->saveBmp("fast_graphs/"+ext+"_gyro.bmp",800,400,2);
}

void RealTimePlotWindow::onSaveGraphButton()
{
    saveGraphWindow->show();
}

//-------------------------------TIMER/MPS------------------------------//

void RealTimePlotWindow::onTimer()
{
    if(wait > 4)
    {
        if(MPS == 0)    ui->statusbar->showMessage(QString("Disconnected, %1 MPS").arg(MPS));
        else ui->statusbar->showMessage(QString("Connected, %1 MPS").arg(MPS));
        wait = 0;
        MPS = 0;
    }
    wait ++;
    triger = true;
}

//-------------------------------------------------------------------------------------------------//
//--------------------GRAPHS SETTINGS-------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------//
void RealTimePlotWindow::startGraph(QCustomPlot *accPlot, QCustomPlot *gyroPlot/*, QCustomPlot *an_gyroPlot*/)
{
    //------------------accelerometer graph-------------------
    accPlot->addGraph(); // blue line
    accPlot->graph(0)->setPen(QPen(Qt::blue));
    accPlot->addGraph(); // red line
    accPlot->graph(1)->setPen(QPen(Qt::red));
    accPlot->addGraph(); // red line
    accPlot->graph(2)->setPen(QPen(Qt::green));

    accPlot->xAxis->setAutoTickStep(false);
    accPlot->xAxis->setTickStep(1);
    accPlot->setTitle("Acceleration LIS3DH");
    accPlot->xAxis->setLabel("time [s]");
    accPlot->yAxis->setLabel("a [mg]");
    //create legend
    accPlot->legend->setVisible(true);
    accPlot->legend->setFont(QFont("Helvetica", 9));
    accPlot->legend->setPositionStyle(QCPLegend::psTopLeft);

    accPlot->graph(0)->setName("x-axis");
    accPlot->graph(1)->setName("y-axis");
    accPlot->graph(2)->setName("z-axis");


    //------------------gyroscope graph-------------------------
    gyroPlot->addGraph(); // blue line
    gyroPlot->graph(0)->setPen(QPen(Qt::blue));
    gyroPlot->addGraph(); // red line
    gyroPlot->graph(1)->setPen(QPen(Qt::red));
    gyroPlot->addGraph(); // red line
    gyroPlot->graph(2)->setPen(QPen(Qt::green));

    gyroPlot->xAxis->setAutoTickStep(false);
    gyroPlot->xAxis->setTickStep(1);
    gyroPlot->setTitle("Angular velocity L3G4200D");
    gyroPlot->xAxis->setLabel("time [s]");
    gyroPlot->yAxis->setLabel("w [dps]");
    //create legend
    gyroPlot->legend->setVisible(true);
    gyroPlot->legend->setFont(QFont("Helvetica", 9));
    gyroPlot->legend->setPositionStyle(QCPLegend::psTopLeft);

    gyroPlot->graph(0)->setName("x-axis");
    gyroPlot->graph(1)->setName("y-axis");
    gyroPlot->graph(2)->setName("z-axis");

    //gyroPlot->graph(0)->setBrush(QBrush(QPixmap("fill.png")));

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(accPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), accPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(accPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), accPlot->yAxis2, SLOT(setRange(QCPRange)));

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(gyroPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), gyroPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(gyroPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), gyroPlot->yAxis2, SLOT(setRange(QCPRange)));

}

//-----------------------------------------------------------------------------------------//
//--------------------------------DRAW NEW POINT TO THE GRAPHS-----------------------------//
//-----------------------------------------------------------------------------------------//
void RealTimePlotWindow::dataAvaible(QByteArray ext)
{
    double przelicznik = 6103515625;//prescaler value
    double memory = 2;

    QVector<measurementData> data = ExtractData(ext);//extract data from dialogwinndow

    quint16 newDataSize = data.size();
    QVector<double> key(newDataSize);

    QVector<double> ax(newDataSize);
    QVector<double> ay(newDataSize);
    QVector<double> az(newDataSize);

    QVector<double> gx(newDataSize);
    QVector<double> gy(newDataSize);
    QVector<double> gz(newDataSize);

    double keyPrescaler =0;
    keyPrescaler = keyCounter / 200;
   // qDebug()<<"znacznik";
    for(double i = 0; i<newDataSize; i++)
    {
        key[i] = (double)keyPrescaler + (i/200);
         // key[i] = (double)keyCounter;
        ax[i] = ((double)data.at(i).ax.as_word)*przelicznik/100000000000;
        ay[i] = ((double)data.at(i).ay.as_word)*(-1)*przelicznik/100000000000;
        az[i] = ((double)data.at(i).az.as_word)*(-1)*przelicznik/100000000000;

        gx[i] = ((double)data.at(i).gx.as_word)*przelicznik/100000000000;
        gy[i] = ((double)data.at(i).gy.as_word)*(-1)*przelicznik/100000000000;
        gz[i] = ((double)data.at(i).gz.as_word)*(-1)*przelicznik/100000000000;
    }
    if((newDataSize>0)&(triger == true))//get instValues 5 times per secound(depend of timmer interval)
    {
        (*instValues)[0] = ax[0];
        (*instValues)[1] = ay[0];
        (*instValues)[2] = az[0];
        (*instValues)[3] = gx[0];
        (*instValues)[4] = gy[0];
        (*instValues)[5] = gz[0];
        triger = false;
        instValWindow->setInstValues(instValues);
    }

//    add new data to graphs
        ui->accPlot->graph(0)->addData(key, ax);
        ui->accPlot->graph(1)->addData(key, ay);
        ui->accPlot->graph(2)->addData(key, az);

        ui->gyroPlot->graph(0)->addData(key, gx);
        ui->gyroPlot->graph(1)->addData(key, gy);
        ui->gyroPlot->graph(2)->addData(key, gz);

//     remove data of lines that's outside visible range:
    ui->accPlot->graph(0)->removeDataBefore(keyPrescaler-memory);
    ui->accPlot->graph(1)->removeDataBefore(keyPrescaler-memory);
    ui->accPlot->graph(2)->removeDataBefore(keyPrescaler-memory);

   // qDebug()<<"znacznik 4\n";

    // rescale value (vertical) axis to fit the current data:
    ui->accPlot->graph(0)->rescaleValueAxis();
    ui->accPlot->graph(1)->rescaleValueAxis(true);
    ui->accPlot->graph(2)->rescaleValueAxis(true);

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->accPlot->xAxis->setRange(keyPrescaler, memory, Qt::AlignRight);
    ui->accPlot->replot();

    // remove data of lines that's outside visible range:
    ui->gyroPlot->graph(0)->removeDataBefore(keyPrescaler-memory);
    ui->gyroPlot->graph(1)->removeDataBefore(keyPrescaler-memory);
    ui->gyroPlot->graph(2)->removeDataBefore(keyPrescaler-memory);

    // rescale value (vertical) axis to fit the current data:
    ui->gyroPlot->graph(0)->rescaleValueAxis();
    ui->gyroPlot->graph(1)->rescaleValueAxis(true);
    ui->gyroPlot->graph(2)->rescaleValueAxis(true);

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->gyroPlot->xAxis->setRange(keyPrescaler, memory, Qt::AlignRight);

    ui->gyroPlot->replot();

    keyCounter += newDataSize;
    MPS += newDataSize;
    qDebug()<<"keyCounter:"<<keyCounter;
}


//----------------------------------------------------------------------------------//
//----------------EXTRACTING DATA SLOT----------------------------------------------//
//----------------------------------------------------------------------------------//
QVector<measurementData> RealTimePlotWindow::ExtractData(QByteArray data)
{
    QVector<measurementData> measurements;

    while(data.size()/frameLenght != 0)
    {
        data.remove(0,1);//removing start char
        QByteArray rawData = data;
        rawData.truncate(16);

        quint8 controlSumThere = data.at(16);
        data.remove(0,17);

        quint8 controlSumHere = 0;
        for(int j = 0; j<16; j++)//calculate control sum
        {
            controlSumHere += rawData[j];
        }
        if(controlSumThere == controlSumHere)//check control sum
        {
           measurementData temp;

           temp.ax.as_bytes.lo = rawData.at(6);
           temp.ax.as_bytes.hi = rawData.at(7);
           temp.ay.as_bytes.lo = rawData.at(8);
           temp.ay.as_bytes.hi = rawData.at(9);
           temp.az.as_bytes.lo = rawData.at(10);
           temp.az.as_bytes.hi = rawData.at(11);

           temp.gx.as_bytes.lo = rawData.at(0);
           temp.gx.as_bytes.hi = rawData.at(1);
           temp.gy.as_bytes.lo = rawData.at(2);
           temp.gy.as_bytes.hi = rawData.at(3);
           temp.gz.as_bytes.lo = rawData.at(4);
           temp.gz.as_bytes.hi = rawData.at(5);

           temp.an_gx.as_bytes.lo = rawData.at(12);
           temp.an_gx.as_bytes.hi = rawData.at(13);
           temp.an_gz.as_bytes.lo = rawData.at(14);
           temp.an_gz.as_bytes.hi = rawData.at(15);

            measurements.append(temp);
        }
        else
        {
            qDebug()<<"Invalid frame detected";
        }
    }

    return measurements;
}

