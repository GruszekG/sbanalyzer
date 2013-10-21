/********************************************************************************
** Form generated from reading UI file 'savemeasurementswindow.ui'
**
** Created: Wed 7. Aug 19:11:36 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEMEASUREMENTSWINDOW_H
#define UI_SAVEMEASUREMENTSWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_saveMeasurementsWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_4;
    QCustomPlot *accPlot;
    QCustomPlot *gyroPlot;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_6;
    QPushButton *startButton;
    QPushButton *cutFirst20Button;
    QVBoxLayout *verticalLayout_7;
    QPushButton *stopButton;
    QPushButton *cutLast20Button;
    QPushButton *pushButton;
    QPushButton *okGraphButton;
    QPushButton *terminalButton;
    QPushButton *quitSaveWindowButton;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QComboBox *skaterBox;
    QLabel *label;
    QComboBox *tricksBox;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *onSaveAsCSVflie;
    QHBoxLayout *horizontalLayout_4;
    QPlainTextEdit *CSVText;
    QPushButton *pushButton_3;
    QPushButton *backButton;
    QWidget *page_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *saveMeasurementsWindow)
    {
        if (saveMeasurementsWindow->objectName().isEmpty())
            saveMeasurementsWindow->setObjectName(QString::fromUtf8("saveMeasurementsWindow"));
        saveMeasurementsWindow->resize(652, 608);
        centralwidget = new QWidget(saveMeasurementsWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        verticalLayout_4 = new QVBoxLayout(page_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        accPlot = new QCustomPlot(page_3);
        accPlot->setObjectName(QString::fromUtf8("accPlot"));

        verticalLayout_4->addWidget(accPlot);

        gyroPlot = new QCustomPlot(page_3);
        gyroPlot->setObjectName(QString::fromUtf8("gyroPlot"));

        verticalLayout_4->addWidget(gyroPlot);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        startButton = new QPushButton(page_3);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        verticalLayout_6->addWidget(startButton);

        cutFirst20Button = new QPushButton(page_3);
        cutFirst20Button->setObjectName(QString::fromUtf8("cutFirst20Button"));

        verticalLayout_6->addWidget(cutFirst20Button);


        horizontalLayout->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        stopButton = new QPushButton(page_3);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        verticalLayout_7->addWidget(stopButton);

        cutLast20Button = new QPushButton(page_3);
        cutLast20Button->setObjectName(QString::fromUtf8("cutLast20Button"));

        verticalLayout_7->addWidget(cutLast20Button);


        horizontalLayout->addLayout(verticalLayout_7);


        verticalLayout_5->addLayout(horizontalLayout);

        pushButton = new QPushButton(page_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_5->addWidget(pushButton);

        okGraphButton = new QPushButton(page_3);
        okGraphButton->setObjectName(QString::fromUtf8("okGraphButton"));

        verticalLayout_5->addWidget(okGraphButton);

        terminalButton = new QPushButton(page_3);
        terminalButton->setObjectName(QString::fromUtf8("terminalButton"));

        verticalLayout_5->addWidget(terminalButton);

        quitSaveWindowButton = new QPushButton(page_3);
        quitSaveWindowButton->setObjectName(QString::fromUtf8("quitSaveWindowButton"));

        verticalLayout_5->addWidget(quitSaveWindowButton);


        verticalLayout_4->addLayout(verticalLayout_5);

        stackedWidget->addWidget(page_3);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        skaterBox = new QComboBox(page);
        skaterBox->setObjectName(QString::fromUtf8("skaterBox"));

        horizontalLayout_5->addWidget(skaterBox);

        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        tricksBox = new QComboBox(page);
        tricksBox->setObjectName(QString::fromUtf8("tricksBox"));

        horizontalLayout_5->addWidget(tricksBox);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        onSaveAsCSVflie = new QCheckBox(page);
        onSaveAsCSVflie->setObjectName(QString::fromUtf8("onSaveAsCSVflie"));

        horizontalLayout_3->addWidget(onSaveAsCSVflie);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        CSVText = new QPlainTextEdit(page);
        CSVText->setObjectName(QString::fromUtf8("CSVText"));

        horizontalLayout_4->addWidget(CSVText);


        verticalLayout->addLayout(horizontalLayout_4);

        pushButton_3 = new QPushButton(page);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        backButton = new QPushButton(page);
        backButton->setObjectName(QString::fromUtf8("backButton"));

        verticalLayout->addWidget(backButton);


        verticalLayout_2->addLayout(verticalLayout);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        verticalLayout_3->addWidget(stackedWidget);

        saveMeasurementsWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(saveMeasurementsWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        saveMeasurementsWindow->setStatusBar(statusbar);

        retranslateUi(saveMeasurementsWindow);
        QObject::connect(quitSaveWindowButton, SIGNAL(clicked()), saveMeasurementsWindow, SLOT(deleteLater()));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(saveMeasurementsWindow);
    } // setupUi

    void retranslateUi(QMainWindow *saveMeasurementsWindow)
    {
        saveMeasurementsWindow->setWindowTitle(QApplication::translate("saveMeasurementsWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("saveMeasurementsWindow", "start", 0, QApplication::UnicodeUTF8));
        cutFirst20Button->setText(QApplication::translate("saveMeasurementsWindow", "cut first 20 samples", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("saveMeasurementsWindow", "stop", 0, QApplication::UnicodeUTF8));
        cutLast20Button->setText(QApplication::translate("saveMeasurementsWindow", "cut last 20 samples", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("saveMeasurementsWindow", "clear", 0, QApplication::UnicodeUTF8));
        okGraphButton->setText(QApplication::translate("saveMeasurementsWindow", "OK", 0, QApplication::UnicodeUTF8));
        terminalButton->setText(QApplication::translate("saveMeasurementsWindow", "terminal", 0, QApplication::UnicodeUTF8));
        quitSaveWindowButton->setText(QApplication::translate("saveMeasurementsWindow", "quit", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("saveMeasurementsWindow", "skater:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("saveMeasurementsWindow", "trick:", 0, QApplication::UnicodeUTF8));
        onSaveAsCSVflie->setText(QApplication::translate("saveMeasurementsWindow", "save as .csv flie", 0, QApplication::UnicodeUTF8));
        CSVText->setPlainText(QString());
        pushButton_3->setText(QApplication::translate("saveMeasurementsWindow", "OK", 0, QApplication::UnicodeUTF8));
        backButton->setText(QApplication::translate("saveMeasurementsWindow", "back", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class saveMeasurementsWindow: public Ui_saveMeasurementsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEMEASUREMENTSWINDOW_H
