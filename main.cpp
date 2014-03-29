
#include <QApplication>

#include "YSMenu.h"
#include "YSEnergySetter.h"
#include "YSPlotWindow.h"
#include "YSOverlappingCircles.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    YSMenu w;
//    YSPlotWindow w;
//    YSOverlappingCircles w;
    w.show();

    return a.exec();
}
