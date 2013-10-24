/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon 21. Oct 23:31:14 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QLabel *skateLogo;
    QLabel *label_4;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QPushButton *quitButton;
    QLabel *label;
    QPushButton *skatersButton;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QPushButton *aboutSkateButton;
    QPushButton *visualizationButton;
    QPushButton *trickMeasurementButton;
    QPushButton *pushButtonRealTimeGraph;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *skatersTable;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *addSkaterButton;
    QPushButton *removeSkaterButton;
    QPushButton *saveSkatersButton;
    QPushButton *MainMenuButton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(675, 452);
        MainWindow->setTabShape(QTabWidget::Triangular);
        MainWindow->setDockNestingEnabled(false);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        verticalLayout_4 = new QVBoxLayout(page_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_3 = new QLabel(page_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QPalette palette;
        QBrush brush(QColor(170, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        label_3->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("Bauhaus 93"));
        font.setPointSize(40);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_3);

        skateLogo = new QLabel(page_3);
        skateLogo->setObjectName(QString::fromUtf8("skateLogo"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(skateLogo->sizePolicy().hasHeightForWidth());
        skateLogo->setSizePolicy(sizePolicy);
        skateLogo->setPixmap(QPixmap(QString::fromUtf8(":/brokeSkate.png")));
        skateLogo->setScaledContents(true);

        verticalLayout_4->addWidget(skateLogo);

        label_4 = new QLabel(page_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_4);

        stackedWidget->addWidget(page_3);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        quitButton = new QPushButton(page);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bauhaus 93"));
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setWeight(50);
        quitButton->setFont(font1);
        quitButton->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(quitButton, 13, 0, 1, 1);

        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        QPalette palette1;
        QBrush brush3(QColor(203, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        label->setPalette(palette1);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Bauhaus 93"));
        font2.setPointSize(36);
        font2.setBold(false);
        font2.setItalic(true);
        font2.setWeight(50);
        label->setFont(font2);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);
        label->setMargin(0);
        label->setIndent(-1);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        skatersButton = new QPushButton(page);
        skatersButton->setObjectName(QString::fromUtf8("skatersButton"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Bauhaus 93"));
        font3.setPointSize(20);
        skatersButton->setFont(font3);
        skatersButton->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(skatersButton, 6, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 10, 0, 1, 1);

        line = new QFrame(page);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(10);
        line->setFrameShape(QFrame::HLine);

        gridLayout_2->addWidget(line, 1, 0, 1, 1);

        aboutSkateButton = new QPushButton(page);
        aboutSkateButton->setObjectName(QString::fromUtf8("aboutSkateButton"));
        aboutSkateButton->setFont(font3);

        gridLayout_2->addWidget(aboutSkateButton, 8, 0, 1, 1);

        visualizationButton = new QPushButton(page);
        visualizationButton->setObjectName(QString::fromUtf8("visualizationButton"));
        visualizationButton->setFont(font3);

        gridLayout_2->addWidget(visualizationButton, 5, 0, 1, 1);

        trickMeasurementButton = new QPushButton(page);
        trickMeasurementButton->setObjectName(QString::fromUtf8("trickMeasurementButton"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Bauhaus 93"));
        font4.setPointSize(20);
        font4.setItalic(false);
        trickMeasurementButton->setFont(font4);
        trickMeasurementButton->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(trickMeasurementButton, 3, 0, 1, 1);

        pushButtonRealTimeGraph = new QPushButton(page);
        pushButtonRealTimeGraph->setObjectName(QString::fromUtf8("pushButtonRealTimeGraph"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Bauhaus 93"));
        font5.setPointSize(20);
        font5.setBold(false);
        font5.setWeight(50);
        font5.setKerning(false);
        pushButtonRealTimeGraph->setFont(font5);
        pushButtonRealTimeGraph->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_2->addWidget(pushButtonRealTimeGraph, 4, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        skatersTable = new QTableWidget(page_2);
        if (skatersTable->columnCount() < 7)
            skatersTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        skatersTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        skatersTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        skatersTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        skatersTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        skatersTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        skatersTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        skatersTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        skatersTable->setObjectName(QString::fromUtf8("skatersTable"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(skatersTable->sizePolicy().hasHeightForWidth());
        skatersTable->setSizePolicy(sizePolicy1);
        skatersTable->setMinimumSize(QSize(0, 0));
        skatersTable->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        skatersTable->setFocusPolicy(Qt::WheelFocus);
        skatersTable->setAutoFillBackground(true);
        skatersTable->setFrameShape(QFrame::StyledPanel);
        skatersTable->setFrameShadow(QFrame::Plain);
        skatersTable->setLineWidth(2);
        skatersTable->setMidLineWidth(4);
        skatersTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        skatersTable->setEditTriggers(QAbstractItemView::EditKeyPressed);
        skatersTable->setTabKeyNavigation(true);
        skatersTable->setProperty("showDropIndicator", QVariant(false));
        skatersTable->setDragDropOverwriteMode(false);
        skatersTable->setAlternatingRowColors(true);
        skatersTable->setSortingEnabled(false);
        skatersTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_2->addWidget(skatersTable);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        addSkaterButton = new QPushButton(page_2);
        addSkaterButton->setObjectName(QString::fromUtf8("addSkaterButton"));

        horizontalLayout->addWidget(addSkaterButton);

        removeSkaterButton = new QPushButton(page_2);
        removeSkaterButton->setObjectName(QString::fromUtf8("removeSkaterButton"));

        horizontalLayout->addWidget(removeSkaterButton);


        verticalLayout_3->addLayout(horizontalLayout);

        saveSkatersButton = new QPushButton(page_2);
        saveSkatersButton->setObjectName(QString::fromUtf8("saveSkatersButton"));

        verticalLayout_3->addWidget(saveSkatersButton);

        MainMenuButton = new QPushButton(page_2);
        MainMenuButton->setObjectName(QString::fromUtf8("MainMenuButton"));
        MainMenuButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_3->addWidget(MainMenuButton);


        verticalLayout_2->addLayout(verticalLayout_3);

        stackedWidget->addWidget(page_2);

        gridLayout_3->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "SkateboardAnalyzer", 0, QApplication::UnicodeUTF8));
        skateLogo->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "sbanalyzer.pl\n"
"MKN Synergia 2013. www.synergia.pwr.wroc.pl", 0, QApplication::UnicodeUTF8));
        quitButton->setText(QApplication::translate("MainWindow", "quit", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "SkateboardAnalzyer v0.5m", 0, QApplication::UnicodeUTF8));
        skatersButton->setText(QApplication::translate("MainWindow", "skaters", 0, QApplication::UnicodeUTF8));
        aboutSkateButton->setText(QApplication::translate("MainWindow", "about the project", 0, QApplication::UnicodeUTF8));
        visualizationButton->setText(QApplication::translate("MainWindow", "skateboard visualization", 0, QApplication::UnicodeUTF8));
        trickMeasurementButton->setText(QApplication::translate("MainWindow", "trick measurement", 0, QApplication::UnicodeUTF8));
        pushButtonRealTimeGraph->setText(QApplication::translate("MainWindow", "real time measurements", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = skatersTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = skatersTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "foot stance", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = skatersTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "training", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = skatersTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "age", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = skatersTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "city", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = skatersTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "email", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = skatersTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "info", 0, QApplication::UnicodeUTF8));
        addSkaterButton->setText(QApplication::translate("MainWindow", "add skater", 0, QApplication::UnicodeUTF8));
        removeSkaterButton->setText(QApplication::translate("MainWindow", "remove skater", 0, QApplication::UnicodeUTF8));
        saveSkatersButton->setText(QApplication::translate("MainWindow", "save", 0, QApplication::UnicodeUTF8));
        MainMenuButton->setText(QApplication::translate("MainWindow", "main menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
