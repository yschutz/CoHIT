#ifndef MENU_H
#define MENU_H

#include <QtWidgets> // inclus tous le module widgets !
//#include "introwidget.h"
class Menu : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

public slots:
    void showSomething(QAction * action);
    
private:
    QLabel * mCenterLabel;
//    IntroWidget * mIntroWidget;
    QMenu * mActionMenu;
};

#endif // MENU_H
