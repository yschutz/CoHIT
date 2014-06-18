//
//  YSF1.cpp
//  A basic 1D function
//
//  Created by Yves Schutz on 06/03/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.

#ifndef YSF1_H
#define YSF1_H

#include <QStringList>
#include <QVector>

class QCustomPlot;

#include "YSDrawableObject.h"

class YSF1 : public YSDrawableObject
{

public:
    explicit YSF1();
             YSF1(const YSF1 &);
    virtual ~YSF1() {;}

    enum YSFitRule {
        kTrapeze, kSimpson
    };

    void            Copy(YSF1 &obj) const;
    int             BinarySearch(const QVector<double> array, qreal value );
    virtual qreal   Eval(qreal) const = 0;
    qreal           GetRandom(qreal xmin, qreal xmax);
    qreal           GetXStep() const { return mDx; }
    qreal           GetYMax() { return mYMax; }
    qreal           GetYMin() const { return mYMin; }
    void            FillYValues();
    qreal           Integral(qreal xmin, qreal xmax, YSFitRule rule) const;
    bool            IsF1() { return true; }
    virtual void    Print() const = 0;
    void            SetXMinMax(qreal min, qreal max);
    void            SetYMinMax(qreal min, qreal max) {mYMin = min; mYMax = max;}
    void            SetName(QString n) { mName = n; }
    void            SetParameterName(int, QString);
    void            SetParameterNames(QStringList);
    void            SetNumberOfBins(int bins) { mNumberOfBins = bins; mYValues.resize(mNumberOfBins + 1); }
    void            SetParameter(int, qreal);
    void            SetParameters(QVector<double>);

    YSF1& operator=(const YSF1 &rhs);


protected:
    QVector<double> mPar;          // parameters of the function
    QStringList     mNames;        // names of the parameters

private:
    QVector<double> mIntegral, mAlpha, mBeta, mGamma; // needed by GetRandom
};

#endif // YSF1_H
