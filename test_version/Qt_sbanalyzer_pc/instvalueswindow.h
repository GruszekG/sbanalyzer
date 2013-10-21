#ifndef INSTVALUESWINDOW_H
#define INSTVALUESWINDOW_H

#include <QMainWindow>

namespace Ui {
class instValuesWindow;
}

class instValuesWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit instValuesWindow(QWidget *parent = 0);
    ~instValuesWindow();
    
private:
    Ui::instValuesWindow *ui;

private slots:

public slots:
    void setInstValues(QVector<double> *array);

};

#endif // INSTVALUESWINDOW_H
