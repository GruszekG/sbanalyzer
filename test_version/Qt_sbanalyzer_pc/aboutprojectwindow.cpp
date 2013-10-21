#include "aboutprojectwindow.h"
#include "ui_aboutprojectwindow.h"

aboutProjectWindow::aboutProjectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::aboutProjectWindow)
{
    ui->setupUi(this);
}

aboutProjectWindow::~aboutProjectWindow()
{
    delete ui;
}
