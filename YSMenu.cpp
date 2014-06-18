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
#include "YSH1.h"
#include "YSIsotope.h"
#include "YSIsotopeSheet.h"
#include "YSMenu.h"
#include "YSNucleus.h"
#include "YS3dView.h"
#include "YSPeriodictable.h"
#include "YSPTView.h"

#include "YSPlotWindow.h"

//______________________________________________________________________________
YSMenu::YSMenu(QWidget *parent) :
    QMainWindow(parent),
    mAview(NULL),
    mCollision(new YSCollision),
    mCountsDisplay(NULL), mCountEvents(1000),mCounterWindow(NULL),
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

    mApp14 = new QAction("pp at 14 TeV", this) ;
    mApp14->setData(QVariant(MENU_KSYSTEMS_PP14));
    mMenuKnownSystems->addAction(mApp14);

    mApPb502 = new QAction("pPb at 5.02 TeV", this);
    mApPb502->setData(QVariant(MENU_KSYSTEMS_PPB502));
    mMenuKnownSystems->addAction(mApPb502);

    mAPbPb276 = new QAction("PbPb at 2.76 TeV", this) ;
    mAPbPb276->setData(QVariant(MENU_KSYSTEMS_PBPB276));
    mMenuKnownSystems->addAction(mAPbPb276);

    mAPbPb552 = new QAction("PbPb at 5.52 TeV", this) ;
    mAPbPb552->setData(QVariant(MENU_KSYSTEMS_PBPB552));
    mMenuKnownSystems->addAction(mAPbPb552);
    mMenuSystem->addMenu(mMenuKnownSystems);

    // action selection (to be added after the collising system is set)

    mAene = new QAction("Select Collision Energy", this);
    mAene->setData(QVariant(MENU_SYSTEM_ENE));
    mMenuSystem->addAction(mAene);
    mAene->setVisible(false);

    mMenuDraw = new QMenu("Draw");
    connect(mMenuDraw, SIGNAL(triggered(QAction*)), this, SLOT(HandleMenu(QAction*)));
    mMenuDraw->menuAction()->setVisible(false);

    mDrawA = new QMenu("nucleus", this);
    mDrawA->menuAction()->setVisible(false);
    mMenuDraw->addMenu(mDrawA);
    connect(mDrawA, SIGNAL(triggered(QAction*)), this, SLOT(HandleMenu(QAction*)));

    mDrawDP = new QMenu("density profile", this);
    mDrawDP->menuAction()->setVisible(false);
    mMenuDraw->addMenu(mDrawDP);
    connect(mDrawDP, SIGNAL(triggered(QAction*)), this, SLOT(HandleMenu(QAction*)));

    mDrawCS = new QAction("Draw pp cross section", this);
    mDrawCS->setVisible(false);
    mMenuDraw->addAction(mDrawCS);

    mDrawC  = new QAction("collision", this);
    mDrawC->setVisible(false);
    mMenuDraw->addAction(mDrawC);

    mDrawCC  = new QAction("collisionS", this);
    mDrawCC->setVisible(false);
    mMenuDraw->addAction(mDrawCC);

    mDrawD  = new QAction("Done", this);
    mDrawD->setVisible(false);
    mMenuDraw->addAction(mDrawD);

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
    delete mApp14;
    delete mApPb502;
    delete mAPbPb276;
    delete mAPbPb552;
    delete mCounterWindow;
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
    if (mCounterWindow)
        mCounterWindow->close();
    mAview = NULL;
    mPlotWindow = NULL;
}

//______________________________________________________________________________
void YSMenu::WriteCollisionInfo(bool reset)
{
     // Draw a box with collision information

    static bool first = true;
    if (reset) {
        first = true;
        return;
    }
    if (!first)
        return;
    first = false;
     qDebug() << "hello";
    QString tempo = mText->text();
    tempo.remove(tempo.indexOf("<br>"), tempo.size());
    mText->setText(tempo.append(QString("<br> <center> b = %2 fm").
                                arg(mCollision->Getb(), 0, 'f',2)));

    mText->setText(tempo.append(QString("<br> <center> N<sub>coll</sub> = %1 N<sub>part</sub> = %2 T<sub>AA</sub> = %3</center></body>").
                                arg(mCollision->GetNcoll()).arg(mCollision->GetNpart()).arg(mCollision->GetTAA(), 0, 'f', 2)));
}

//______________________________________________________________________________
void YSMenu::CollectStatistics()
{
    // generates mCountEvents
    if (mGoButton->text() == "Stop") {
        mGoButton->setText("Go");
        mGoButton->repaint();
        mGoButton->update();
        return;
    }
    mGoButton->setText("Stop");
    mGoButton->repaint();
    mGoButton->update();
    qApp->processEvents();
    QString tempo = mText->text();
    tempo.remove(tempo.indexOf("<br>"), tempo.size());
    mText->setText(tempo.append(QString("<br> <center> <font size=4>%1 collisions with random b").
                                arg(mCountEvents)));
    // select random impact parameter

    YSH1 hImpact("impact parameter", 100, mCollision->BMin(), mCollision->BMax());
    hImpact.SetAxisLabel("b (fm)", "#");
    mCollision->Setb(0);
    mCollision->MakeCollision();
    int nCollMax = mCollision->GetNcoll() * 1.2 ;
    YSH1 hNColl("Binary collisions", 100, 0, nCollMax);
    hNColl.SetAxisLabel("Ncoll", "#");
    qreal nCollAverage = 0.;
    qreal nPartAverage = 0.;
    qreal nTAAAverage = 0.;
    for (unsigned int counter = 0; counter < mCountEvents; counter++) {
        if (counter % 10 == 0) {
            mCountsDisplay->setText(QString("%1").arg(counter));
            mCountsDisplay->repaint();
            mCountsDisplay->update();
            qApp->processEvents();
        }

        qreal b =  qSqrt((mCollision->BMax() * mCollision->BMax() - mCollision->BMin() * mCollision->BMin()) *
                         (qreal)(qrand()) / (qreal)RAND_MAX + mCollision->BMin() * mCollision->BMin());
        mCollision->Setb(b);
        mCollision->MakeCollision();
        hImpact.Fill(b);
        hNColl.Fill(mCollision->GetNcoll());

        nCollAverage += mCollision->GetNcoll();
        nPartAverage += mCollision->GetNpart();
        nTAAAverage  += mCollision->GetTAA();

        // calculate average Ncoll, Npart and TAA
    }
    mGoButton->setText("Go");
    mGoButton->repaint();
    mGoButton->update();
    nCollAverage /= mCountEvents;
    nPartAverage /= mCountEvents;
    nTAAAverage  /= mCountEvents;
    tempo = mText->text();
    tempo.append(QString("<br> &lt;Ncoll&gt;=%1 &lt;Npart&gt;=%2 &lt;TAA&gt;=%3</font></center></body>").arg(nCollAverage, 0, 'f', 2).arg(nPartAverage, 0, 'f', 2).arg(nTAAAverage, 0, 'f', 2));
    mText->setStyleSheet("QLabel { background-color : white; color : red; font: 18pt;}");
    mText->setText(tempo);

    if (mPlotWindow)
        delete mPlotWindow;
    mPlotWindow = new YSPlotWindow("Results from N collisions", 1000, 500, this);
    mPlotWindow->Divide(1, 2);
    mPlotWindow->Cd(1);
    mPlotWindow->Add(&hNColl, "L");
    mPlotWindow->Show();
    mPlotWindow->Cd(2);
    mPlotWindow->Add(&hImpact, "L");
    mPlotWindow->Show();

}

//______________________________________________________________________________
void YSMenu::DrawCrossSection()
{
    // Draw the pp cross sections as a function of ecm
    CloseView();
    if (mPlotWindow)
        delete mPlotWindow;
    mPlotWindow = new YSPlotWindow("pp cross sections", 548, 420, this);
    YSCrossSectionpp cspp;
    cspp.SetNumberOfBins(100);
    cspp.SetXMinMax(0.0, 14000);

    cspp.SetType(YSCrossSectionpp::kTotal);
    cspp.FillXValues();
    cspp.FillYValues();
    cspp.SetName("Total");
    mPlotWindow->Add(&cspp);

    cspp.SetType(YSCrossSectionpp::kInelastic);
    cspp.FillXValues();
    cspp.FillYValues();
    cspp.SetName("Inelastic");
    mPlotWindow->Add(&cspp, "S");

    cspp.SetType(YSCrossSectionpp::kElastic);
    cspp.FillXValues();
    cspp.FillYValues();
    cspp.SetName("Elastic");
    mPlotWindow->Add(&cspp, "S");

    mPlotWindow->Show();
}

//______________________________________________________________________________
void YSMenu::DrawCollisionView()
{
    // Draw a GL view of the collision

    CloseView();
    mAview = new YS3dView(this, mCollision);
    if (mAview->stereoType() != QGLView::RedCyanAnaglyph)
        mAview->camera()->setEyeSeparation(0.3f);
    mAview->resize(900, 500);
    mAview->setPosition(QPoint(600,500));
    mAview->show();
}

//______________________________________________________________________________
void YSMenu::DrawCollisions()
{
    // Generate N collisions with random b and draws histograms

    // pop up a window to count the number of events
    mCounterWindow = new QMainWindow;
    mCounterWindow->setWindowTitle("Event counter");
    mCounterWindow->setGeometry(250, 500, 250, 50);
    QWidget * counterDisplay = new QWidget(mCounterWindow);
    mCounterWindow->setCentralWidget(counterDisplay);
    counterDisplay->setLayout(new QHBoxLayout());
    mCountsDisplay = new QLineEdit(counterDisplay);
    mCountsDisplay->setFixedHeight(25);
    mCountsDisplay->setAlignment(Qt::AlignRight);
    counterDisplay->layout()->addWidget(mCountsDisplay);
    QLabel * eventLabel = new QLabel(counterDisplay);
    eventLabel->setText("events");
    counterDisplay->layout()->addWidget(eventLabel);
    mGoButton = new QPushButton(counterDisplay);
    mGoButton->setText("Go");
    counterDisplay->layout()->addWidget(mGoButton);
    mCounterWindow->show();

    connect(mCountsDisplay, SIGNAL(textChanged(QString)), this, SLOT(SetNumberOfEvents()));
    connect(mGoButton, SIGNAL(clicked()), this, SLOT(CollectStatistics()));
   }

//______________________________________________________________________________
void YSMenu::DrawDensityProfile(YSNucleus *nuc)
{
    // Draw the density profile (qcustomplot)
    CloseView();
    if (mPlotWindow)
        delete mPlotWindow;
    mPlotWindow = new YSPlotWindow("Density Profile", 528, 420, this);
    YSWoodSaxon *ws = nuc->DensityProfile();
    ws->FillXValues();
    ws->FillYValues();
    ws->SetName(QString("Density distribution %1%2").arg(nuc->A()).arg(nuc->Symbol()));
    mPlotWindow->Add(ws);
    mPlotWindow->Show();
}

//______________________________________________________________________________
void YSMenu::DrawNucleusView(YSNucleus *nuc)
{
    // Draw a GL view of the nucleus

    CloseView();
    mAview = new YS3dView(0, nuc);
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
    {
        YSPeriodicTable pt;
        SetNucleus(pt.FindElement("H")->FindIsotope(1));
        SetNucleus(pt.FindElement("H")->FindIsotope(1));
        qreal beamEnergy = 1.18; // Z=1 beam energy in TeV
        qreal ene1 = beamEnergy * mCollision->Nucleus(1)->Z() / mCollision->Nucleus(1)->A();
        qreal ene2 = beamEnergy * mCollision->Nucleus(2)->Z() / mCollision->Nucleus(2)->A();
        mCollision->SetEnergies(ene1, ene2);
        SetEnergy();
        break;
    }
    case MENU_KSYSTEMS_PP7:
    {
        YSPeriodicTable pt;
        SetNucleus(pt.FindElement("H")->FindIsotope(1));
        SetNucleus(pt.FindElement("H")->FindIsotope(1));
        qreal beamEnergy = 3.5; // Z=1 beam energy in TeV
        qreal ene1 = beamEnergy * mCollision->Nucleus(1)->Z() / mCollision->Nucleus(1)->A();
        qreal ene2 = beamEnergy * mCollision->Nucleus(2)->Z() / mCollision->Nucleus(2)->A();
        mCollision->SetEnergies(ene1, ene2);
        SetEnergy();
        break;
    }
    case MENU_KSYSTEMS_PP8:
    {
        YSPeriodicTable pt;
        SetNucleus(pt.FindElement("H")->FindIsotope(1));
        SetNucleus(pt.FindElement("H")->FindIsotope(1));
        qreal beamEnergy = 4; // Z=1 beam energy in TeV
        qreal ene1 = beamEnergy * mCollision->Nucleus(1)->Z() / mCollision->Nucleus(1)->A();
        qreal ene2 = beamEnergy * mCollision->Nucleus(2)->Z() / mCollision->Nucleus(2)->A();
        mCollision->SetEnergies(ene1, ene2);
        SetEnergy();
        break;
    }
    case MENU_KSYSTEMS_PP14:
    {
        YSPeriodicTable pt;
        SetNucleus(pt.FindElement("H")->FindIsotope(1));
        SetNucleus(pt.FindElement("H")->FindIsotope(1));
        qreal beamEnergy = 7; // Z=1 beam energy in TeV
        qreal ene1 = beamEnergy * mCollision->Nucleus(1)->Z() / mCollision->Nucleus(1)->A();
        qreal ene2 = beamEnergy * mCollision->Nucleus(2)->Z() / mCollision->Nucleus(2)->A();
        mCollision->SetEnergies(ene1, ene2);
        SetEnergy();
        break;
    }
    case MENU_KSYSTEMS_PPB502:
    {
        YSPeriodicTable pt ;
        SetNucleus(pt.FindElement("H")->FindIsotope(1));
        SetNucleus(pt.FindElement("Pb")->FindIsotope(208));
        qreal beamEnergy = 4; // Z=1 beam energy in TeV
        qreal ene1 = beamEnergy * mCollision->Nucleus(1)->Z() / mCollision->Nucleus(1)->A();
        qreal ene2 = beamEnergy * mCollision->Nucleus(2)->Z() / mCollision->Nucleus(2)->A();
        mCollision->SetEnergies(ene1, ene2);
        SetEnergy();
        break;
    }
    case MENU_KSYSTEMS_PBPB276:
    {
        YSPeriodicTable pt ;
        SetNucleus(pt.FindElement("Pb")->FindIsotope(208));
        SetNucleus(pt.FindElement("Pb")->FindIsotope(208));
        qreal beamEnergy = 3.5; // Z=1 beam energy in TeV
        qreal ene1 = beamEnergy * mCollision->Nucleus(1)->Z() / mCollision->Nucleus(1)->A();
        qreal ene2 = beamEnergy * mCollision->Nucleus(2)->Z() / mCollision->Nucleus(2)->A();
        mCollision->SetEnergies(ene1, ene2);
        SetEnergy();
        break;
    }
    case MENU_KSYSTEMS_PBPB552:
    {
        YSPeriodicTable pt ;
        SetNucleus(pt.FindElement("Pb")->FindIsotope(208));
        SetNucleus(pt.FindElement("Pb")->FindIsotope(208));
        qreal beamEnergy = 7; // Z=1 beam energy in TeV
        qreal ene1 = beamEnergy * mCollision->Nucleus(1)->Z() / mCollision->Nucleus(1)->A();
        qreal ene2 = beamEnergy * mCollision->Nucleus(2)->Z() / mCollision->Nucleus(2)->A();
        mCollision->SetEnergies(ene1, ene2);
        SetEnergy();
        break;
    }
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
        DrawCollisionView();
        break;
    }
    case MENU_DRAW_CC:
    {
        DrawCollisions();
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

    mAene->setVisible(true);
}

//______________________________________________________________________________
void YSMenu::SelectEnergy()
{
    // selects the colliding energy
    YSEnergySetter *eneset = new YSEnergySetter(mMenuBar, mCollision);
    connect(eneset, SIGNAL(destroyed()), this, SLOT(SetEnergy()));
    eneset->show();
    mAene->setVisible(true);
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
    mDrawCC->setData(QVariant(MENU_DRAW_CC));
    mDrawD->setData(QVariant(MENU_DRAW_D));

    mDrawA->addAction(mDrawA1);
    mDrawDP->addAction(mDrawDP1);
    if(*(mCollision->Nucleus(1)) != *(mCollision->Nucleus(2))) {
        mDrawA->addAction(mDrawA2);
        mDrawDP->addAction(mDrawDP2);
    }
    mDrawA->menuAction()->setVisible(true);
    mDrawDP->menuAction()->setVisible(true);
    mDrawCS->setVisible(true);
    mDrawC->setVisible(true);
    mDrawCC->setVisible(true);
    mDrawD->setVisible(true);

    mMenuDraw->menuAction()->setVisible(true);
}

//______________________________________________________________________________
void YSMenu::Setb()
{
    //update the menu display
    QString tempo = mText->text();
    tempo.remove(tempo.indexOf("<br>"), tempo.size());
    mText->setText(tempo.append(QString("<br> <center> b = %2 fm </center></body>").
                                arg(mCollision->Getb(), 0, 'f',2)));
    mAview->Setb(mCollision->Getb());
    mCollision->MakeCollision();
    mAview->ReDraw(mCollision->Gamma(1), mCollision->Gamma(2), mCollision->Beta(1), mCollision->Beta(2));
    WriteCollisionInfo(true);
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

//______________________________________________________________________________
void YSMenu::SetNumberOfEvents()
{
    // set the number of events to be generated
 if (mGoButton->text() == "Stop")
     return;
 else
     mCountEvents = mCountsDisplay->text().toUInt();
}
