#include "menu.h"
Menu::Menu(QWidget *parent) :
    QMainWindow(parent)
{

    // Main Window settings
    setWindowTitle("HI Collision Toy");
    resize(800,600);
    setMinimumSize(800,600);

    //===============================================================
    //==1) methode 1 du widget personalisé==========================
    //===  J'ai crée un widget, on l'affiche juste !

//    mIntroWidget = new IntroWidget;
//    mIntroWidget->setText("CoHIT \n A Toy for Heavy-Ion Collisions \n \n by Yves Schutz");
//    setCentralWidget(mIntroWidget);


    //===============================================================
    //==2) methode 2 de la composition avec des widgets
    //on ecrit le texte en HTML... et pour la ligne, on met un <hr/>

    QWidget * centralWidget = new QWidget;
    QLabel * label = new QLabel;
    centralWidget->setLayout(new QVBoxLayout);
    centralWidget->layout()->addWidget(label);
    centralWidget->layout()->setContentsMargins(70,70,70,70);
    centralWidget->setStyleSheet("QWidget {background-color:blue}");
    label->setAutoFillBackground(true);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(QFont("Comic Sans MS", 30));
    label->setFrameShadow(QFrame::Raised);
    label->setFrameShape(QFrame::Panel);
    label->setLineWidth(10);
    label->setStyleSheet("QLabel { background-color : white; color : red; }");
    label->setText("<html>CoHIT \n A Toy for Heavy-Ion Collisions \n \n <hr width=\"60%\"/> by Yves Schutz </html>");
    setCentralWidget(centralWidget);


    //===============================================================
    //==3) methode 3 du QGraphicsView

    //    QGraphicsView * view = new QGraphicsView;
    //    view->setScene(new QGraphicsScene);
    //    view->scene()->setBackgroundBrush(Qt::blue);
    //    view->setResizeAnchor(QGraphicsView::NoAnchor);
    //    QGraphicsRectItem * whiteCenter =  new QGraphicsRectItem(rect().adjusted(70,70,-70,-70));
    //    QGraphicsTextItem * textCenter = new QGraphicsTextItem;
    //    whiteCenter->setBrush(QBrush(Qt::white));
    //    textCenter->setHtml("<html>BOUGE MOI !! CoHIT \n A Toy for Heavy-Ion Collisions \n \n <hr width=\"60%\"/> by Yves Schutz </html>");
    //    textCenter->setDefaultTextColor(Qt::red);
    //    textCenter->setFont(QFont("Comic Sans MS", 30));
    //    view->scene()->addItem(whiteCenter);
    //    view->scene()->addItem(textCenter);
    //    textCenter->setFlag(QGraphicsItem::ItemIsMovable,true);
    //    textCenter->setPos(view->scene()->sceneRect().center());
    //    setCentralWidget(view);



    //===== Creation du menu TYPE 1
    QMenu * systemMenu  = new QMenu("System");
    mActionMenu = new QMenu("Actions");
    systemMenu->addAction("Select from Periodic tables");
    systemMenu->addAction("Select from known system");
    menuBar()->addMenu(systemMenu);
    menuBar()->addMenu(mActionMenu);
    connect(menuBar(),SIGNAL(triggered(QAction*)),this,SLOT(showSomething(QAction*)));

    //===== Creation du menu TYPE 2
    QToolBar * toolbar = new QToolBar;
    toolbar->addActions(systemMenu->actions());
    addToolBar(toolbar);
    connect(toolbar,SIGNAL(actionTriggered(QAction*)),this,SLOT(showSomething(QAction*)));

}

Menu::~Menu()
{
}

void Menu::showSomething(QAction *action)
{

    QMessageBox box(this);
    box.setText(action->text() + "\n on va remplir les actions");
    box.exec(); // a l'inverse de show(), exec() bloque l'application!

    //une fois le dialog validé, on remplis le menu actions
    mActionMenu->clear();
    for (int i=0; i<10; ++i)
        mActionMenu->addAction(QString("action %1").arg(i));

}
