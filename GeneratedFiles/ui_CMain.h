/********************************************************************************
** Form generated from reading UI file 'CMain.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAIN_H
#define UI_CMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMainClass
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *butLoad;
    QPushButton *butSave;
    QSpacerItem *horizontalSpacer;
    QPushButton *butPreference;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QPushButton *butUtility;
    QPushButton *butSPARTS;
    QPushButton *butPICA;
    QPushButton *butFluMod;
    QPushButton *butNSMod;
    QPushButton *butProfiling;
    QPushButton *butChemRateMod;

    void setupUi(QWidget *CMainClass)
    {
        if (CMainClass->objectName().isEmpty())
            CMainClass->setObjectName(QStringLiteral("CMainClass"));
        CMainClass->resize(640, 372);
        verticalLayout = new QVBoxLayout(CMainClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));

        verticalLayout->addLayout(horizontalLayout_3);

        groupBox = new QGroupBox(CMainClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        butLoad = new QPushButton(groupBox);
        butLoad->setObjectName(QStringLiteral("butLoad"));

        horizontalLayout_2->addWidget(butLoad);

        butSave = new QPushButton(groupBox);
        butSave->setObjectName(QStringLiteral("butSave"));

        horizontalLayout_2->addWidget(butSave);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        butPreference = new QPushButton(groupBox);
        butPreference->setObjectName(QStringLiteral("butPreference"));

        horizontalLayout_2->addWidget(butPreference);


        verticalLayout->addWidget(groupBox);

        scrollArea = new QScrollArea(CMainClass);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1448, 250));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        butUtility = new QPushButton(scrollAreaWidgetContents);
        butUtility->setObjectName(QStringLiteral("butUtility"));
        butUtility->setMinimumSize(QSize(200, 200));
        butUtility->setMaximumSize(QSize(200, 200));

        horizontalLayout->addWidget(butUtility);

        butSPARTS = new QPushButton(scrollAreaWidgetContents);
        butSPARTS->setObjectName(QStringLiteral("butSPARTS"));
        butSPARTS->setMinimumSize(QSize(200, 200));
        butSPARTS->setMaximumSize(QSize(200, 200));

        horizontalLayout->addWidget(butSPARTS);

        butPICA = new QPushButton(scrollAreaWidgetContents);
        butPICA->setObjectName(QStringLiteral("butPICA"));
        butPICA->setMinimumSize(QSize(200, 200));
        butPICA->setMaximumSize(QSize(200, 200));

        horizontalLayout->addWidget(butPICA);

        butFluMod = new QPushButton(scrollAreaWidgetContents);
        butFluMod->setObjectName(QStringLiteral("butFluMod"));
        butFluMod->setMinimumSize(QSize(200, 200));
        butFluMod->setMaximumSize(QSize(200, 200));

        horizontalLayout->addWidget(butFluMod);

        butNSMod = new QPushButton(scrollAreaWidgetContents);
        butNSMod->setObjectName(QStringLiteral("butNSMod"));
        butNSMod->setMinimumSize(QSize(200, 200));
        butNSMod->setMaximumSize(QSize(200, 200));

        horizontalLayout->addWidget(butNSMod);

        butProfiling = new QPushButton(scrollAreaWidgetContents);
        butProfiling->setObjectName(QStringLiteral("butProfiling"));
        butProfiling->setMinimumSize(QSize(200, 200));
        butProfiling->setMaximumSize(QSize(200, 200));

        horizontalLayout->addWidget(butProfiling);

        butChemRateMod = new QPushButton(scrollAreaWidgetContents);
        butChemRateMod->setObjectName(QStringLiteral("butChemRateMod"));
        butChemRateMod->setMinimumSize(QSize(200, 200));
        butChemRateMod->setMaximumSize(QSize(200, 200));

        horizontalLayout->addWidget(butChemRateMod);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(CMainClass);
        QObject::connect(butLoad, SIGNAL(clicked()), CMainClass, SLOT(slotLoadProject()));
        QObject::connect(butSave, SIGNAL(clicked()), CMainClass, SLOT(slotSaveProject()));
        QObject::connect(butPreference, SIGNAL(clicked()), CMainClass, SLOT(slotPreference()));

        QMetaObject::connectSlotsByName(CMainClass);
    } // setupUi

    void retranslateUi(QWidget *CMainClass)
    {
        CMainClass->setWindowTitle(QApplication::translate("CMainClass", "RAPIT Platform", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("CMainClass", "Project File", Q_NULLPTR));
        butLoad->setText(QApplication::translate("CMainClass", "Load Project File...", Q_NULLPTR));
        butSave->setText(QApplication::translate("CMainClass", "Save Project File...", Q_NULLPTR));
        butPreference->setText(QApplication::translate("CMainClass", "Preference", Q_NULLPTR));
        butUtility->setText(QApplication::translate("CMainClass", "UltraUtility", Q_NULLPTR));
        butSPARTS->setText(QApplication::translate("CMainClass", "UltraSPARATS", Q_NULLPTR));
        butPICA->setText(QApplication::translate("CMainClass", "UltraPICA", Q_NULLPTR));
        butFluMod->setText(QApplication::translate("CMainClass", "UltraFluMod", Q_NULLPTR));
        butNSMod->setText(QApplication::translate("CMainClass", "UltraNSMod", Q_NULLPTR));
        butProfiling->setText(QApplication::translate("CMainClass", "UltraProfiling", Q_NULLPTR));
        butChemRateMod->setText(QApplication::translate("CMainClass", "UltraChemRateMod", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CMainClass: public Ui_CMainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAIN_H
