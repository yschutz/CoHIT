//
//  YSGrid3dFloat.cpp
//  A 3D Grid of float
//
//  Created by Yves Schutz on 02/06/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#include <stdlib.h>
#include <QDebug>

#include "YSGrid3d.h"
#include "YSGrid3dFloat.h"

//______________________________________________________________________________
YSGrid3dFloat::YSGrid3dFloat(const unsigned int x, const unsigned int y, const unsigned int z) :
    YSGrid3d(x, y,z)
{
    // ctor
    mElements = new qreal[mDim];
    Clear();
}

//______________________________________________________________________________
YSGrid3dFloat::YSGrid3dFloat(const YSGrid3dFloat &grid) :
    YSGrid3d(grid.mDimX, grid.mDimY, grid.mDimZ)
{
    // copy ctor
    mElements = new qreal[mDim];
    for(unsigned index = 0; index < mDim; index++)
        mElements[index] = grid.mElements[index];
}

//______________________________________________________________________________
YSGrid3dFloat::~YSGrid3dFloat()
{
    // dtor
    delete[] mElements;
}

//______________________________________________________________________________
void YSGrid3dFloat::Add(const qreal addVal)
{
    // add a constant to elements of grid
    for (unsigned int index = 0; index < mDim; index++)
        mElements[index] += addVal;
}

//______________________________________________________________________________
void YSGrid3dFloat::Add(YSGrid3dFloat *grid, const qreal val)
{
    // add 2 grids
    if ( grid->mDim != mDim) {
        qDebug() << "ERROR YSGrid3dFloat::Add: grids havs different dimensions!";
        abort();
    }

    for (unsigned int index = 0; index < mDim; index++)
        mElements[index] += grid->mElements[index] * val;
}

//______________________________________________________________________________
void YSGrid3dFloat::Clear()
{
    // zero the Grid elements

    for(unsigned int index = 0; index < mDim; index++)
        mElements[index] = 0.0;
}

//______________________________________________________________________________
qreal YSGrid3dFloat::GetMax() const
{
    // search maximum value on the grid
    qreal max = -9999.99;
    for(unsigned int index = 0; index < mDimX; index++)
        for(unsigned int indey = 0; indey < mDimY; indey++)
            for(unsigned int indez = 0; indez < mDimZ; indez++) {
                if (Get(index, indey, indez) >= max)
                    max = Get(index, indey, indez);
            }
    return max;
}

//______________________________________________________________________________
void YSGrid3dFloat::Multiply(const qreal mult)
{
    // multiply by a constant
    for(unsigned int index = 0; index < mDim; index++)
        mElements[index] *= mult;

}

//______________________________________________________________________________
void YSGrid3dFloat::Print() const
{
    // print the grid
    for(unsigned int index = 0; index < mDimX; index++)
        for(unsigned int indey = 0; indey < mDimY; indey++)
            for(unsigned int indez = 0; indez < mDimZ; indez++)
                qDebug() << QString("(%1, %2, %3) = %4").arg(index).arg(indey).arg(indez).arg(Get(index, indey, indez));
}

//______________________________________________________________________________
void YSGrid3dFloat::Resize(YSGrid3dFloat *out, const unsigned int size)
{
    // resizes the grid into a new grid out by averaging over k cells

    const unsigned int dimX = mDimX / size;
    const unsigned int dimY = mDimY / size;
    const unsigned int dimZ = mDimZ / size;

    if ( out->DimX() != dimX || out->DimY() != dimY || out->DimZ() != dimY) {
        qDebug() << "YSGrid3dFloat::Resize: Fatal Error not matching grid size";
        exit(1);
    }

    qreal average = 0.;
    for(unsigned int index = 0; index < dimX; index++)
        for(unsigned int indey = 0; indey < dimY; indey++)
            for(unsigned int indez = 0; indez < dimZ; indez++) {
                for(unsigned int indexx = index * size; indexx < (index + 1) * size; indexx++)
                    for(unsigned int indeyy = indey * size; indeyy < (indey + 1) * size; indeyy++)
                        for(unsigned int indezz = indey * size; indezz < (indez + 1) * size; indezz++)
                            average += Get(indexx, indeyy, indezz);
                out->Set(index, indey, indez, average / (size * size * size));
                average = 0.0;
            }
}
