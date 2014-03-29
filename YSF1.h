//
//  YSF1.cpp
//  A basic 1D function
//
//  Created by Yves Schutz on 06/03/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.

#ifndef YSF1_H
#define YSF1_H

#include <QObject>
#include <QStringList>
#include <QVector>

class QCustomPlot;
class YSF1 : public QObject
{
    Q_OBJECT
public:
    explicit YSF1(QObject *parent = 0);
             YSF1(const YSF1 &);
    virtual ~YSF1() {;}

    enum YSFitRule {
        kTrapeze, kSimpson
    };

    void            Copy(QObject &obj) const;
    int             BinarySearch(const QVector<double> array, qreal value );
    virtual void    Draw(QCustomPlot *cp) = 0;
    virtual qreal   Eval(qreal) const = 0;
    int             GetNumberOfBins() const { return mNumberOfBins; }
    qreal           GetDx() const { return mDx; }
    QString         GetName() const { return mName; }
    qreal           GetRandom(qreal xmin, qreal xmax);
    qreal           GetXMin() const { return mXMin; }
    qreal           GetXMax() const { return mXMax; }
    qreal           GetXStep() const { return mDx; }
    QVector<double> GetXValues();
    qreal           GetYMax() const { return mYMax; }
    qreal           GetYMin() const { return mYMin; }
    QVector<double> GetYValues();
    qreal           Integral(qreal xmin, qreal xmax, YSFitRule rule) const;
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
    qreal           mDx;                              // x step
    QString         mName;                            // name of the function
    int             mNumberOfBins;                    // number of bins
    QObject         *mParent;                         // the parent hooked object if any
    qreal           mXMax;                            // maximum x value
    qreal           mXMin;                            // minimum x value
    QVector<double> mXValues;                         // calculated x values
    qreal           mYMax;                            // calculated max y value
    qreal           mYMin;                            // min y value
    QVector<double> mYValues;                         // calculated y values
};

#endif // YSF1_H
