#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QTimer>
#include "dialogwindow.h"
#include "instvalueswindow.h"
#include "measurementData.h"
#include <QFile>
#include "qskater.h"
#include "aboutprojectwindow.h"
#include "savemeasurementswindow.h"
#include "savegraphwindow.h"
#include "realtimeplotwindow.h"
#include "visualizationwindow.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool getMeasurementState();
    
private:
    Ui::MainWindow *ui;
    QTimer *delay;
    QFile *file;

    QVector<QSkater> skaters;

    aboutProjectWindow *aboutSkateAn;
    saveMeasurementsWindow *saveMeasureWindow;
    RealTimePlotWindow *realTimePlotWindow;
    VisualizationWindow *visWindow;


private slots:
    void onMainMenuButton();

    void onRealTimeGraphButton();
    void onSkatersButton();
    void onTrickMeasuerementButton();
    void onVisualizationButton();

    void hideWelcomewWindow();

    void fillTable(QVector<QSkater> skat);
    void getSkatersFromTable(QVector<QSkater> *skat);
    void getSkatersFromFile(QVector<QSkater> *skat);
    void putSkatersToFile(QVector<QSkater> *skat);

    void onSaveSkatersButton();
    void onAddSkaterButton();
    void onRemoveSkaterButton();
    void onAboutSkateButton();

};

#endif // MAINWINDOW_H
