/********************************************************************************
** Form generated from reading UI file 'savegraphwindow.ui'
**
** Created: Wed 7. Aug 19:11:36 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEGRAPHWINDOW_H
#define UI_SAVEGRAPHWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SaveGraphWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QFrame *line;
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *pdfCheckBox;
    QCheckBox *pngCheckBox;
    QCheckBox *bmpCheckBox;
    QCheckBox *jpgCheckBox;
    QPushButton *saveGraphButton;
    QPushButton *cancelButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SaveGraphWindow)
    {
        if (SaveGraphWindow->objectName().isEmpty())
            SaveGraphWindow->setObjectName(QString::fromUtf8("SaveGraphWindow"));
        SaveGraphWindow->resize(246, 280);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/skate.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        SaveGraphWindow->setWindowIcon(icon);
        centralwidget = new QWidget(SaveGraphWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("Bauhaus 93"));
        font.setPointSize(14);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(7);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        pdfCheckBox = new QCheckBox(centralwidget);
        pdfCheckBox->setObjectName(QString::fromUtf8("pdfCheckBox"));

        verticalLayout->addWidget(pdfCheckBox);

        pngCheckBox = new QCheckBox(centralwidget);
        pngCheckBox->setObjectName(QString::fromUtf8("pngCheckBox"));

        verticalLayout->addWidget(pngCheckBox);

        bmpCheckBox = new QCheckBox(centralwidget);
        bmpCheckBox->setObjectName(QString::fromUtf8("bmpCheckBox"));

        verticalLayout->addWidget(bmpCheckBox);

        jpgCheckBox = new QCheckBox(centralwidget);
        jpgCheckBox->setObjectName(QString::fromUtf8("jpgCheckBox"));

        verticalLayout->addWidget(jpgCheckBox);

        saveGraphButton = new QPushButton(centralwidget);
        saveGraphButton->setObjectName(QString::fromUtf8("saveGraphButton"));

        verticalLayout->addWidget(saveGraphButton);

        cancelButton = new QPushButton(centralwidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        verticalLayout->addWidget(cancelButton);

        SaveGraphWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SaveGraphWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SaveGraphWindow->setStatusBar(statusbar);

        retranslateUi(SaveGraphWindow);

        QMetaObject::connectSlotsByName(SaveGraphWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SaveGraphWindow)
    {
        SaveGraphWindow->setWindowTitle(QApplication::translate("SaveGraphWindow", "save graph", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SaveGraphWindow", "SAVE GRAPH", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SaveGraphWindow", "graph name:", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("SaveGraphWindow", "graph_name", 0, QApplication::UnicodeUTF8));
        pdfCheckBox->setText(QApplication::translate("SaveGraphWindow", "save as PDF flie", 0, QApplication::UnicodeUTF8));
        pngCheckBox->setText(QApplication::translate("SaveGraphWindow", "save as PNG file", 0, QApplication::UnicodeUTF8));
        bmpCheckBox->setText(QApplication::translate("SaveGraphWindow", "save as BMP file", 0, QApplication::UnicodeUTF8));
        jpgCheckBox->setText(QApplication::translate("SaveGraphWindow", "save as JPG file", 0, QApplication::UnicodeUTF8));
        saveGraphButton->setText(QApplication::translate("SaveGraphWindow", "save graph", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("SaveGraphWindow", "cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SaveGraphWindow: public Ui_SaveGraphWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEGRAPHWINDOW_H
