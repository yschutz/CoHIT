//
//  YSPlotWindow.h
//  A window for various plot (qcustomplot)
//
//  Created by Yves Schutz on 02/01/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#ifndef YSPLOTWINDOW_H
#define YSPLOTWINDOW_H

#include <QMainWindow>

#include "qcustomplot.h"

class QCPItemLine;
class QLineEdit;
class QWidget;
class YSF1;

class YSPlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit YSPlotWindow(QWidget *parent = 0);
    ~YSPlotWindow();

    void Draw(YSF1 *obj);

public slots:
    void MouseOverGraph(QMouseEvent *event);
    void ChangeCoord();

private:
    QCPItemLine * mArrow;         // arrow
    QLineEdit   *mCoorX, *mCoorY; // box that contains the coordinates value aof mouse position
    QWidget     *mCentralWidget;  // the central widget containing the qcustomplot widget
    QCustomPlot *mCP;             // the qcustomplot widget
    YSF1        *mF1;             // the 1D function to be plotted
    QWidget     *mCoordWidget;    // widget where x, y coordinates are displayed

};

#endif // YSPLOTWINDOW_H
