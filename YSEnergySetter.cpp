//
//  YSEnergySetter.cpp
//  Widget for setting the collision energy
//
//  Created by Yves Schutz on 09/12/13.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#include <QAction>
#include <QContextMenuEvent>
#include <QDebug>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QRadioButton>
#include <QSlider>

#include "YSCollision.h"
#include "YSEnergySetter.h"
#include "YSNucleus.h"

//______________________________________________________________________________
YSEnergySetter::YSEnergySetter(YSCollision *coll)
{
    //ctor default ctor
    SetColl(coll);
    Draw();
}

//______________________________________________________________________________
YSEnergySetter::YSEnergySetter(QMenuBar *mb, YSCollision *coll)
{
    // ctor adopting the common Menubar 
    SetColl(coll);
    Draw();

    // adds an entry to the general menu bar
    AddToMenu(mb);
}

//______________________________________________________________________________
YSEnergySetter::~YSEnergySetter()
{
    delete mActionQuit;
    delete mLHC;
    delete mRHIC;
    delete mSPS;
    delete mB1Label;
    delete mB2Label;
    delete mB1VBox;
    delete mB2VBox;
    delete mTeVLabel1;
    delete mTeVLabel2;
    delete mEnergySlider;
    delete mSValueBox;
    delete mTeVLabel;
    delete mBeamsBox;
    delete mABBox;
    delete mSBox;
}

//______________________________________________________________________________
void YSEnergySetter::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu aMenu(this);
    aMenu.addAction(mActionQuit);
    aMenu.exec(event->globalPos());
}

//______________________________________________________________________________
void YSEnergySetter::AddToMenu(QMenuBar *mb)
{
    // add actions to the main menu bar
    mMenuBar = mb;
    CreateActions();
    CreateMenus();
}

//______________________________________________________________________________
void YSEnergySetter::CreateActions()
{
    // create the actions for the menu items
    mActionQuit = new QAction(tr("&Done"), this);
    mActionQuit->setShortcuts(QKeySequence::Quit);
    mActionQuit->setStatusTip(tr("Quit this view"));
    connect(mActionQuit, SIGNAL(triggered()), this, SLOT(Done()));
}

//______________________________________________________________________________
void YSEnergySetter::CreateMenus()
{
    // create the menu (so far only Done implemented)
    mMenu = mMenuBar->addMenu(tr("Energy Setter"));
    mMenu->addAction(mActionQuit);
}

//______________________________________________________________________________
void YSEnergySetter::CreateABBox()
{
    // create the box with radio buttons to select accelerator
    mABBox = new QGroupBox(tr("Accelerators"));

    QGridLayout *abboxLayout = new QGridLayout();
    mLHC  = new QRadioButton("LHC", mABBox);
    mLHC->setChecked(true);
    mEnergyHigh = 7.0;  // TeV
    mEnergyLow  = 0.45; // TeV
    mRHIC = new QRadioButton("RHIC", mABBox);
    mSPS  = new QRadioButton("SPS", mABBox);

    abboxLayout->addWidget(mLHC,  0, 0);
    abboxLayout->addWidget(mRHIC, 1, 0);
    abboxLayout->addWidget(mSPS,  2, 0);

    mABBox->setLayout(abboxLayout);
}

//______________________________________________________________________________
void YSEnergySetter::CreateBeamsBox()
{
    // box displaying the beams energy

    mBeamsBox = new QGroupBox(tr("Beams energy"));

    // Beam specie
    mB1Label = new QLabel(QString("<body><sup>%1</sup>%2</body>").
                          arg(mColl->Nucleus(1)->A()).arg(mColl->Nucleus(1)->Symbol()));
    mB2Label = new QLabel(QString("<body><sup>%1</sup>%2</body>").
                          arg(mColl->Nucleus(2)->A()).arg(mColl->Nucleus(2)->Symbol()));
    // Energie value
    mB1VBox = new QLineEdit(this);
    mB1VBox->setAlignment(Qt::AlignRight);
    mB1VBox->setText(mSValueBox->text());
    mB1VBox->adjustSize();
    mB1VBox->setFixedWidth(mB1VBox->width());
    mB1VBox->setText(mSValueBox->text());
    mB2VBox = new QLineEdit(this);
    mB2VBox->setAlignment(Qt::AlignRight);
    mB2VBox->setText(mSValueBox->text());
    mB2VBox->adjustSize();
    mB2VBox->setFixedWidth(mB2VBox->width());

    // units
    mTeVLabel1 = new QLabel("TeV", this);
    mTeVLabel2 = new QLabel("TeV", this);

    // position it
    QGridLayout *bboxLayout = new QGridLayout();
    bboxLayout->addWidget(mB1Label, 0, 0);
    bboxLayout->addWidget(mB2Label,1, 0);
    bboxLayout->addWidget(mB1VBox, 0, 1);
    bboxLayout->addWidget(mB2VBox, 1, 1);
    bboxLayout->addWidget(mTeVLabel1, 0, 2);
    bboxLayout->addWidget(mTeVLabel2, 1, 2);

    mBeamsBox->setLayout(bboxLayout);
}

//______________________________________________________________________________
void YSEnergySetter::CreateSBox()
{
    // makes the energy slider in TeV for Z = 1
    mSBox = new QGroupBox(tr("Z=1 momentum"));
    QGridLayout *sboxLayout = new QGridLayout();

    // the slider
    mEnergySlider = new QSlider(Qt::Vertical, this);
    mEnergySlider->setFocusPolicy(Qt::StrongFocus);
    mEnergySlider->setTickPosition(QSlider::TicksBothSides);
    mEnergySlider->setTickInterval(10);
    mEnergySlider->setSingleStep(1);
    mScaleLow  = 0;
    mScaleHigh = 100;
    mEnergySlider->setMinimum(mScaleLow);
    mEnergySlider->setMaximum(mScaleHigh);

    // the box with the slider value
    mSValueBox = new QLineEdit(this);
    mSValueBox->setAlignment(Qt::AlignRight);
    mSValueBox->adjustSize();
    mSValueBox->setFixedWidth(mSValueBox->width());

    // the label
    mTeVLabel = new QLabel("TeV/c", this);

    sboxLayout->addWidget(mEnergySlider, 0, 0, 2, 1);
    sboxLayout->addWidget(mSValueBox, 0, 1);
    sboxLayout->addWidget(mTeVLabel, 0, 2);

    mSBox->setLayout(sboxLayout);
}

//______________________________________________________________________________
void YSEnergySetter::Done()
{
    // close window and finish

    qreal ene1 = mSliderPos * mColl->Nucleus(1)->Z() / mColl->Nucleus(1)->A();
    qreal ene2 = mSliderPos * mColl->Nucleus(2)->Z() / mColl->Nucleus(2)->A();
    mColl->SetEnergies(ene1, ene2);
    delete this;
}

//______________________________________________________________________________
void YSEnergySetter::Draw()
{
   // Draws the window contents
    int finalXSize = 400, finalYSize = 400;
    mSliderFlag = false;
    setWindowTitle(tr("Collision Energy Setter"));
    CreateABBox();
    CreateSBox();
    CreateBeamsBox();
    ReadSlider(mEnergySlider->sliderPosition());
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(mABBox, 0, 0);
    layout->addWidget(mSBox, 0, 1);
    layout->addWidget(mBeamsBox, 1, 0, 1, 2);
    setLayout(layout);
    resize(finalXSize, finalYSize);

    connect(mLHC,  SIGNAL(clicked()), this, SLOT(SetSliderScale()));
    connect(mRHIC, SIGNAL(clicked()), this, SLOT(SetSliderScale()));
    connect(mSPS,  SIGNAL(clicked()), this, SLOT(SetSliderScale()));
    connect(mEnergySlider, SIGNAL(valueChanged(int)), this, SLOT(ReadSlider(int)));
    connect(mSValueBox, SIGNAL(textChanged(const QString)), this, SLOT(SetSliderPos(const QString)));
}

//______________________________________________________________________________
void YSEnergySetter::ReadSlider(int pos)
{
    // reads the value of the energy slider
    if(mSliderFlag) return;
    mSliderPos = pos * (mEnergyHigh - mEnergyLow) / mScaleHigh + mEnergyLow + 0.005;
    mSValueBox->setText(QString("%1").arg(mSliderPos, 0, 'f', 2));
    qreal ene1 = mSliderPos * mColl->Nucleus(1)->Z() / mColl->Nucleus(1)->A();
    qreal ene2 = mSliderPos * mColl->Nucleus(2)->Z() / mColl->Nucleus(2)->A();
    mB1VBox->setText(QString("%1").arg(ene1, 0, 'f', 2));
    mB2VBox->setText(QString("%1").arg(ene2, 0, 'f', 2));
}

//______________________________________________________________________________
void YSEnergySetter::SetSliderScale()
{
    if ( mLHC->isChecked() ) {
        mEnergyHigh = 7.0;  // *Z TeV
        mEnergyLow  = 0.45; // *Z TeV
    } else if ( mRHIC->isChecked() ) {
        mEnergyHigh = 0.26;  // *Z TeV
        mEnergyLow  = 0.096; // *Z TeV
    } else if ( mSPS->isChecked() ) {
        mEnergyHigh = 0.45;  // *Z TeV
        mEnergyLow  = 0.026; // *Z TeV
    }
    ReadSlider(mEnergySlider->sliderPosition());
}

//______________________________________________________________________________
void YSEnergySetter::SetSliderPos(const QString txt)
{
    // set the position of the cursor on the slider
    mSliderFlag = true;
    qreal pos = txt.toDouble();
    int ipos = (pos - mEnergyLow) * mScaleHigh / (mEnergyHigh - mEnergyLow);
    mEnergySlider->setSliderPosition(ipos);
    qreal ene1 = pos * mColl->Nucleus(1)->Z() / mColl->Nucleus(1)->A();
    qreal ene2 = pos  * mColl->Nucleus(2)->Z() / mColl->Nucleus(2)->A();
    mB1VBox->setText(QString("%1").arg(ene1, 0, 'f', 2));
    mB2VBox->setText(QString("%1").arg(ene2, 0, 'f', 2));
    mSliderFlag = false;
}
