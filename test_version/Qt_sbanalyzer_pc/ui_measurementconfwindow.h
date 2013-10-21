/********************************************************************************
** Form generated from reading UI file 'measurementconfwindow.ui'
**
** Created: Tue 10. Sep 20:16:04 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEASUREMENTCONFWINDOW_H
#define UI_MEASUREMENTCONFWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MeasurementConfWindow
{
public:
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QComboBox *FreqComboBox;
    QComboBox *AccComboBox;
    QComboBox *GyroComboBox;
    QSpinBox *TimeSpinBox;
    QFrame *line_2;
    QPushButton *OkButton;
    QPushButton *CancelButton;

    void setupUi(QDialog *MeasurementConfWindow)
    {
        if (MeasurementConfWindow->objectName().isEmpty())
            MeasurementConfWindow->setObjectName(QString::fromUtf8("MeasurementConfWindow"));
        MeasurementConfWindow->resize(249, 228);
        horizontalLayout_4 = new QHBoxLayout(MeasurementConfWindow);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_5 = new QLabel(MeasurementConfWindow);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_5);

        line = new QFrame(MeasurementConfWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(2);
        line->setFrameShape(QFrame::HLine);

        verticalLayout_5->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(MeasurementConfWindow);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(MeasurementConfWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        label_3 = new QLabel(MeasurementConfWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        label_4 = new QLabel(MeasurementConfWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_3->addWidget(label_4);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        FreqComboBox = new QComboBox(MeasurementConfWindow);
        FreqComboBox->setObjectName(QString::fromUtf8("FreqComboBox"));

        verticalLayout_2->addWidget(FreqComboBox);

        AccComboBox = new QComboBox(MeasurementConfWindow);
        AccComboBox->setObjectName(QString::fromUtf8("AccComboBox"));

        verticalLayout_2->addWidget(AccComboBox);

        GyroComboBox = new QComboBox(MeasurementConfWindow);
        GyroComboBox->setObjectName(QString::fromUtf8("GyroComboBox"));

        verticalLayout_2->addWidget(GyroComboBox);

        TimeSpinBox = new QSpinBox(MeasurementConfWindow);
        TimeSpinBox->setObjectName(QString::fromUtf8("TimeSpinBox"));

        verticalLayout_2->addWidget(TimeSpinBox);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_5->addLayout(horizontalLayout_3);

        line_2 = new QFrame(MeasurementConfWindow);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setLineWidth(2);
        line_2->setFrameShape(QFrame::HLine);

        verticalLayout_5->addWidget(line_2);

        OkButton = new QPushButton(MeasurementConfWindow);
        OkButton->setObjectName(QString::fromUtf8("OkButton"));
        OkButton->setCursor(QCursor(Qt::PointingHandCursor));
        OkButton->setAutoDefault(false);

        verticalLayout_5->addWidget(OkButton);

        CancelButton = new QPushButton(MeasurementConfWindow);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));
        CancelButton->setAutoDefault(false);

        verticalLayout_5->addWidget(CancelButton);


        horizontalLayout_4->addLayout(verticalLayout_5);


        retranslateUi(MeasurementConfWindow);

        QMetaObject::connectSlotsByName(MeasurementConfWindow);
    } // setupUi

    void retranslateUi(QDialog *MeasurementConfWindow)
    {
        MeasurementConfWindow->setWindowTitle(QApplication::translate("MeasurementConfWindow", "Dialog", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MeasurementConfWindow", "Settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MeasurementConfWindow", "Freqency", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MeasurementConfWindow", "LIS3DH Range", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MeasurementConfWindow", "L3G4200D Range", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MeasurementConfWindow", "Measurement Time[s]", 0, QApplication::UnicodeUTF8));
        OkButton->setText(QApplication::translate("MeasurementConfWindow", "OK", 0, QApplication::UnicodeUTF8));
        CancelButton->setText(QApplication::translate("MeasurementConfWindow", "CANCEL", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MeasurementConfWindow: public Ui_MeasurementConfWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASUREMENTCONFWINDOW_H
