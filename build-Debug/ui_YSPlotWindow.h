/********************************************************************************
** Form generated from reading UI file 'YSPlotWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YSPLOTWINDOW_H
#define UI_YSPLOTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_YSPlotWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QCustomPlot *customPlot;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *YSPlotWindow)
    {
        if (YSPlotWindow->objectName().isEmpty())
            YSPlotWindow->setObjectName(QStringLiteral("YSPlotWindow"));
        YSPlotWindow->resize(548, 420);
        centralWidget = new QWidget(YSPlotWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));

        verticalLayout->addWidget(customPlot);

        YSPlotWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(YSPlotWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        YSPlotWindow->setStatusBar(statusBar);

        retranslateUi(YSPlotWindow);

        QMetaObject::connectSlotsByName(YSPlotWindow);
    } // setupUi

    void retranslateUi(QMainWindow *YSPlotWindow)
    {
        YSPlotWindow->setWindowTitle(QApplication::translate("YSPlotWindow", "YSPlotWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class YSPlotWindow: public Ui_YSPlotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YSPLOTWINDOW_H
