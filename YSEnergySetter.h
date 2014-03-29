//
//  YSEnergySetter.h
//  Widget for setting the collision energy
//
//  Created by Yves Schutz on 09/12/13.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#ifndef YSENERGYSETTER_H
#define YSENERGYSETTER_H

#include <QObject>
#include <QWidget>

class QAction;
class QGroupBox;
class QLabel;
class QMenu;
class QMenuBar;
class QRadioButton;
class QSlider;
class QLineEdit;

class YSCollision;

class YSEnergySetter : public QWidget
{
    Q_OBJECT

public:
    YSEnergySetter(YSCollision *);
    YSEnergySetter(QMenuBar *, YSCollision *);
    virtual ~YSEnergySetter();

    void  AddToMenu(QMenuBar *);

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:
    void  CreateActions();
    void  CreateABBox();
    void  CreateBeamsBox();
    void  CreateMenus();
    void  CreateSBox();
    void  Draw();
    void  SetColl(YSCollision *coll) { mColl = coll; }

public slots:
    void Done();
    void ReadSlider(int);
    void SetSliderScale();
    void SetSliderPos(const QString);

private:
    QGroupBox    *mABBox;                 // box with radio buttons to select accelerator
    QAction      *mActionQuit;            // the quit action in the menu
    QLabel       *mB1Label, *mB2Label;    // beams specie label
    QLineEdit    *mB1VBox, *mB2VBox;      // box with beams energy
    QGroupBox    *mBeamsBox;              // box to display beam energies
    YSCollision  *mColl;                  // colliding sytem
    qreal        mEnergyHigh, mEnergyLow; // max and min energy of the accelerator
    QSlider      *mEnergySlider;          // the slider to select the enrgy in TeV for Z = 1
    QRadioButton *mLHC, *mRHIC, *mSPS;    // radio button to select accelerator
    QMenu        *mMenu;                  // the menu in the menuBar
    QMenuBar     *mMenuBar;               // the common menubar
    QGroupBox    *mSBox;                  // box with slider
    int          mScaleHigh, mScaleLow;   // low and hig scale od slider
    bool         mSliderFlag;             // a flag to control behaviour od slider
    qreal        mSliderPos;              // current positin of slider
    QLineEdit    *mSValueBox;             // to display the current value of the slider
    QLabel       *mTeVLabel;              // TeV/c label
    QLabel       *mTeVLabel1, *mTeVLabel2;// TeV label
};

#endif // YSENERGYSETTER_H
