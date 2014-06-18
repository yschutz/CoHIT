//
//  YSGrid3dVector.cpp
//  A 3D Grid of float
//
//  Created by Yves Schutz on 02/06/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#include <stdlib.h>
#include <QDebug>
#include <QVector3D>

#include "YSGrid3dVector.h"

//______________________________________________________________________________
YSGrid3dVector::YSGrid3dVector(const unsigned int x, const unsigned int y, const unsigned int z) :
    YSGrid3d(x, y, z)
{
    // ctor
    mElements = new QVector3D[mDim];
    Clear();
}

//______________________________________________________________________________
YSGrid3dVector::YSGrid3dVector(const YSGrid3dVector &grid) :
    YSGrid3d(grid.mDimX, grid.mDimY, grid.mDimZ)
{
    // copy ctor
    mElements = new QVector3D[mDim];
    for(unsigned index = 0; index < mDim; index++)
        mElements[index] = grid.mElements[index];
}

//______________________________________________________________________________
YSGrid3dVector::~YSGrid3dVector()
{
    // dtor
    delete[] mElements;
}

//______________________________________________________________________________
void YSGrid3dVector::Add(const QVector3D addVal)
{
    // add a constant to elements of grid
    for (unsigned int index = 0; index < mDim; index++)
        mElements[index] += addVal;
}

//______________________________________________________________________________
void YSGrid3dVector::Add(YSGrid3dVector *grid, const float addVal)
{
    // add 2 grids
    if ( grid->mDim != mDim) {
        qDebug() << "ERROR YSGrid3dVector::Add: grids havs different dimensions!";
        abort();
    }

    for (unsigned int index = 0; index < mDim; index++)
        mElements[index] += grid->mElements[index] * addVal;
}

//______________________________________________________________________________
void YSGrid3dVector::Clear()
{
    // zero the Grid elements

    for(unsigned int index = 0; index < mDim; index++) {
        mElements[index].setX(0.0) ;
        mElements[index].setY(0.0) ;
        mElements[index].setZ(0.0) ;
    }
}

//______________________________________________________________________________
void YSGrid3dVector::Multiply(const float mult)
{
    // multiply by a constant
    for(unsigned int index = 0; index < mDim; index++)
        mElements[index] *= mult;

}

//______________________________________________________________________________
void YSGrid3dVector::Print() const
{
    // print the grid
    for(unsigned int index = 0; index < mDimX; index++)
        for(unsigned int indey = 0; indey < mDimY; indey++)
            for(unsigned int indez = 0; indez < mDimZ; indez++)
                qDebug() << QString("(%1, %2, %3) = (%4, %5, %6)").arg(index).arg(indey).arg(indez).
                            arg(Get(index, indey, indez).x()).arg(Get(index, indey, indez).y()).arg(Get(index, indey, indez).z());
}

//______________________________________________________________________________
void YSGrid3dVector::Resize(YSGrid3dVector *out, const unsigned int size)
{
    // resizes the grid into a new grid out by averaging over k cells

    const unsigned int dimX = mDimX / size;
    const unsigned int dimY = mDimY / size;
    const unsigned int dimZ = mDimZ / size;

    if ( out->DimX() != dimX || out->DimY() != dimY || out->DimZ() != dimY) {
        qDebug() << "YSGrid3dFloat::Resize: Fatal Error not matching grid size";
        exit(1);
    }

    QVector3D average(0., 0., 0.);

    for(unsigned int index = 0; index < dimX; index++)
        for(unsigned int indey = 0; indey < dimY; indey++)
            for(unsigned int indez = 0; indez < dimZ; indez++) {
                for(unsigned int indexx = index * size; indexx < (index + 1) * size; indexx++)
                    for(unsigned int indeyy = indey * size; indeyy < (indey + 1) * size; indeyy++)
                        for(unsigned int indezz = indez * size; indezz < (indez + 1) * size; indezz++)
                            average += Get(indexx, indeyy, indezz);
                average /= (size * size * size);
                out->Set(index, indey, indez, average);
                average.setX(0.0);
                average.setY(0.0);
                average.setZ(0.0);
            }
}
