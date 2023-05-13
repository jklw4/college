/********************************************************************************
** Form generated from reading UI file 'sm3_sign.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SM3_SIGN_H
#define UI_SM3_SIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <customlineedit.h>

QT_BEGIN_NAMESPACE

class Ui_sm3_sign
{
public:
    QWidget *centralwidget;
    QPushButton *btn_sm3sign_sign;
    CustomLineEdit *lineEdit_dir_raw_file;
    QPushButton *btn_sm3sign_cho_raw_file;
    CustomLineEdit *lineEdit_dir_pri_file;
    QPushButton *btn_sm3sign_cho_pri_file;
    CustomLineEdit *lineEdit_dir_signed_file;
    QPushButton *btn_sm3sign_cho_signed_dir;
    CustomLineEdit *lineEdit_signer_id;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *sm3_sign)
    {
        if (sm3_sign->objectName().isEmpty())
            sm3_sign->setObjectName(QStringLiteral("sm3_sign"));
        sm3_sign->resize(763, 611);
        centralwidget = new QWidget(sm3_sign);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        btn_sm3sign_sign = new QPushButton(centralwidget);
        btn_sm3sign_sign->setObjectName(QStringLiteral("btn_sm3sign_sign"));
        btn_sm3sign_sign->setGeometry(QRect(280, 380, 121, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/-_\345\217\246\345\255\230\344\270\272.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_sm3sign_sign->setIcon(icon);
        lineEdit_dir_raw_file = new CustomLineEdit(centralwidget);
        lineEdit_dir_raw_file->setObjectName(QStringLiteral("lineEdit_dir_raw_file"));
        lineEdit_dir_raw_file->setGeometry(QRect(280, 170, 311, 31));
        btn_sm3sign_cho_raw_file = new QPushButton(centralwidget);
        btn_sm3sign_cho_raw_file->setObjectName(QStringLiteral("btn_sm3sign_cho_raw_file"));
        btn_sm3sign_cho_raw_file->setGeometry(QRect(110, 170, 131, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/-_\346\211\223\345\274\200\351\241\271\347\233\256.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_sm3sign_cho_raw_file->setIcon(icon1);
        lineEdit_dir_pri_file = new CustomLineEdit(centralwidget);
        lineEdit_dir_pri_file->setObjectName(QStringLiteral("lineEdit_dir_pri_file"));
        lineEdit_dir_pri_file->setGeometry(QRect(280, 240, 311, 31));
        btn_sm3sign_cho_pri_file = new QPushButton(centralwidget);
        btn_sm3sign_cho_pri_file->setObjectName(QStringLiteral("btn_sm3sign_cho_pri_file"));
        btn_sm3sign_cho_pri_file->setGeometry(QRect(110, 240, 131, 31));
        btn_sm3sign_cho_pri_file->setIcon(icon1);
        lineEdit_dir_signed_file = new CustomLineEdit(centralwidget);
        lineEdit_dir_signed_file->setObjectName(QStringLiteral("lineEdit_dir_signed_file"));
        lineEdit_dir_signed_file->setGeometry(QRect(280, 310, 311, 31));
        btn_sm3sign_cho_signed_dir = new QPushButton(centralwidget);
        btn_sm3sign_cho_signed_dir->setObjectName(QStringLiteral("btn_sm3sign_cho_signed_dir"));
        btn_sm3sign_cho_signed_dir->setGeometry(QRect(110, 310, 131, 31));
        btn_sm3sign_cho_signed_dir->setIcon(icon1);
        lineEdit_signer_id = new CustomLineEdit(centralwidget);
        lineEdit_signer_id->setObjectName(QStringLiteral("lineEdit_signer_id"));
        lineEdit_signer_id->setGeometry(QRect(280, 110, 311, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 110, 91, 31));
        sm3_sign->setCentralWidget(centralwidget);
        menubar = new QMenuBar(sm3_sign);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 763, 26));
        sm3_sign->setMenuBar(menubar);
        statusbar = new QStatusBar(sm3_sign);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        sm3_sign->setStatusBar(statusbar);

        retranslateUi(sm3_sign);

        QMetaObject::connectSlotsByName(sm3_sign);
    } // setupUi

    void retranslateUi(QMainWindow *sm3_sign)
    {
        sm3_sign->setWindowTitle(QApplication::translate("sm3_sign", "\346\226\207\344\273\266\347\255\276\345\220\215", Q_NULLPTR));
        btn_sm3sign_sign->setText(QApplication::translate("sm3_sign", "\347\255\276\345\220\215\345\271\266\344\277\235\345\255\230", Q_NULLPTR));
        btn_sm3sign_cho_raw_file->setText(QApplication::translate("sm3_sign", "\351\200\211\346\213\251\345\216\237\346\226\207\344\273\266", Q_NULLPTR));
        btn_sm3sign_cho_pri_file->setText(QApplication::translate("sm3_sign", "\351\200\211\346\213\251\347\247\201\351\222\245\346\226\207\344\273\266", Q_NULLPTR));
        btn_sm3sign_cho_signed_dir->setText(QApplication::translate("sm3_sign", "\351\200\211\346\213\251\344\277\235\345\255\230\350\267\257\345\276\204", Q_NULLPTR));
        lineEdit_signer_id->setText(QApplication::translate("sm3_sign", "123hello#@", Q_NULLPTR));
        label_2->setText(QApplication::translate("sm3_sign", "\347\255\276\345\220\215\350\200\205\346\240\207\350\257\206\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sm3_sign: public Ui_sm3_sign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SM3_SIGN_H
