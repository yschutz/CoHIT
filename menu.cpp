#include <QListWidget>
#include <QListWidgetItem>
#include <QPalette>
#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QMainWindow(parent)
//    ui(new Ui::Menu)
{
//    ui->setupUi(this);

    // Main Window settings

    setWindowTitle("HI Collision Toy");
    int xorg = 500, yorg = 500;
    int mwidth = 600, mheight = 300;
    setGeometry(xorg, yorg, mwidth, mheight);
    QPalette menuPalette ;
    menuPalette.setColor(QPalette::Background, Qt::blue);
    setPalette(menuPalette);

    //Add text in the main window

    mList = new QListWidget(this);
    int lwidth  = 500, lheight = 200;
    xorg = (mwidth - lwidth) / 2;
    yorg = (mheight - lheight) / 2;
    mList->setGeometry(xorg, yorg, lwidth, lheight);

    mListItem = new QListWidgetItem(mList);
    mListItem->setTextColor(Qt::red);
    mListItem->setTextAlignment(Qt::AlignHCenter);
    mListItem->setFont(QFont("Comic Sans MS", 30));

    mListItem->setText("CoHIT \n A Toy for Heavy-Ion Collisions \n \n by Yves Schutz");
    mList->addItem(mListItem);

    QLine * line = new QLine(50, 100, 300, 100) ;


}

Menu::~Menu()
{
//    delete ui;
    delete mList;
}
