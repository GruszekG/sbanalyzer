#include "dialogwindow.h"
#include "ui_dialogwindow.h"
#include <iostream>
#include <QDebug>

DialogWindow::DialogWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DialogWindow),
    command(0),
    measurement(false),
    configurationInProgress(false),
    count(0),
    measTime(5)

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
    timerCom->setInterval(10000);
    timerCom->stop();

    timerInit = new QTimer(this);
    timerInit->setInterval(1000);
    timerInit->stop();

    timerGetInfo = new QTimer(this);
    timerGetInfo->setInterval(1000);
    timerGetInfo->stop();

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
   // connect(ui->startButton, SIGNAL(clicked()),SLOT(onStartButton()));
   // connect(ui->stopButton, SIGNAL(clicked()), SLOT(onStopButton()));
    //timers
    connect(timerMes, SIGNAL(timeout()), SLOT(prepareDataMeasurement()));
    connect(timerCom, SIGNAL(timeout()), SLOT(onCom()));
    connect(timerInit, SIGNAL(timeout()), SLOT(initializationHelloRepeater()));
    connect(timerGetInfo, SIGNAL(timeout()), SLOT(onTimerGetInfo()));

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

void DialogWindow::scrollDown()
{
    QTextCursor *c = &(ui->recvEdit->textCursor());
    c->movePosition(QTextCursor::End);
    ui->recvEdit->setTextCursor(*c);
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
void DialogWindow::onTimerGetInfo()
{
    onInfoCommand();
    qDebug("get info");
    timerGetInfo->stop();
}

void DialogWindow::onOpenCloseButtonClicked()
{
    if (!port->isOpen()) {
        port->setPortName(ui->portBox->currentText());
        port->open(QIODevice::ReadWrite);
      //  command = 0x03;
     //   timerCom->setInterval(100);
     //   timerCom->start();
    }
    else {
        command = 0x03;
      //  port->write(&command);
     ////   command = 0x00;
      //  measurement = false;
        port->close();
    }

    if (port->isOpen()) {
        if (port->queryMode() == QextSerialPort::Polling)
        ui->led->turnOn();
        ui->recvEdit->insertPlainText("PC:> The measurement system has been connected.\n");
        ui->recvEdit->insertPlainText("PC:> Checking connection ....\n");
        timerInit->start();
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

void DialogWindow::initializationHelloRepeater()
{

    QByteArray dane;
    unsigned int _timeOut = 200;

    HelloCmd _cmd;
    port->write(_cmd.getHelloCmd());

    char _end;
    do
    {
        if(port->getChar(&_end) == true)
           dane.append(_end);
    }while(_end != 0x0d);
    port->readAll();
    port->flush();
    _timeOut --;

    port->readAll();
    port->flush();

    if((QString(dane)==QString("ACK\r")))
    {
        ui->recvEdit->insertPlainText(QString("SB:> Hello MAN. I'm ready, so let's get started. ;)\r\n"));
        ui->recvEdit->insertPlainText(QString("PC:> Connection OK\n"));
        timerInit->stop();
        timerGetInfo->start();
    }
    scrollDown();
}



/*-----------SEND AND RECIV TEXT EDIT----------------*/

void DialogWindow::sendTextEdit()
{
    QString bufor;
    port->flush();
    if(!ui->sendEdit->toPlainText().isEmpty())
    {
        bufor = ui->sendEdit->toPlainText();
        ui->recvEdit->insertPlainText(QString("YOU:> ") + bufor);
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
            }else
            if(bufor == QString("hello\n"))
            {
                onHelloCommand();
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
    scrollDown();
}

void DialogWindow::onSendConfCommand(ConfCmd _cmd)
{
    port->flush();
    QByteArray bufor = _cmd.getConfCmdToBuf();

    qDebug()<<"buf[0]"<<(unsigned char)bufor.at(0)<<"   ~buf[0]"<<~(unsigned char)bufor.at(0);
    qDebug()<<"buf[1]"<<(unsigned char)bufor.at(1)<<"   ~buf[1]"<<~(unsigned char)bufor.at(1);
    qDebug()<<"buf[2]"<<(unsigned char)bufor.at(2)<<"   ~buf[2]"<<~(unsigned char)bufor.at(2);
    qDebug()<<"buf[3]"<<(unsigned char)bufor.at(3)<<"   ~buf[3]"<<~(unsigned char)bufor.at(3);
    qDebug()<<"buf[4]"<<(unsigned char)bufor.at(4)<<"   ~buf[4]"<<~(unsigned char)bufor.at(4);
    qDebug()<<"buf[5]"<<(unsigned char)bufor.at(5)<<"   ~buf[5]"<<~(unsigned char)bufor.at(5);
    qDebug()<<"buf[6]"<<(unsigned char)bufor.at(6)<<"   ~buf[6]"<<~(unsigned char)bufor.at(6);

    measTime = _cmd.getMeasurementTime();

    QByteArray dane;
    port->write(bufor);
    char _end;
    do
    {
        if(port->getChar(&_end) == true)
           dane.append(_end);
    }while(_end != 0x0d);
    ui->recvEdit->insertPlainText(QString("SB:> ") + QString(dane));
}

void DialogWindow::onStartCommand()
{
    MeasureCmd MCmd;
    MCmd.loadMeasureCmd(6);
    QByteArray bytes = MCmd.getMeasureCmd();
    port->readAll();
    port->flush();
    port->write(bytes.constData());
    QByteArray dane;
    char _end;
    do
    {
        if(port->getChar(&_end) == true)
           dane.append(_end);
    }while(_end != 0x0d);
    ui->recvEdit->insertPlainText(QString("SB:> ") + QString(dane));
    port->readAll();
    port->flush();
    if(QString(dane) == QString("ACK\r"))
    {
        timerCom->setInterval(measTime* 1000 + 3000);
        timerCom->start();
        timerMes->setInterval(50);
        timerMes->start();
        ui->recvEdit->insertPlainText("PC:> Measuring");
        qDebug()<<"TIME "<<measTime* 1000 + 3000;
        ui->sendEdit->setEnabled(false);
    }
}

/*---------------------------------------------------------------------------------*/
/*------------------SENDING COMMAND SLOTS------------------------------------------*/
/*---------------------------------------------------------------------------------*/

void DialogWindow::onCom()
{
    qDebug()<<"TIMER COM";
    timerMes->stop();
    timerCom->stop();
    ui->recvEdit->insertPlainText(QString("\r\nPC:> End of measurement.\r\n"));
    ui->sendEdit->setEnabled(true);
    count = 0;
    scrollDown();
}

/*---------------------------------------------------------------------------------*/
/*------------------MEASUREMENTS SLOTS---------------------------------------------*/
/*---------------------------------------------------------------------------------*/

void DialogWindow::prepareDataMeasurement()
{
    char startByte = 'S';
    bool startByteFound = false;
   // qDebug()<<"TIMER MEAS";

        QByteArray array = port->readAll();

        if(array.length()>=(2*frameLenght))
        {
            while(!startByteFound)
            {
                while(!array.startsWith(startByte))
                {
                    array.remove(0,1);
                   // qDebug()<<"szukam pocz¹tku ramki";
                }
                if( array.at(frameLenght) != startByte ) // char at 0 is not a start byte
                {
                    array.remove(0,1); // remove it
                  // qDebug()<<"nie ma nastêpnego pocz¹tku ramki";
                }
                else
                {
                    startByteFound = true;
                }
            }

//            int count = array.length()/16;

//            for(int i = 0; i < count; i++)
//            {
//                ui->recvEdit->insertPlainText(QString(" ax: ") + QString::number(array.at(i*16+1)*0x100+array.at(i*16+0)));
//                ui->recvEdit->insertPlainText(QString(" ay: ") + QString::number(array.at(i*16+3)*0x100+array.at(i*16+2)));
//                ui->recvEdit->insertPlainText(QString(" az: ") + QString::number(array.at(i*16+5)*0x100+array.at(i*16+4)));
//                ui->recvEdit->insertPlainText(QString(" gx: ") + QString::number(array.at(i*16+6)*0x100+array.at(i*16+6)));
//                ui->recvEdit->insertPlainText(QString(" gy: ") + QString::number(array.at(i*16+9)*0x100+array.at(i*16+8)));
//                ui->recvEdit->insertPlainText(QString(" gz: ") + QString::number(array.at(i*16+11)*0x100+array.at(i*16+10)));
//                ui->recvEdit->insertPlainText(QString("\r\n"));
//            }

             count += array.length();
             if(count > 1000)
             {
                 count = 0;
                 ui->recvEdit->insertPlainText(" .");
             }
             emit dataAvaible(array);
        }


}

void DialogWindow::onInfoCommand()
{
    InfoCmd _cmd;

    port->readAll();
    port->write(_cmd.getInfoCmdToBuf());

    QByteArray dane;
    char _end;
    do{
        if(port->getChar(&_end) == true)
           dane.append(_end);
    }while(_end != 0x0d);
    qDebug()<<"RECEIVE ANSWER";
    if(QString(dane)!=QString("NACK\r"))
    {
        InfoCmd cmd;
        cmd.loadCmd((const unsigned char*)dane.constData());
        ui->recvEdit->insertPlainText(QString("SB:> ") + cmd.printCmd());
    }else
    {
        ui->recvEdit->insertPlainText(QString("SB:> ") + QString(dane));
    }
    scrollDown();

}

void DialogWindow::onHelloCommand()
{
    QByteArray dane;
    unsigned int _timeOut = 200;

    HelloCmd _cmd;
    port->write(_cmd.getHelloCmd());

    char _end;
    do
    {
        if(port->getChar(&_end) == true)
           dane.append(_end);
    }while(_end != 0x0d);
    port->readAll();
    port->flush();
    _timeOut --;

    port->readAll();
    port->flush();

    if((QString(dane)==QString("ACK\r")))
        ui->recvEdit->insertPlainText(QString("SB:> Hello MAN. I'm ready, so let's get started. ;)\r\n"));
    else
        ui->recvEdit->insertPlainText(QString("PC:> Measurement board do not response. Reset measurement board, or wait a 10 seconds and repeat hello command\r\n"));
}

