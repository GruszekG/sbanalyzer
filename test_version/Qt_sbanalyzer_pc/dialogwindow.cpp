#include "dialogwindow.h"
#include "ui_dialogwindow.h"
#include <iostream>
#include <QDebug>

DialogWindow::DialogWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DialogWindow),
    command(0),
    measurement(false),
    configurationInProgress(false)

{
    //-------Ui settings---------------------------//
    ui->setupUi(this);
    setWindowTitle("Terminal");

    confWind = new MeasurementConfWindow(this);

    ui->portBox->setEditable(true);
    ui->portBox->addItems(QStringList()<<QLatin1String("COM6")<<QLatin1String("COM2")<<QLatin1String("COM3")<<QLatin1String("COM4")<<QLatin1String("COM1"));

    ui->baudRateBox->addItem(QLatin1String("1200"), BAUD1200);
    ui->baudRateBox->addItem(QLatin1String("2400"), BAUD2400);
    ui->baudRateBox->addItem(QLatin1String("4800"), BAUD4800);
    ui->baudRateBox->addItem(QLatin1String("9600"), BAUD9600);
    ui->baudRateBox->addItem(QLatin1String("19200"), BAUD19200);
    ui->baudRateBox->addItem(QLatin1String("256000"), BAUD256000);
    ui->baudRateBox->addItem(QLatin1String("921600"), BAUD921600);
    ui->baudRateBox->setCurrentIndex(6);

    PortSettings settings = {BAUD921600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};
    port = new QextSerialPort(ui->portBox->currentText(), settings, QextSerialPort::Polling);// create port

    //---------------------------------------------------//
    //--------------triger settings-----------------------//
    timerMes = new QTimer(this);
    timerMes->setInterval(50);
    timerMes->stop();

    timerCom = new QTimer(this);
    timerCom->setInterval(100);
    timerCom->stop();

 //   confWind->show();

//    command = 0;
//    measurement = false;
    /*---------------------------------------------------------------------------------*/
    /*------------------CONNECTS  SETTINGS---------------------------------------------*/
    /*---------------------------------------------------------------------------------*/

    //port settings
    connect(ui->portBox, SIGNAL(currentIndexChanged(QString)), SLOT(onPortNameChanged(QString)));
    connect(ui->baudRateBox, SIGNAL(currentIndexChanged(int)), SLOT(onBaudRateChanged(int)));
    connect(ui->openCloseButton, SIGNAL(clicked()), SLOT(onOpenCloseButtonClicked()));
    //sending window
    connect(ui->sendEdit, SIGNAL(blockCountChanged(int)),SLOT(sendTextEdit()));
    //buttons
    connect(ui->closeButton, SIGNAL(clicked()), SLOT(closeWindow()));
    connect(ui->clearTerminalButton, SIGNAL(clicked()), SLOT(clearTerminal()));
    connect(ui->startButton, SIGNAL(clicked()),SLOT(onStartButton()));
    connect(ui->stopButton, SIGNAL(clicked()), SLOT(onStopButton()));
    //timers
    connect(timerMes, SIGNAL(timeout()), SLOT(prepareDataMeasurement()));
    connect(timerCom, SIGNAL(timeout()), SLOT(onCom()));

    connect(confWind, SIGNAL(newConf(ConfCmd)), SLOT(onSendConfCommand(ConfCmd)));

    ui->led->turnOff();

    ui->recvEdit->ensureCursorVisible();
}


DialogWindow::~DialogWindow()
{
    delete ui;
    delete timerMes;
    delete timerCom;
    delete confWind;
    //delete dane;

    qDebug("ooooooooooffffffffffffffffffffff");
}

void DialogWindow::closeWindow()
{
    hide();
}

bool DialogWindow::getMeasurementState()
{
    return measurement;
}

void DialogWindow::setTimerMes(int interval)
{
    timerMes->setInterval(interval);
    timerMes->stop();
}

/*---------------------------------------------------------------------------------*/
/*------------------PORT SETTINGS--------------------------------------------------*/
/*---------------------------------------------------------------------------------*/

void DialogWindow::onPortNameChanged(const QString & /*name*/)
{
    if (port->isOpen()) {
        port->close();
        ui->led->turnOff();
    }
}

void DialogWindow::onBaudRateChanged(int idx)
{
    port->setBaudRate((BaudRateType)ui->baudRateBox->itemData(idx).toInt());
    qDebug("baud changed");
}

void DialogWindow::onOpenCloseButtonClicked()
{
    if (!port->isOpen()) {
        port->setPortName(ui->portBox->currentText());
        port->open(QIODevice::ReadWrite);
        command = 0x03;
        timerCom->setInterval(100);
        timerCom->start();
    }
    else {
        command = 0x03;
        port->write(&command);
        command = 0x00;
        measurement = false;
        port->close();
    }

    if (port->isOpen()) {
        if (port->queryMode() == QextSerialPort::Polling)
        ui->led->turnOn();
        ui->recvEdit->insertPlainText("PC:> The measurement system has been connected.\n");
    }
    else {
       // timer->stop();
        ui->led->turnOff();
        ui->recvEdit->insertPlainText("PC:> The measurement system has been disconnected.\n");
    }
}

/*---------------------------------------------------------------------------------*/
/*------------------TERMINAL  SLOTS-------------------------------------------------*/
/*---------------------------------------------------------------------------------*/

/*-----------BUTTONS----------------*/
void DialogWindow::clearTerminal()
{
    ui->recvEdit->clear();
}

void DialogWindow::onStartButton()
{
    if(measurement == false)
    {
        if(port->isOpen())
        {
            ui->recvEdit->insertPlainText("YOU:> start\n");
            command = 0x02;
            timerCom->setInterval(100);
            timerCom->start();
         }else ui->recvEdit->insertPlainText("PC:> The measurement system is not connected.\n");
    }
}

void DialogWindow::onStopButton()
{
    if(port->isOpen())
    {
        ui->recvEdit->insertPlainText("YOU:> stop\n");
        command = 0x03;
        timerCom->setInterval(100);
        timerCom->start();
    }else ui->recvEdit->insertPlainText("PC:> The measurement system is not connected.\n");
}



/*-----------SEND AND RECIV TEXT EDIT----------------*/

void DialogWindow::sendTextEdit()
{
    QString bufor;
    port->flush();
    if(!ui->sendEdit->toPlainText().isEmpty())
    {
        bufor = ui->sendEdit->toPlainText();
        ui->recvEdit->insertPlainText(QString("YOU:>") + bufor);
        if(port->isOpen())
        {
            if(bufor == QString("start\n"))
            {
                onStartCommand();
            }else
            if(bufor == QString("info\n"))
            {
                onInfoCommand();
            }else
            if(bufor == QString("conf\n"))
            {
                confWind->show();
            }
            else
            {
                ui->recvEdit->insertPlainText("PC:> Unknown command!\n");
            }
             ui->sendEdit->clear();
        }
        else
        {
            ui->recvEdit->insertPlainText("PC:> The measurement system is not connected.\n");
            ui->sendEdit->clear();
        }
    }
    QTextCursor *c = &(ui->recvEdit->textCursor());
    c->movePosition(QTextCursor::End);
    ui->recvEdit->setTextCursor(*c);
}

void DialogWindow::onSendConfCommand(ConfCmd _cmd)
{
    port->flush();
    QByteArray bufor = _cmd.getConfCmdToBuf();

    qDebug()<<"CMD:"<<(unsigned char)bufor.at(0);
    qDebug()<<"buf[1]:"<<(unsigned char)bufor.at(1);
    qDebug()<<"CKS: "<<(unsigned char)bufor.at(7);
    qDebug()<<"LAST:"<<(unsigned char)bufor.at(8);
    qDebug()<<"SEND CONFIGURATION";

    qDebug()<<"WRITE BYTES: "<<(unsigned int)port->write(bufor.constData());
     qDebug()<<"DATA WRITE";
    QByteArray dane;
    port->write(bufor);
    char _end;
    do
    {
        if(port->getChar(&_end) == true)
           dane.append(_end);
    }while(_end != 0x0d);
    ui->recvEdit->insertPlainText(QString("SB:>") + QString(dane));
}

void DialogWindow::onStartCommand()
{
    MeasureCmd MCmd;
    MCmd.loadMeasureCmd(6);
    QByteArray bytes = MCmd.getMeasureCmd();
    port->write(bytes.constData());
    QByteArray dane;
    char _end;
    do
    {
        if(port->getChar(&_end) == true)
           dane.append(_end);
    }while(_end != 0x0d);
    ui->recvEdit->insertPlainText(QString("SB:>") + QString(dane));
}

/*---------------------------------------------------------------------------------*/
/*------------------SENDING COMMAND SLOTS------------------------------------------*/
/*---------------------------------------------------------------------------------*/

void DialogWindow::onCom()
{
}

/*---------------------------------------------------------------------------------*/
/*------------------MEASUREMENTS SLOTS---------------------------------------------*/
/*---------------------------------------------------------------------------------*/

void DialogWindow::prepareDataMeasurement()
{
    char startByte = 'S';
    bool startByteFound = false;

        QByteArray array = port->readAll();

        if(array.length()>=(2*frameLenght))
        {
            while(!startByteFound)
            {
                while(!array.startsWith(startByte))
                {
                    array.remove(0,1);
                  //  qDebug()<<"szukam pocz¹tku ramki";
                }
                if( array.at(frameLenght) != startByte ) // char at 0 is not a start byte
                {
                    array.remove(0,1); // remove it
                  //  qDebug()<<"nie ma nastêpnego pocz¹tku ramki";
                }
                else
                {
                    startByteFound = true;
                }
            }

             emit dataAvaible(array);
        }

}

void DialogWindow::onInfoCommand()
{
    QByteArray cmdToSend;

    port->readAll();
    cmdToSend.append(Info_Cmd);
    cmdToSend.append(0x0d);
    port->write(cmdToSend.constData());

    QByteArray dane;
    char _end;
    do{
        if(port->getChar(&_end) == true)
           dane.append(_end);
    }while(_end != 0x0d);
    if(QString(dane)!=QString("NACK\r"))
    {
        InfoCmd cmd;
        cmd.loadCmd(dane.constData());
        ui->recvEdit->insertPlainText(QString("SB:>") + cmd.printCmd());
    }else
    {
        ui->recvEdit->insertPlainText(QString("SB:>") + QString(dane));
    }

}

