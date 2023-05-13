/********************************************************************************
** Form generated from reading UI file 'key_change.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEY_CHANGE_H
#define UI_KEY_CHANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <customlineedit.h>

QT_BEGIN_NAMESPACE

class Ui_key_change
{
public:
    QWidget *centralwidget;
    QPushButton *btn_key_change_get_shared_key;
    QLabel *label_2;
    QFrame *line;
    QLabel *label_3;
    QPushButton *btn_key_change_cho_pri_file_1;
    CustomLineEdit *lineEdit_key_change_dir_pri_file_1;
    QPushButton *btn_key_change_cho_pub_file_1;
    CustomLineEdit *lineEdit_key_change_dir_pub_file_1;
    QPushButton *btn_key_change_cho_pri_file_2;
    QPushButton *btn_key_change_cho_pub_file_2;
    CustomLineEdit *lineEdit_key_change_dir_pub_file_2;
    CustomLineEdit *lineEdit_key_change_dir_pri_file_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *key_change)
    {
        if (key_change->objectName().isEmpty())
            key_change->setObjectName(QStringLiteral("key_change"));
        key_change->resize(850, 600);
        centralwidget = new QWidget(key_change);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        btn_key_change_get_shared_key = new QPushButton(centralwidget);
        btn_key_change_get_shared_key->setObjectName(QStringLiteral("btn_key_change_get_shared_key"));
        btn_key_change_get_shared_key->setGeometry(QRect(320, 440, 191, 51));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/-_\345\217\246\345\255\230\344\270\272.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_key_change_get_shared_key->setIcon(icon);
        btn_key_change_get_shared_key->setIconSize(QSize(30, 30));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(160, 70, 72, 15));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(11);
        label_2->setFont(font);
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(410, 30, 20, 391));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(580, 65, 72, 20));
        label_3->setFont(font);
        btn_key_change_cho_pri_file_1 = new QPushButton(centralwidget);
        btn_key_change_cho_pri_file_1->setObjectName(QStringLiteral("btn_key_change_cho_pri_file_1"));
        btn_key_change_cho_pri_file_1->setGeometry(QRect(120, 190, 141, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(9);
        btn_key_change_cho_pri_file_1->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/-_\346\211\223\345\274\200\351\241\271\347\233\256.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_key_change_cho_pri_file_1->setIcon(icon1);
        lineEdit_key_change_dir_pri_file_1 = new CustomLineEdit(centralwidget);
        lineEdit_key_change_dir_pri_file_1->setObjectName(QStringLiteral("lineEdit_key_change_dir_pri_file_1"));
        lineEdit_key_change_dir_pri_file_1->setGeometry(QRect(50, 120, 311, 51));
        btn_key_change_cho_pub_file_1 = new QPushButton(centralwidget);
        btn_key_change_cho_pub_file_1->setObjectName(QStringLiteral("btn_key_change_cho_pub_file_1"));
        btn_key_change_cho_pub_file_1->setGeometry(QRect(120, 340, 141, 41));
        btn_key_change_cho_pub_file_1->setIcon(icon1);
        lineEdit_key_change_dir_pub_file_1 = new CustomLineEdit(centralwidget);
        lineEdit_key_change_dir_pub_file_1->setObjectName(QStringLiteral("lineEdit_key_change_dir_pub_file_1"));
        lineEdit_key_change_dir_pub_file_1->setGeometry(QRect(50, 270, 311, 51));
        btn_key_change_cho_pri_file_2 = new QPushButton(centralwidget);
        btn_key_change_cho_pri_file_2->setObjectName(QStringLiteral("btn_key_change_cho_pri_file_2"));
        btn_key_change_cho_pri_file_2->setGeometry(QRect(570, 190, 141, 41));
        btn_key_change_cho_pri_file_2->setIcon(icon1);
        btn_key_change_cho_pub_file_2 = new QPushButton(centralwidget);
        btn_key_change_cho_pub_file_2->setObjectName(QStringLiteral("btn_key_change_cho_pub_file_2"));
        btn_key_change_cho_pub_file_2->setGeometry(QRect(570, 340, 141, 41));
        btn_key_change_cho_pub_file_2->setIcon(icon1);
        lineEdit_key_change_dir_pub_file_2 = new CustomLineEdit(centralwidget);
        lineEdit_key_change_dir_pub_file_2->setObjectName(QStringLiteral("lineEdit_key_change_dir_pub_file_2"));
        lineEdit_key_change_dir_pub_file_2->setGeometry(QRect(470, 270, 311, 51));
        lineEdit_key_change_dir_pri_file_2 = new CustomLineEdit(centralwidget);
        lineEdit_key_change_dir_pri_file_2->setObjectName(QStringLiteral("lineEdit_key_change_dir_pri_file_2"));
        lineEdit_key_change_dir_pri_file_2->setGeometry(QRect(470, 120, 311, 51));
        key_change->setCentralWidget(centralwidget);
        menubar = new QMenuBar(key_change);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 850, 26));
        key_change->setMenuBar(menubar);
        statusbar = new QStatusBar(key_change);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        key_change->setStatusBar(statusbar);

        retranslateUi(key_change);

        QMetaObject::connectSlotsByName(key_change);
    } // setupUi

    void retranslateUi(QMainWindow *key_change)
    {
        key_change->setWindowTitle(QApplication::translate("key_change", "\345\257\206\351\222\245\344\272\244\346\215\242", Q_NULLPTR));
        btn_key_change_get_shared_key->setText(QApplication::translate("key_change", "\347\224\237\346\210\220\345\205\261\344\272\253\345\257\206\351\222\245\345\271\266\344\277\235\345\255\230", Q_NULLPTR));
        label_2->setText(QApplication::translate("key_change", "\347\224\250\346\210\267A", Q_NULLPTR));
        label_3->setText(QApplication::translate("key_change", "\347\224\250\346\210\267B", Q_NULLPTR));
        btn_key_change_cho_pri_file_1->setText(QApplication::translate("key_change", "\351\200\211\346\213\251\347\247\201\351\222\245\346\226\207\344\273\266", Q_NULLPTR));
        btn_key_change_cho_pub_file_1->setText(QApplication::translate("key_change", "\351\200\211\346\213\251\345\205\254\351\222\245\346\226\207\344\273\266", Q_NULLPTR));
        btn_key_change_cho_pri_file_2->setText(QApplication::translate("key_change", "\351\200\211\346\213\251\347\247\201\351\222\245\346\226\207\344\273\266", Q_NULLPTR));
        btn_key_change_cho_pub_file_2->setText(QApplication::translate("key_change", "\351\200\211\346\213\251\345\205\254\351\222\245\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class key_change: public Ui_key_change {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEY_CHANGE_H
