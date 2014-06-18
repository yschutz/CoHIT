//
//  YSGrid3dFloat.h
//  A 3D Grid of float
//
//  Created by Yves Schutz on 02/06/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#ifndef YSGRID3dFLOAT_H
#define YSGRID3dFLOAT_H

#include "YSGrid3d.h"

class YSGrid3dFloat : public YSGrid3d
{
public:
    YSGrid3dFloat(const unsigned int x, const unsigned int y, const unsigned int z);
    YSGrid3dFloat(const YSGrid3dFloat &grid);
    ~YSGrid3dFloat();

    void         Add(const qreal addVal);
    void         Add(YSGrid3dFloat *grid, const qreal val = 1.0);
    void         Clear();
    qreal        Get(const unsigned int x, unsigned int y, unsigned int z) const
       { return mElements[x * mDimX + y * mDimY + z]; }
    qreal        *GetElements() const { return mElements; }
    qreal        GetMax() const;
    void         Multiply(const qreal mult);
    void         Print() const;
    void         Resize(YSGrid3dFloat *out, const unsigned int size);
    void         Set(const unsigned int x, unsigned int y, unsigned int z, qreal val)
        { mElements[x * mDimX + y * mDimY + z] = val; }


private:
    qreal        *mElements;             // the elements of the Grid
};

#endif // YSGRID3DFLOAT_H
