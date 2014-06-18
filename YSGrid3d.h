//
//  YSGrid3d.h
//  A 3D Grid virtual base class
//
//  Created by Yves Schutz on 02/06/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#ifndef YSGRID3D_H
#define YSGRID3D_H

class YSGrid3d
{
public:
    YSGrid3d(const unsigned int x, const unsigned int y, const unsigned int z);
    virtual ~YSGrid3d(){;}

    virtual void Clear() = 0;
    unsigned int Dim() const  { return mDim; }
    unsigned int DimX() const { return mDimX; }
    unsigned int DimY() const { return mDimY; }
    unsigned int DimZ() const { return mDimZ; }
    virtual void Print() const = 0;

protected:
    unsigned int mDimX, mDimY, mDimZ;    // (x, y, z) dimensiond of the Grid
    unsigned int mDim ;                  // dimension of the Grid
};

#endif // YSGRID3D_H
