//
//  YSDrawableObject.cpp
//  A basic 1D function
//
//  Created by Yves Schutz on 10/05/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.

#ifndef YSDRAWABLEOBJECT_H
#define YSDRAWABLEOBJECT_H

#include <QObject>

#include "qcustomplot.h"

class YSDrawableObject : public QObject
{
    Q_OBJECT

public:
    YSDrawableObject();

    void            FillXValues();
    QString         GetAxisLabel(QString xOrY) const
                    { if ( xOrY == "X" ) return mXLabel;
                      else if (xOrY == "Y") return mYLabel;
                      else return 0;}
    qreal           GetDx() const { return mDx; }
    QString         GetName() const { return mName; }
    int             GetNumberOfBins() const { return mNumberOfBins; }
    qreal           GetXMin() const { return mXMin; }
    qreal           GetXMax() const { return mXMax; }
    virtual qreal   GetYMax() = 0;
    QVector<double> GetXValues() const { return mXValues; }
    QVector<double> GetYValues() const { return mYValues; }
    virtual bool    IsF1() { return false; }
    virtual bool    IsH1() { return false; }
    void            SetAxisLabel(QString xLabel, QString yLabel) { mXLabel = xLabel; mYLabel = yLabel; }




protected:
    qreal           mDx;                              // x step
    QString         mName;                            // name of the function
    int             mNumberOfBins;                    // number of bins
    qreal           mXMax;                            // maximum x value
    qreal           mXMin;                            // minimum x value
    QString         mXLabel, mYLabel;                 // labels on x and y axis
    QVector<double> mXValues;                         // calculated x values
    qreal           mYMax;                            // calculated max y value
    qreal           mYMin;                            // min y value
    QVector<double> mYValues;                         // calculated y values

};

#endif // YSDRAWABLEOBJECT_H
