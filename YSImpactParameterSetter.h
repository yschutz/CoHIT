//
//  YSImpactParameterSetter.h
//  Widget for setting the collision mpact parameter
//
//  Created by Yves Schutz on 26/02/14.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#ifndef YSIMPACTPARAMETERSETTER_H
#define YSIMPACTPARAMETERSETTER_H

#include <QObject>
#include <QWidget>

class QAction;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QSlider;

class YSCollision;
class YSMenu;
class YSOverlappingCircles;

class YSImpactParameterSetter : public QWidget
{
    Q_OBJECT

public:
    YSImpactParameterSetter(YSMenu * parent, YSCollision *);
    virtual ~YSImpactParameterSetter();

private:
    void  CreateSBox();
    void  Draw();
    void  SetColl(YSCollision *coll) { mColl = coll; }

public slots:
    void  ReadSlider(int);
    void  SetSliderPos(const QString);

private:
    qreal                mbMin, mbMax;              // min and max value of b
    QSlider              *mbSlider;                 // b slider
    YSCollision          *mColl;                    // colliding sytem
    QLabel               *mLCentral, *mLPeripheral; // Labels
    QLabel               *mLFermi;                  // Labels
    YSMenu               *mParent;                  // parent menu
    YSOverlappingCircles *mOC;                      // 2 overlapping circles to illustrate b
    QPushButton          *mOk;                      // OK push button
    QGroupBox            *mSBox;                    // box with slider
    QLineEdit            *mSBoxValue;               // box containing b value
    qreal                mScaleLow, mScaleHigh;     // lower and upper limit for b
    bool                 mSliderFlag;               // flag to inhibit ReadSlider
    qreal                mSliderPos;                // slider position

};

#endif // YSIMPACTPARAMETERSETTER_H
