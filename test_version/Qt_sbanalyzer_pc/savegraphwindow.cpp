#include "savegraphwindow.h"
#include "ui_savegraphwindow.h"

SaveGraphWindow::SaveGraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SaveGraphWindow)
{
    ui->setupUi(this);

    connect(ui->saveGraphButton, SIGNAL(clicked()), SLOT(onSaveButton()));
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(onCancelButton()));
}

SaveGraphWindow::~SaveGraphWindow()
{
    delete ui;
}

void SaveGraphWindow::onSaveButton()
{
    if(ui->bmpCheckBox->checkState() == Qt::Checked) emit putGraphsAsBMP(ui->lineEdit->displayText());
    if(ui->pngCheckBox->checkState() == Qt::Checked) emit putGraphsAsPNG(ui->lineEdit->displayText());
    if(ui->jpgCheckBox->checkState() == Qt::Checked) emit putGraphsAsJPG(ui->lineEdit->displayText());
    if(ui->pdfCheckBox->checkState() == Qt::Checked) emit putGraphsAsPDF(ui->lineEdit->displayText());

    close();
}

void SaveGraphWindow::onCancelButton()
{
    close();
}
