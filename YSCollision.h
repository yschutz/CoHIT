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
    qreal       CMEnergy() const;
    qreal       CMEnergyNN() const;
    qreal       BeamEnergy(int index)  const { return mEnergy[index-1]; }
    qreal       CrossSectionGeo() const;
    qreal       CrossSectionpp(qreal ecm, const QString type) const ;
    qreal       Gamma(int index) const ;
    qreal       Getb() const { return mb; }
    void        MakeCollision();
    YSNucleus   *Nucleus(int index) const { return mNucleus[index-1]; }
    void        Print() const;
    void        Setb(qreal b) { mb = b; }
    void        SetEnergies(qreal e1, qreal e2) {mEnergy[0] = e1; mEnergy[1]=e2;}
    void        SetNucleus(YSIsotope *);
    qreal       YBeam(int index) const ;

private:
    qreal     mb;           // impact parameter
    qreal     mEnergy[2];   // energy of each beam
    YSNucleus *mNucleus[2]; // colliding nuclei

};

#endif // YSCOLLISION_H
