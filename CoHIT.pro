#-------------------------------------------------
#
# Project created by QtCreator 2013-07-23T15:26:23
#
#-------------------------------------------------

QT       += core gui 3d

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = CoHIT

LIBS += -lPeriodicTableLib -lqcustomplot
LIBS += -L/Users/schutz/group/Qt/PeriodicTableLib/build-Debug -L/Users/schutz/group/qt/qcustomplot/build-Release

INCLUDEPATH += /Users/schutz/group/Qt/PeriodicTableLib /Users/schutz/group/qt/qcustomplot

SOURCES += main.cpp \
    YSMenu.cpp \
    YSCollision.cpp \
    YSNucleus.cpp \
    YSEnergySetter.cpp \
    YSPlotWindow.cpp \
    ../qcustomplot/qcustomplot.cpp \
    YSWoodSaxon.cpp \
    YS3dView.cpp \
    YSImpactParameterSetter.cpp \
    YSOverlappingCircles.cpp \
    YSCrossSectionpp.cpp \
    YSF1.cpp \
    YSH1.cpp \
    YSDrawableObject.cpp \
    YSHdro3d.cpp \
    YSGrid3dFloat.cpp \
    YSGrid3dVector.cpp \
    YSGrid3d.cpp \
    YSTest.cpp

HEADERS  += \
    YSMenu.h \
    YSCollision.h \
    YSNucleus.h \
    YSEnergySetter.h \
    YSPlotWindow.h \
    ../qcustomplot/qcustomplot.h \
    YSWoodSaxon.h \
    YSImpactParameterSetter.h \
    YSOverlappingCircles.h \
    YSCrossSectionpp.h \
    YSF1.h \
    YSH1.h \
    YSDrawableObject.h \
    YSHydro3d.h \
    YS3dView.h \
    YSGrid3dFloat.h \
    YSGrid3dVector.h \
    YSGrid3d.h \
    YSTest.h

FORMS    += menu.ui \
    YSPlotWindow.ui
