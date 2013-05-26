/********************************************************************************
** Form generated from reading UI file 'cwidget.ui'
**
** Created: Tue Aug 16 15:01:08 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CWIDGET_H
#define UI_CWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CWidget
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLineEdit *commandline;
    QPushButton *send;
    QTextEdit *log;
    QTextEdit *doc;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CWidget)
    {
        if (CWidget->objectName().isEmpty())
            CWidget->setObjectName(QString::fromUtf8("CWidget"));
        CWidget->resize(752, 451);
        centralWidget = new QWidget(CWidget);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        commandline = new QLineEdit(centralWidget);
        commandline->setObjectName(QString::fromUtf8("commandline"));

        gridLayout->addWidget(commandline, 1, 0, 1, 1);

        send = new QPushButton(centralWidget);
        send->setObjectName(QString::fromUtf8("send"));

        gridLayout->addWidget(send, 1, 1, 1, 1);

        log = new QTextEdit(centralWidget);
        log->setObjectName(QString::fromUtf8("log"));
        log->setReadOnly(true);

        gridLayout->addWidget(log, 0, 0, 1, 2);

        doc = new QTextEdit(centralWidget);
        doc->setObjectName(QString::fromUtf8("doc"));
        doc->setMinimumSize(QSize(300, 0));
        doc->setMaximumSize(QSize(300, 16777215));
        doc->setReadOnly(true);

        gridLayout->addWidget(doc, 0, 2, 2, 1);

        CWidget->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CWidget);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 752, 21));
        CWidget->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CWidget);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CWidget->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CWidget);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CWidget->setStatusBar(statusBar);

        retranslateUi(CWidget);

        QMetaObject::connectSlotsByName(CWidget);
    } // setupUi

    void retranslateUi(QMainWindow *CWidget)
    {
        CWidget->setWindowTitle(QApplication::translate("CWidget", "CWidget", 0, QApplication::UnicodeUTF8));
        send->setText(QApplication::translate("CWidget", "Send", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CWidget: public Ui_CWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CWIDGET_H
