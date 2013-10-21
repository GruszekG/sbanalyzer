#include "measurementconfwindow.h"
#include "ui_measurementconfwindow.h"
#include "command.h"
#include "LIS3DH.h"
#include "L3G4200D.h"
#include <QDebug>

MeasurementConfWindow::MeasurementConfWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasurementConfWindow)
{
    ui->setupUi(this);

    ui->AccComboBox->addItem(QLatin1String("2 g"), LIS3DH_2G);
    ui->AccComboBox->addItem(QLatin1String("4 g"), LIS3DH_4G);
    ui->AccComboBox->addItem(QLatin1String("8 g"), LIS3DH_8G);
    ui->AccComboBox->addItem(QLatin1String("16 g"), LIS3DH_16G);

    ui->GyroComboBox->addItem(QLatin1String("250 dps"), L3G4200D_250dps);
    ui->GyroComboBox->addItem(QLatin1String("500 dps"), L3G4200D_500dps);
    ui->GyroComboBox->addItem(QLatin1String("2000 dps"), L3G4200D_2000dps);

    ui->FreqComboBox->addItem(QLatin1String("100 Hz"), L3G4200D_100Hz);
    ui->FreqComboBox->addItem(QLatin1String("200 Hz"), L3G4200D_200Hz);
    ui->FreqComboBox->addItem(QLatin1String("400 Hz"), L3G4200D_400Hz);
    ui->FreqComboBox->addItem(QLatin1String("800 Hz"), L3G4200D_800Hz);

    ui->TimeSpinBox->setValue(5);
    ui->TimeSpinBox->setMinimum(1);
    ui->TimeSpinBox->setMaximum(3600);

    connect(ui->OkButton,SIGNAL(clicked()),this,SLOT(onOkButton()));
    connect(ui->AccComboBox, SIGNAL(currentIndexChanged(int)),this,SLOT(onAccChange(int)));
    connect(ui->GyroComboBox, SIGNAL(currentIndexChanged(int)),this,SLOT(onGyroChange(int)));
    connect(ui->TimeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onTimeChange(int)));
    connect(ui->FreqComboBox, SIGNAL(currentIndexChanged(int)), this,SLOT(onFreqChange(int)));
}


MeasurementConfWindow::~MeasurementConfWindow()
{
    delete ui;
}

void MeasurementConfWindow::onAccChange(int idx)
{
    settings.setAccRange((LIS3DH_Range)ui->AccComboBox->itemData(idx).toInt());
    #ifdef QDEBUG_H
    qDebug()<<"Acc Range: "<<settings.printAccRange();
    #endif
}

void MeasurementConfWindow::onFreqChange(int idx)
{
    settings.setFreq((L3G4200D_ODR)ui->FreqComboBox->itemData(idx).toInt());
    #ifdef QDEBUG_H
    qDebug()<<"Freq: "<<settings.printFreqSet();
    #endif
}

void MeasurementConfWindow::onTimeChange(int idx)
{
    settings.setTime(idx);
    #ifdef QDEBUG_H
    qDebug()<<"Time: "<<settings.printMeasurementTime();
    #endif
}

void MeasurementConfWindow::onGyroChange(int idx)
{
    settings.setGyroRange((L3G4200D_Range)ui->GyroComboBox->itemData(idx).toInt());
    #ifdef QDEBUG_H
    qDebug()<<"Gyro range: "<<settings.printGyroRange();
    #endif
}

ConfCmd MeasurementConfWindow::getSettings()
{
    return settings;
}

void MeasurementConfWindow::onOkButton()
{
    hide();
    #ifdef QDEBUG_H
    qDebug()<<settings.printConfig();
    #endif
    emit newConf(settings);
}

void MeasurementConfWindow::onCancelButton()
{

}


