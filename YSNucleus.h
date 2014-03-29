//
//  YSNucleus.h
//  Nucleus class for A
//
//  Created by Yves Schutz on 09/12/13.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#ifndef YSNUCLEUS_H
#define YSNUCLEUS_H

#include <QObject>
#include <QDebug>

#include "YSIsotope.h"
#include "YSPeriodictable.h"
#include "YSWoodSaxon.h"

class QGLView;

class YSNucleus : public YSIsotope
{
    Q_OBJECT

public:
    const static qreal kgOneOverThree;   //1/3
    const static qreal kgProtonRadius;   //fm
    const static qreal kgRadiusConstant; //fm
    const static qreal kgA2MeV;          //MeV/c2
    const static qreal kgA2Kg;           //kg
    const static qreal kgEMass;          //MeV/c2
    const static qreal kgFm2M;           //fermi to meter
    const static qreal kgHardSphere;     //fm


    YSNucleus();
    YSNucleus(const YSIsotope & iso) ;
    virtual ~YSNucleus();

    YSWoodSaxon *   DensityProfile() const { return mDensityProfil; }
    QVector3D *     GetNucleons() const { return mNucleons; }
    qreal           HardSphere() { return 0.4; } //fm
    void            Print() const { qDebug() << A() << " " << Z(); }
    qreal           Radius() const { return mRadius; }
    qreal           RadiusMax() const { return mRadiusMax; }
    qreal           RadiusMean() const { return mRadiusMean; }
    void            SetDensityParam(qreal *val) { mKw = val[0]; mRho0 = val[1]; mSkin = val[2]; mRadiusMax = val[3]; }
    void            SetKw(qreal val)        { mKw   = val; }
    void            SetRadiusMax(qreal val) { mRadiusMax = val; }
    void            SetRho0(qreal val)      { mRho0 = val; }
    void            SetSkin(qreal val)      { mSkin = val; }

    static  YSNucleus * Proton()     { return (YSNucleus*)(YSPeriodicTable::Proton()) ;}
    static  YSNucleus * Neutron()     { return (YSNucleus*)(YSPeriodicTable::Neutron()) ;}

    inline  bool operator==(const YSNucleus& ) const ;
    inline  bool operator!=(const YSNucleus& ) const ;

private:

    void MakeDensityProfile();
    void MakeNucleus();

    YSWoodSaxon     *mDensityProfil; // density profile function
    qreal           mKw;             // density parameter > 0 if density max not at center
    QVector3D       *mNucleons;      // position of nucleons inside nucleus
    QRect           mNpos;           // needed ba Property Animation
    qreal           mRadius;         // nuclear radius (fm)
    qreal           mRadiusMax;      // radius up to which density profile is calculated
    qreal           mRadiusMean;     // radius at 10% of density
    qreal           mRho0;           // density parameter (fm-3)
    qreal           mSkin;           // skin thickness (fm)
    qint8           *mWounded;       // indicates if nucleon i wounded

};

inline bool YSNucleus::operator == (const YSNucleus& nucleus) const {
  return (nucleus.A()==A() && nucleus.Z()==Z()) ? true : false;
}

inline bool YSNucleus::operator != (const YSNucleus& nucleus) const {
  return (nucleus.A()!=A() || nucleus.Z()!=Z()) ? true : false;
}

#endif // YSNUCLEUS_H
