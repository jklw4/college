/********************************************************************************
** Form generated from reading UI file 'sm3_trace.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SM3_TRACE_H
#define UI_SM3_TRACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sm3_trace
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *sm3_trace)
    {
        if (sm3_trace->objectName().isEmpty())
            sm3_trace->setObjectName(QStringLiteral("sm3_trace"));
        sm3_trace->resize(800, 600);
        centralwidget = new QWidget(sm3_trace);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(310, 310, 72, 15));
        sm3_trace->setCentralWidget(centralwidget);
        menubar = new QMenuBar(sm3_trace);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        sm3_trace->setMenuBar(menubar);
        statusbar = new QStatusBar(sm3_trace);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        sm3_trace->setStatusBar(statusbar);

        retranslateUi(sm3_trace);

        QMetaObject::connectSlotsByName(sm3_trace);
    } // setupUi

    void retranslateUi(QMainWindow *sm3_trace)
    {
        sm3_trace->setWindowTitle(QApplication::translate("sm3_trace", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("sm3_trace", "sm3_trace", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sm3_trace: public Ui_sm3_trace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SM3_TRACE_H
