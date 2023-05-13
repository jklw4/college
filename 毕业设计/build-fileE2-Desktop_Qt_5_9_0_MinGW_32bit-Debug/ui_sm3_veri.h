/********************************************************************************
** Form generated from reading UI file 'sm3_veri.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SM3_VERI_H
#define UI_SM3_VERI_H

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

class Ui_sm3_veri
{
public:
    QWidget *centralwidget;
    CustomLineEdit *lineEdit_dir_raw_file;
    QPushButton *btn_sm3veri_cho_raw_file;
    CustomLineEdit *lineEdit_signer_id;
    QLabel *label_2;
    CustomLineEdit *lineEdit_dir_sig_file;
    QPushButton *btn_sm3veri_cho_sig_file;
    CustomLineEdit *lineEdit_dir_pub_file;
    QPushButton *btn_sm3veri_cho_pub_file;
    QPushButton *btn_sm3veri_verification;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *sm3_veri)
    {
        if (sm3_veri->objectName().isEmpty())
            sm3_veri->setObjectName(QStringLiteral("sm3_veri"));
        sm3_veri->resize(788, 599);
        centralwidget = new QWidget(sm3_veri);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        lineEdit_dir_raw_file = new CustomLineEdit(centralwidget);
        lineEdit_dir_raw_file->setObjectName(QStringLiteral("lineEdit_dir_raw_file"));
        lineEdit_dir_raw_file->setGeometry(QRect(290, 190, 311, 31));
        btn_sm3veri_cho_raw_file = new QPushButton(centralwidget);
        btn_sm3veri_cho_raw_file->setObjectName(QStringLiteral("btn_sm3veri_cho_raw_file"));
        btn_sm3veri_cho_raw_file->setGeometry(QRect(140, 190, 131, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/-_\346\211\223\345\274\200\351\241\271\347\233\256.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_sm3veri_cho_raw_file->setIcon(icon);
        lineEdit_signer_id = new CustomLineEdit(centralwidget);
        lineEdit_signer_id->setObjectName(QStringLiteral("lineEdit_signer_id"));
        lineEdit_signer_id->setGeometry(QRect(290, 130, 311, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(160, 130, 91, 31));
        lineEdit_dir_sig_file = new CustomLineEdit(centralwidget);
        lineEdit_dir_sig_file->setObjectName(QStringLiteral("lineEdit_dir_sig_file"));
        lineEdit_dir_sig_file->setGeometry(QRect(290, 260, 311, 31));
        btn_sm3veri_cho_sig_file = new QPushButton(centralwidget);
        btn_sm3veri_cho_sig_file->setObjectName(QStringLiteral("btn_sm3veri_cho_sig_file"));
        btn_sm3veri_cho_sig_file->setGeometry(QRect(140, 260, 131, 31));
        btn_sm3veri_cho_sig_file->setIcon(icon);
        lineEdit_dir_pub_file = new CustomLineEdit(centralwidget);
        lineEdit_dir_pub_file->setObjectName(QStringLiteral("lineEdit_dir_pub_file"));
        lineEdit_dir_pub_file->setGeometry(QRect(290, 330, 311, 31));
        btn_sm3veri_cho_pub_file = new QPushButton(centralwidget);
        btn_sm3veri_cho_pub_file->setObjectName(QStringLiteral("btn_sm3veri_cho_pub_file"));
        btn_sm3veri_cho_pub_file->setGeometry(QRect(140, 330, 131, 31));
        btn_sm3veri_cho_pub_file->setIcon(icon);
        btn_sm3veri_verification = new QPushButton(centralwidget);
        btn_sm3veri_verification->setObjectName(QStringLiteral("btn_sm3veri_verification"));
        btn_sm3veri_verification->setGeometry(QRect(300, 420, 121, 41));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(10);
        btn_sm3veri_verification->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/-_\345\217\246\345\255\230\344\270\272.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_sm3veri_verification->setIcon(icon1);
        btn_sm3veri_verification->setIconSize(QSize(30, 30));
        sm3_veri->setCentralWidget(centralwidget);
        menubar = new QMenuBar(sm3_veri);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 788, 26));
        sm3_veri->setMenuBar(menubar);
        statusbar = new QStatusBar(sm3_veri);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        sm3_veri->setStatusBar(statusbar);

        retranslateUi(sm3_veri);

        QMetaObject::connectSlotsByName(sm3_veri);
    } // setupUi

    void retranslateUi(QMainWindow *sm3_veri)
    {
        sm3_veri->setWindowTitle(QApplication::translate("sm3_veri", "\351\252\214\350\257\201\347\255\276\345\220\215", Q_NULLPTR));
        btn_sm3veri_cho_raw_file->setText(QApplication::translate("sm3_veri", "\351\200\211\346\213\251\345\216\237\346\226\207\344\273\266", Q_NULLPTR));
        lineEdit_signer_id->setText(QApplication::translate("sm3_veri", "123hello#@", Q_NULLPTR));
        label_2->setText(QApplication::translate("sm3_veri", "\347\255\276\345\220\215\350\200\205\346\240\207\350\257\206\357\274\232", Q_NULLPTR));
        btn_sm3veri_cho_sig_file->setText(QApplication::translate("sm3_veri", "\351\200\211\346\213\251\347\255\276\345\220\215\346\226\207\344\273\266", Q_NULLPTR));
        btn_sm3veri_cho_pub_file->setText(QApplication::translate("sm3_veri", "\351\200\211\346\213\251\345\205\254\351\222\245\346\226\207\344\273\266", Q_NULLPTR));
        btn_sm3veri_verification->setText(QApplication::translate("sm3_veri", "\351\252\214\347\255\276", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sm3_veri: public Ui_sm3_veri {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SM3_VERI_H
