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
    YS3Dview.cpp \
    YSImpactParameterSetter.cpp \
    YSOverlappingCircles.cpp \
    YSCrossSectionpp.cpp \
    YSF1.cpp

HEADERS  += \
    YSMenu.h \
    YSCollision.h \
    YSNucleus.h \
    YSEnergySetter.h \
    YSPlotWindow.h \
    ../qcustomplot/qcustomplot.h \
    YSWoodSaxon.h \
    YS3DView.h \
    YSImpactParameterSetter.h \
    YSOverlappingCircles.h \
    YSCrossSectionpp.h \
    YSF1.h

FORMS    += menu.ui \
    YSPlotWindow.ui
