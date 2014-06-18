//
//  YSCollision.h
//  Collision class for A+A
//
//  Created by Yves Schutz on 09/12/13.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#ifndef YSCOLLISION_H
#define YSCOLLISION_H

#include <QObject>

class YSIsotope;
class YSNucleus;

class YSCollision : public QObject
{
    Q_OBJECT

public:
    YSCollision();
    virtual ~YSCollision();

public:
    qreal       Beta(int index) const;
    qreal       BMax() const { return mbMax; }
    qreal       BMin() const { return mbMin; }
    qreal       CMEnergy() const;
    qreal       CMEnergyNN() const; // in TeV
    qreal       CMEnergyNNGeV() const { return CMEnergyNN() * 1000.;} // in GeV
    qreal       BeamEnergy(int index)  const { return mEnergy[index-1]; }
    qreal       CrossSectionGeo() const;
    qreal       CrossSectionpp(qreal ecm, const QString type) const ;
    qreal       Gamma(int index) const ;
    qreal       Getb() const { return mb; }
    int         GetNcoll() const { return mNcoll; }
    int         GetNpart() const { return mNpart; }
    qreal       GetTAA() const { return mTAA; }
    void        MakeCollision();
    YSNucleus   *Nucleus(int index) const { return mNucleus[index-1]; }
    void        Print() const;
    void        Setb(qreal b) { mb    = b; }
    void        SetbMM();
    void        SetEnergies(qreal e1, qreal e2) {mEnergy[0] = e1; mEnergy[1]=e2;}
    void        SetNucleus(YSIsotope *);
    qreal       YBeam(int index) const ;

private:
    qreal     mb;           // impact parameter
    qreal     mbMax, mbMin; // max and min impact parameter value
    qreal     mEnergy[2];   // energy of each beam
    int       mNcoll;       // number of binary collisions
    int       mNpart;       // number of participants
    YSNucleus *mNucleus[2]; // colliding nuclei
    qreal     mTAA;         // nuclear overlap function

};

#endif // YSCOLLISION_H
