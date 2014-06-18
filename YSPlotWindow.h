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

#include "YSDrawableObject.h"

class QCPItemLine;
class QLineEdit;
class QWidget;

class YSPlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit YSPlotWindow(QString name, int w = 548, int h = 420, QWidget *parent = 0);
    ~YSPlotWindow();

    void Add(YSDrawableObject *obj, QString opt ="l");
    void Cd(unsigned int w) { mCurrentWindow = w; }
    void Divide(unsigned int nx, unsigned int ny);
    void Show();

public slots:
    void MouseOverGraph(QMouseEvent *event);
    void ChangeCoord();

private:
    QCPItemLine   *mArrow;          // arrow
    unsigned int  mCurrentCP;       // current custom plot
    unsigned int  mCurrentWindow;   // window where to draw
    QCustomPlot   **mCP;            // the qcustomplot widgets
    QWidget       *mCentralWidget;  // central widget containing display + infos;
    QList<QColor> mColorList;       // list of colors for multiple graphs window
    QWidget       *mCoordWidget;    // widget where x, y coordinates are displayed
    QLineEdit     *mCoorX, *mCoorY; // box that contains the coordinates value aof mouse position
    QWidget       *mDisplayArea;    // display area for plots
    QGridLayout   *mGridLayout;     // grid layout for many plots in one window
    QWidget       **mSubWindows;     // the central widget containing the qcustomplot widget
    unsigned int  mSubX, mSubY;     // horizontal and vertical subdivisions of main window
};

#endif // YSPLOTWINDOW_H
