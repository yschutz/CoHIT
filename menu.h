#ifndef MENU_H
#define MENU_H

#include <QMainWindow>

class QListWidget;
class QListWidgetItem;

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();
    
private:
//    Ui::Menu *ui;
    QListWidget     *mList;
    QListWidgetItem *mListItem;
};

#endif // MENU_H
