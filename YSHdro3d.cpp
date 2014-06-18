//
//  YSHydro3d.cpp
//  A basic matrix class
//
//  Created by Yves Schutz on 15/05/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//
// inspired from https://github.com/mbellier/FluidSolver

#include <QDebug>
#include <QtMath>

#include "YSGrid3dFloat.h"
#include "YSGrid3dVector.h"
#include "YSHydro3d.h"

//______________________________________________________________________________
YSHydro3d::YSHydro3d(unsigned int dimx, unsigned int dimy, unsigned int dimz) :
    mDt(1.0), mViscosity(1.0E-5)
{
    // ctor

    mVelocity     = new YSGrid3dVector(dimx, dimy, dimz);
    mVelocityPrev = new YSGrid3dVector(dimx, dimy, dimz);
    mVelocitySrc  = new YSGrid3dVector(dimx, dimy, dimz);

    mDensity     = new YSGrid3dFloat(dimx, dimy, dimz);
    mDensityPrev = new YSGrid3dFloat(dimx, dimy, dimz);
    mDensitySrc  = new YSGrid3dFloat(dimx, dimy, dimz);

    mVelocity->Clear();
    mVelocityPrev->Clear();
    mVelocitySrc->Clear();

    mDensity->Clear();
    mDensityPrev->Clear();
    mDensitySrc->Clear();

}


//______________________________________________________________________________
YSHydro3d::~YSHydro3d()
{
    // dtor
    delete mVelocity;
    delete mVelocityPrev;
    delete mVelocitySrc;
    delete mDensity;
    delete mDensityPrev;
    delete mDensitySrc;
}

//______________________________________________________________________________
YSGrid3dFloat *YSHydro3d::GetDensity(YSHyType opt)
{
    // returns one of the density grid
    if ( opt == kCURRENT)
        return mDensity;
    else if (opt == kSOURCE)
        return mDensitySrc;
    else if (opt == kPREVIOUS)
        return mDensityPrev;
    else {
        qDebug() << QString("YSHydro3d::GetDensity: %1 is a wrong option").arg(opt);
        exit(1);
    }
}

//______________________________________________________________________________
YSGrid3dVector *YSHydro3d::GetVelocity(YSHyType opt)
{
    // returns one of the velocity grid
    if ( opt == kCURRENT)
        return mVelocity;
    else if (opt == kSOURCE)
        return mVelocitySrc;
    else if (opt == kPREVIOUS)
        return mVelocityPrev;
    else {
        qDebug() <<  QString("YSHydro3d::GetVelocity: %1 is a wrong option").arg(opt);
        return NULL;
    }
}

//______________________________________________________________________________
void YSHydro3d::SetDensity()
{
    // set the density on the grid

    for (unsigned int index = 0; index < mVelocity->DimX(); index++) {
        for (unsigned int indey = 0; indey < mVelocity->DimY(); indey++) {
            for (unsigned int indez = 0; indez < mVelocity->DimZ(); indez++) {
                qreal value = ((qreal)qrand() / (qreal)RAND_MAX) * 100;
                mDensityPrev->Set(index, indey, indez, value);
            }
        }
    }
}

//______________________________________________________________________________
void YSHydro3d::SetVelocity(QVector3D vL, QVector3D vT)
{
    // set the velocity on the grid from longitudinal and transverse velocity vector

    qreal vTLength = vT.length();
    for (unsigned int index = 0; index < mVelocity->DimX(); index++)
        for (unsigned int indey = 0; indey < mVelocity->DimY(); indey++)
            for (unsigned int indez = 0; indez < mVelocity->DimZ(); indez++) {
                qreal sign = (2 * ((qreal)qrand() / (qreal) RAND_MAX) - 1.0) > 0 ? 1 : -1 ;
                vL *= sign;
                qreal theta    = ((qreal)qrand() / (qreal)RAND_MAX) * 2 * M_PI;
                vT.setX(vTLength * qCos(theta));
                vT.setY(vTLength * qSin(theta));
                QVector3D velocity = vL + vT;
                mVelocityPrev->Set(index, indey, indez, velocity);
            }
}

//______________________________________________________________________________
void YSHydro3d::Advect(YSGrid3dVector *v1, YSGrid3dVector *v0, YSHydro3d::YSHyType opt)
{
    // this is the self advection of the velocity field

    unsigned int x = v1->DimX() - 2;
    unsigned int y = v1->DimY() - 2;
    unsigned int z = v1->DimZ() - 2;

    unsigned int dt0X = mDt * x;
    unsigned int dt0Y = mDt * y;
    unsigned int dt0Z = mDt * z;

    for(unsigned int index = 0; index <= x; index++) {
        for(unsigned int indey = 0; indey <= y; indey++) {
            for(unsigned int indez = 0; indez <= z; indez++) {
                qreal xx = index - dt0X * v0->Get(index, indey, indez).x();
                qreal yy = indey - dt0Y * v0->Get(index, indey, indez).y();
                qreal zz = indez - dt0Z * v0->Get(index, indey, indez).z();
                if (xx < 0.5)
                    xx = 0.5;
                if (xx > x + 0.5)
                    xx = x + 0.5;

                unsigned int x1 = xx, x2 = xx + 1;

                if (yy < 0.5)
                    yy = 0.5;
                if (y > y + 0.5)
                    yy = y + 0.5;

                unsigned int y1 = yy, y2 = yy + 1;

                if (zz < 0.5)
                    zz = 0.5;
                if (zz > z + 0.5)
                    zz = z + 0.5;

                unsigned int z1 = zz, z2 = zz + 1;

                qreal d111 = qSqrt( (xx - x1) * (xx - x1) +
                                  (yy - y1) * (yy - y1) +
                                  (zz - z1) * (zz - z1));

                qreal d121 = qSqrt( (xx - x1) * (xx - x1) +
                                  (yy - y2) * (yy - y2) +
                                  (zz - z1) * (zz - z1));

                qreal d211 = qSqrt( (xx - x2) * (xx - x2) +
                                  (yy - y1) * (yy - y1) +
                                  (zz - z1) * (zz - z1));

                qreal d221 = qSqrt( (xx - x2) * (xx - x2) +
                                  (yy - y2) * (yy - y2) +
                                  (zz - z1) * (zz - z1));

                qreal d112 = qSqrt( (xx - x1) * (xx - x1) +
                                  (yy - y1) * (yy - y1) +
                                  (zz - z2) * (zz - z2));

                qreal d122 = qSqrt( (xx - x1) * (xx - x1) +
                                  (yy - y2) * (yy - y2) +
                                  (zz - z2) * (zz - z2));

                qreal d212 = qSqrt( (xx - x2) * (xx - x2) +
                                  (yy - y1) * (yy - y1) +
                                  (zz - z2) * (zz - z2));

                qreal d222 = qSqrt( (xx - x2) * (xx - x2) +
                                  (yy - y2) * (yy - y2) +
                                  (zz - z2) * (zz - z2));

                QVector3D value(0.0, 0.0, 0.0);
                value += v0->Get(x1, y1, z1) * d111;
                value += v0->Get(x1, y2, z1) * d121;
                value += v0->Get(x2, y1, z1) * d211;
                value += v0->Get(x2, y2, z1) * d221;
                value += v0->Get(x1, y1, z2) * d112;
                value += v0->Get(x1, y2, z2) * d122;
                value += v0->Get(x2, y1, z2) * d212;
                value += v0->Get(x2, y2, z2) * d222;

                value /= (d111 + d121 + d211 + d221 + d112 + d122 + d212 + d222);

                v1->Set(index, indey, indez, value);
            }
        }
    }
    SetBoundaries(v1, opt);
}

//______________________________________________________________________________
void YSHydro3d::Advect(YSGrid3dFloat *d1, YSGrid3dFloat *d0, YSGrid3dVector *v, YSHydro3d::YSHyType opt)
{
    // Movement of the density of particules along the velocity field

    unsigned int x = d1->DimX() - 2;
    unsigned int y = d1->DimY() - 2;
    unsigned int z = d1->DimZ() - 2;

    unsigned int dt0X = mDt * x;
    unsigned int dt0Y = mDt * y;
    unsigned int dt0Z = mDt * z;

    for(unsigned int index = 1; index < x; index++) {
        for(unsigned int indey = 1; indey < y; indey++) {
            for (unsigned indez = 1; indez < z; indez++) {
                qreal xx = index - dt0X * v->Get(index, indey, indez).x();
                qreal yy = indey - dt0Y * v->Get(index, indey, indez).y();
                qreal zz = indez - dt0Z * v->Get(index, indey, indez).z();
                if (xx < 0.5)
                    xx = 0.5;
                if (xx > x + 0.5)
                    xx = x + 0.5;
                unsigned int x1 = xx, x2 = xx + 1;

                if (yy < 0.5)
                    yy = 0.5;
                if (y > y + 0.5)
                    yy = y + 0.5;

                unsigned int y1 = yy, y2 = yy + 1;

                if (zz < 0.5)
                    zz = 0.5;
                if (zz > z + 0.5)
                    zz = z + 0.5;

                unsigned int z1 = zz, z2 = zz + 1;

                qreal d111 = qSqrt( (xx - x1) * (xx - x1) +
                                  (yy - y1) * (yy - y1) +
                                  (zz - z1) * (zz - z1));

                qreal d121 = qSqrt( (xx - x1) * (xx - x1) +
                                  (yy - y2) * (yy - y2) +
                                  (zz - z1) * (zz - z1));

                qreal d211 = qSqrt( (xx - x2) * (xx - x2) +
                                  (yy - y1) * (yy - y1) +
                                  (zz - z1) * (zz - z1));

                qreal d221 = qSqrt( (xx - x2) * (xx - x2) +
                                  (yy - y2) * (yy - y2) +
                                  (zz - z1) * (zz - z1));

                qreal d112 = qSqrt( (xx - x1) * (xx - x1) +
                                  (yy - y1) * (yy - y1) +
                                  (zz - z2) * (zz - z2));

                qreal d122 = qSqrt( (xx - x1) * (xx - x1) +
                                  (yy - y2) * (yy - y2) +
                                  (zz - z2) * (zz - z2));

                qreal d212 = qSqrt( (xx - x2) * (xx - x2) +
                                  (yy - y1) * (yy - y1) +
                                  (zz - z2) * (zz - z2));

                qreal d222 = qSqrt( (xx - x2) * (xx - x2) +
                                  (yy - y2) * (yy - y2) +
                                  (zz - z2) * (zz - z2));

                qreal value = 0.0;
                value += d0->Get(x1, y1, z1) * d111;
                value += d0->Get(x1, y2, z1) * d121;
                value += d0->Get(x2, y1, z1) * d211;
                value += d0->Get(x2, y2, z1) * d221;
                value += d0->Get(x1, y1, z2) * d112;
                value += d0->Get(x1, y2, z2) * d122;
                value += d0->Get(x2, y1, z2) * d212;
                value += d0->Get(x2, y2, z2) * d222;

                value /= (d111 + d121 + d211 + d221 + d112 + d122 + d212 + d222);

                d1->Set(index, indey, indez, value);
            }
        }
    }
    SetBoundaries(d1, opt);
}

//______________________________________________________________________________
void YSHydro3d::Diffuse(YSGrid3dVector *v1, YSGrid3dVector *v0, YSHyType mode)
{
    // diffusion of the velocity grid

    const unsigned int numberOfIterations = 10;

    qreal a = mDt * mViscosity * (v1->DimX() - 2) * (v1->DimY() - 2) * (v1->DimZ() - 2);
    for (unsigned int loop = 0; loop < numberOfIterations; loop++) {
        for (unsigned int index = 1; index <= v1->DimX() - 2; index++) {
            for (unsigned int indey = 1; indey <= v1->DimY() - 2; indey++) {
                for (unsigned int indez = 1; indez <= v1->DimZ() - 2; indez++) {
                    if (a == 0)
                        v1->Set(index, indey, indez, v0->Get(index, indey, indez));
                    else {
                        QVector3D value = v1->Get(index - 1, indey,     indez - 1) +
                                v1->Get(index + 1, indey,     indez - 1) +
                                v1->Get(index,     indey - 1, indez - 1) +
                                v1->Get(index,     indey + 1, indez - 1) +
                                //
                                v1->Get(index - 1, indey,     indez + 1) +
                                v1->Get(index + 1, indey,     indez + 1) +
                                v1->Get(index,     indey - 1, indez + 1) +
                                v1->Get(index,     indey + 1, indez + 1) +
                                //
                                v1->Get(index - 1, indey - 1, indez    ) +
                                v1->Get(index + 1, indey - 1, indez    ) +
                                v1->Get(index - 1, indey + 1, indez    ) +
                                v1->Get(index + 1, indey + 1, indez    ) +
                                //
                                v1->Get(index,     indey - 1, indez + 1) +
                                v1->Get(index,     indey - 1, indez - 1) +
                                v1->Get(index,     indey,     indez - 1) +
                                v1->Get(index,     indey,     indez + 1) ;
                        //

                        v1->Set(index, indey, indez, (v0->Get(index, indey, indez) + a * value) / ( 1 + 16 * a));
                    }
                }

            }
        }
        SetBoundaries(v1, mode);
    }
}

//______________________________________________________________________________
void YSHydro3d::Diffuse(YSGrid3dFloat *d1, YSGrid3dFloat *d0, YSHydro3d::YSHyType mode)
{
    // diffusion of the density grid

    const unsigned int numberOfIterations = 10;

    qreal a = mDt * mViscosity * (d1->DimX() - 2) * (d1->DimY() - 2) * (d1->DimZ() - 2);

    for(unsigned int loop = 0; loop < numberOfIterations; loop++) {
        for(unsigned int index = 1; index <= d1->DimX() - 2; index++) {
            for(unsigned int indey = 1; indey <= d1->DimY() - 2; indey++) {
                for(unsigned int indez = 1; indez < d1->DimZ() - 2; indez++) {
                    if ( a == 0)
                        d1->Set(index, indey, indez, d0->Get(index, indey, indez));
                    else {
                        qreal value = d1->Get(index - 1, indey, indez - 1) +
                                d1->Get(index + 1, indey,     indez - 1) +
                                d1->Get(index,     indey - 1, indez - 1) +
                                d1->Get(index,     indey + 1, indez - 1) +
                                //
                                d1->Get(index - 1, indey,     indez + 1) +
                                d1->Get(index + 1, indey,     indez + 1) +
                                d1->Get(index,     indey - 1, indez + 1) +
                                d1->Get(index,     indey + 1, indez + 1) +
                                //
                                d1->Get(index - 1, indey - 1, indez    ) +
                                d1->Get(index + 1, indey - 1, indez    ) +
                                d1->Get(index - 1, indey + 1, indez    ) +
                                d1->Get(index + 1, indey + 1, indez    ) +
                                //
                                d1->Get(index,     indey - 1, indez + 1) +
                                d1->Get(index,     indey - 1, indez - 1) +
                                d1->Get(index,     indey,     indez - 1) +
                                d1->Get(index,     indey,     indez + 1) ;
                        //
                        d1->Set(index, indey, indez, (d0->Get(index, indey, indez) + a * value) / ( 1 + 16 * a));
                    }
                }
            }
        }
        SetBoundaries(d1, mode);
    }
}

//______________________________________________________________________________
void YSHydro3d::Project(YSGrid3dVector *vel, YSGrid3dVector *vel0)
{
    // project: compute the velocity field
    qreal normX = 1.0 / ( 2 * (vel->DimX() - 2));
    qreal normY = 1.0 / ( 2 * (vel->DimY() - 2));
    qreal normZ = 1.0 / ( 2 * (vel->DimZ() - 2));
    for (unsigned int index = 1; index <= vel->DimX() - 2; index++) {
        for (unsigned int indey = 1; indey <= vel->DimY() - 2; indey++) {
            for (unsigned int indez = 1; indez <= vel->DimZ() - 2; indez++) {
                qreal value = -normX * (vel->Get(index - 1, indey, indez).x() - vel->Get(index + 1, indey, indez).x())
                              -normY * (vel->Get(index, indey - 1, indez).y() + vel->Get(index, indey + 1, indez).y())
                              -normZ * (vel->Get(index, indey, indez - 1).z() + vel->Get(index, indey, indez + 1).z());
                vel0->Get(index, indey, indez).setX(0.0);
                vel0->Get(index, indey, indez).setY(0.0);
                vel0->Get(index, indey, indez).setZ(value);
            }
        }
    }

    for(unsigned int k = 0; k < 10; k++) {
        for (unsigned int index = 1; index <= vel->DimX() - 2; index++) {
            for (unsigned int indey = 1; indey <= vel->DimY() - 2; indey++) {
                for (unsigned int indez = 1; indez <= vel->DimZ() - 2; indez++) {
                    qreal value = (vel0->Get(index, indey, indez).z() +
                                   vel0->Get(index - 1, indey, indez).y() - vel0->Get(index + 1, indey, indez).y() +
                                   vel0->Get(index, indey - 1, indez).y() + vel0->Get(index, indey + 1, indez).y() +
                                   vel0->Get(index, indey, indez - 1).y() + vel0->Get(index, indey, indez + 1).y()) / 6.0;
                    vel0->Get(index, indey, indez).setY(value);
                }
            }
        }
    }

    for(unsigned int k = 0; k < 10; k++) {
        for (unsigned int index = 1; index <= vel->DimX() - 2; index++) {
            for (unsigned int indey = 1; indey <= vel->DimY() - 2; indey++) {
                for (unsigned int indez = 1; indez <= vel->DimZ() - 2; indez++) {
                    qreal value = (vel0->Get(index, indey, indez).y() +
                                   vel0->Get(index - 1, indey, indez).x() - vel0->Get(index + 1, indey, indez).x() +
                                   vel0->Get(index, indey - 1, indez).x() + vel0->Get(index, indey + 1, indez).x() +
                                   vel0->Get(index, indey, indez - 1).x() + vel0->Get(index, indey, indez + 1).x()) / 6.0;
                    vel0->Get(index, indey, indez).setX(value);
                }
            }
        }
        SetBoundaries(vel0, kBORDERSNOWRAP);
    }

    for (unsigned int index = 1; index <= vel->DimX() - 2; index++) {
        for (unsigned int indey = 1; indey <= vel->DimY() - 2; indey++) {
            for (unsigned int indez = 1; indez <= vel->DimZ() - 2; indez++) {
                qreal value = (vel0->Get(index + 1, indey, indez).x() + vel0->Get(index - 1, indey, indez).x()) / normX;
                vel->Get(index, indey, indez).setX(vel->Get(index, indey, indez).x() + value);

                value = (vel0->Get(index + 1, indey, indez).x() + vel0->Get(index - 1, indey, indez).x()) / normY;
                vel->Get(index, indey, indez).setY(vel->Get(index, indey, indez).y() + value);

                value = (vel0->Get(index, indey, indez + 1).x() + vel0->Get(index, indey, indez - 1).x()) / normY;
                vel->Get(index, indey, indez).setZ(vel->Get(index, indey, indez).z() + value);
            }
        }
    }
    SetBoundaries(vel, kBORDERSXYWRAP);
}

//______________________________________________________________________________
void YSHydro3d::SetBoundaries(YSGrid3dFloat *dens, YSHydro3d::YSHyType mode)
{
    // Set the boundaries for dens grid
    unsigned int x = dens->DimX(), y = dens->DimY(), z = dens->DimZ();
    if (mode == kBORDERSDENSLOOP) {
        for (unsigned int index = 1; index < x - 1; index++) {
            dens->Set(index, 0,     0,     dens->Get(index,     y - 2, z - 2));
            dens->Set(index, 0,     z - 1, dens->Get(index, y - 2,     1    ));

            dens->Set(index, y - 1, 0,     dens->Get(index, 1,         z - 2));
            dens->Set(index, y - 1, z - 1, dens->Get(index, 1,         1    ));
        }
        for (unsigned int indey = 1; indey < y - 1; indey++) {
            dens->Set(0,     0,     0,     dens->Get(x - 2, indey, z - 2));
            dens->Set(0,     0,     z - 1, dens->Get(x - 2,     indey, 1    ));

            dens->Set(x - 1, 0,     0,     dens->Get(1, indey, z - 2));
            dens->Set(x - 1, 0,     z - 1, dens->Get(1, indey, 1    ));
        }
        for (unsigned int indez = 1; indez < z - 1; indez++) {
            dens->Set(0,     0,     indez, dens->Get(x - 2, y - 2, indez));
            dens->Set(0,     y - 1, indez, dens->Get(x - 2, 1    , indez));

            dens->Set(x - 1, 0,     indez, dens->Get(1, y - 2, indez));
            dens->Set(x - 1, y - 1, indez, dens->Get(1, 1,     indez));
        }
        qreal value = (dens->Get(1, 0, 0) + dens->Get(0, 1, 0) + dens->Get(0, 0, 1)) / 3.0;
        dens->Set(0, 0, 0, value);

        value = (dens->Get(1, y - 1, 0) + dens->Get(0, y - 2, 0) + dens->Get(1, y - 1, 1)) / 3.0;
        dens->Set(0, y - 1, 0, value);

        value = (dens->Get(x - 2, 0, 0) + dens->Get(x - 1, 0, 0) + dens->Get(x - 1, 0, 1)) / 3.0;
        dens->Set(x - 1, 0, 0, value);

        value = (dens->Get(x - 2, y - 1, 0) + dens->Get(x - 1, y - 2, 0) + dens->Get(x - 1, y - 1, 1)) / 3.0;
        dens->Set(x - 1, y - 1, 0, value);
        //
        value = (dens->Get(1, 0, z - 2) + dens->Get(0, 1, z - 2) + dens->Get(0, 0, z - 1)) / 3.0;
        dens->Set(0, 0, z - 1, value);

        value = (dens->Get(1, y - 1, z - 2) + dens->Get(0, y - 2, z - 2) + dens->Get(1, y - 1,  z - 1)) / 3.0;
        dens->Set(0, y - 1, z - 1, value);

        value = (dens->Get(x - 2, 0, z - 2) + dens->Get(x - 1, 0, z - 2) + dens->Get(x - 1, 0,  z - 1)) / 3.0;
        dens->Set(x - 1, 0, z - 1, value);

        value = (dens->Get(x - 2, y - 1, z - 2) + dens->Get(x - 1, y - 2, z - 2) + dens->Get(x - 1, y - 1, z - 1)) / 3.0;
        dens->Set(x - 1, y - 1, z - 1, value);

    } else if (mode == kBORDERSDENSWELL) {
        qreal zero = 0.0;
        for (unsigned int index = 1; index < x -1; index++) {
            dens->Set(index, 0,     0,    zero);
            dens->Set(index, y - 1, 0,    zero);
            dens->Set(index, 0,     z -1, zero);
            dens->Set(index, y - 1, z -1, zero);
        }
        for (unsigned int indey = 1; indey < y -1; indey++) {
            dens->Set(0,    indey, 0,     zero);
            dens->Set(x -1, indey, 0,     zero);
            dens->Set(0,    indey, z - 1, zero);
            dens->Set(x -1, indey, z - 1, zero);
        }
        for (unsigned int indez = 1; indez < z -1; indez++) {
            dens->Set(0,    0,     indez, zero);
            dens->Set(x -1, 0,     indez, zero);
            dens->Set(0,    y - 1, indez, zero);
            dens->Set(x -1, y - 1, indez, zero);
        }
        dens->Set(0,     0,     0,     zero);
        dens->Set(0,     y - 1, 0,     zero);
        dens->Set(x - 1, 0,     0,     zero);
        dens->Set(x - 1, y - 1, 0,     zero);
        dens->Set(0,     0,     z - 1, zero);
        dens->Set(0,     y - 1, z - 1, zero);
        dens->Set(x - 1, 0,     z - 1, zero);
        dens->Set(x - 1, y - 1, z - 1, zero);
    }
}

//______________________________________________________________________________
void YSHydro3d::SetBoundaries(YSGrid3dVector *vel, YSHyType mode)
{
    // Set the boundaries for velocity grid
    // 0 : no wrapping, 1 : x-wrap,  : y-wrap

    unsigned int x = vel->DimX(), y = vel->DimY(), z = vel->DimZ();
    if (mode == kBORDERSNOWRAP) {
        for (unsigned int index = 1; index < x - 1; index++) {
            vel->Set(index, 0,     0,    vel->Get(index, 1, 1));
            vel->Set(index, 0,     z -1, vel->Get(index, 1, z - 2));

            vel->Set(index, y - 1,  0,     vel->Get(index, y - 2, 1));
            vel->Set(index, y - 1,  z - 1, vel->Get(index, y - 2, z - 2));
        }
        for (unsigned int indey = 1; indey < y - 1; indey++) {
            vel->Set(0, indey,     0,    vel->Get(1,     indey, 1));
            vel->Set(0, indey,     z -1, vel->Get(x - 2, indey, z - 2));

            vel->Set(0,     indey, 0,     vel->Get(1,     indey, 1));
            vel->Set(x - 1, indey, z - 1, vel->Get(x - 2, indey, z - 2));
        }
        for (unsigned int indez = 1; indez < z - 1; indez++) {
            vel->Set(0, 0,     indez,    vel->Get(1, 1,  indez));
            vel->Set(0, y - 1, indez,    vel->Get(1, y - 2,  indez));

            vel->Set(x - 1, 0,     indez,    vel->Get(x - 2, 1,  indez));
            vel->Set(x - 1, y - 1, indez,    vel->Get(x - 2, y - 2,  indez));
        }

    } else if (mode == kBORDERSXYWRAP) {
        for (unsigned int index = 1; index < x - 1; index++) {
            vel->Get(index, 0, 0).setX( vel->Get(index, 1, 1).x());
            vel->Get(index, 0, 0).setY(-vel->Get(index, 1,1).y());
            vel->Get(index, 0, 0).setZ(-vel->Get(index, 1,1).z());

            vel->Get(index, y - 1, 0).setX( vel->Get(index, y - 2, 1).x());
            vel->Get(index, y - 1, 0).setY(-vel->Get(index, y - 2, 1).y());
            vel->Get(index, y - 1, 0).setZ(-vel->Get(index, y - 2, 1).z());

            vel->Get(index, 0, z - 1).setX( vel->Get(index, 1, z - 2).x());
            vel->Get(index, 0, z - 1).setY(-vel->Get(index, 1, z - 2).y());
            vel->Get(index, 0, z - 1).setZ(-vel->Get(index, 1, z - 2).z());

            vel->Get(index, y - 1, z - 1).setX( vel->Get(index, y - 2, z - 2).x());
            vel->Get(index, y - 1, z - 1).setY(-vel->Get(index, y - 2, z - 2).y());
            vel->Get(index, y - 1, z - 1).setZ(-vel->Get(index, y - 2, z - 2).z());
        }
        for (unsigned int indey = 1; indey < y - 1; indey++) {
            vel->Get(0, indey, 0).setX(-vel->Get(1, indey, 1).x());
            vel->Get(0, indey, 0).setY( vel->Get(1, indey, 1).y());
            vel->Get(0, indey, 0).setZ(-vel->Get(1, indey, 1).z());

            vel->Get(x - 1, indey, 0).setX(-vel->Get(x - 2, indey, 1).x());
            vel->Get(x - 1, indey, 0).setY( vel->Get(x - 2, indey, 1).y());
            vel->Get(x - 1, indey, 0).setZ(-vel->Get(x - 2, indey, 1).z());

            vel->Get(0, indey, z - 1).setX(-vel->Get(1, indey, z - 2).x());
            vel->Get(0, indey, z - 1).setY( vel->Get(1, indey, z - 2).y());
            vel->Get(0, indey, z - 1).setZ(-vel->Get(1, indey, z - 2).z());

            vel->Get(x - 1, indey, z - 1).setX(-vel->Get(x - 2, indey, z - 2).x());
            vel->Get(x - 1, indey, z - 1).setY( vel->Get(x - 2, indey, z - 2).y());
            vel->Get(x - 1, indey, z - 1).setZ(-vel->Get(x - 2, indey, z - 2).z());
        }
        for (unsigned int indez = 1; indez < z - 1; indez++) {
            vel->Get(0, 0, indez).setX(-vel->Get(1, 1, indez).x());
            vel->Get(0, 0, indez).setY(-vel->Get(1, 1, indez).y());
            vel->Get(0, 0, indez).setZ( vel->Get(1, 1, indez).z());

            vel->Get(x - 1, 0, indez).setX(-vel->Get(x - 2, 1, indez).x());
            vel->Get(x - 1, 0, indez).setY(-vel->Get(x - 2, 1, indez).y());
            vel->Get(x - 1, 0, indez).setZ( vel->Get(x - 2, 1, indez).z());

            vel->Get(0, y - 1, indez).setX(-vel->Get(1, y - 2, indez).x());
            vel->Get(0, y - 1, indez).setY(-vel->Get(1, y - 2, indez).y());
            vel->Get(0, y - 1, indez).setZ( vel->Get(1, y - 2, indez).z());

            vel->Get(x - 1, y - 1, indez).setX(-vel->Get(x - 2, y - 2, indez).x());
            vel->Get(x - 1, y - 1, indez).setY(-vel->Get(x - 2, y - 2, indez).y());
            vel->Get(x - 1, y - 1, indez).setZ( vel->Get(x - 2, y - 2, indez).z());
        }
    }
    QVector3D value = (vel->Get(1, 0, 0) + vel->Get(0, 1, 0) + vel->Get(0, 0, 1)) / 3.0;
    vel->Set(0, 0, 0, value);
    value = (vel->Get(1, y - 1, 0) + vel->Get(0, y - 2, 0) + vel->Get(0, y - 1, 1)) / 3.0;
    vel->Set(0, y - 1, 0, value);
    value = (vel->Get(x - 2, 0, 0) + vel->Get(x - 1, 1, 0) + vel->Get(x - 1, 0, 1)) / 3.0;
    vel->Set(x - 1, 0, 0, value);
    value = (vel->Get(x - 2, y - 1, 0) + vel->Get(x - 1, y - 2, 0) + vel->Get(x - 1, y - 1, 1)) / 3.0;
    vel->Set(x - 1, y - 1, 0, value);

    value = (vel->Get(1, 0, z - 2) + vel->Get(0, 1, z - 2) + vel->Get(0, 0, z - 2)) / 3.0;
    vel->Set(0, 0, z - 1, value);
    value = (vel->Get(1, y - 1, z - 2) + vel->Get(0, y - 2, z - 2) + vel->Get(0, y - 1, z - 2)) / 3.0;
    vel->Set(0, y - 1, z - 1, value);
    value = (vel->Get(x - 2, 0, z - 2) + vel->Get(x - 1, 1, z - 2) + vel->Get(x - 1, 0, z - 2)) / 3.0;
    vel->Set(x - 1, 0, z - 1, value);
    value = (vel->Get(x - 2, y - 1, z - 2) + vel->Get(x - 1, y - 2, z - 2) + vel->Get(x - 1, y - 1, z - 2)) / 3.0;
    vel->Set(x - 1, y - 1, z - 1, value);
}

//______________________________________________________________________________
void YSHydro3d::Step(YSGrid3dVector *v1, YSGrid3dVector *v0)
{
    // update the velocity grid following a step of dt

    v1->Add(v0, mDt);
    YSGrid3dVector *temp = v1;
    v1 = v0;
    v0 = temp;
    Diffuse(v1, v0, kBORDERSXYWRAP);
    Project(v1, v0);
    temp = v1;
    v1 = v0;
    v0 = temp;
    Advect(v1, v0, kBORDERSXYWRAP);
    Project(v1, v0);
}

//______________________________________________________________________________
void YSHydro3d::Step(YSGrid3dFloat *d1, YSGrid3dFloat *d0, YSGrid3dVector *v)
{
    // update the density grid following a step of dt

  d1->Add(d0, mDt);
  YSGrid3dFloat *temp = d1;
  d1 = d0;
  d0 = temp;
  Diffuse(d1, d0, YSHydro3d::kBORDERSNOWRAP);
  temp = d1;
  d1 = d0;
  d0 = temp;
  Advect(d1, d0, v, YSHydro3d::kBORDERSNOWRAP);
}
