#include "savemeasurementswindow.h"
#include "ui_savemeasurementswindow.h"

saveMeasurementsWindow::saveMeasurementsWindow(QWidget *parent) :
    QMainWindow(parent),
    keyCounter(0),
    graphMemSizeBefore(2),
    graphMemSizeAfter(0),
    ui(new Ui::saveMeasurementsWindow)
{

    dialogWin = new DialogWindow(this);

    qDebug()<<"dupa";
    ui->setupUi(this);
     setWindowTitle("Trick measurement");
   // connect(ui->quitSaveWindowButton, SIGNAL(clicked()),SLOT(onQuitButton()));
    connect(ui->okGraphButton, SIGNAL(clicked()), SLOT(onOkGraphbutton()));
    connect(ui->backButton, SIGNAL(clicked()), SLOT(onBackButton()));

    connect(ui->startButton, SIGNAL(clicked()), SLOT(onStartButton()));
    connect(ui->stopButton, SIGNAL(clicked()), SLOT(onStopButton()));
    connect(ui->terminalButton, SIGNAL(clicked()), SLOT(onTerminalButton()));

    connect(ui->cutFirst20Button, SIGNAL(clicked()), SLOT(onCutFirst20Button()));
    connect(ui->cutLast20Button, SIGNAL(clicked()), SLOT(onCutLast20Button()));


    //dialog window
    connect(dialogWin, SIGNAL(dataAvaible(QByteArray)), this, SLOT(drawGraph(QByteArray)));

    //dialog window
   // connect(dialogWin, SIGNAL(dataAvaible(QByteArray)), this, SLOT(dataAvaible(QByteArray)));

    ui->tricksBox->setEditable(true);
    ui->tricksBox->addItems(QStringList()
                            <<QLatin1String("ollie")
                            <<QLatin1String("kickflip")
                            <<QLatin1String("pop shove it")
                            <<QLatin1String("heelflip")
                            <<QLatin1String("360flip")
                            <<QLatin1String("varial kickflip")
                            <<QLatin1String("fs ollie 180")
                            <<QLatin1String("bs ollie 180"));

    for(int i = 0; i< skaters.size(); i++)
        ui->skaterBox->addItem(skaters[i].getName());

    startGraph(ui->accPlot,ui->gyroPlot);

}
void saveMeasurementsWindow::onQuitButton()
{
    ui->stackedWidget->setCurrentIndex(1);
    close();
}

void saveMeasurementsWindow::onOkGraphbutton()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void saveMeasurementsWindow::onTerminalButton()
{
    dialogWin->showNormal();
}

void saveMeasurementsWindow::startMeasurementWindow()
{
    ui->stackedWidget->setCurrentIndex(0);

    ui->skaterBox->clear();

    //ui->buforBarAcce->setVisible(false);
    //ui->buforBarGyro->setVisible(false);

    for(int i = 0; i< skaters.size(); i++)
        ui->skaterBox->addItem(skaters[i].getName());
}

saveMeasurementsWindow::~saveMeasurementsWindow()
{
    delete ui;
}

void saveMeasurementsWindow::onStartButton()
{
    emit startMeasure();
    ui->startButton->setDown(true);
    dialogWin->onStartButton();

   // ui->buforBarAcce->setVisible(true);
   // ui->buforBarGyro->setVisible(true);
}

void saveMeasurementsWindow::onStopButton()
{
    ui->stopButton->setDown(true);
    dialogWin->onStopButton();

   //ui->buforBarAcce->setVisible(false);
  // ui->buforBarGyro->setVisible(false);
}

void saveMeasurementsWindow::onCutFirst20Button()
{
    double memory = 2, keyPrescaler = 0;

    keyPrescaler = keyCounter /200;

    graphMemSizeBefore -= 0.1;

   //     remove data of lines that's outside visible range:
       ui->accPlot->graph(0)->removeDataBefore(keyPrescaler-graphMemSizeBefore);
       ui->accPlot->graph(1)->removeDataBefore(keyPrescaler-graphMemSizeBefore);
       ui->accPlot->graph(2)->removeDataBefore(keyPrescaler-graphMemSizeBefore);

      // qDebug()<<"znacznik 4\n";

       // rescale value (vertical) axis to fit the current data:
       ui->accPlot->graph(0)->rescaleValueAxis();
       ui->accPlot->graph(1)->rescaleValueAxis(true);
       ui->accPlot->graph(2)->rescaleValueAxis(true);

       // make key axis range scroll with the data (at a constant range size of 8):
       ui->accPlot->xAxis->setRange(keyPrescaler - graphMemSizeAfter, graphMemSizeBefore - graphMemSizeAfter, Qt::AlignRight);
       ui->accPlot->replot();

       // remove data of lines that's outside visible range:
       ui->gyroPlot->graph(0)->removeDataBefore(keyPrescaler-graphMemSizeBefore);
       ui->gyroPlot->graph(1)->removeDataBefore(keyPrescaler-graphMemSizeBefore);
       ui->gyroPlot->graph(2)->removeDataBefore(keyPrescaler-graphMemSizeBefore);

       // rescale value (vertical) axis to fit the current data:
       ui->gyroPlot->graph(0)->rescaleValueAxis();
       ui->gyroPlot->graph(1)->rescaleValueAxis(true);
       ui->gyroPlot->graph(2)->rescaleValueAxis(true);

       // make key axis range scroll with the data:
       ui->gyroPlot->xAxis->setRange(keyPrescaler - graphMemSizeAfter, graphMemSizeBefore - graphMemSizeAfter, Qt::AlignRight);

       ui->gyroPlot->replot();
       qDebug()<<"Memory of graph before:"<<graphMemSizeBefore<<"\nMemory of graph After:"<<graphMemSizeAfter<<"\nMemory of graph:"<<graphMemSizeBefore -graphMemSizeAfter;
}

void saveMeasurementsWindow::onCutLast20Button()//-zzzzzzzzzzzzzzzzzzzzzzlllllllllllllllleeeeeeeeeeeeeeeeee ddddddddddzzzzzzzzzziiiiiiiiiiaaaaaaaaaallllllllllllaaaaaaaaaaa
{
    double memory = 2, keyPrescaler = 0;

    keyPrescaler = keyCounter /200;

    graphMemSizeAfter += 0.1;

   //     remove data of lines that's outside visible range:
//   ui->accPlot->graph(0)->removeDataBefore(keyPrescaler-graphMemSize);
//   ui->accPlot->graph(1)->removeDataBefore(keyPrescaler-graphMemSize);
//   ui->accPlot->graph(2)->removeDataBefore(keyPrescaler-graphMemSize);
   ui->accPlot->graph(0)->removeDataAfter(keyPrescaler - graphMemSizeAfter);
   ui->accPlot->graph(1)->removeDataAfter(keyPrescaler - graphMemSizeAfter);
   ui->accPlot->graph(2)->removeDataAfter(keyPrescaler - graphMemSizeAfter);

  // qDebug()<<"znacznik 4\n";

   // rescale value (vertical) axis to fit the current data:
   ui->accPlot->graph(0)->rescaleValueAxis();
   ui->accPlot->graph(1)->rescaleValueAxis(true);
   ui->accPlot->graph(2)->rescaleValueAxis(true);

   // make key axis range scroll with the data (at a constant range size of 8):
   ui->accPlot->xAxis->setRange(keyPrescaler - graphMemSizeAfter, graphMemSizeBefore - graphMemSizeAfter, Qt::AlignRight);
   ui->accPlot->replot();

   // remove data of lines that's outside visible range:
   ui->gyroPlot->graph(0)->removeDataAfter(keyPrescaler - graphMemSizeAfter);
   ui->gyroPlot->graph(1)->removeDataAfter(keyPrescaler - graphMemSizeAfter);
   ui->gyroPlot->graph(2)->removeDataAfter(keyPrescaler - graphMemSizeAfter);

   // rescale value (vertical) axis to fit the current data:
   ui->gyroPlot->graph(0)->rescaleValueAxis();
   ui->gyroPlot->graph(1)->rescaleValueAxis(true);
   ui->gyroPlot->graph(2)->rescaleValueAxis(true);

   // make key axis range scroll with the data:
   ui->gyroPlot->xAxis->setRange(keyPrescaler - graphMemSizeAfter, graphMemSizeBefore - graphMemSizeAfter, Qt::AlignRight);

   ui->gyroPlot->replot();
   // qDebug()<<"Memory of graph"<<graphMemSize;

   qDebug()<<"Memory of graph before:"<<graphMemSizeBefore<<"\nMemory of graph After:"<<graphMemSizeBefore<<"\nMemory of graph:"<<graphMemSizeBefore -graphMemSizeAfter;
}

void saveMeasurementsWindow::startGraph(QCustomPlot *accPlot, QCustomPlot *gyroPlot)
{
    //------------------accelerometer graph-------------------
    accPlot->addGraph(); // blue line
    accPlot->graph(0)->setPen(QPen(Qt::blue,0));
    accPlot->addGraph(); // red line
    accPlot->graph(1)->setPen(QPen(Qt::red,0));
    accPlot->addGraph(); // red line
    accPlot->graph(2)->setPen(QPen(Qt::green,0));

    accPlot->xAxis->setAutoTickStep(false);
    accPlot->xAxis->setTickStep(0.5);
    accPlot->setTitle("Acceleration LIS3DH");
    //accPlot->setTitleFont(QFont("Helvetica", 9);
    accPlot->xAxis->setLabel("time [s]");
    accPlot->yAxis->setLabel("a [mg]");

    //------------------gyroscope graph-------------------------
    gyroPlot->addGraph(); // blue line
    gyroPlot->graph(0)->setPen(QPen(Qt::blue,0));
    gyroPlot->addGraph(); // red line
    gyroPlot->graph(1)->setPen(QPen(Qt::red,0));
    gyroPlot->addGraph(); // red line
    gyroPlot->graph(2)->setPen(QPen(Qt::green,0));

    gyroPlot->xAxis->setAutoTickStep(false);
    gyroPlot->xAxis->setTickStep(0.1);
    gyroPlot->setTitle("Angular velocity L3G4200D");
    gyroPlot->xAxis->setLabel("time [s]");
    gyroPlot->yAxis->setLabel("w [dps]");

    //gyroPlot->graph(0)->setBrush(QBrush(QPixmap("fill.png")));

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(accPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), accPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(accPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), accPlot->yAxis2, SLOT(setRange(QCPRange)));

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(gyroPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), gyroPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(gyroPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), gyroPlot->yAxis2, SLOT(setRange(QCPRange)));

}

void saveMeasurementsWindow::drawGraph(QByteArray newData)
{
    double przelicznik = 6103515625;//prescaler value
    double memory = 2;

    QVector<measurementData> data = ExtractData(newData);//extract data from dialogwinndow

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
//    for(double i = 0; i<newDataSize; i++)
//    {
//        key[i] = (double)keyPrescaler + (i/200);
//         // key[i] = (double)keyCounter;
//        ax[i] = ((double)data.at(i).ax.as_word)*przelicznik/100000000000;
//        ay[i] = ((double)data.at(i).ay.as_word)*(-1)*przelicznik/100000000000;
//        az[i] = ((double)data.at(i).az.as_word)*(-1)*przelicznik/100000000000;

//        gx[i] = ((double)data.at(i).gx.as_word)*przelicznik/100000000000;
//        gy[i] = ((double)data.at(i).gy.as_word)*(-1)*przelicznik/100000000000;
//        gz[i] = ((double)data.at(i).gz.as_word)*(-1)*przelicznik/100000000000;
//    }

////    add new data to graphs
//        ui->accPlot->graph(0)->addData(key, ax);
//        ui->accPlot->graph(1)->addData(key, ay);
//        ui->accPlot->graph(2)->addData(key, az);

//        ui->gyroPlot->graph(0)->addData(key, gx);
//        ui->gyroPlot->graph(1)->addData(key, gy);
//        ui->gyroPlot->graph(2)->addData(key, gz);

////     remove data of lines that's outside visible range:
//    ui->accPlot->graph(0)->removeDataBefore(keyPrescaler-memory);
//    ui->accPlot->graph(1)->removeDataBefore(keyPrescaler-memory);
//    ui->accPlot->graph(2)->removeDataBefore(keyPrescaler-memory);

//   // qDebug()<<"znacznik 4\n";

//    // rescale value (vertical) axis to fit the current data:
//    ui->accPlot->graph(0)->rescaleValueAxis();
//    ui->accPlot->graph(1)->rescaleValueAxis(true);
//    ui->accPlot->graph(2)->rescaleValueAxis(true);

//    // make key axis range scroll with the data (at a constant range size of 8):
//    ui->accPlot->xAxis->setRange(keyPrescaler, memory, Qt::AlignRight);
//    ui->accPlot->replot();

//    // remove data of lines that's outside visible range:
//    ui->gyroPlot->graph(0)->removeDataBefore(keyPrescaler-memory);
//    ui->gyroPlot->graph(1)->removeDataBefore(keyPrescaler-memory);
//    ui->gyroPlot->graph(2)->removeDataBefore(keyPrescaler-memory);

//    // rescale value (vertical) axis to fit the current data:
//    ui->gyroPlot->graph(0)->rescaleValueAxis();
//    ui->gyroPlot->graph(1)->rescaleValueAxis(true);
//    ui->gyroPlot->graph(2)->rescaleValueAxis(true);

//    // make key axis range scroll with the data:
//    ui->gyroPlot->xAxis->setRange(keyPrescaler, memory, Qt::AlignRight);

//    ui->gyroPlot->replot();

    keyCounter += newDataSize;
//    MPS += newDataSize;
   qDebug()<<"Counter: "<<keyCounter;
}

void saveMeasurementsWindow::getSkaters(QVector<QSkater> skat)
{
    skaters = skat;
}

void saveMeasurementsWindow::onBackButton()
{
    ui->stackedWidget->setCurrentIndex(0);
}

