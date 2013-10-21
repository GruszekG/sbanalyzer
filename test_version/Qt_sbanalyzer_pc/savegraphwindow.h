#ifndef SAVEGRAPHWINDOW_H
#define SAVEGRAPHWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class SaveGraphWindow;
}

class SaveGraphWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SaveGraphWindow(QWidget *parent = 0);
    ~SaveGraphWindow();
    
private:
    Ui::SaveGraphWindow *ui;

public slots:
    void onSaveButton();
    void onCancelButton();

signals:
    void putGraphsAsPDF(QString);
    void putGraphsAsPNG(QString);
    void putGraphsAsJPG(QString);
    void putGraphsAsBMP(QString);
};

#endif // SAVEGRAPHWINDOW_H
