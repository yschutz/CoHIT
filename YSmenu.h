#ifndef YSMENU_H
#define YSMENU_H

#include <QMainWindow>

class QAction;
class QLabel;
class QMenu;

class YSMenu : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit YSMenu(QWidget *parent = 0);
    ~YSMenu();

public slots:
    void HandleMenu(QAction * action);
    
private:
    QAction *mApp;                           // list of actions
    QMenu   *mMenuSystem, *mMenuActions;     // Menu entries
    QMenu   *mMenuKnownSystems;
    QLabel  *mText;                          // text in the menu frame
    QWidget *mTextBox;                       // Box containing mText in menu frame
};

#endif // YSMENU_H
