//
//  YSOverlappingCircles.cpp
//  A widget to draw 2 overlapping circles to demonstarte impact parameter
//
//  Created by Yves Schutz on 28/02/14.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#include <QDebug>
#include <QPainter>

#include "YSOverlappingCircles.h"

//______________________________________________________________________________
YSOverlappingCircles::YSOverlappingCircles(QWidget *parent) :
    QWidget(parent), mb(0.0)
{
    // ctor
    setBackgroundRole(QPalette::Base);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

//______________________________________________________________________________
YSOverlappingCircles::~YSOverlappingCircles()
{
    // dtor
}

//______________________________________________________________________________
void YSOverlappingCircles::paintEvent(QPaintEvent * /*event*/)
{
    // draws 2 overlapping circles
    qreal scale = 50. / std::max(mR1, mR2);
    qreal hw1 = mR1 * scale, hw2 = mR2 * scale;
    qreal posx1 = 25 + std::max(hw1, hw2) / 2., posy1 = 100. + hw1;
    qreal posx2 = posx1, posy2 = 0.;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    // circle 1
    painter.setPen(QPen(Qt::NoPen));
    qreal posy = posy1 - mb/2. * scale;
    QRadialGradient g1(posx1, posy, hw1);
    QColor trwhite(Qt::white);
    trwhite.setAlpha(200);
    g1.setColorAt(0.0, trwhite);
    QColor trred(Qt::red);
    trred.setAlpha(200);
    g1.setColorAt(1.0, trred);
    painter.setBrush(g1);
    painter.drawEllipse(QPointF(posx1, posy), hw1, hw1);
    //circle 2
    painter.setPen(QPen(Qt::NoPen));
    posy2 = posy1 + mb/2 * scale;
    QRadialGradient g2(posx1, posy2, hw2);
    g2.setColorAt(0.0, trwhite);
    QColor trblue(Qt::blue);
    trblue.setAlpha(120);
    g2.setColorAt(1.0, trblue);
    painter.setBrush(g2);
    painter.drawEllipse(QPointF(posx2, posy2), hw2, hw2);
    // axe x
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::NoBrush);
    qreal xorg = 120., yorg = posy1;
    qreal xlen = 60., ylen = 60.;
    painter.drawLine(xorg, yorg, xorg + xlen, yorg);
    qreal offset = 15;
    painter.drawText(xorg + xlen - offset, yorg + offset, QString("x"));
    // axe y
    painter.drawLine(xorg, yorg, xorg, yorg - ylen);
    painter.drawText(xorg + offset, yorg - ylen + offset, QString("y"));
    // axe z
    painter.drawLine(xorg, yorg, xorg - xlen / 2, yorg + ylen / 2);
    painter.drawText(xorg - xlen / 2 + offset, yorg + ylen / 2 + offset, QString("beam axis"));
    // impact parameter
    painter.setPen((QPen(Qt::green, 3)));
    painter.drawLine(posx1, posy1 - mb/2. * scale, posx2, posy2);
}
