#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

#include <QMainWindow>
#include "qextserialport.h"
#include <QTimer>
#include <QDebug>
#include <iostream>
#include "measurementData.h"
#include "command.h"
#include "measurementconfwindow.h"



namespace Ui {
class DialogWindow;
}

class DialogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DialogWindow(QWidget *parent = 0);
    ~DialogWindow();




private:
    Ui::DialogWindow *ui; //terminal window
    QextSerialPort *port; //port com
    MeasurementConfWindow *confWind;

    QTimer *timerMes;      //measurement triger
    QTimer *timerCom;       //comunication triger

    bool measurement;       //sate of measurement(true- running, false- stop)
    bool configurationInProgress;
    char command;           //command number





private slots:
    void sendTextEdit();        //recognize sending command

    void onPortNameChanged(const QString &name);
    void onBaudRateChanged(int idx);
    void onOpenCloseButtonClicked();

    void onCom();           // send command to SA

    void prepareDataMeasurement();

    void closeWindow();    //hide window
    void clearTerminal();

public slots:
    void onStartButton();  //send start command
    void onStopButton();    //send stop command

    bool getMeasurementState();
    void setTimerMes(int interval);
    void onStartCommand();
    void onInfoCommand();
    void onSendConfCommand(ConfCmd _cmd);


signals:
    void dataAvaible(QByteArray);  //prepared new measurements

};

#endif // DIALOGWINDOW_H
