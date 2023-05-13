/********************************************************************************
** Form generated from reading UI file 'sm4_crypto.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SM4_CRYPTO_H
#define UI_SM4_CRYPTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <customlineedit.h>

QT_BEGIN_NAMESPACE

class Ui_sm4_crypto
{
public:
    QWidget *centralwidget;
    QPushButton *btn_sm4_crypto_cho_shared_key_file;
    QPushButton *btn_sm4_crypto_cho_raw_file;
    CustomLineEdit *lineEdit_sm4_crypto_dir_shared_key_file;
    CustomLineEdit *lineEdit_sm4_crypto_dir_raw_file;
    QPushButton *btn_sm4_crypto_encryption;
    QPushButton *btn_sm4_crypto_decryption;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *sm4_crypto)
    {
        if (sm4_crypto->objectName().isEmpty())
            sm4_crypto->setObjectName(QStringLiteral("sm4_crypto"));
        sm4_crypto->resize(766, 518);
        centralwidget = new QWidget(sm4_crypto);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        btn_sm4_crypto_cho_shared_key_file = new QPushButton(centralwidget);
        btn_sm4_crypto_cho_shared_key_file->setObjectName(QStringLiteral("btn_sm4_crypto_cho_shared_key_file"));
        btn_sm4_crypto_cho_shared_key_file->setGeometry(QRect(140, 200, 131, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/-_\346\211\223\345\274\200\351\241\271\347\233\256.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_sm4_crypto_cho_shared_key_file->setIcon(icon);
        btn_sm4_crypto_cho_raw_file = new QPushButton(centralwidget);
        btn_sm4_crypto_cho_raw_file->setObjectName(QStringLiteral("btn_sm4_crypto_cho_raw_file"));
        btn_sm4_crypto_cho_raw_file->setGeometry(QRect(140, 130, 131, 41));
        btn_sm4_crypto_cho_raw_file->setIcon(icon);
        lineEdit_sm4_crypto_dir_shared_key_file = new CustomLineEdit(centralwidget);
        lineEdit_sm4_crypto_dir_shared_key_file->setObjectName(QStringLiteral("lineEdit_sm4_crypto_dir_shared_key_file"));
        lineEdit_sm4_crypto_dir_shared_key_file->setGeometry(QRect(290, 200, 321, 41));
        lineEdit_sm4_crypto_dir_raw_file = new CustomLineEdit(centralwidget);
        lineEdit_sm4_crypto_dir_raw_file->setObjectName(QStringLiteral("lineEdit_sm4_crypto_dir_raw_file"));
        lineEdit_sm4_crypto_dir_raw_file->setGeometry(QRect(290, 130, 321, 41));
        btn_sm4_crypto_encryption = new QPushButton(centralwidget);
        btn_sm4_crypto_encryption->setObjectName(QStringLiteral("btn_sm4_crypto_encryption"));
        btn_sm4_crypto_encryption->setGeometry(QRect(210, 300, 121, 51));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/-_\345\217\246\345\255\230\344\270\272.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_sm4_crypto_encryption->setIcon(icon1);
        btn_sm4_crypto_decryption = new QPushButton(centralwidget);
        btn_sm4_crypto_decryption->setObjectName(QStringLiteral("btn_sm4_crypto_decryption"));
        btn_sm4_crypto_decryption->setGeometry(QRect(390, 300, 121, 51));
        btn_sm4_crypto_decryption->setIcon(icon1);
        sm4_crypto->setCentralWidget(centralwidget);
        menubar = new QMenuBar(sm4_crypto);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 766, 26));
        sm4_crypto->setMenuBar(menubar);
        statusbar = new QStatusBar(sm4_crypto);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        sm4_crypto->setStatusBar(statusbar);

        retranslateUi(sm4_crypto);

        QMetaObject::connectSlotsByName(sm4_crypto);
    } // setupUi

    void retranslateUi(QMainWindow *sm4_crypto)
    {
        sm4_crypto->setWindowTitle(QApplication::translate("sm4_crypto", "\346\226\207\344\273\266\345\212\240\350\247\243\345\257\206", Q_NULLPTR));
        btn_sm4_crypto_cho_shared_key_file->setText(QApplication::translate("sm4_crypto", "\351\200\211\346\213\251\345\205\261\344\272\253\345\257\206\351\222\245", Q_NULLPTR));
        btn_sm4_crypto_cho_raw_file->setText(QApplication::translate("sm4_crypto", "\351\200\211\346\213\251\345\216\237\346\226\207\344\273\266", Q_NULLPTR));
        lineEdit_sm4_crypto_dir_shared_key_file->setText(QString());
        lineEdit_sm4_crypto_dir_raw_file->setText(QString());
        btn_sm4_crypto_encryption->setText(QApplication::translate("sm4_crypto", "\345\212\240\345\257\206\345\271\266\344\277\235\345\255\230", Q_NULLPTR));
        btn_sm4_crypto_decryption->setText(QApplication::translate("sm4_crypto", "\350\247\243\345\257\206\345\271\266\344\277\235\345\255\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sm4_crypto: public Ui_sm4_crypto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SM4_CRYPTO_H
