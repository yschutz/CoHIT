#include <QApplication>
#include "YSmenu.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    YSMenu w;
    w.show();
    
    return a.exec();
}
