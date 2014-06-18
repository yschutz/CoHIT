//
//  YSH1.cpp
//  A basic 1D function
//
//  Created by Yves Schutz on 10/05/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.

#include "qcustomplot.h"
#include "YSH1.h"

//______________________________________________________________________________
YSH1::YSH1(QString name, int bins, qreal xmin, qreal xmax)
{
    // ctor
    mName         = name;
    mNumberOfBins = bins;
    mXMax         = xmax;
    mXMin         = xmin;
    mXValues.resize(mNumberOfBins + 2);
    mYValues.resize(mNumberOfBins + 2);
    mDx = (mXMax - mXMin) / mNumberOfBins;
    FillXValues();
}

//______________________________________________________________________________
YSH1::YSH1(const YSH1 &h1)
{
    // copy ctor
    ((YSH1&)h1).Copy(*this);
}

//______________________________________________________________________________
void YSH1::Copy(QObject &obj) const
{
    // copy this H1 to a new H1
    ((YSH1&) obj).mDx             = mDx;
    ((YSH1&) obj).mName           = mName;
    ((YSH1&) obj).mNumberOfBins   = mNumberOfBins;
    ((YSH1&) obj).mXMax           = mXMax;
    ((YSH1&) obj).mXMin           = mXMin;
    for (int index = 0; index < mNumberOfBins; index++) {
        ((YSH1&) obj).mXValues[index] = mXValues[index];
        ((YSH1&) obj).mYValues[index] = mYValues[index];
    }
}

//______________________________________________________________________________
void YSH1::Fill(qreal x, qreal weight)
{
    // fills the array with the x values
    int index;
    if ( x < mXMin || x > mXMax) // overflow
        index = 0;
    else {
        index = ( x - mXMin) / mDx + 1;
    }
    mYValues[index] += weight;
}

//______________________________________________________________________________
qreal YSH1::GetYMax()
{
    // search highest Y value

    qreal ymax = 0.0;
    for (int index = 0; index < mNumberOfBins -1; index++) {
           if( mYValues[index] > ymax )
               ymax = mYValues[index];
    }
    mYMax = ymax;
    return ymax;
}
