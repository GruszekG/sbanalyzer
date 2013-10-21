/********************************************************************************
** Form generated from reading UI file 'aboutprojectwindow.ui'
**
** Created: Wed 7. Aug 19:11:36 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTPROJECTWINDOW_H
#define UI_ABOUTPROJECTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_aboutProjectWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFrame *line;
    QLabel *label_2;
    QFrame *line_2;
    QLabel *label_3;
    QFrame *line_3;
    QLabel *label_4;
    QFrame *line_4;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *aboutProjectWindow)
    {
        if (aboutProjectWindow->objectName().isEmpty())
            aboutProjectWindow->setObjectName(QString::fromUtf8("aboutProjectWindow"));
        aboutProjectWindow->resize(605, 417);
        centralwidget = new QWidget(aboutProjectWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QPalette palette;
        QBrush brush(QColor(170, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("Bauhaus 93"));
        font.setPointSize(40);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(10);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bauhaus 93"));
        font1.setPointSize(16);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        aboutProjectWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(aboutProjectWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        aboutProjectWindow->setStatusBar(statusbar);

        retranslateUi(aboutProjectWindow);

        QMetaObject::connectSlotsByName(aboutProjectWindow);
    } // setupUi

    void retranslateUi(QMainWindow *aboutProjectWindow)
    {
        aboutProjectWindow->setWindowTitle(QApplication::translate("aboutProjectWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("aboutProjectWindow", "SkateboardAnalyzer", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("aboutProjectWindow", "authors:\n"
"Grzegorz Gruszka\n"
"organization: MKN Synergia\n"
"Wroclaw University of Technology", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("aboutProjectWindow", "website: sbanalyzer.pl\n"
"contact: grzegorz@sbanalyzer.pl", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("aboutProjectWindow", "version: v0.5m\n"
"year: 2013", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class aboutProjectWindow: public Ui_aboutProjectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTPROJECTWINDOW_H
