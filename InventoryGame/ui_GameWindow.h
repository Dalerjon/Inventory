/********************************************************************************
** Form generated from reading UI file 'GameWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "dropabletable.h"

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *mainMenuWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *startBtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *closeBtn;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QWidget *gamePanelWidget;
    QGridLayout *gridLayout;
    QWidget *itemWidget;
    QVBoxLayout *verticalLayout_2;
    DropableTable *objTableWidget;
    QPushButton *menuBtn;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_5;
    DropableTable *invTableWidget;
    QWidget *statusWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *statusLb;

    void setupUi(QMainWindow *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QStringLiteral("GameWindow"));
        GameWindow->resize(812, 629);
        GameWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        centralwidget = new QWidget(GameWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(12, 12, 12, 12);
        mainMenuWidget = new QWidget(centralwidget);
        mainMenuWidget->setObjectName(QStringLiteral("mainMenuWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainMenuWidget->sizePolicy().hasHeightForWidth());
        mainMenuWidget->setSizePolicy(sizePolicy);
        mainMenuWidget->setMaximumSize(QSize(16777215, 45));
        horizontalLayout = new QHBoxLayout(mainMenuWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        startBtn = new QPushButton(mainMenuWidget);
        startBtn->setObjectName(QStringLiteral("startBtn"));
        startBtn->setMinimumSize(QSize(250, 23));
        startBtn->setAutoDefault(false);
        startBtn->setFlat(false);

        horizontalLayout->addWidget(startBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        closeBtn = new QPushButton(mainMenuWidget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setMinimumSize(QSize(250, 23));
        closeBtn->setFlat(false);

        horizontalLayout->addWidget(closeBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addWidget(mainMenuWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        gamePanelWidget = new QWidget(centralwidget);
        gamePanelWidget->setObjectName(QStringLiteral("gamePanelWidget"));
        gamePanelWidget->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(gamePanelWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(50, 50, 50, 50);
        itemWidget = new QWidget(gamePanelWidget);
        itemWidget->setObjectName(QStringLiteral("itemWidget"));
        verticalLayout_2 = new QVBoxLayout(itemWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        objTableWidget = new DropableTable(itemWidget);
        if (objTableWidget->columnCount() < 1)
            objTableWidget->setColumnCount(1);
        if (objTableWidget->rowCount() < 1)
            objTableWidget->setRowCount(1);
        objTableWidget->setObjectName(QStringLiteral("objTableWidget"));
        objTableWidget->setMinimumSize(QSize(150, 150));
        objTableWidget->setMaximumSize(QSize(150, 150));
        objTableWidget->setRowCount(1);
        objTableWidget->setColumnCount(1);
        objTableWidget->horizontalHeader()->setVisible(false);
        objTableWidget->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(objTableWidget);

        menuBtn = new QPushButton(itemWidget);
        menuBtn->setObjectName(QStringLiteral("menuBtn"));
        menuBtn->setAutoFillBackground(false);
        menuBtn->setCheckable(false);
        menuBtn->setAutoRepeat(false);
        menuBtn->setAutoExclusive(false);
        menuBtn->setAutoDefault(false);
        menuBtn->setFlat(false);

        verticalLayout_2->addWidget(menuBtn);


        gridLayout->addWidget(itemWidget, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 3, 1, 1);

        invTableWidget = new DropableTable(gamePanelWidget);
        if (invTableWidget->columnCount() < 3)
            invTableWidget->setColumnCount(3);
        if (invTableWidget->rowCount() < 3)
            invTableWidget->setRowCount(3);
        invTableWidget->setObjectName(QStringLiteral("invTableWidget"));
        invTableWidget->setMinimumSize(QSize(452, 452));
        invTableWidget->setMaximumSize(QSize(452, 452));
        invTableWidget->setFrameShape(QFrame::StyledPanel);
        invTableWidget->setFrameShadow(QFrame::Sunken);
        invTableWidget->setLineWidth(1);
        invTableWidget->setRowCount(3);
        invTableWidget->setColumnCount(3);
        invTableWidget->horizontalHeader()->setVisible(false);
        invTableWidget->horizontalHeader()->setHighlightSections(true);
        invTableWidget->verticalHeader()->setVisible(false);

        gridLayout->addWidget(invTableWidget, 0, 0, 1, 1);


        verticalLayout->addWidget(gamePanelWidget);

        statusWidget = new QWidget(centralwidget);
        statusWidget->setObjectName(QStringLiteral("statusWidget"));
        horizontalLayout_2 = new QHBoxLayout(statusWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        statusLb = new QLabel(statusWidget);
        statusLb->setObjectName(QStringLiteral("statusLb"));

        horizontalLayout_2->addWidget(statusLb);


        verticalLayout->addWidget(statusWidget);

        GameWindow->setCentralWidget(centralwidget);

        retranslateUi(GameWindow);

        menuBtn->setDefault(false);


        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "Inventory", 0));
        startBtn->setText(QApplication::translate("GameWindow", "Start", 0));
        closeBtn->setText(QApplication::translate("GameWindow", "Close", 0));
        menuBtn->setText(QApplication::translate("GameWindow", "Main menu", 0));
        statusLb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
