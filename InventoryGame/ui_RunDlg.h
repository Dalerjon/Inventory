/********************************************************************************
** Form generated from reading UI file 'RunDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNDLG_H
#define UI_RUNDLG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RunDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *serverRbx;
    QRadioButton *clientRbx;
    QHBoxLayout *horizontalLayout_2;
    QWidget *hidenWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *ipLbl;
    QLineEdit *ipEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *RunDlg)
    {
        if (RunDlg->objectName().isEmpty())
            RunDlg->setObjectName(QStringLiteral("RunDlg"));
        RunDlg->setWindowModality(Qt::ApplicationModal);
        RunDlg->resize(400, 114);
        RunDlg->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(RunDlg);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        serverRbx = new QRadioButton(RunDlg);
        serverRbx->setObjectName(QStringLiteral("serverRbx"));
        serverRbx->setChecked(true);

        horizontalLayout->addWidget(serverRbx);

        clientRbx = new QRadioButton(RunDlg);
        clientRbx->setObjectName(QStringLiteral("clientRbx"));

        horizontalLayout->addWidget(clientRbx);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        hidenWidget = new QWidget(RunDlg);
        hidenWidget->setObjectName(QStringLiteral("hidenWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(hidenWidget->sizePolicy().hasHeightForWidth());
        hidenWidget->setSizePolicy(sizePolicy);
        hidenWidget->setMinimumSize(QSize(0, 0));
        horizontalLayout_4 = new QHBoxLayout(hidenWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        ipLbl = new QLabel(hidenWidget);
        ipLbl->setObjectName(QStringLiteral("ipLbl"));

        horizontalLayout_4->addWidget(ipLbl);

        ipEdit = new QLineEdit(hidenWidget);
        ipEdit->setObjectName(QStringLiteral("ipEdit"));

        horizontalLayout_4->addWidget(ipEdit);


        horizontalLayout_2->addWidget(hidenWidget);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        okBtn = new QPushButton(RunDlg);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        horizontalLayout_3->addWidget(okBtn);

        cancelBtn = new QPushButton(RunDlg);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout_3->addWidget(cancelBtn);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(RunDlg);

        QMetaObject::connectSlotsByName(RunDlg);
    } // setupUi

    void retranslateUi(QDialog *RunDlg)
    {
        RunDlg->setWindowTitle(QApplication::translate("RunDlg", "Start as..", 0));
        serverRbx->setText(QApplication::translate("RunDlg", "Server", 0));
        clientRbx->setText(QApplication::translate("RunDlg", "Client", 0));
        ipLbl->setText(QApplication::translate("RunDlg", "IP address:", 0));
        okBtn->setText(QApplication::translate("RunDlg", "OK", 0));
        cancelBtn->setText(QApplication::translate("RunDlg", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class RunDlg: public Ui_RunDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNDLG_H
