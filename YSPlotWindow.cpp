//
//  YSPlotWindow.cpp
//  A window for various plot (qcustomplot)
//
//  Created by Yves Schutz on 02/01/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#include "YSCrossSectionpp.h"
#include "YSF1.h"
#include "YSNucleus.h"
#include "YSPlotWindow.h"

//______________________________________________________________________________
YSPlotWindow::YSPlotWindow(QWidget *parent) :
    QMainWindow(parent), mF1(NULL)
{
    // Main Window
    int windowWidth = 548, windowHeight = 420.;
    int windowX = 500, windowY = 500;
    setGeometry(windowX, windowY, windowWidth, windowHeight); // position and size of the window

    // Central widget
    mCentralWidget = new QWidget(this);
    mCentralWidget->setLayout(new QVBoxLayout());
    int xMargin = windowWidth / 30., yMargin = windowHeight / 30.;
    mCentralWidget->layout()->setContentsMargins(xMargin, yMargin, xMargin, yMargin);

    // Plot area
    mCP = new QCustomPlot(this);
    mCP->legend->setVisible(true);
    mCP->legend->setFont(QFont("Helvetica", 9));
    mCP->installEventFilter(this);

    // Add an arrow
    mArrow = new QCPItemLine(mCP);
    mCP->addItem(mArrow);
    mArrow->setHead(QCPLineEnding::esSpikeArrow);
    mArrow->setPen(QPen(Qt::red));
    mArrow->start->setCoords(0., 0.);
    mArrow->end->setCoords(0., 0.);


    // widget to display x, z coordinates
    mCoordWidget = new QWidget(mCentralWidget);
    mCoordWidget->setLayout(new QHBoxLayout);
    mCoordWidget->setFixedSize(windowX, windowY*0.06);
    mCoordWidget->layout()->setAlignment(Qt::AlignTop);
    int height = mCoordWidget->height()*0.6;


    QLabel *labx = new QLabel("x =", mCoordWidget);
    labx->setFont(QFont("Helvetica", 12));
    labx->setFixedHeight(height);//  setFixedSize(QSize(widthlabel, height));
    mCoordWidget->layout()->addWidget(labx);

    mCoorX = new QLineEdit(mCoordWidget);
    mCoorX->setFont(QFont("Helvetica", 12));
    mCoorX->setFixedHeight(height);//  setFixedSize(QSize(widthtext, height));
    mCoorX->setAlignment(Qt::AlignCenter);
    mCoorX->setAlignment(Qt::AlignHCenter);
    mCoordWidget->layout()->addWidget(mCoorX);

    QLabel *laby = new QLabel("y =", mCoordWidget);
    laby->setFixedHeight(height); // setFixedSize(QSize(widthlabel, height));
    mCoordWidget->layout()->addWidget(laby);

    mCoorY = new QLineEdit(mCoordWidget);
    mCoorY->setFont(QFont("Helvetica", 12));
    mCoorY->setFixedHeight(height);// setFixedSize(QSize(widthtext, height));
    mCoorY->setAlignment(Qt::AlignCenter);
    mCoorY->setAlignment(Qt::AlignHCenter);
    mCoorY->setReadOnly(true);
    mCoordWidget->layout()->addWidget(mCoorY);

    mCentralWidget->layout()->addWidget(mCP);
    mCentralWidget->layout()->addWidget(mCoordWidget);

    setCentralWidget(mCentralWidget);

    connect(mCoorX, SIGNAL(returnPressed()), this, SLOT(ChangeCoord()));
    connect(mCoorY, SIGNAL(returnPressed()), this, SLOT(ChangeCoord()));
}

//______________________________________________________________________________
YSPlotWindow::~YSPlotWindow()
{
    delete mCoorX;
    delete mCoorY;
    delete mCoordWidget;
    delete mCP;
    delete mCentralWidget;
}

//______________________________________________________________________________
void YSPlotWindow::MouseOverGraph(QMouseEvent *event)
{
    // returns coordinate of the cliked position

    QCPGraph * g = NULL;
    double dmin = 999.;
    int indexMin = 0;
    for (int index = 0; index < mCP->graphCount(); index++) {
        double d = mCP->graph(index)->selectTest(QPointF(event->x(), event->y()), true);
        if (d < dmin) {
            dmin = d;
            indexMin = index;
        }
    }
    if (dmin < 10.0)
        g = mCP->graph(indexMin);
    if (g) {
        const QCPDataMap *dataMap = g->data();
        double find = mCP->xAxis->pixelToCoord(event->x());
        QMap<double, QCPData>::const_iterator i = dataMap->constBegin();
        indexMin = 0;
        dmin     = 999.;
        double xClosest = 0;
        while (i != dataMap->constEnd()) {
            double d = qAbs(i.key() - find);
            if (d < dmin) {
                dmin = d;
                xClosest = i.key();
            }
            ++i;
        }

        QMap<double, QCPData>::const_iterator ii = dataMap->constFind(xClosest);

        double x = mCP->xAxis->pixelToCoord(event->x());
        mCoorX->setText(QString("%1").arg(x));
        mCoorY->setText(QString("%1").arg(ii.value().value));
    }
}

//______________________________________________________________________________
void YSPlotWindow::ChangeCoord()
{
    // put an arrow at the position selected in the text box

    QCPGraph * g = NULL;
    for (int index = 0; index < mCP->graphCount(); index++) {
       if (mCP->graph(index)->selected()){
           g = mCP->graph(index);
           break;
       }
    }
    if (g) {
        const QCPDataMap *dataMap = g->data();
        double x = mCoorX->text().toDouble();
        QMap<double, QCPData>::const_iterator i = dataMap->constBegin();
        double dmin     = 999.;
        double xClosest = 0;
        while (i != dataMap->constEnd()) {
            double d = qAbs(i.key() - x);
            if (d < dmin) {
                dmin = d;
                xClosest = i.key();
            }
            ++i;
        }
        QMap<double, QCPData>::const_iterator ii = dataMap->constFind(xClosest);
        double y = ii.value().value;
        mCoorY->setText(QString("%1").arg(y));
        mArrow->end->setCoords(x, y);
        y = y - mCP->yAxis->range().upper * 0.1;
        mArrow->start->setCoords(x, y);
        mCP->replot();
    }
}

//______________________________________________________________________________
void YSPlotWindow::Draw(YSF1 *obj)
{
    mF1 = obj;
    connect(mCP, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(MouseOverGraph(QMouseEvent*)));
    setWindowTitle(mF1->GetName());

    mF1->Draw(mCP);

    mCP->xAxis2->setVisible(true);
    mCP->xAxis2->setTickLabels(false);
    mCP->yAxis2->setVisible(true);
    mCP->yAxis2->setTickLabels(false);

    connect(mCP->xAxis, SIGNAL(rangeChanged(QCPRange)), mCP->xAxis2, SLOT(setRange(QCPRange)));
    connect(mCP->yAxis, SIGNAL(rangeChanged(QCPRange)), mCP->yAxis2, SLOT(setRange(QCPRange)));
    mCP->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    statusBar()->clearMessage();
    mCP->replot();

}
