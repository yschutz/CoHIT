//
//  YSNucleus.cpp
//  Nucleus class for A
//
//  Created by Yves Schutz on 09/12/13.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#include <QtMath>

#include "YSIsotope.h"
#include "YSNucleus.h"
#include "YSPlotWindow.h"
#include "YSWoodSaxon.h"

const qreal YSNucleus::kgOneOverThree                = 1./3.;            //1/3
const qreal YSNucleus::kgProtonRadius                = 0.8775;           //fm
const qreal YSNucleus::kgRadiusConstant              = 1.1173;           //fm
const qreal YSNucleus::kgA2MeV                       = 931.494061;       //MeV/c2
const qreal YSNucleus::kgA2Kg                        = 1.660538921E-27;  //MeV/c2
const qreal YSNucleus::kgEMass                       = 0.510998928;      //MeV/c2
const qreal YSNucleus::kgFm2M                        = 1E-15;            //fermi to meter
const qreal YSNucleus::kgHardSphere                  = 0.4;              //fm

//______________________________________________________________________________
YSNucleus::YSNucleus() :
    mNucleons(NULL), mWounded(NULL)
{
    //just an intialisation of a dummy nucleus
}

//______________________________________________________________________________
YSNucleus::YSNucleus(const YSIsotope & iso) :
    mKw(0.0), mRadiusMax(10.), mRho0(0.16), mSkin(0.546)
{
    // ctor: make nucleus from isotope
   ((YSIsotope&)iso).Copy(*this) ;

    if(A() == 1)
      mRadius = kgProtonRadius ;
    else
      mRadius   = kgRadiusConstant * qPow(A(), kgOneOverThree) ;

//    mKw        = 0.0;
//    mRadiusMax = 10.0;  //fm
//    mRho0      = 0.16;  //fm-3
//    mSkin      = 0.546; //fm

    MakeDensityProfile();
    MakeNucleus();

}

//______________________________________________________________________________
YSNucleus::~YSNucleus()
{
    delete [] mNucleons;
    delete [] mWounded;
}

//______________________________________________________________________________
void YSNucleus::MakeDensityProfile()
{
    // make the function (Wodd Saxon distribution) describing the density profile of the nucleus

    mDensityProfil = new YSWoodSaxon();
    mDensityProfil->SetName(QString("%1%2 Density Profile").arg(A()).arg(Symbol()));
    mDensityProfil->SetNumberOfBins(100);
    mDensityProfil->SetXMinMax(0., mRadiusMax);

    QVector<double> array;
    qreal normalisation = 1.;
    array << normalisation << mRho0 << mKw << mRadius << mSkin;
    mDensityProfil->SetParameters(array);
    QStringList names;
    names << "normalisation" << "rho0" << "kw" << "r" << "w";
    mDensityProfil->SetParameterNames(names);
    QVector<double> densityProfile = mDensityProfil->GetYValues();

    normalisation = A() / mDensityProfil->Integral(0.0, RadiusMax(), YSWoodSaxon::kTrapeze);
    mDensityProfil->SetParameter(0, normalisation) ;
    densityProfile = mDensityProfil->GetYValues();

    for (int index = 0; index < mDensityProfil->GetNumberOfBins(); index++) {
        qreal xx = mDensityProfil->GetXMin() + index * mDensityProfil->GetDx();
        if (densityProfile[index] <= densityProfile[0] * 0.1) {
            mRadiusMean = xx;
            break;
        }
    }
}

//______________________________________________________________________________
void YSNucleus::MakeNucleus()
{
   // fill the nucleus with nucleons distributed according density profile

    YSWoodSaxon rws;
    rws.SetType(YSWoodSaxon::kRWS);
    QVector<double> array;
    array << mRadius << mSkin << mKw;
    rws.SetParameters(array);
    QStringList names;
    names << "r" << "w" << "kw";
    rws.SetParameterNames(names);

    mNucleons = new QVector3D[A()];
    mWounded  = new bool[A()];

    qreal sumx = 0.0, sumy = 0.0, sumz = 0.;

    for (int nucleon = 0; nucleon < A(); nucleon++) {
        qreal radius = rws.GetRandom(0., mRadiusMax);
        qreal phi = ((qreal)qrand() / (qreal)RAND_MAX) * 2 * M_PI;
        qreal ctheta = 2 * ((qreal)qrand() / (qreal)RAND_MAX) - 1;
        qreal stheta = qSqrt(1 - ctheta * ctheta);
        (mNucleons[nucleon]).setX(radius * stheta * qCos(phi));
        (mNucleons[nucleon]).setY(radius * stheta * qSin(phi));
        (mNucleons[nucleon]).setZ(radius * ctheta);
        SetWounded(nucleon, false);
        qreal d = 0.0;
         for (int nucleon2 = 0; nucleon2 < nucleon; nucleon2++) {
           d = qSqrt(qPow(mNucleons[nucleon].x() - mNucleons[nucleon2].x(), 2) +
                           qPow(mNucleons[nucleon].y() - mNucleons[nucleon2].y(), 2) +
                           qPow(mNucleons[nucleon].z() - mNucleons[nucleon2].z(), 2));
           if (d < HardSphere()) {
             nucleon--;
             break;
           }
         }
         if (d < HardSphere()) {
           sumx += mNucleons[nucleon].x();
           sumy += mNucleons[nucleon].y();
           sumz += mNucleons[nucleon].z();
         }
    }
    sumx = sumx / A();
    sumy = sumy / A();
    sumz = sumz / A();

    for (int nucleon = 0 ; nucleon < A() ; nucleon++) {
      qreal x = mNucleons[nucleon].x() - sumx;
      qreal y = mNucleons[nucleon].y() - sumy;
      qreal z = mNucleons[nucleon].z() - sumz;
      mNucleons[nucleon].setX(x);
      mNucleons[nucleon].setY(y);
      mNucleons[nucleon].setZ(z);
    }
}
