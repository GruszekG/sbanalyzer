#ifndef MEASUREMENTCONFWINDOW_H
#define MEASUREMENTCONFWINDOW_H

#include <QDialog>
#include "command.h"

namespace Ui {
class MeasurementConfWindow;
}

class MeasurementConfWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit MeasurementConfWindow(QWidget *parent = 0);
    ~MeasurementConfWindow();

    ConfCmd getSettings(void);
public slots:
    void onOkButton(void);
    void onCancelButton(void);
    void onAccChange(int idx);
    void onGyroChange(int idx);
    void onFreqChange(int idx);
    void onTimeChange(int idx);

signals:
    void newConf(ConfCmd);  //prepared new measurements
    
private:
    ConfCmd settings;
    Ui::MeasurementConfWindow *ui;
};

#endif // MEASUREMENTCONFWINDOW_H
