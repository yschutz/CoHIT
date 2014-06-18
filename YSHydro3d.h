//
//  YSHydro3d.h
//  A basic matrix class
//
//  Created by Yves Schutz on 15/05/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//
// inspired from https://github.com/mbellier/FluidSolver

#ifndef YSHYDRO3D_H
#define YSHYDRO3D_H

class QVector3D;

class YSGrid3dFloat;
class YSGrid3dVector;

class YSHydro3d
{
public:
    explicit YSHydro3d(unsigned int dimx, unsigned int dimy, unsigned int dimz);
             ~YSHydro3d();

    enum YSHyType {
        kCURRENT, kPREVIOUS, kSOURCE,
        kBORDERSNOWRAP, kBORDERSXYWRAP, kBORDERSDENSLOOP, kBORDERSDENSWELL
    };

    YSGrid3dFloat  *GetDensity(YSHyType opt = kCURRENT);
    YSGrid3dVector *GetVelocity(YSHyType opt = kCURRENT);
    void           SetDensity();
    void           SetDt(qreal val) { mDt = val; }
    void           SetVelocity(QVector3D vL, QVector3D vT);
    void           SetViscosity(qreal val) { mViscosity = val; }
    void           Step(YSGrid3dVector *v1, YSGrid3dVector *v0);
    void           Step(YSGrid3dFloat  *d1, YSGrid3dFloat  *d0, YSGrid3dVector *v);

private:
    void Advect(YSGrid3dVector *v1, YSGrid3dVector *v0, YSHyType opt);
    void Advect(YSGrid3dFloat *d1, YSGrid3dFloat *d0, YSGrid3dVector *v, YSHyType opt);
    void Diffuse(YSGrid3dVector *v1, YSGrid3dVector *v0, YSHyType mode);
    void Diffuse(YSGrid3dFloat *d1, YSGrid3dFloat *d0, YSHyType mode);
    void Project(YSGrid3dVector *v, YSGrid3dVector *vel0);
    void SetBoundaries(YSGrid3dFloat * dens, YSHyType mode);
    void SetBoundaries(YSGrid3dVector * vel, YSHyType mode);

    YSGrid3dFloat  *mDensity, *mDensityPrev, *mDensitySrc;    // grids of density
    qreal          mDt;
    YSGrid3dVector *mVelocity, *mVelocityPrev, *mVelocitySrc; // grids of velocity vectors
    qreal          mViscosity;
};

#endif // YSHYDRO3D_H
