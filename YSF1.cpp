//
//  YSF1.cpp
//  A basic 1D function
//
//  Created by Yves Schutz on 06/03/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.

#include <QDebug>
#include <QtMath>
#include <QStringListIterator>

#include "YSF1.h"

//______________________________________________________________________________
YSF1::YSF1(QObject *parent) :
    QObject(parent), mDx(1.0), mNumberOfBins(0), mParent(parent), mXMax(0.0), mXMin(0.0),
    mYMax(0.0)
{
    // ctor
    mYValues.resize(mNumberOfBins + 1);
    mXValues.resize(mNumberOfBins + 1);
}

//______________________________________________________________________________
YSF1::YSF1(const YSF1 &f1)
{
    // copy ctor
    ((YSF1&)f1).Copy(*this);
}

//______________________________________________________________________________
void YSF1::Copy(QObject &obj) const
{
   // copy this F1 to a new F1
    ((YSF1&) obj).mDx           = mDx;
    ((YSF1&) obj).mName         = mName;
    ((YSF1&) obj).mNumberOfBins = mNumberOfBins;
    ((YSF1&) obj).mParent       = mParent;
    ((YSF1&) obj).mXMax         = mXMax;
    ((YSF1&) obj).mXMin         = mXMin;
    for (int index = 0; index < mNumberOfBins; index++) {
        ((YSF1&) obj).mXValues[index] = mXValues[index];
        ((YSF1&) obj).mYValues[index] = mYValues[index];
    }
    ((YSF1&) obj).mYMax         = mYMax;
    ((YSF1&) obj).mYMin         = mYMin;
}

//______________________________________________________________________________
int YSF1::BinarySearch(const QVector<double> array, qreal value)
{
    // Binary search in an array of n values to locate value.
    // http://root.cern.ch/root/html534/src/TMath.h.html#SgVqyE
    // Array is supposed  to be sorted prior to this call.
    // If match is found, function returns position of element.
    // If no match found, function gives nearest element smaller than value.

    const double *pind;
    pind = qLowerBound(array.begin(), array.end(), value);
    if ( (pind != array.end()) && (*pind == value) )
        return (pind - array.begin());
    else
        return ( pind - array.begin() - 1);
}

//______________________________________________________________________________
qreal YSF1::GetRandom(qreal xmin, qreal xmax)
{
  // generate a random radius wighted by the function (http://root.cern.ch/root/html534/src/TF1.cxx.html#gYdi6C)

    int numberOfBins = 100;
    qreal dx = (xmax - xmin) / (qreal)numberOfBins;

    if (mIntegral.size() == 0) {
        mIntegral.resize(numberOfBins+1);
        mAlpha.resize(numberOfBins);
        mBeta.resize(numberOfBins);
        mGamma.resize(numberOfBins);
        mIntegral[0] = 0.;

        qreal integ = 0.0;
        for (int i = 0; i < numberOfBins; i++) {
            qreal deb = xmin + i * dx;
            qreal fin = xmin + i * dx + dx;
            integ = Integral(deb, fin, kTrapeze);
            mIntegral[i+1] = mIntegral[i] + integ;
        }
        if (mIntegral[numberOfBins] == 0) {
            qWarning("YSWoodSaxon::GetRandom: Integral of function is zero");
            return 0;
        }
        qreal sum = mIntegral[numberOfBins];
        for(int i = 0; i <= numberOfBins; i++) // normalize to 1
            mIntegral[i] /= sum;

        // the integral r for each bin is approximated by a parabola
        // x = alpha + beta*r +gamma*r**2
        // compute the coefficients alpha, beta, gamma for each bin

        qreal x0, r1, r2, r3;
          for (int i = 0; i < numberOfBins; i++) {
             x0 = xmin + i * dx;
             r2 = mIntegral[i+1] - mIntegral[i];
             r1 = Integral(x0, x0 + 0.5 * dx, kTrapeze) / sum;
             r3 = 2 * r2 - 4 * r1;
             if (qAbs(r3) > 1e-8)
                 mGamma[i] = r3 / (dx * dx);
             else
                 mGamma[i] = 0;
             mBeta[i]  = r2 / dx - mGamma[i] * dx;
             mAlpha[i] = x0;
             mGamma[i] *= 2;
          }
    }
    // return the random number
    int binmin = (int)(xmin / dx);
    int binmax = (int)(xmax / dx) + 2;
    if (binmax > numberOfBins)
        binmax = numberOfBins;
    qreal pmin = mIntegral[binmin];
    qreal pmax = mIntegral[binmax];

    qreal r, x, xx, rr;
    do {
        r = pmin + (qreal)(qrand()) / (qreal)RAND_MAX * (pmax - pmin);
        int bin = BinarySearch(mIntegral, r);
        rr = r - mIntegral[bin];
        if (mGamma[bin] != 0)
            xx = (-mBeta[bin] + qSqrt(mBeta[bin] * mBeta[bin] + 2 * mGamma[bin] * rr)) / mGamma[bin];
        else
            xx = rr / mBeta[bin];
        x = mAlpha[bin] + xx;
    }  while(x < xmin || x > xmax);

    return x;
}

//______________________________________________________________________________
QVector<double> YSF1::GetXValues()
{
    // fills the array with the x values
    mXValues.resize(mNumberOfBins + 1);
    for(int index =0; index < mNumberOfBins; index++) {
        mXValues[index] = index * mDx;
    }
    return mXValues;
}

//______________________________________________________________________________
QVector<double> YSF1::GetYValues()
{
    // fills the vector with values calculated from the function
    mYValues.resize(mNumberOfBins + 1);

    // fill the function
    for (int index = 0; index < mNumberOfBins; index++) {
        qreal xx = mXMin + index * mDx;
        mYValues[index] = Eval(xx);
//        qDebug() << "YSF1::GetYValues" << xx << mYValues[index];
    }
    mYValues[mNumberOfBins] = Eval(mXMax);

    // calculates the maximum of the function
    qreal ymax = 0.0;
    for (int index = 0; index < mNumberOfBins -1; index++) {
           if( mYValues[index] > ymax )
               ymax = mYValues[index];
    }
    SetYMinMax(0.0, ymax);
    return mYValues;
}

//______________________________________________________________________________
qreal YSF1::Integral(qreal xmin, qreal xmax, YSFitRule rule) const
{
    // calculates integral between xmin and xmax
    // Composite trapezoidal rule

    int numberOfBins = 100; // number of bins to subdivide [xmin, xmax] interval
    qreal dx = (xmax - xmin) / numberOfBins; // step size to evaluate the function
    qreal sum = 0.0;
    switch (rule) {
    case kTrapeze: {
        // Composite trapezoidal rule (http://en.wikipedia.org/wiki/Numerical_integration)
        sum = (Eval(xmin) + Eval(xmax)) / 2.;
        for (int i = 1; i < numberOfBins; i++) {
            sum += Eval(xmin + i * dx);
        }
        sum *= (xmax - xmin) / numberOfBins;
        break;
    }
    case kSimpson: {
        // composite Simpson rule (http://en.wikipedia.org/wiki/Simpson%27s_rule)
        sum = Eval(xmin) + Eval(xmax);
        for (int i = 1; i < numberOfBins; i+=2)
           sum += 4 * Eval(xmin + i * dx);
       for (int i = 2; i < numberOfBins-1; i+=2)
           sum += 2 * Eval(xmin + i * dx);

       sum = sum  * dx / 3.;
    }
    default:
        break;
    }

    return sum;
}

//______________________________________________________________________________
void YSF1::SetParameterName(int index, QString name)
{
    // sets the name of parameter #index
    if (index >= mPar.size())
        mNames.append(name);
    else
        mNames[index] = name;
}
//______________________________________________________________________________
void YSF1::SetParameterNames(QStringList names)
{
    // set the name of parameteres at once
    QStringListIterator iterator(names);
      while (iterator.hasNext())
          mNames.append(iterator.next());
}

//______________________________________________________________________________
void YSF1::SetParameter(int index, qreal parameter)
{
    // set parameter # index
    if (index >= mPar.size()) {
        mPar.resize(index + 1);
        qDebug() << "YSF1::SetParameter: mPar resized";
    }
    mPar[index] = parameter;
}

//______________________________________________________________________________
void YSF1::SetParameters(QVector<double> parameters)
{
    // set all parameters at once
    mPar.resize(parameters.size());
    for(int index = 0; index < parameters.size(); index++) {
        mPar[index] = parameters[index];
    }
}

//______________________________________________________________________________
void YSF1::SetXMinMax(qreal min, qreal max)
{
    // set x min and max and calcultes step
    mXMin = min;
    mXMax = max;
    mDx   = mXMax / mNumberOfBins ;
}

//______________________________________________________________________________
YSF1& YSF1::operator=(const YSF1 &rhs)
{
    // Operator =

    if (this != &rhs) {
      rhs.Copy(*this);
   }
   return *this;
}
