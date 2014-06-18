//  YSMenu.h
//  Main Menu for the CoHIT project
//
//  Created by Yves Schutz on 09/12/13.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#ifndef YSMENU_H
#define YSMENU_H

#include <QMainWindow>

class QAction;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;

class YSNucleus;
class YSCollision;
class YSIsotope;
class YS3dView;
class YSPlotWindow;
class YSPTView;

#include <QDebug>

class YSMenu : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit YSMenu(QWidget *parent = 0);
    virtual ~YSMenu();

    QMenuBar *MenuBar() const { return mMenuBar; }

    void WriteCollisionInfo(bool reset = false);

public slots:
    void CollectStatistics();
    void HandleMenu(QAction *action);
    void SelectEnergy();
    void Setb();
    void SetEnergy();
    void SetNucleus(YSIsotope *iso);
    void SetNumberOfEvents();

private:
    void CloseView();
    void DrawCrossSection();
    void DrawDensityProfile(YSNucleus *nuc);
    void DrawCollisions();
    void DrawCollisionView();
    void DrawNucleusView(YSNucleus *nuc);

    QAction        *mApt, *mAene;                                   // action to select A, energy
    QAction        *mApp236, *mApp7, *mApp8, *mApp14;               // known systems
    QAction        *mApPb502, *mAPbPb276, *mAPbPb552;               // known systems
    YS3dView       *mAview;                                         // a GL view
    YSCollision    *mCollision;                                     // the collidind system
    QLineEdit      *mCountsDisplay;                                 // to set and display events generated
    unsigned int   mCountEvents;                                    // the number of events
    QMainWindow    *mCounterWindow;                                 // the main windoe that holds the event counter
    QAction        *mDrawA1, *mDrawA2, *mDrawDP1, *mDrawDP2;        // action to draw nucleus, density profile
    QAction        *mDrawC, *mDrawCS, *mDrawCC;                      // action to draw collision, cross section
    QAction        *mDrawD;                                         // action to quit Draw menu
    QMenu          *mMenuSystem, *mMenuDraw;                        // Main menus to select system and drawing options
    QPushButton    *mGoButton;                                      // Button to start collecting statistics
    QMenu          *mDrawA, *mDrawDP;                               // sub menus to select nucleus, density profile, collision
    QMenuBar       *mMenuBar;                                       // a menubar without parent
    QMenu          *mMenuKnownSystems;                              // Menu for known systems
    YSPlotWindow   *mPlotWindow;                                    // a window to display varius plots
    YSPTView       *mPtView;                                        // a view of the periodic table
    QLabel         *mText;                                          // text in the menu frame
    QWidget        *mTextBox;                                       // Box containing mText in menu frame

enum EMenuCommandIdentifier {
    MENU_SYSTEM_PT,
    MENU_SYSTEM_ENE,
    MENU_KSYSTEMS_PP236,
    MENU_KSYSTEMS_PP7,
    MENU_KSYSTEMS_PP8,
    MENU_KSYSTEMS_PP14,
    MENU_KSYSTEMS_PPB502,
    MENU_KSYSTEMS_PBPB276,
    MENU_KSYSTEMS_PBPB552,
    MENU_DRAW_A1,
    MENU_DRAW_A2,
    MENU_DRAW_DP1,
    MENU_DRAW_DP2,
    MENU_DRAW_C,
    MENU_DRAW_CS,
    MENU_DRAW_CC,
    MENU_DRAW_D
};
};

#endif // YSMENU_H
