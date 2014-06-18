/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QAction *actionTest;
    QAction *actionSelect_a_System;
    QAction *actionFrom_Periodic_Table;
    QWidget *centralWidget;
    QListWidget *MenuListWidget;
    QFrame *line;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuSystem;

    void setupUi(QMainWindow *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName(QStringLiteral("Menu"));
        Menu->resize(600, 300);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(0, 0, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        Menu->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Lucida Console"));
        Menu->setFont(font);
        actionTest = new QAction(Menu);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionSelect_a_System = new QAction(Menu);
        actionSelect_a_System->setObjectName(QStringLiteral("actionSelect_a_System"));
        QFont font1;
        font1.setFamily(QStringLiteral("Comic Sans MS"));
        font1.setBold(true);
        font1.setWeight(75);
        actionSelect_a_System->setFont(font1);
        actionFrom_Periodic_Table = new QAction(Menu);
        actionFrom_Periodic_Table->setObjectName(QStringLiteral("actionFrom_Periodic_Table"));
        QFont font2;
        font2.setFamily(QStringLiteral("Comic Sans MS"));
        actionFrom_Periodic_Table->setFont(font2);
        centralWidget = new QWidget(Menu);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MenuListWidget = new QListWidget(centralWidget);
        QBrush brush2(QColor(247, 5, 11, 255));
        brush2.setStyle(Qt::SolidPattern);
        QBrush brush3(QColor(0, 0, 0, 255));
        brush3.setStyle(Qt::NoBrush);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(MenuListWidget);
        __qlistwidgetitem->setBackground(brush3);
        __qlistwidgetitem->setForeground(brush2);
        QBrush brush4(QColor(255, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        QBrush brush5(QColor(12, 0, 0, 255));
        brush5.setStyle(Qt::NoBrush);
        QFont font3;
        font3.setFamily(QStringLiteral("Comic Sans MS"));
        font3.setPointSize(30);
        font3.setKerning(true);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(MenuListWidget);
        __qlistwidgetitem1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qlistwidgetitem1->setFont(font3);
        __qlistwidgetitem1->setBackground(brush5);
        __qlistwidgetitem1->setForeground(brush4);
        QBrush brush6(QColor(255, 0, 0, 255));
        brush6.setStyle(Qt::NoBrush);
        QFont font4;
        font4.setFamily(QStringLiteral("Comic Sans MS"));
        font4.setPointSize(30);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(MenuListWidget);
        __qlistwidgetitem2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qlistwidgetitem2->setFont(font4);
        __qlistwidgetitem2->setForeground(brush6);
        new QListWidgetItem(MenuListWidget);
        new QListWidgetItem(MenuListWidget);
        QBrush brush7(QColor(255, 0, 0, 255));
        brush7.setStyle(Qt::NoBrush);
        QFont font5;
        font5.setFamily(QStringLiteral("Comic Sans MS"));
        font5.setPointSize(20);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(MenuListWidget);
        __qlistwidgetitem3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qlistwidgetitem3->setFont(font5);
        __qlistwidgetitem3->setForeground(brush7);
        MenuListWidget->setObjectName(QStringLiteral("MenuListWidget"));
        MenuListWidget->setGeometry(QRect(60, 25, 480, 200));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MenuListWidget->sizePolicy().hasHeightForWidth());
        MenuListWidget->setSizePolicy(sizePolicy);
        MenuListWidget->setFont(font5);
        MenuListWidget->setFrameShape(QFrame::StyledPanel);
        MenuListWidget->setLineWidth(10);
        MenuListWidget->setMidLineWidth(2);
        MenuListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(210, 160, 231, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        Menu->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(Menu);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Menu->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Menu);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Menu->setStatusBar(statusBar);
        menuBar = new QMenuBar(Menu);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        menuSystem = new QMenu(menuBar);
        menuSystem->setObjectName(QStringLiteral("menuSystem"));
        Menu->setMenuBar(menuBar);

        menuBar->addAction(menuSystem->menuAction());
        menuSystem->addSeparator();
        menuSystem->addAction(actionSelect_a_System);
        menuSystem->addSeparator();
        menuSystem->addAction(actionFrom_Periodic_Table);

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QMainWindow *Menu)
    {
        Menu->setWindowTitle(QApplication::translate("Menu", "HI Collision toy", 0));
        actionTest->setText(QApplication::translate("Menu", "test", 0));
        actionSelect_a_System->setText(QApplication::translate("Menu", "Select a System", 0));
        actionFrom_Periodic_Table->setText(QApplication::translate("Menu", "From Periodic Table", 0));

        const bool __sortingEnabled = MenuListWidget->isSortingEnabled();
        MenuListWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = MenuListWidget->item(1);
        ___qlistwidgetitem->setText(QApplication::translate("Menu", "COHIT", 0));
        QListWidgetItem *___qlistwidgetitem1 = MenuListWidget->item(2);
        ___qlistwidgetitem1->setText(QApplication::translate("Menu", "A Toy for HI Collisions", 0));
        QListWidgetItem *___qlistwidgetitem2 = MenuListWidget->item(5);
        ___qlistwidgetitem2->setText(QApplication::translate("Menu", "by Yves Schutz", 0));
        MenuListWidget->setSortingEnabled(__sortingEnabled);

        menuSystem->setTitle(QApplication::translate("Menu", "System", 0));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
