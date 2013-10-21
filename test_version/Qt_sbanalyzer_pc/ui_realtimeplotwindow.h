/********************************************************************************
** Form generated from reading UI file 'realtimeplotwindow.ui'
**
** Created: Wed 7. Aug 19:11:36 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALTIMEPLOTWINDOW_H
#define UI_REALTIMEPLOTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_RealTimePlotWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QCustomPlot *accPlot;
    QCustomPlot *gyroPlot;
    QHBoxLayout *horizontalLayout;
    QPushButton *startButton;
    QPushButton *stopButton;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *terminalButton;
    QPushButton *saveGraphButton;
    QPushButton *instantValuesButton;
    QPushButton *closeButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RealTimePlotWindow)
    {
        if (RealTimePlotWindow->objectName().isEmpty())
            RealTimePlotWindow->setObjectName(QString::fromUtf8("RealTimePlotWindow"));
        RealTimePlotWindow->resize(662, 474);
        centralwidget = new QWidget(RealTimePlotWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        accPlot = new QCustomPlot(centralwidget);
        accPlot->setObjectName(QString::fromUtf8("accPlot"));

        verticalLayout->addWidget(accPlot);

        gyroPlot = new QCustomPlot(centralwidget);
        gyroPlot->setObjectName(QString::fromUtf8("gyroPlot"));

        verticalLayout->addWidget(gyroPlot);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        horizontalLayout->addWidget(startButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        horizontalLayout->addWidget(stopButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        terminalButton = new QPushButton(centralwidget);
        terminalButton->setObjectName(QString::fromUtf8("terminalButton"));

        horizontalLayout_2->addWidget(terminalButton);

        saveGraphButton = new QPushButton(centralwidget);
        saveGraphButton->setObjectName(QString::fromUtf8("saveGraphButton"));

        horizontalLayout_2->addWidget(saveGraphButton);

        instantValuesButton = new QPushButton(centralwidget);
        instantValuesButton->setObjectName(QString::fromUtf8("instantValuesButton"));

        horizontalLayout_2->addWidget(instantValuesButton);


        verticalLayout->addLayout(horizontalLayout_2);

        closeButton = new QPushButton(centralwidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        verticalLayout->addWidget(closeButton);

        RealTimePlotWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(RealTimePlotWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        RealTimePlotWindow->setStatusBar(statusbar);

        retranslateUi(RealTimePlotWindow);
        QObject::connect(closeButton, SIGNAL(clicked()), RealTimePlotWindow, SLOT(deleteLater()));

        QMetaObject::connectSlotsByName(RealTimePlotWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RealTimePlotWindow)
    {
        RealTimePlotWindow->setWindowTitle(QApplication::translate("RealTimePlotWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("RealTimePlotWindow", "start", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("RealTimePlotWindow", "stop", 0, QApplication::UnicodeUTF8));
        terminalButton->setText(QApplication::translate("RealTimePlotWindow", "terminal", 0, QApplication::UnicodeUTF8));
        saveGraphButton->setText(QApplication::translate("RealTimePlotWindow", "save graph", 0, QApplication::UnicodeUTF8));
        instantValuesButton->setText(QApplication::translate("RealTimePlotWindow", "instantaneous values", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("RealTimePlotWindow", "close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RealTimePlotWindow: public Ui_RealTimePlotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALTIMEPLOTWINDOW_H
