
#include <QApplication>
#include <QDebug>
#include <QVector3D>

#include "YSMenu.h"
//#include "YSHydro3d.h"
//#include "YSTest.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    YSMenu w;
    w.show();

//    YSTest * test = new YSTest();
//    test->resize(500, 500);
//    test->SetDisplayOpt(YSTest::kDENSITY);
//    test->GetFluid()->SetViscosity(1.0E-5);
//    test->GetFluid()->SetDt(1.0);
//    test->show();
    return a.exec();
}
