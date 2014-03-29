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
class QMenu;

class YSNucleus;
class YSCollision;
class YSIsotope;
class YS3DView;
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

public slots:
    void HandleMenu(QAction *action);
    void SetNucleus(YSIsotope *iso);
    void SelectEnergy();
    void SetEnergy();
    void Setb();

private:
    void CloseView();
    void DrawCrossSection();
    void DrawDensityProfile(YSNucleus *nuc);
    void DrawCollisionView(YSCollision *coll);
    void DrawNucleusView(YSNucleus *nuc);

    QAction        *mApt, *mAene;                                   // action to select A, energy
    QAction        *mApp236, *mApp7, *mApp8, *mApPb501, *mAPbPb276; // known systems
    YS3DView       *mAview;                                         // a GL view
    YSCollision    *mCollision;                                     // the collidind system
    QAction        *mDrawA1, *mDrawA2, *mDrawDP1, *mDrawDP2;        // action to draw nucleus, density profile
    QAction        *mDrawC, *mDrawCS;                               // action to draw collision, cross section
    QAction        *mDrawD;                                         // action to quit Draw menu
    QMenu          *mMenuSystem, *mMenuDraw;                        // Main menus to select system and drawing options
    QMenu          *mDrawA, *mDrawDP         ;                      // sub menus to select nucleus, density profile, collision
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
    MENU_KSYSTEMS_PPB501,
    MENU_KSYSTEMS_PBPB276,
    MENU_DRAW_A1,
    MENU_DRAW_A2,
    MENU_DRAW_DP1,
    MENU_DRAW_DP2,
    MENU_DRAW_C,
    MENU_DRAW_CS,
    MENU_DRAW_D
};
};

#endif // YSMENU_H
