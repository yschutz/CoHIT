//
//  YSGrid3dVector.h
//  A 3D Grid of float
//
//  Created by Yves Schutz on 02/06/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#ifndef YSGRID3dVECTOR_H
#define YSGRID3dVECTOR_H

#include "YSGrid3d.h"

#include <QVector3D>

class YSGrid3dVector : public YSGrid3d
{
public:
    YSGrid3dVector(const unsigned int x, const unsigned int y, const unsigned int z);
    YSGrid3dVector(const YSGrid3dVector &grid);
    ~YSGrid3dVector();

    void         Add(const QVector3D addVal);
    void         Add(YSGrid3dVector *grid, const float addVal = 1.0);
    void         Clear();
    QVector3D    Get(const unsigned int x, unsigned int y, unsigned int z) const
       { return mElements[x * mDimX + y * mDimY + z]; }
    QVector3D    *GetElements() const { return mElements; }
    void         Multiply(const float mult);
    void         Print() const;
    void         Set(const unsigned int x, unsigned int y, unsigned int z, QVector3D val)
        { mElements[x * mDimX + y * mDimY + z] = val; }
    void         Resize(YSGrid3dVector *out, const unsigned int size);


private:
    QVector3D    *mElements;             // the elements of the Grid
};

#endif // YSGRID3dVECTOR_H
