//
//  YSQuark.h
//  a quark
//
//  Created by Yves Schutz on 05/01/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#ifndef YSQUARK_H
#define YSQUARK_H

#include <QGLSphere>
#include <QGLView>

#include "YSNucleus.h"

class YSQuark : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal QGLPos READ QGLPos WRITE SetQGLPos)

public:
    explicit YSQuark(QObject *parent = 0);

    QGLSphere QuarkView() const { return QGLSphere(YSNucleus::kgProtonRadius / 20.); } // the quark is in fact 1000 times smaller than the nucleon
    qreal QGLPos() const { return mQpos; }
    void  SetQGLPos(qreal pos) { mQpos = pos; mView->update(); }

signals:

public slots:

private:
    qreal   mQpos;     // needed ba Property Animation
    QGLView *mView;    // the view where the object will be displayed

};

#endif // YSQUARK_H
