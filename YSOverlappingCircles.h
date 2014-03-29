//
//  YSOverlappingCircles.h
//  A widget to draw 2 overlapping circles to demonstarte impact parameter
//
//  Created by Yves Schutz on 28/02/14.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#ifndef YSOVERLAPPINGCIRCLES_H
#define YSOVERLAPPINGCIRCLES_H

#include <QWidget>

class YSOverlappingCircles : public QWidget
{
    Q_OBJECT

public:
    explicit YSOverlappingCircles(QWidget *parent = 0);
    virtual ~YSOverlappingCircles();

    void  Setb(qreal b) { mb = b; }
    void  SetR(qreal r1, qreal r2) { mR1 = r1; mR2 = r2; }

protected:
    void paintEvent(QPaintEvent *);

private:
    qreal Getb() const { return mb; }

    qreal mb;           // impact parameter value
    qreal mR1, mR2;     // radius of the 2 circles
};

#endif // YSOVERLAPPINGCIRCLES_H
