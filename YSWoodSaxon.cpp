//
//  YSWoodSaxon.cpp
//  The Wood Saxon function
//
//  Created by Yves Schutz on 03/01/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#include <QDebug>
#include <QtMath>

#include "qcustomplot.h"
#include "YSWoodSaxon.h"

//______________________________________________________________________________
YSWoodSaxon::YSWoodSaxon(QObject *parent) :
    YSF1(parent), mType(kWS)
{
    SetName("");
}

//______________________________________________________________________________
void YSWoodSaxon::Draw(QCustomPlot *cp)
{
   // Draw this
    cp->addGraph();

    QVector<double> y = GetYValues();
    QVector<double> x = GetXValues();

    cp->graph(0)->setData(x, y);
    cp->graph(0)->setName(GetName());

    cp->xAxis->setLabel("Radius (fm)");
    cp->yAxis->setLabel("Density (/fm3)");
    cp->yAxis->setRange(0, GetYMax() * 1.1);

    cp->xAxis->setRange(GetXMin(), GetXMax());

}

//______________________________________________________________________________
qreal YSWoodSaxon::Eval(qreal x) const
{
    // compute the function at x
    qreal rv = 0.;
    switch (mType) {
    case kWS: {
        rv = mPar[0] * mPar[1] * ( 1 + mPar[2] * qPow(x / mPar[3], 2)) / (1 + qExp((x - mPar[3]) / mPar[4]));
        break;
    }
    case kRWS: {
        rv = x * x * (1 + mPar[2] * qPow(x / mPar[0], 2)) / (1 + qExp(( x - mPar[0]) / mPar[1]));
        break;
    }
    default:
        break;
    }

    return rv;
}

//______________________________________________________________________________
void YSWoodSaxon::Print() const
{
    // print the formula
    switch (mType) {
    case kWS: {
        qDebug() << "Wood Saxon formula for nuclear density radial distribution";
        if (mNames.size() == mPar.size()) {
            qDebug() << QString("%1 * %2 * ( 1 +  %3 * power(x / %4, 2)) / (1+ exp(x - %4) / %5))").arg(mNames[0])
                    .arg(mNames[1]).arg(mNames[2]).arg(mNames[3]).arg(mNames[4]);
            for(int index = 0; index < mPar.size(); index++)
                qDebug() << QString("%1 = %2").arg(mNames[index]).arg(mPar[index]);
        }
        else {
            qDebug() << QString("[0] * [1] * ( 1 + * [2] * power(x / [3], 2)) / (1+ exp(x - [3]) / [4]))");
            for(int index = 0; index < mPar.size(); index++)
                qDebug() << QString("[%1] = %2").arg(index).arg(mPar[index]);
        }
        break;
    }
    case kRWS: {
        qDebug() << "R times Wood Saxon formula for nuclear density radial distribution";
        if (mNames.size() == mPar.size()) {
            qDebug() << QString("x * x * ( 1 + %3 * power(x / %1, 2)) / (1+ exp(x - %1) / %2))").arg(mNames[0])
                    .arg(mNames[1]).arg(mNames[2]);
            for(int index = 0; index < mPar.size(); index++)
                qDebug() << QString("%1 = %2").arg(mNames[index]).arg(mPar[index]);
        }
        else {
            qDebug() << QString("x * x * ( 1 + * [2] * power(x / [0], 2)) / (1+ exp(x - [0]) / [1]))");
            for(int index = 0; index < mPar.size(); index++)
                qDebug() << QString("[%1] = %2").arg(index).arg(mPar[index]);
        }
        break;
    }
    default:
        break;
    }
}
