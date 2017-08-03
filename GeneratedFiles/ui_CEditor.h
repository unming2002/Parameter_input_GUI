/********************************************************************************
** Form generated from reading UI file 'CEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CEDITOR_H
#define UI_CEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CEditor
{
public:
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTreeWidget *treeWidget;
    QWidget *layoutWidget;
    QVBoxLayout *layout;
    QTextEdit *textEdit;
    QGroupBox *groupBox;

    void setupUi(QWidget *CEditor)
    {
        if (CEditor->objectName().isEmpty())
            CEditor->setObjectName(QStringLiteral("CEditor"));
        CEditor->setWindowModality(Qt::ApplicationModal);
        CEditor->resize(748, 600);
        horizontalLayout = new QHBoxLayout(CEditor);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(CEditor);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        treeWidget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QStringLiteral("2"));
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setColumnCount(2);
        splitter->addWidget(treeWidget);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layout = new QVBoxLayout(layoutWidget);
        layout->setSpacing(6);
        layout->setContentsMargins(11, 11, 11, 11);
        layout->setObjectName(QStringLiteral("layout"));
        layout->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(layoutWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMinimumSize(QSize(220, 0));
        textEdit->setReadOnly(true);

        layout->addWidget(textEdit);

        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(220, 220));

        layout->addWidget(groupBox);

        splitter->addWidget(layoutWidget);

        horizontalLayout->addWidget(splitter);

        horizontalLayout->setStretch(0, 6);

        retranslateUi(CEditor);
        QObject::connect(treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), CEditor, SLOT(slotItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));

        QMetaObject::connectSlotsByName(CEditor);
    } // setupUi

    void retranslateUi(QWidget *CEditor)
    {
        CEditor->setWindowTitle(QApplication::translate("CEditor", "Property Editor", 0));
        groupBox->setTitle(QApplication::translate("CEditor", "Project Setting", 0));
    } // retranslateUi

};

namespace Ui {
    class CEditor: public Ui_CEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CEDITOR_H
