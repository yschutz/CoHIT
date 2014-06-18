//
//  YSGrid3d.cpp
//  A 3D Grid virtual base class
//
//  Created by Yves Schutz on 02/06/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#include "YSGrid3d.h"

//______________________________________________________________________________
YSGrid3d::YSGrid3d(const unsigned int x, const unsigned int y, const unsigned int z):
    mDimX(x), mDimY(y), mDimZ(z), mDim(x * y * z)
{
}
