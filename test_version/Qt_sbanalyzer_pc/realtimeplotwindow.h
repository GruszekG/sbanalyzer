#ifndef REALTIMEPLOTWINDOW_H
#define REALTIMEPLOTWINDOW_H

#include <QMainWindow>
#include "dialogwindow.h"
#include "instvalueswindow.h"
#include "savegraphwindow.h"
#include "qskater.h"
#include "measurementData.h"

namespace Ui {
class RealTimePlotWindow;
}

class RealTimePlotWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit RealTimePlotWindow(QWidget *parent = 0);
    ~RealTimePlotWindow();
    
private:
    Ui::RealTimePlotWindow *ui;

    QTimer *timer;

    double keyCounter; //x-axis of graphs

    DialogWindow *dialogWindow;  //terminal window
    instValuesWindow *instValWindow;
    SaveGraphWindow *saveGraphWindow;

    QVector<QSkater> skaters;
     unsigned long int MPS;
     unsigned char wait;
     bool triger;
     bool measurementState;

     QVector<double> *instValues; //instantaneous measurement values
private slots:
     void onInstButton();
     void onTerminalButton();

     void onStopButton();
     void onStartButton();

     void onSaveGraphButton();

     void onTimer();

     void startGraph(QCustomPlot *accPlot, QCustomPlot *gyroPlot/*, QCustomPlot *an_gyroPlot*/);

     void dataAvaible(QByteArray ext);

     void saveAsPNG(QString ext);
     void saveAsPDF(QString ext);
     void saveAsBMP(QString ext);
     void saveAsJPG(QString ext);

     QVector<measurementData> RealTimePlotWindow::ExtractData(QByteArray data);

public slots:
     void stopDialog();

};

#endif // REALTIMEPLOTWINDOW_H
