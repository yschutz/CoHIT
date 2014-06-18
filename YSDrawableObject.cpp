//
//  YSDrawabbleObject.cpp
//  A basic 1D function
//
//  Created by Yves Schutz on 10/05/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.

#include "YSDrawableObject.h"


//______________________________________________________________________________
YSDrawableObject::YSDrawableObject() :  mDx(1.0), mNumberOfBins(0), mXMax(0.0), mXMin(0.0),
    mYMax(0.0)
{
    // ctor
}

//______________________________________________________________________________
void YSDrawableObject::FillXValues()
{
    // fills the array with the x values
    mXValues.resize(mNumberOfBins + 1);
    for(int index = 1; index < mNumberOfBins; index++) {
        mXValues[index] = index * mDx;
    }
}
