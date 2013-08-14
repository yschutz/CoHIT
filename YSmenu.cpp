#include <QLabel>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>

#include "YSMenu.h"
YSMenu::YSMenu(QWidget *parent) :
    QMainWindow(parent)
{

    // Main Window settings
    setWindowTitle("HI Collision Toy");
    int windowWidth = 600, windowHeight = 300;
    resize(windowWidth,windowHeight);
    setMinimumSize(windowWidth,windowHeight);

    // define the text box
    mTextBox = new QWidget(this);
    mTextBox->setLayout(new QVBoxLayout());
    int xMargin = windowWidth/10, yMargin = windowHeight / 10;
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
    mMenuSystem  = new QMenu("System");
    mApp = new QAction("Select from &Periodic tables", this);
    mMenuSystem->addAction(mApp);

    mMenuKnownSystems = new QMenu("Select from known system");
    mMenuKnownSystems->addAction("pp at 2.36 TeV");
    mMenuKnownSystems->addAction("pPb at 5.01 TeV");
    mMenuKnownSystems->addAction("pp at 7 TeV");
    mMenuKnownSystems->addAction("pp at 8 TeV");
    mMenuKnownSystems->addAction("PbPb at 2.76 TeV");
    mMenuSystem->addMenu(mMenuKnownSystems);

    mMenuActions = new QMenu("Actions");

    menuBar()->addMenu(mMenuSystem);
    menuBar()->addMenu(mMenuActions);

    connect(menuBar(),SIGNAL(triggered(QAction*)),this,SLOT(HandleMenu(QAction*)));


//    //===== Creation du menu TYPE 2
//    QToolBar * toolbar = new QToolBar;
//    toolbar->addActions(systemMenu->actions());
//    addToolBar(toolbar);
//    connect(toolbar,SIGNAL(actionTriggered(QAction*)),this,SLOT(showSomething(QAction*)));

}

YSMenu::~YSMenu()
{
    delete mApp;
    delete mMenuSystem;
    delete mMenuActions;
    delete mMenuKnownSystems;
    delete mText;
    delete mTextBox;
}

void YSMenu::HandleMenu(QAction *action)
{

    QMessageBox box(this);
    box.setText(action->text() + "\n on va remplir les actions");
    box.exec(); // a l'inverse de show(), exec() bloque l'application!

//    //une fois le dialog validé, on remplis le menu actions
//    mActionMenu->clear();
//    for (int i=0; i<10; ++i)
//        mActionMenu->addAction(QString("action %1").arg(i));

}
