//
//  YSMenu.cpp
//  Main Menu for the CoHIT project
//
//  Created by Yves Schutz on 09/12/13.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>

#include "stdio.h"

#include "YSCollision.h"
#include "YSCrossSectionpp.h"
#include "YSEnergySetter.h"
#include "YSIsotope.h"
#include "YSIsotopeSheet.h"
#include "YSMenu.h"
#include "YSNucleus.h"
#include "YS3DView.h"
#include "YSPeriodictable.h"
#include "YSPTView.h"

#include "YSPlotWindow.h"

//______________________________________________________________________________
YSMenu::YSMenu(QWidget *parent) :
    QMainWindow(parent),
    mAview(NULL),
    mCollision(new YSCollision),
    mPlotWindow(NULL)
{
    // Main Window settings
    setWindowTitle("HI Collision Toy");
    int windowWidth = 600, windowHeight = 350;

    // define the text box
    mTextBox = new QWidget(this);
    mTextBox->setLayout(new QVBoxLayout());
    int xMargin = windowWidth/15, yMargin = windowHeight / 15;
    mTextBox->layout()->setContentsMargins(xMargin, yMargin, xMargin, yMargin);
    mTextBox->setStyleSheet("QWidget {background-color:blue}");

    // define the text
    mText = new QLabel(mTextBox);
    mText->setAutoFillBackground(true);
    mText->setAlignment(Qt::AlignCenter);
    mText->setFont(QFont("Comic Sans MS", 30));
    mText->setFrameShadow(QFrame::Raised);
    mText->setFrameShape(QFrame::Panel);
    mText->setLineWidth(1);
    mText->setStyleSheet("QLabel { background-color : white; color : red; }");
    mText->setText("<body>CoHIT <br> A Toy for Heavy-Ion Collisions <hr width=\"60%\"/> by Yves Schutz</body>");

    //add text into text box
    mTextBox->layout()->addWidget(mText);

    setCentralWidget(mTextBox);


    // define Menus
    // systems selection
    mMenuSystem  = new QMenu("Colliding System");
    connect(mMenuSystem, SIGNAL(triggered(QAction*)), this, SLOT(HandleMenu(QAction*)));
    mApt = new QAction("Select A1 & A2 from &Periodic tables", this);
    mApt->setData(QVariant(MENU_SYSTEM_PT));
    mMenuSystem->addAction(mApt);

    mMenuKnownSystems = new QMenu("Select from known system");
    connect(mMenuKnownSystems, SIGNAL(triggered(QAction*)), this, SLOT(HandleMenu(QAction*)));

    mApp236 = new QAction("pp at 2.36 TeV", this) ;
    mApp236->setData(QVariant(MENU_KSYSTEMS_PP236));
    mMenuKnownSystems->addAction(mApp236);

    mApp7 = new QAction("pp at 7 TeV", this) ;
    mApp7->setData(QVariant(MENU_KSYSTEMS_PP7));
    mMenuKnownSystems->addAction(mApp7);

    mApp8 = new QAction("pp at 8 TeV", this) ;
    mApp8->setData(QVariant(MENU_KSYSTEMS_PP8));
    mMenuKnownSystems->addAction(mApp8);

    mApPb501 = new QAction("pPb at 5.01 TeV", this);
    mApPb501->setData(QVariant(MENU_KSYSTEMS_PPB501));
    mMenuKnownSystems->addAction(mApPb501);

    mAPbPb276 = new QAction("pp at 2.36 TeV", this) ;
    mAPbPb276->setData(QVariant(MENU_KSYSTEMS_PBPB276));
    mMenuKnownSystems->addAction(mAPbPb276);

    mMenuSystem->addMenu(mMenuKnownSystems);

    // action selection (to be added after the collising system is set)
    mMenuDraw = new QMenu("Draw");
    connect(mMenuDraw, SIGNAL(triggered(QAction*)), this, SLOT(HandleMenu(QAction*)));
    mDrawA = new QMenu("nucleus", this);
    connect(mDrawA, SIGNAL(triggered(QAction*)), this, SLOT(HandleMenu(QAction*)));
    mDrawDP = new QMenu("density profile", this);
    connect(mDrawDP, SIGNAL(triggered(QAction*)), this, SLOT(HandleMenu(QAction*)));

    mDrawCS = new QAction("Draw pp cross section", this);
    mDrawC  = new QAction("collision", this);
    mDrawD  = new QAction("Done", this);

    mMenuBar = new QMenuBar(0);
    mMenuBar->addMenu(mMenuSystem);
    mMenuBar->addMenu(mMenuDraw);

    resize(windowWidth,windowHeight);
    setMinimumSize(windowWidth,windowHeight);
    move(0,0);
}

//______________________________________________________________________________
YSMenu::~YSMenu()
{
    delete mApt;
    delete mApp236;
    delete mApp7;
    delete mApp8;
    delete mApPb501;
    delete mAPbPb276;
    delete mMenuSystem;
    delete mMenuDraw;
    delete mMenuBar;
    delete mMenuKnownSystems;
    delete mText;
    delete mTextBox;
    delete mAview;
    delete mPlotWindow;
}

//______________________________________________________________________________
void YSMenu::CloseView()
{
    // close all the windows displaying Nucleus, Collision,etc...
    if (mAview)
       delete mAview;
    if (mPlotWindow)
        delete mPlotWindow;
    mAview = NULL;
    mPlotWindow = NULL;
}

//______________________________________________________________________________
void YSMenu::DrawCrossSection()
{
    // Draw the pp cross sections as a function of ecm
    CloseView();
    mPlotWindow = new YSPlotWindow();
    YSCrossSectionpp cspp;
    mPlotWindow->Draw(&cspp);
    mPlotWindow->show();
}

//______________________________________________________________________________
void YSMenu::DrawCollisionView(YSCollision *coll)
{
    // Draw a GL view of the collision

    CloseView();
    mAview = new YS3DView(this, coll);
    if (mAview->stereoType() != QGLView::RedCyanAnaglyph)
        mAview->camera()->setEyeSeparation(0.3f);
    mAview->resize(900, 500);
    mAview->setPosition(QPoint(600,500));
    mAview->show();
}

//______________________________________________________________________________
void YSMenu::DrawDensityProfile(YSNucleus *nuc)
{
    // Draw the density profile (qcustomplot)
    CloseView();
    mPlotWindow = new YSPlotWindow();
    mPlotWindow->Draw(nuc->DensityProfile());
    mPlotWindow->show();
}

//______________________________________________________________________________
void YSMenu::DrawNucleusView(YSNucleus *nuc)
{
    // Draw a GL view of the nucleus

    CloseView();
    mAview = new YS3DView(0, nuc);
    if (mAview->stereoType() != QGLView::RedCyanAnaglyph)
        mAview->camera()->setEyeSeparation(0.3f);
    mAview->resize(1000, 1000);
    mAview->show();

}

//______________________________________________________________________________
void YSMenu::HandleMenu(QAction *action)
{
    switch (action->data().toInt()) {
    case MENU_SYSTEM_PT:
    {
        mPtView = new YSPTView(mMenuBar);
        YSPeriodicTable * pt = mPtView->PT();
        connect(pt, SIGNAL(IsotopeIsSelected(YSIsotope *)), this, SLOT(SetNucleus(YSIsotope*)));
        connect(mPtView, SIGNAL(destroyed()), this, SLOT(SelectEnergy()));
        mPtView->show();
        break;
    }
    case MENU_SYSTEM_ENE:
    {
        YSEnergySetter *eneset = new YSEnergySetter(mMenuBar, mCollision);
        connect(eneset, SIGNAL(destroyed()), this, SLOT(SetEnergy()));
        eneset->show();
        break;
    }
    case MENU_KSYSTEMS_PP236:
        qDebug() << " pp 2.36";
        break;
    case MENU_KSYSTEMS_PP7:
        qDebug() << " pp 7";
        break;
    case MENU_KSYSTEMS_PP8:
        qDebug() << " pp 8";
        break;
    case MENU_KSYSTEMS_PPB501:
        qDebug() << " pPb 5.01";
        break;
    case MENU_KSYSTEMS_PBPB276:
        qDebug() << " PbPb 2.76";
        break;
    case MENU_DRAW_A1:
    {
        DrawNucleusView(mCollision->Nucleus(1));
        break;
    }
    case MENU_DRAW_A2:
    {
        DrawNucleusView(mCollision->Nucleus(2));
        break;
    }
    case MENU_DRAW_DP1:
    {
        DrawDensityProfile(mCollision->Nucleus(1));
        break;
    }
    case MENU_DRAW_DP2:
    {
        DrawDensityProfile(mCollision->Nucleus(2));
        break;
    }
    case MENU_DRAW_CS:
    {
        DrawCrossSection();
        break;
    }
    case MENU_DRAW_C:
    {
        DrawCollisionView(mCollision);
        break;
    }
    case MENU_DRAW_D:
    {
        CloseView();
        break;
    }
    default:
        break;
    }
}

//______________________________________________________________________________
void YSMenu::SelectEnergy()
{
    // selects the colliding energy
    YSEnergySetter *eneset = new YSEnergySetter(mMenuBar, mCollision);
    connect(eneset, SIGNAL(destroyed()), this, SLOT(SetEnergy()));
    eneset->show();
    mAene = new QAction("Select Collision Energy", this);
    mAene->setData(QVariant(MENU_SYSTEM_ENE));
    mMenuSystem->addAction(mAene);
}

//______________________________________________________________________________
void YSMenu::SetEnergy()
{
    // sets the colliding energy
    qreal ene = mCollision->CMEnergyNN();
    QString tempo = mText->text();
    int index = tempo.indexOf("@");
    if (index != -1) {
        tempo = tempo.remove(index, tempo.size());
    }
    mText->setText(tempo.append(QString(" @ &radic;s<sub>NN</sub> = %1 TeV ").
                                arg(ene, 0, 'f', 2)));

    mDrawA1  = new QAction(QString("%1%2").arg(mCollision->Nucleus(1)->A()).arg(mCollision->Nucleus(1)->Symbol()), this);
    mDrawA2  = new QAction(QString("%1%2").arg(mCollision->Nucleus(2)->A()).arg(mCollision->Nucleus(2)->Symbol()), this);
    mDrawDP1 = new QAction(QString("%1%2").arg(mCollision->Nucleus(1)->A()).arg(mCollision->Nucleus(1)->Symbol()), this);
    mDrawDP2 = new QAction(QString("%1%2").arg(mCollision->Nucleus(2)->A()).arg(mCollision->Nucleus(2)->Symbol()), this);

    mDrawA1->setData(QVariant(MENU_DRAW_A1));
    mDrawA2->setData(QVariant(MENU_DRAW_A2));
    mDrawDP1->setData(QVariant(MENU_DRAW_DP1));
    mDrawDP2->setData(QVariant(MENU_DRAW_DP2));
    mDrawCS->setData(QVariant(MENU_DRAW_CS));
    mDrawC->setData(QVariant(MENU_DRAW_C));
    mDrawD->setData(QVariant(MENU_DRAW_D));

    mDrawA->addAction(mDrawA1);
    mDrawDP->addAction(mDrawDP1);
    if(*(mCollision->Nucleus(1)) != *(mCollision->Nucleus(2))) {
        mDrawA->addAction(mDrawA2);
        mDrawDP->addAction(mDrawDP2);
    }
    mMenuDraw->addMenu(mDrawA);
    mMenuDraw->addMenu(mDrawDP);
    mMenuDraw->addAction(mDrawCS);
    mMenuDraw->addAction(mDrawC);
    mMenuDraw->addAction(mDrawD);
}

//______________________________________________________________________________
void YSMenu::Setb()
{
    //update the menu display
    QString tempo = mText->text();
    tempo.remove(tempo.indexOf("<br>"), tempo.size());
    mText->setText(tempo.append(QString("<br> <center> b = %2 </center></body>").
                                arg(mCollision->Getb(), 0, 'f',2)));
    mAview->Setb(mCollision->Getb());
    mAview->update();
}

//______________________________________________________________________________
void YSMenu::SetNucleus(YSIsotope *iso)
{
    // set the colliding system one nucleus at the time
    mCollision->SetNucleus(iso);
    mText->setText(QString("<body> <sup>%1</sup>%2 + <sup>%3</sup>%4")
                   .arg(mCollision->Nucleus(1)->A()).arg(mCollision->Nucleus(1)->Symbol())
                   .arg(mCollision->Nucleus(2)->A()).arg(mCollision->Nucleus(2)->Symbol()));
}
