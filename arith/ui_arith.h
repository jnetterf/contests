/********************************************************************************
** Form generated from reading UI file 'arith.ui'
**
** Created: Sun May 22 18:29:47 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARITH_H
#define UI_ARITH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Arith
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *eqLabel;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QLabel *ptLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Arith)
    {
        if (Arith->objectName().isEmpty())
            Arith->setObjectName(QString::fromUtf8("Arith"));
        Arith->resize(400, 300);
        centralWidget = new QWidget(Arith);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        eqLabel = new QLabel(centralWidget);
        eqLabel->setObjectName(QString::fromUtf8("eqLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("Cambria"));
        font.setPointSize(20);
        eqLabel->setFont(font);
        eqLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(eqLabel, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFont(font);

        gridLayout->addWidget(lineEdit, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);

        ptLabel = new QLabel(centralWidget);
        ptLabel->setObjectName(QString::fromUtf8("ptLabel"));
        ptLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(ptLabel, 0, 0, 1, 1);

        Arith->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Arith);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        Arith->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Arith);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Arith->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Arith);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Arith->setStatusBar(statusBar);

        retranslateUi(Arith);

        QMetaObject::connectSlotsByName(Arith);
    } // setupUi

    void retranslateUi(QMainWindow *Arith)
    {
        Arith->setWindowTitle(QApplication::translate("Arith", "Arith", 0, QApplication::UnicodeUTF8));
        eqLabel->setText(QApplication::translate("Arith", "Equation", 0, QApplication::UnicodeUTF8));
        ptLabel->setText(QApplication::translate("Arith", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Arith: public Ui_Arith {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARITH_H
