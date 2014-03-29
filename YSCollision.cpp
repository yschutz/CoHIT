//
//  YSCollision.cpp
//  Collision class for A+A
//
//  Created by Yves Schutz on 09/12/13.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#include <QDebug>
#include <QtMath>

#include "YSCollision.h"
#include "YSCrossSectionpp.h"
#include "YSNucleus.h"

//______________________________________________________________________________
YSCollision::YSCollision() : mb(0.0)
{
    mNucleus[0] = new YSNucleus();
    mNucleus[1] = new YSNucleus();
    mEnergy[0]  = 0.0;
    mEnergy[1]  = 0.0;

    MakeCollision();
}

//______________________________________________________________________________
YSCollision::~YSCollision()
{
    delete mNucleus[0];
    delete Nucleus(1);
}

//______________________________________________________________________________
qreal YSCollision::Beta(int id) const
{
    // calculates velocity of beam: beta = p/E

   qreal m = 0.0, p = 0.0, e = 0.0  ;
   qreal rv = -1.0 ;

   if (id == 1) {
     m = Nucleus(1)->Mass(YSIsotope::U_TEV) ; // in TeV
     p = BeamEnergy(1) * Nucleus(1)->A() ;
   }
   else if (id == 2) {
     m = Nucleus(2)->Mass(YSIsotope::U_TEV) ; // in TeV
     p = BeamEnergy(2) * Nucleus(2)->A() ;
   }
   e = qSqrt(p * p + m * m) ;
   if (e != 0 )
     rv = p / e ;

   return rv  ;
}

//______________________________________________________________________________
qreal YSCollision::CMEnergy() const
{
    // calculate center of mass energy of the collision Ecm = (m1^2+m2^2 + 2E1E2(1-beta1*beta2*cos(theta)))^1/2; theta = 180°

    qreal m1 = Nucleus(1)->Mass(YSIsotope::U_TEV) ;
    qreal m2 = Nucleus(2)->Mass(YSIsotope::U_TEV) ;

    qreal p1 = BeamEnergy(1) * Nucleus(1)->A() ;
    qreal p2 = BeamEnergy(2) * Nucleus(2)->A() ;

    qreal e1 = qSqrt(m1 * m1 + p1 * p1) ;
    qreal e2 = qSqrt(m2 * m2 + p2 * p2) ;

    qreal ecm = qSqrt( m1 * m1 + m2 * m2 + 2 * e1 * e2 * (1 + Beta(1) * Beta(2)) ) ;

    return ecm ;
}

//______________________________________________________________________________
qreal YSCollision::CMEnergyNN() const
{
    // calculates the  nuclean-nucleon center of mass energy Ecm = (m1^2+m2^2 + 2E1E2(1-beta1*beta2*cos(theta)))^1/2; theta = 180°

    qreal m1 = Nucleus(1)->Mass(YSIsotope::U_TEV) / Nucleus(1)->A() ;
    qreal m2 = Nucleus(2)->Mass(YSIsotope::U_TEV) / Nucleus(2)->A() ;
    qreal e1 = qSqrt(m1 * m1 + BeamEnergy(1) * BeamEnergy(1)) ;
    qreal e2 = qSqrt(m2 * m2 + BeamEnergy(2) * BeamEnergy(2)) ;

    qreal ecm = qSqrt( m1 * m1 + m2 * m2 + 2 * e1 * e2 * (1 + Beta(1) * Beta(2)) ) ;

    return ecm ;
}

qreal YSCollision::CrossSectionGeo() const
{
    // Geometric cross section
    return 1E-2 * M_PI * qPow(Nucleus(1)->Radius() + Nucleus(2)->Radius(), 2);
}

//______________________________________________________________________________
//qreal YSCollision::CrossSectionpp(qreal ecm, const QString type) const
//{
//    // calculates the pp cross section from systematics data in mb
//    // energy (√s) in GeV


//    qreal rv = 0.0 ;
//    qreal ecm2 = ecm * ecm;

//    if (type.compare("total") == 0) {
//        //[0]+[1]*pow(x*x,[2])+[3]*pow(log(x*x/[4]),2.)+[5]*pow(x*x,[6]) ;
//        qreal par[7] = {3.55E1, 4.259E1, -4.6E-1, 3.076E-1, 2.92E1, -3.336E1, -5.454E-1} ;
//        rv = par[0]+par[1]*qPow(ecm2,par[2])+par[3]*qPow(qLn(ecm2/par[4]),2.)+par[5]*qPow(ecm2,par[6]);
//    }
//    else if (type.compare("elastic") == 0) {
//        //[0]+[1]*pow(x*x,[2])+[3]*pow(log(x*x/[4]),2.)
//        qreal par[5] = {5.166342, 1.287805E1, -4.059868E-1, 9.028824E-2, 2.92E1} ;
//        rv = par[0]+par[1]*qPow(ecm2,par[2])+par[3]*qPow(qLn(ecm2/par[4]),2.);
//    }
//    else if (type.compare("inelastic") == 0) {
//        //[0]+[1]*pow(x*x,[2])+[3]*pow(log(x*x/[4]),2.)+[5]*pow(x*x,[6]))-([7]+[8]*pow(x*x,[9])+[10]*pow(log(x*x/[11]),2.)+[12]*pow(x*x,[13]))
//        qreal par[14] = {35.5, 42.59, -0.46, 0.3076, 29.2, -33.36, -0.5454, 5.166342, 12.87805, -0.4059868, 0.09028824, 29.2, 0.0, 0.0};
//        rv = (par[0]+par[1]*qPow(ecm2,par[2])+par[3]*qPow(qLn(ecm2/par[4]),2.)+par[5]*qPow(ecm2,par[6]))-
//                (par[7]+par[8]*qPow(ecm2,par[9])+par[10]*qPow(qLn(ecm2/par[11]),2.)+par[12]*qPow(ecm2,par[13]));
//    } else {
//        qCritical() << QString("%1::GetppCrossSection: option error, choose among total, elastic, inelastic").arg(objectName());
//    }
//    return rv ; // mbarn
//}

//______________________________________________________________________________
qreal YSCollision::Gamma(int id) const
{
    // Lorentz gamma factor : γ = 1/√(1-β**2); L = L0/γ

    return (1 / qSqrt(1-Beta(id)*Beta(id))) ;
}

//______________________________________________________________________________
void YSCollision::MakeCollision()
{
    // Nuclei collide, mark wounded nucleons
    YSCrossSectionpp cspp;
    cspp.SetType(YSCrossSectionpp::kInelastic);
}

//______________________________________________________________________________
void YSCollision::Print() const
{
    // print some information on the collising system
    qDebug() << Nucleus(1)->A() << " + " << Nucleus(2)->A();
}

//______________________________________________________________________________
void YSCollision::SetNucleus(YSIsotope *iso)
{
    // set one of the two nuclei of the colliding system
    static int count = 0;
    if(count > 1)
        count = 0;
    delete mNucleus[count];
    mNucleus[count] = new YSNucleus(*iso);
    count++;
}

//______________________________________________________________________________
qreal YSCollision::YBeam(int index) const
{
    //Calculates beta max of beam

    YSNucleus * nuc = NULL;
    qreal energy = 0.0;

    if (index == 1) {
        nuc    = Nucleus(1);
        energy = BeamEnergy(1);
    }
    else if (index == 2) {
        nuc    = Nucleus(2);
        energy = BeamEnergy(2);
    }
    else
        return 0.0 ;

    qreal m = nuc->Mass(YSIsotope::U_TEV) ;

    qreal p = energy * nuc->A() ;

    qreal e = qSqrt(m * m + p * p) ;

    qreal yBeam = 0.5 * log( (e-p) / (e+p) ) ;

    if (mNucleus[0] == mNucleus[1])
        return qAbs(yBeam) ;
    else
        return yBeam ;
}
