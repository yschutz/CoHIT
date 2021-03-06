//
//  YSCrossSectionpp.cpp
// calculates the pp cross section from systematics data in mb energy (√s) in GeV
//
//  Created by Yves Schutz on 06/03/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#include <QDebug>
#include <QtMath>

#include "qcustomplot.h"
#include "YSCrossSectionpp.h"

//______________________________________________________________________________
YSCrossSectionpp::YSCrossSectionpp()
{
    // ctor
    SetName("pp Cross Section");
    SetAxisLabel("√s (GeV)", "sigma (mb)");
}

//______________________________________________________________________________
YSCrossSectionpp::~YSCrossSectionpp()
{
    // dtor
}

//______________________________________________________________________________
qreal YSCrossSectionpp::Eval(qreal x) const
{
    // compute the function at x
    qreal rv = 0.;
    if (x == 0)
        return rv;
    switch (mType) {
    case kElastic:
    {
        rv = mPar[0] + mPar[1] *pow(x * x, mPar[2])+
                mPar[3] * pow(log(x * x / mPar[4]), 2.);
        break;
    }
    case kInelastic:
    {
       rv = (mPar[0] + mPar[1] *pow(x * x, mPar[2]) +
               mPar[3] * pow(log(x * x / mPar[4]), 2.)+
               mPar[5] * pow(x * x, mPar[6])) -
               (mPar[7] + mPar[8] * pow(x * x, mPar[9]) +
               mPar[10] * pow(log(x * x / mPar[11]), 2.) +
               mPar[12] * pow(x * x, mPar[13]));
        break;
    }
    case kTotal:
    {
        rv = mPar[0] + mPar[1] * pow(x * x, mPar[2])+
                mPar[3] * pow(log(x * x / mPar[4]), 2.) +
                mPar[5] * pow(x * x, mPar[6]);
        break;
    }

    default:
        break;
    }

    return rv;
}

//______________________________________________________________________________
void YSCrossSectionpp::Print() const
{
    // print the formula
    switch (mType) {
    case kElastic:
    {
        qDebug() << "pp elastic cross section";
        qDebug() << "[0]+[1]*pow(x*x,[2])+[3]*pow(log(x*x/[4]),2.)";
        break;
    }
    case kInelastic:
    {
        qDebug() << "pp inelastic cross section";
        qDebug() <<  "([0]+[1]*pow(x*x,[2])+[3]*pow(log(x*x/[4]),2.)+[5]*pow(x*x,[6]))-([7]+[8]*pow(x*x,[9])+[10]*pow(log(x*x/[11]),2.)+[12]*pow(x*x,[13]))";
        break;
    }
    case kTotal:
    {
        qDebug() << "pp total cross section";
        qDebug() << "[0]+[1]*pow(x*x,[2])+[3]*pow(log(x*x/[4]),2.)+[5]*pow(x*x,[6])";
        break;
    }

    default:
        break;
    }
    qDebug() << "cross section in mb (10**-27 cm2)";
    for(int index = 0; index < mPar.size(); index++)
        qDebug() << QString("[%1] = %2").arg(index).arg(mPar[index]);
}

//______________________________________________________________________________
void YSCrossSectionpp::SetType(YSCrossSectionpp::YSCSType type)
{
    // selects among elastic, inelastic and total

    // cross seection in mb

    mType = type;
    QVector<double> array;

    switch (mType) {
    case kElastic:
    {
        array << 5.166342 << 1.287805E1 << -4.059868E-1 << 9.028824E-2 << 2.92E1;
        break;
    }
    case kInelastic:
    {
        array << 35.5 << 42.59 << -0.46 << 0.3076 << 29.2 << -33.36 << -0.5454 << 5.166342 << 12.87805 << -0.4059868 << 0.09028824 << 29.2 << 0.0 << 0.0;
        break;
    }
    case kTotal:
    {
        array << 3.55E1 << 4.259E1 << -4.6E-1 << 3.076E-1 << 2.92E1 << -3.336E1 << -5.454E-1;
        break;
    }

    default:
        break;
    }
    SetParameters(array);

}

