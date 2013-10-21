#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qskater.h"
#include <QtSql/QtSql>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //-------Ui settings---------------------------//
    ui->setupUi(this);

    setWindowTitle("SkateboardAnalyzer v0.5 measuring");
    setWindowIcon(QIcon(":/skate"));

    //--------------SETS VARIABLES--------------//
   // aboutSkateAn = new aboutProjectWindow(this);
   // saveMeasureWindow = new saveMeasurementsWindow(this);
   // realTimePlotWindow = new RealTimePlotWindow(this);
    //visWindow = new VisualizationWindow(this);

    delay = new QTimer(this);
    delay->start(1000);

    getSkatersFromFile(&skaters);

    //---------------------------------------------------//
    //-----------------CONNECTS--------------------------//
    //---------------------------------------------------//
    //buttons
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pushButtonRealTimeGraph, SIGNAL(clicked()), SLOT(onRealTimeGraphButton()));
    connect(ui->skatersButton, SIGNAL(clicked()), SLOT(onSkatersButton()));
    connect(ui->MainMenuButton, SIGNAL(clicked()), SLOT(onMainMenuButton()));
    connect(delay, SIGNAL(timeout()), SLOT(hideWelcomewWindow()));
    connect(ui->aboutSkateButton, SIGNAL(clicked()), SLOT(onAboutSkateButton()));
    connect(ui->trickMeasurementButton, SIGNAL(clicked()), SLOT(onTrickMeasuerementButton()));

    connect(ui->addSkaterButton, SIGNAL(clicked()), SLOT(onAddSkaterButton()));
    connect(ui->removeSkaterButton, SIGNAL(clicked()), SLOT(onRemoveSkaterButton()));
    connect(ui->saveSkatersButton, SIGNAL(clicked()), SLOT(onSaveSkatersButton()));
    connect(ui->visualizationButton, SIGNAL(clicked()), SLOT(onVisualizationButton()));

     ui->stackedWidget->setCurrentIndex(0);//first page of mainwindow
}

MainWindow::~MainWindow()
{
    delete ui;
  //  delete file;
    delete delay;
  //  delete saveMeasureWindow;
}

void MainWindow::hideWelcomewWindow()
{
    ui->stackedWidget->setCurrentIndex(1);
    delay->stop();
    //disconnect(delay,SLOT(hideWelcomewWindow()));
}

void MainWindow::onRealTimeGraphButton()
{
    //ui->stackedWidget->setCurrentIndex(2);
    realTimePlotWindow = new RealTimePlotWindow(this);
    realTimePlotWindow->show();
}

void MainWindow::onMainMenuButton()
{
   ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::onTrickMeasuerementButton()
{
    qDebug()<<"open window";
    saveMeasureWindow = new saveMeasurementsWindow(this);
    qDebug()<<"open window";
    saveMeasureWindow->getSkaters(skaters);
    qDebug()<<"open window";
    saveMeasureWindow->startMeasurementWindow();
    qDebug()<<"open window";
    saveMeasureWindow->show();
}

void MainWindow::onVisualizationButton()
{
    visWindow = new VisualizationWindow(this);
    visWindow->show();
}

//-------------------------------BUTTONS----------------------------------//

void MainWindow::onAboutSkateButton()
{
    aboutSkateAn = new aboutProjectWindow(this);
    aboutSkateAn->show();
}

void MainWindow::onSkatersButton()
{

    getSkatersFromFile(&skaters);
    qDebug("skaterButton");

    ui->stackedWidget->setCurrentIndex(2);

    fillTable(skaters);
}
//-------------------SKATERS INFO------------------------------------//
void MainWindow::getSkatersFromFile(QVector<QSkater> *skat)
{
    char sign = '#';
    file = new QFile("skaters.txt");
    file->open(file->ReadOnly);
    file->getChar(&sign);

    skat->clear();

    QByteArray data;

    while(sign != '#')
    {
        file->getChar(&sign);
    }

    file->read(3);
    do
    {
        file->getChar(&sign);
        do
        {
            data.append(sign);
            file->getChar(&sign);
        }while(sign!='\n');

        file->getChar(&sign);

        QSkater skater(data);
        skat->append(skater);
        data.clear();
    }while(sign !='#');

    file->close();
    delete file;

}

void MainWindow::fillTable(QVector<QSkater> skat)
{
    ui->skatersTable->setRowCount(skat.size());
    //ui->skatersTable->setVerticalHeader();
    for(int i = 0; i<skat.size(); i++)
    {
        QTableWidgetItem **items = new QTableWidgetItem*[7];
       for (int j = 0; j<7;j++) items[j] = new QTableWidgetItem();

       items[0]->setText(skat[i].getName());
       ui->skatersTable->setItem(i,0,items[0]);
       items[1]->setText(skat[i].getFootStance());
       ui->skatersTable->setItem(i,1,items[1]);
       items[2]->setText(skat[i].getCity());
       ui->skatersTable->setItem(i,4,items[2]);
       items[3]->setText(skat[i].getEmail());
       ui->skatersTable->setItem(i,5,items[3]);
       items[4]->setText(skat[i].getInfo());
       ui->skatersTable->setItem(i,6,items[4]);

       items[5]->setText(skat[i].getTraining());
       ui->skatersTable->setItem(i,2,items[5]);
       items[6]->setText(skat[i].getAge());
       ui->skatersTable->setItem(i,3,items[6]);
    }
}
void MainWindow::putSkatersToFile(QVector<QSkater> *skat)
{
    file = new QFile("skaters.txt");
    file->open(file->WriteOnly);
    file->write(QString("SKATEBOARD ANALYZER SKATERS DATABASE\n#\n").toAscii());
    int n = skat->size();
    for(int i = 0; i<n ;i++)
    {
        QString *line;
        line = new QString();
        //line = "dupa"+"koniec dupy";
        //line.append("line"+i+"dupa");
        line->append(">" + QString::number(i+1) + ";"
                    + skaters[i].getName()+ ";"
                    + skaters[i].getFootStance()+ ";"
                    + skaters[i].getCity()+ ";"
                    + skaters[i].getEmail()+ ";"
                    + skaters[i].getInfo()+ ";"
                    + skaters[i].getTraining()+ ";"
                    + skaters[i].getAge()+ ";");
        //qDebug()<<QString(">%1;%2").arg(i,QString(skaters.at(0).getName()));
        //qDebug()<<QString::number(i+1)<<skaters[i].getName();
        qDebug()<<line;
        //line<<">"<<(i+1)<<";"<<skaters[i].getName()<<";";
        file->write(line->toAscii());
        file->write(QString('\n').toAscii());
        delete line;
    }
    file->write(QString("#").toAscii());

   file->close();
    delete file;

}

void MainWindow::getSkatersFromTable(QVector<QSkater> *skat)
{
    int row = ui->skatersTable->rowCount();
    skat->clear();
    qDebug()<<"skater";
    //bool *ok;
    for(int i =0; i<row;i++)
    {
        QSkater tempSkater;
//        QTableWidgetItem temp;
//        temp = *(ui->skatersTable->item(i,0));
        tempSkater.setNumber(i+1);
        qDebug()<<"skater";
        if(ui->skatersTable->item(i,0)!=0)
            tempSkater.setName((ui->skatersTable->item(i,0))->text());
        else tempSkater.setName("-");
        if(ui->skatersTable->item(i,1)!=0)
            tempSkater.setFootStance((ui->skatersTable->item(i,1))->text());
        else tempSkater.setFootStance("-");
        qDebug()<<"dupa";
        if(ui->skatersTable->item(i,2)!=0)
            tempSkater.setTraining(ui->skatersTable->item(i,2)->text());
        else tempSkater.setTraining("-");
        if(ui->skatersTable->item(i,3)!=0)
            tempSkater.setAge(ui->skatersTable->item(i,3)->text());
        else tempSkater.setAge("-");
        if(ui->skatersTable->item(i,4)!=0)
            tempSkater.setCity((ui->skatersTable->item(i,4))->text());
        else tempSkater.setCity("-");
        if(ui->skatersTable->item(i,5)!=0)
            tempSkater.setEmail((ui->skatersTable->item(i,5))->text());
        else tempSkater.setEmail("-");
        if(ui->skatersTable->item(i,6)!=0)
            tempSkater.setInfo((ui->skatersTable->item(i,6))->text());
        else tempSkater.setInfo("-");
        qDebug()<<"zapis";
        skat->append(tempSkater);
        qDebug()<<"skater";
    }
}

void MainWindow::onSaveSkatersButton()
{
    getSkatersFromTable(&skaters);
    putSkatersToFile(&skaters);
}

void MainWindow::onAddSkaterButton()
{
    //skaters.append(QSkater());
    //fillTable(skaters);
    ui->skatersTable->setRowCount(ui->skatersTable->rowCount()+1);

}

void MainWindow::onRemoveSkaterButton()
{
   uint row = 0;
   row = ui->skatersTable->currentRow();
   if(row!=-1)
   {
       //skaters.remove(row,1);
       //fillTable(skaters);
       ui->skatersTable->removeRow(row);
   }
  // qDebug()<<row;
}

