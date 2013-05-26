/********************************************************************************
** Form generated from reading UI file 'tablecolumn.ui'
**
** Created: Thu Jun 30 12:25:57 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLECOLUMN_H
#define UI_TABLECOLUMN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTableView>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include "cclineedit.h"

QT_BEGIN_NAMESPACE

class Ui_TableColumn
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    Kst::CCLineEdit *lineEdit;
    QToolButton *toolButton;
    QTableView *tableView;

    void setupUi(QFrame *TableColumn)
    {
        if (TableColumn->objectName().isEmpty())
            TableColumn->setObjectName(QString::fromUtf8("TableColumn"));
        TableColumn->resize(322, 584);
        TableColumn->setFrameShape(QFrame::StyledPanel);
        TableColumn->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(TableColumn);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(TableColumn);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        lineEdit = new Kst::CCLineEdit(TableColumn);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_4->addWidget(lineEdit);

        toolButton = new QToolButton(TableColumn);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        horizontalLayout_4->addWidget(toolButton);


        verticalLayout->addLayout(horizontalLayout_4);

        tableView = new QTableView(TableColumn);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);


        retranslateUi(TableColumn);

        QMetaObject::connectSlotsByName(TableColumn);
    } // setupUi

    void retranslateUi(QFrame *TableColumn)
    {
        TableColumn->setWindowTitle(QApplication::translate("TableColumn", "Frame", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TableColumn", "=", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("TableColumn", "&Detach", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TableColumn: public Ui_TableColumn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLECOLUMN_H
