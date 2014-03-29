//
//  YSImpactParameterSetter.cpp
//  Widget for setting the collision energy
//
//  Created by Yves Schutz on 26/02/14.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#include <QAction>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QSlider>

#include "YSCollision.h"
#include "YSImpactParameterSetter.h"
#include "YSMenu.h"
#include "YSNucleus.h"
#include "YSOverlappingCircles.h"

//______________________________________________________________________________
YSImpactParameterSetter::YSImpactParameterSetter(YSMenu * parent, YSCollision *coll) :
    mbMin(0), mParent(parent), mScaleLow(0.0), mScaleHigh(100.0)
{
    //default ctor
    SetColl(coll);
    mbMax = coll->Nucleus(1)->Radius() + coll->Nucleus(2)->Radius();

    Draw();
    connect(this, SIGNAL(destroyed()), mParent, SLOT(Update()));
    connect(mOk, SIGNAL(clicked()), mParent, SLOT(Setb()));
}

//______________________________________________________________________________
YSImpactParameterSetter::~YSImpactParameterSetter()
{
    delete mbSlider;
    delete mLCentral;
    delete mLPeripheral;
    delete mLFermi;
    delete mOk;
    delete mSBoxValue;
    delete mSBox;
}

//______________________________________________________________________________
void YSImpactParameterSetter::CreateSBox()
{
    // creates the slider to select b

    mSBox = new QGroupBox(tr("b selection"));
    QGridLayout *sboxLayout = new QGridLayout();

    // the slider
    mbSlider = new QSlider(Qt::Vertical, this);
    mbSlider->setFocusPolicy(Qt::StrongFocus);
    mbSlider->setTickPosition(QSlider::TicksBothSides);
    mbSlider->setTickInterval(10);
    mbSlider->setSingleStep(1);
    mbSlider->setMinimum(mScaleLow);
    mbSlider->setMaximum(mScaleHigh);

    // labels
    mLCentral    = new QLabel(tr("Central"), this);
    mLPeripheral = new QLabel(tr("Peripheral"), this);
    mLFermi      = new QLabel("fm", this);

    // box with the b value
    mSBoxValue = new QLineEdit(this);
    mSBoxValue->setAlignment(Qt::AlignRight);
    mSBoxValue->adjustSize();
    mSBoxValue->setFixedWidth((mSBoxValue->width()));

    // the 2 circles animation
    mOC = new YSOverlappingCircles(this);
    mOC->Setb(mColl->Getb());
    mOC->SetR(mColl->Nucleus(1)->Radius(), mColl->Nucleus(2)->Radius());

    // the OK pushbutton
    mOk = new QPushButton(QString(tr("OK")));

    // position objects in sbox
    sboxLayout->addWidget(mbSlider, 0, 0, 3, 1);
    sboxLayout->addWidget(mLPeripheral,0, 1, Qt::AlignTop);
    sboxLayout->addWidget(mLCentral, 2, 1, Qt::AlignBottom);
    sboxLayout->addWidget(mSBoxValue, 3, 0, 1, 2);
    sboxLayout->addWidget(mLFermi, 3, 2);
    sboxLayout->addWidget(mOC, 0, 2, 3, 1);
    sboxLayout->addWidget(mOk, 3, 2, 1, 1);

    mSBox->setLayout(sboxLayout);

}

//______________________________________________________________________________
void YSImpactParameterSetter::Draw()
{
    // Draws the windows content
    int finalXSize = 400, finalYSize = 400;
    mSliderFlag = false;
    setWindowTitle("Impact Paremeter Setter");
    CreateSBox();
    ReadSlider(mbSlider->sliderPosition());

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(mSBox, 0,0);
    setLayout(layout);
    resize(finalXSize, finalYSize);

    connect(mbSlider, SIGNAL(valueChanged(int)), this, SLOT(ReadSlider(int)));
    connect(mSBoxValue, SIGNAL(textChanged(const QString)), this, SLOT(SetSliderPos(const QString)));
}

//______________________________________________________________________________
void YSImpactParameterSetter::ReadSlider(int pos)
{
    // reads the value of b from the slider position
    if (mSliderFlag) return;
    mSliderPos = pos * (mbMax - mbMin) / mScaleHigh + mbMin + 0.005;
    mSBoxValue->setText(QString("%1").arg(mSliderPos, 0, 'f', 2));
    mColl->Setb(mSBoxValue->text().toDouble());
    mOC->Setb(mSliderPos);
    mOC->update();
    mColl->Setb(mSliderPos);
}

//______________________________________________________________________________
void YSImpactParameterSetter::SetSliderPos(const QString txt)
{
    // sets the slider position from value in edit box
    mSliderFlag = true;
    qreal pos = txt.toDouble();
    mColl->Setb(pos);
    int  ipos = (pos - mbMin) * mScaleHigh / (mbMax - mbMin);
    mbSlider->setSliderPosition(ipos);
    mSliderFlag = false;
    mOC->Setb(mSliderPos);
    mOC->update();
    mColl->Setb(mSliderPos);
}
