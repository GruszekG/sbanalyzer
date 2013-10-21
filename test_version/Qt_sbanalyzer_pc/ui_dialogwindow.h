/********************************************************************************
** Form generated from reading UI file 'dialogwindow.ui'
**
** Created: Tue 27. Aug 21:29:27 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGWINDOW_H
#define UI_DIALOGWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "hled.h"

QT_BEGIN_NAMESPACE

class Ui_DialogWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QPlainTextEdit *recvEdit;
    QPlainTextEdit *sendEdit;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_2;
    QComboBox *baudRateBox;
    QComboBox *portBox;
    HLed *led;
    QPushButton *openCloseButton;
    QLabel *label_4;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *clearTerminalButton;
    QSpacerItem *verticalSpacer;
    QPushButton *closeButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DialogWindow)
    {
        if (DialogWindow->objectName().isEmpty())
            DialogWindow->setObjectName(QString::fromUtf8("DialogWindow"));
        DialogWindow->resize(575, 305);
        centralwidget = new QWidget(DialogWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        recvEdit = new QPlainTextEdit(centralwidget);
        recvEdit->setObjectName(QString::fromUtf8("recvEdit"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(4, 255, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        QBrush brush3(QColor(240, 240, 240, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        recvEdit->setPalette(palette);
        QFont font;
        font.setStyleStrategy(QFont::PreferDefault);
        recvEdit->setFont(font);
        recvEdit->setMouseTracking(true);
        recvEdit->setContextMenuPolicy(Qt::NoContextMenu);
        recvEdit->setLayoutDirection(Qt::LeftToRight);
        recvEdit->setAutoFillBackground(true);
        recvEdit->setInputMethodHints(Qt::ImhNone);
        recvEdit->setFrameShape(QFrame::Box);
        recvEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        recvEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        recvEdit->setTabChangesFocus(true);
        recvEdit->setUndoRedoEnabled(false);
        recvEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        recvEdit->setReadOnly(true);
        recvEdit->setOverwriteMode(false);
        recvEdit->setMaximumBlockCount(800);
        recvEdit->setBackgroundVisible(false);
        recvEdit->setCenterOnScroll(false);

        verticalLayout_4->addWidget(recvEdit);

        sendEdit = new QPlainTextEdit(centralwidget);
        sendEdit->setObjectName(QString::fromUtf8("sendEdit"));
        sendEdit->setMaximumSize(QSize(16777215, 24));
        sendEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));

        verticalLayout_4->addWidget(sendEdit);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);

        verticalLayout_5->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_3->addWidget(label_5);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        baudRateBox = new QComboBox(centralwidget);
        baudRateBox->setObjectName(QString::fromUtf8("baudRateBox"));

        verticalLayout_2->addWidget(baudRateBox);

        portBox = new QComboBox(centralwidget);
        portBox->setObjectName(QString::fromUtf8("portBox"));

        verticalLayout_2->addWidget(portBox);

        led = new HLed(centralwidget);
        led->setObjectName(QString::fromUtf8("led"));

        verticalLayout_2->addWidget(led);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_5->addLayout(horizontalLayout);

        openCloseButton = new QPushButton(centralwidget);
        openCloseButton->setObjectName(QString::fromUtf8("openCloseButton"));
        openCloseButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_5->addWidget(openCloseButton);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        label_4->setFont(font2);

        verticalLayout_5->addWidget(label_4);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_5->addWidget(startButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_5->addWidget(stopButton);

        clearTerminalButton = new QPushButton(centralwidget);
        clearTerminalButton->setObjectName(QString::fromUtf8("clearTerminalButton"));
        clearTerminalButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_5->addWidget(clearTerminalButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        closeButton = new QPushButton(centralwidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_5->addWidget(closeButton);


        horizontalLayout_2->addLayout(verticalLayout_5);

        DialogWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(DialogWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DialogWindow->setStatusBar(statusbar);

        retranslateUi(DialogWindow);

        QMetaObject::connectSlotsByName(DialogWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DialogWindow)
    {
        DialogWindow->setWindowTitle(QApplication::translate("DialogWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DialogWindow", "Com settings:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogWindow", "BAUD RATE:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogWindow", "PORT:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("DialogWindow", "Open:", 0, QApplication::UnicodeUTF8));
        openCloseButton->setText(QApplication::translate("DialogWindow", "Open/Close", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("DialogWindow", "Terminal:", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("DialogWindow", "Start", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("DialogWindow", "Stop", 0, QApplication::UnicodeUTF8));
        clearTerminalButton->setText(QApplication::translate("DialogWindow", "Clear", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("DialogWindow", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogWindow: public Ui_DialogWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGWINDOW_H
