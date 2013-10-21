#ifndef SAVEMEASUREMENTSWINDOW_H
#define SAVEMEASUREMENTSWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "qskater.h"
#include "dialogwindow.h"
#include "measurementData.h"

namespace Ui {
class saveMeasurementsWindow;
}

class saveMeasurementsWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit saveMeasurementsWindow(QWidget *parent = 0);
    ~saveMeasurementsWindow();
    
private:
    Ui::saveMeasurementsWindow *ui;
    QVector<QSkater> skaters;
    DialogWindow *dialogWin;
    double keyCounter;
    double graphMemSizeBefore;
    double graphMemSizeAfter;

private slots:
    void onOkGraphbutton();
    void onQuitButton();

    void startGraph(QCustomPlot *accPlot, QCustomPlot *gyroPlot);
    void onBackButton();

    void onStartButton();
    void onStopButton();

    void onTerminalButton();

    void drawGraph(QByteArray newData);

    void onCutFirst20Button();
    void onCutLast20Button();

public:
    void startMeasurementWindow();
    void getSkaters(QVector<QSkater> skat);

signals:
    void stopMeasure();
    void startMeasure();

};

#endif // SAVEMEASUREMENTSWINDOW_H
