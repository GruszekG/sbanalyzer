/********************************************************************************
** Form generated from reading UI file 'aboutproject.ui'
**
** Created: Sun 31. Mar 13:24:12 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTPROJECT_H
#define UI_ABOUTPROJECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_aboutProject
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFrame *line;
    QLabel *label_3;
    QFrame *line_2;
    QLabel *label_4;
    QFrame *line_3;
    QLabel *label_5;
    QFrame *line_4;
    QLabel *label_2;
    QFrame *line_5;
    QPushButton *closeButton;

    void setupUi(QWidget *aboutProject)
    {
        if (aboutProject->objectName().isEmpty())
            aboutProject->setObjectName(QString::fromUtf8("aboutProject"));
        aboutProject->resize(521, 332);
        verticalLayout = new QVBoxLayout(aboutProject);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(aboutProject);
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
        font.setPointSize(36);
        font.setItalic(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        line = new QFrame(aboutProject);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(10);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        label_3 = new QLabel(aboutProject);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bauhaus 93"));
        font1.setPointSize(16);
        font1.setItalic(true);
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        line_2 = new QFrame(aboutProject);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        label_4 = new QLabel(aboutProject);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Bauhaus 93"));
        font2.setPointSize(16);
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        line_3 = new QFrame(aboutProject);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        label_5 = new QLabel(aboutProject);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_5);

        line_4 = new QFrame(aboutProject);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        label_2 = new QLabel(aboutProject);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        line_5 = new QFrame(aboutProject);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShadow(QFrame::Plain);
        line_5->setLineWidth(10);
        line_5->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line_5);

        closeButton = new QPushButton(aboutProject);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Bauhaus 93"));
        font3.setPointSize(13);
        closeButton->setFont(font3);

        verticalLayout->addWidget(closeButton);


        retranslateUi(aboutProject);

        QMetaObject::connectSlotsByName(aboutProject);
    } // setupUi

    void retranslateUi(QWidget *aboutProject)
    {
        aboutProject->setWindowTitle(QApplication::translate("aboutProject", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("aboutProject", "SkateboardAnalyzer", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("aboutProject", "author: inz. Grzegorz Gruszka", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("aboutProject", "org: MKN Synergia\n"
"www.synergia.pwr.wroc.pl\n"
"contact: grzegorz.gruszka1990@gmail.com", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("aboutProject", "Wroclaw University of Technology", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("aboutProject", "version: v0.2", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("aboutProject", "close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class aboutProject: public Ui_aboutProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTPROJECT_H
