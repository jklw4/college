/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionintegrid;
    QAction *actionobit;
    QAction *actionspybot;
    QAction *actionwordoffice;
    QAction *actionwstarpage;
    QAction *actiongravira;
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *btn_to_SM2_get;
    QPushButton *btn_to_key_change;
    QPushButton *btn_to_sm3_sign;
    QPushButton *btn_to_sm4_crypto;
    QPushButton *btn_to_sm3_veri;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1014, 739);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/-_\346\211\223\345\274\200\351\241\271\347\233\256.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionintegrid = new QAction(MainWindow);
        actionintegrid->setObjectName(QStringLiteral("actionintegrid"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/-_\347\272\277\346\200\247.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionintegrid->setIcon(icon1);
        actionobit = new QAction(MainWindow);
        actionobit->setObjectName(QStringLiteral("actionobit"));
        actionobit->setIcon(icon1);
        actionspybot = new QAction(MainWindow);
        actionspybot->setObjectName(QStringLiteral("actionspybot"));
        actionspybot->setIcon(icon1);
        actionwordoffice = new QAction(MainWindow);
        actionwordoffice->setObjectName(QStringLiteral("actionwordoffice"));
        actionwordoffice->setIcon(icon1);
        actionwstarpage = new QAction(MainWindow);
        actionwstarpage->setObjectName(QStringLiteral("actionwstarpage"));
        actionwstarpage->setIcon(icon1);
        actiongravira = new QAction(MainWindow);
        actiongravira->setObjectName(QStringLiteral("actiongravira"));
        actiongravira->setIcon(icon1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(240, 100, 501, 101));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(36);
        label->setFont(font);
        btn_to_SM2_get = new QPushButton(centralWidget);
        btn_to_SM2_get->setObjectName(QStringLiteral("btn_to_SM2_get"));
        btn_to_SM2_get->setGeometry(QRect(240, 280, 181, 51));
        btn_to_SM2_get->setIcon(icon1);
        btn_to_key_change = new QPushButton(centralWidget);
        btn_to_key_change->setObjectName(QStringLiteral("btn_to_key_change"));
        btn_to_key_change->setGeometry(QRect(240, 380, 181, 51));
        btn_to_key_change->setStyleSheet(QStringLiteral(""));
        btn_to_key_change->setIcon(icon1);
        btn_to_sm3_sign = new QPushButton(centralWidget);
        btn_to_sm3_sign->setObjectName(QStringLiteral("btn_to_sm3_sign"));
        btn_to_sm3_sign->setGeometry(QRect(550, 280, 181, 51));
        btn_to_sm3_sign->setIcon(icon1);
        btn_to_sm4_crypto = new QPushButton(centralWidget);
        btn_to_sm4_crypto->setObjectName(QStringLiteral("btn_to_sm4_crypto"));
        btn_to_sm4_crypto->setGeometry(QRect(390, 480, 181, 51));
        btn_to_sm4_crypto->setStyleSheet(QStringLiteral(""));
        btn_to_sm4_crypto->setIcon(icon1);
        btn_to_sm3_veri = new QPushButton(centralWidget);
        btn_to_sm3_veri->setObjectName(QStringLiteral("btn_to_sm3_veri"));
        btn_to_sm3_veri->setGeometry(QRect(550, 380, 181, 51));
        btn_to_sm3_veri->setIcon(icon1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1014, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionintegrid);
        menu->addAction(actionobit);
        menu->addAction(actionspybot);
        menu->addAction(actionwordoffice);
        menu->addAction(actionwstarpage);
        menu->addAction(actiongravira);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\212\240\345\257\206\350\256\244\350\257\201\347\263\273\347\273\237", Q_NULLPTR));
        actionintegrid->setText(QApplication::translate("MainWindow", "integrid", Q_NULLPTR));
        actionobit->setText(QApplication::translate("MainWindow", "obit", Q_NULLPTR));
        actionspybot->setText(QApplication::translate("MainWindow", "spybot", Q_NULLPTR));
        actionwordoffice->setText(QApplication::translate("MainWindow", "wordoffice", Q_NULLPTR));
        actionwstarpage->setText(QApplication::translate("MainWindow", "wstarpage", Q_NULLPTR));
        actiongravira->setText(QApplication::translate("MainWindow", "gravira", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\212\240\345\257\206\350\256\244\350\257\201\347\263\273\347\273\237", Q_NULLPTR));
        btn_to_SM2_get->setText(QApplication::translate("MainWindow", "sm2\345\257\206\351\222\245\347\224\237\346\210\220", Q_NULLPTR));
        btn_to_key_change->setText(QApplication::translate("MainWindow", "\345\257\206\351\222\245\344\272\244\346\215\242", Q_NULLPTR));
        btn_to_sm3_sign->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\347\255\276\345\220\215", Q_NULLPTR));
        btn_to_sm4_crypto->setText(QApplication::translate("MainWindow", "sm4\345\212\240\350\247\243\345\257\206", Q_NULLPTR));
        btn_to_sm3_veri->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\351\252\214\347\255\276", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\344\270\273\351\242\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
