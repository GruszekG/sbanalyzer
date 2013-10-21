/********************************************************************************
** Form generated from reading UI file 'instvalueswindow.ui'
**
** Created: Wed 7. Aug 19:11:36 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTVALUESWINDOW_H
#define UI_INSTVALUESWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_instValuesWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelAcc;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QLCDNumber *axLCD;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QLCDNumber *ayLCD;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QLCDNumber *azLCD;
    QLabel *label;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_5;
    QLCDNumber *gxLCD;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_6;
    QLCDNumber *gyLCD;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_7;
    QLCDNumber *gzLCD;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *instValuesWindow)
    {
        if (instValuesWindow->objectName().isEmpty())
            instValuesWindow->setObjectName(QString::fromUtf8("instValuesWindow"));
        instValuesWindow->resize(480, 378);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        instValuesWindow->setFont(font);
        centralwidget = new QWidget(instValuesWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelAcc = new QLabel(centralwidget);
        labelAcc->setObjectName(QString::fromUtf8("labelAcc"));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setUnderline(true);
        font1.setWeight(75);
        labelAcc->setFont(font1);
        labelAcc->setTextFormat(Qt::RichText);
        labelAcc->setScaledContents(true);
        labelAcc->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelAcc);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_2);

        axLCD = new QLCDNumber(centralwidget);
        axLCD->setObjectName(QString::fromUtf8("axLCD"));

        verticalLayout_4->addWidget(axLCD);


        horizontalLayout_7->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_3);

        ayLCD = new QLCDNumber(centralwidget);
        ayLCD->setObjectName(QString::fromUtf8("ayLCD"));

        verticalLayout_5->addWidget(ayLCD);


        horizontalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_4);

        azLCD = new QLCDNumber(centralwidget);
        azLCD->setObjectName(QString::fromUtf8("azLCD"));

        verticalLayout_3->addWidget(azLCD);


        horizontalLayout_7->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout_7);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_5);

        gxLCD = new QLCDNumber(centralwidget);
        gxLCD->setObjectName(QString::fromUtf8("gxLCD"));

        verticalLayout_8->addWidget(gxLCD);


        horizontalLayout_8->addLayout(verticalLayout_8);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_6);

        gyLCD = new QLCDNumber(centralwidget);
        gyLCD->setObjectName(QString::fromUtf8("gyLCD"));

        verticalLayout_7->addWidget(gyLCD);


        horizontalLayout_8->addLayout(verticalLayout_7);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_7);

        gzLCD = new QLCDNumber(centralwidget);
        gzLCD->setObjectName(QString::fromUtf8("gzLCD"));
        QFont font2;
        font2.setPointSize(14);
        gzLCD->setFont(font2);

        verticalLayout_6->addWidget(gzLCD);


        horizontalLayout_8->addLayout(verticalLayout_6);


        verticalLayout->addLayout(horizontalLayout_8);

        instValuesWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(instValuesWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        instValuesWindow->setStatusBar(statusbar);

        retranslateUi(instValuesWindow);

        QMetaObject::connectSlotsByName(instValuesWindow);
    } // setupUi

    void retranslateUi(QMainWindow *instValuesWindow)
    {
        instValuesWindow->setWindowTitle(QApplication::translate("instValuesWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        labelAcc->setText(QApplication::translate("instValuesWindow", "Acceleration LIS3DH", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("instValuesWindow", "ax [mg]:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("instValuesWindow", "ay [mg]:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("instValuesWindow", "az [mg]:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("instValuesWindow", "Angular velocity L3G4200D", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("instValuesWindow", "wx [dps]:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("instValuesWindow", "wy [dps]:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("instValuesWindow", "wz [dps]:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class instValuesWindow: public Ui_instValuesWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTVALUESWINDOW_H
