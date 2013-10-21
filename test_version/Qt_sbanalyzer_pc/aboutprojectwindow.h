#ifndef ABOUTPROJECTWINDOW_H
#define ABOUTPROJECTWINDOW_H

#include <QMainWindow>

namespace Ui {
class aboutProjectWindow;
}

class aboutProjectWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit aboutProjectWindow(QWidget *parent = 0);
    ~aboutProjectWindow();
    
private:
    Ui::aboutProjectWindow *ui;
};

#endif // ABOUTPROJECTWINDOW_H
