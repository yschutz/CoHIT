//
//  YSQuark.cpp
//  a quark
//
//  Created by Yves Schutz on 05/01/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#include "YSQuark.h"

YSQuark::YSQuark(QObject *parent) : QObject(parent), mView((QGLView*) parent)
{
}
