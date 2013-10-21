#include "instvalueswindow.h"
#include "ui_instvalueswindow.h"

instValuesWindow::instValuesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::instValuesWindow)
{
    ui->setupUi(this);
    setWindowTitle("Instantaneous values");
}



instValuesWindow::~instValuesWindow()
{
    delete ui;
}

void instValuesWindow::setInstValues(QVector<double> *array)
{
    ui->axLCD->display((int)array->at(0));
    ui->ayLCD->display((int)array->at(1));
    ui->azLCD->display((int)array->at(2));
    ui->gxLCD->display((int)array->at(3));
    ui->gyLCD->display((int)array->at(4));
    ui->gzLCD->display((int)array->at(5));
}
