//
//  YSPlotWindow.cpp
//  A window for various plot (qcustomplot)
//
//  Created by Yves Schutz on 02/01/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#include "YSCrossSectionpp.h"
#include "YSDrawableObject.h"
#include "YSF1.h"
#include "YSNucleus.h"
#include "YSPlotWindow.h"

//______________________________________________________________________________
YSPlotWindow::YSPlotWindow(QString name, int w, int h, QWidget *parent) :
    QMainWindow(parent),
    mCurrentCP(0), mCurrentWindow(1), mSubWindows(NULL), mSubX(1), mSubY(1)
{
    // Main Window
    setWindowTitle(name);

    int windowWidth = w, windowHeight = h;
    int windowX = 500, windowY = 500;
    setGeometry(windowX, windowY, windowWidth, windowHeight); // position and size of the window

        // Central Window
    mCentralWidget = new QWidget(this);
    setCentralWidget(mCentralWidget);
    mCentralWidget->setLayout(new QVBoxLayout());
    int xMargin = width() / 30., yMargin = height() / 30.;
    mCentralWidget->layout()->setContentsMargins(xMargin, yMargin, xMargin, yMargin);

            // display area for plots
    mDisplayArea = new QWidget(mCentralWidget);
    mGridLayout = new QGridLayout;
    mDisplayArea->setLayout(mGridLayout);
    Divide(1,1);

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

    connect(mCoorX, SIGNAL(returnPressed()), this, SLOT(ChangeCoord()));
    connect(mCoorY, SIGNAL(returnPressed()), this, SLOT(ChangeCoord()));

    mColorList.append(Qt::black);
    mColorList.append(Qt::red);
    mColorList.append(Qt::green);
    mColorList.append(Qt::blue);

}

//______________________________________________________________________________
YSPlotWindow::~YSPlotWindow()
{
    delete mCoorX;
    delete mCoorY;
    delete mCoordWidget;
    delete[] mCP;
}

//______________________________________________________________________________
void YSPlotWindow::MouseOverGraph(QMouseEvent *event)
{
    // returns coordinate of the cliked position

    unsigned int winUnderMouse = 0;
    for (unsigned int index = 0; index < mSubX * mSubY; index++) {
        if (mSubWindows[index]->underMouse()) {
            winUnderMouse = index;
            break;
        }
    }
    QCPGraph * g = NULL;
    double dmin = 999.;
    int indexMin = 0;

    for (int index = 0; index < mCP[winUnderMouse]->graphCount(); index++) {
        double d = mCP[winUnderMouse]->graph(index)->selectTest(QPointF(event->x(), event->y()), true);
        if (d < dmin) {
            dmin = d;
            indexMin = index;
        }
    }
    if (dmin < 10.0)
        g = mCP[winUnderMouse]->graph(indexMin);
    if (g) {
        const QCPDataMap *dataMap = g->data();
        double find = mCP[winUnderMouse]->xAxis->pixelToCoord(event->x());
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

        double x = mCP[winUnderMouse]->xAxis->pixelToCoord(event->x());
        mCoorX->setText(QString("%1").arg(x));
        mCoorY->setText(QString("%1").arg(ii.value().value));
    }
}

//______________________________________________________________________________
void YSPlotWindow::ChangeCoord()
{
    // put an arrow at the position selected in the text box

    QCPGraph * g = NULL;
    for (int index = 0; index < mCP[mCurrentCP]->graphCount(); index++) {
       if (mCP[mCurrentCP]->graph(index)->selected()){
           g = mCP[mCurrentCP]->graph(index);
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
        y = y - mCP[mCurrentCP]->yAxis->range().upper * 0.1;
        mArrow->start->setCoords(x, y);
        mCP[mCurrentCP]->replot();
    }
}

//______________________________________________________________________________
void YSPlotWindow::Add(YSDrawableObject *obj, QString opt)
{
    // Custom plot parameters
    mCurrentCP = mCurrentWindow - 1;
    if (!opt.contains("S")) // plot on a new graph
       mCP[mCurrentCP] = new QCustomPlot(this);

    // Basic settingy of qcustumplot
    mCP[mCurrentCP]->xAxis2->setVisible(true);
    mCP[mCurrentCP]->xAxis2->setTickLabels(false);
    mCP[mCurrentCP]->yAxis2->setVisible(true);
    mCP[mCurrentCP]->yAxis2->setTickLabels(false);

    mCP[mCurrentCP]->legend->setVisible(true);
    mCP[mCurrentCP]->legend->setFont(QFont("Helvetica", 9));
    mCP[mCurrentCP]->installEventFilter(this);

    // Add an arrow
    mArrow = new QCPItemLine(mCP[mCurrentCP]);
    mCP[mCurrentCP]->addItem(mArrow);
    mArrow->setHead(QCPLineEnding::esSpikeArrow);
    mArrow->setPen(QPen(Qt::red));
    mArrow->start->setCoords(0., 0.);
    mArrow->end->setCoords(0., 0.);

    connect(mCP[mCurrentCP], SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(MouseOverGraph(QMouseEvent*)));

    mCP[mCurrentCP]->addGraph();

    int currentGraph = mCP[mCurrentCP]->graphCount() - 1;
    mCP[mCurrentCP]->graph(currentGraph)->setData(obj->GetXValues(), obj->GetYValues());
    mCP[mCurrentCP]->graph(currentGraph)->setName(obj->GetName());
    if (obj->IsH1())
        mCP[mCurrentCP]->graph(currentGraph)->setLineStyle(QCPGraph::lsStepCenter);
    if (obj->IsF1())
        mCP[mCurrentCP]->graph(currentGraph)->setLineStyle(QCPGraph::lsLine);
    mCP[mCurrentCP]->graph(currentGraph)->setPen(mColorList.at(currentGraph));

    if (currentGraph == 0) {
        mCP[mCurrentCP]->xAxis->setRange(obj->GetXMin(), obj->GetXMax());
        mCP[mCurrentCP]->xAxis->setLabel(obj->GetAxisLabel("X"));

        mCP[mCurrentCP]->yAxis->setLabel(obj->GetAxisLabel("Y"));
        mCP[mCurrentCP]->yAxis->setRange(0.0, obj->GetYMax() * 1.1);

        if (opt.contains("L")) { //Log scale requested
         mCP[mCurrentCP]->yAxis->setScaleType(QCPAxis::stLogarithmic);
         mCP[mCurrentCP]->yAxis->setScaleLogBase(100);
         mCP[mCurrentCP]->yAxis->setNumberFormat("eb");
         mCP[mCurrentCP]->yAxis->setNumberPrecision(0);
            mCP[mCurrentCP]->yAxis->setSubTickCount(10);
        }
        if (opt.contains("l")) { //lin scale requested
            mCP[mCurrentCP]->yAxis->setScaleType(QCPAxis::stLinear);
        }
        connect(mCP[mCurrentCP]->xAxis, SIGNAL(rangeChanged(QCPRange)), mCP[mCurrentCP]->xAxis2, SLOT(setRange(QCPRange)));
        connect(mCP[mCurrentCP]->yAxis, SIGNAL(rangeChanged(QCPRange)), mCP[mCurrentCP]->yAxis2, SLOT(setRange(QCPRange)));
        mCP[mCurrentCP]->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    }
}

//______________________________________________________________________________
void YSPlotWindow::Divide(unsigned int nx, unsigned int ny)
{
    // divide the mainwindow in nx times ny subwindows

    mSubX = nx;
    mSubY = ny;
    mSubWindows = new QWidget*[mSubX * mSubY];
    for (unsigned int index = 0; index < mSubX * mSubY; index++)
        mSubWindows[index] = new QWidget(mDisplayArea);
    mCP = new QCustomPlot*[mSubX * mSubY];
}

//______________________________________________________________________________
void YSPlotWindow::Show()
{
    // displays the windows with all graphs

   QWidget *current = mSubWindows[mCurrentWindow -1];
    current->setLayout(new QVBoxLayout());
    current->layout()->addWidget(mCP[mCurrentCP]);
    int nx = 0, ny = 1;
    if (mCurrentWindow > mSubX) {
        nx = (mCurrentWindow - mSubX -1);
        ny = mSubY - mCurrentWindow % mSubX + 1;
    }
    else
        nx = mCurrentWindow -1;
    mGridLayout->addWidget(current, nx, ny);
    mCentralWidget->layout()->addWidget(mDisplayArea);
    mCentralWidget->layout()->addWidget(mCoordWidget);
    mCP[mCurrentCP]->replot();
    show();
}
