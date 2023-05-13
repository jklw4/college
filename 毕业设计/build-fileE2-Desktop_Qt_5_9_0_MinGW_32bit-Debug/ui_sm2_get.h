/********************************************************************************
** Form generated from reading UI file 'sm2_get.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SM2_GET_H
#define UI_SM2_GET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sm2_get
{
public:
    QListView *sm2_get_dir_listView;
    QPushButton *sm2_get_choDir_btn;
    QPushButton *sm2_get_getAndSave_btn;

    void setupUi(QWidget *sm2_get)
    {
        if (sm2_get->objectName().isEmpty())
            sm2_get->setObjectName(QStringLiteral("sm2_get"));
        sm2_get->resize(457, 329);
        sm2_get_dir_listView = new QListView(sm2_get);
        sm2_get_dir_listView->setObjectName(QStringLiteral("sm2_get_dir_listView"));
        sm2_get_dir_listView->setGeometry(QRect(60, 10, 341, 201));
        sm2_get_choDir_btn = new QPushButton(sm2_get);
        sm2_get_choDir_btn->setObjectName(QStringLiteral("sm2_get_choDir_btn"));
        sm2_get_choDir_btn->setGeometry(QRect(70, 230, 131, 41));
        sm2_get_getAndSave_btn = new QPushButton(sm2_get);
        sm2_get_getAndSave_btn->setObjectName(QStringLiteral("sm2_get_getAndSave_btn"));
        sm2_get_getAndSave_btn->setGeometry(QRect(270, 230, 131, 41));

        retranslateUi(sm2_get);

        QMetaObject::connectSlotsByName(sm2_get);
    } // setupUi

    void retranslateUi(QWidget *sm2_get)
    {
        sm2_get->setWindowTitle(QApplication::translate("sm2_get", "Form", Q_NULLPTR));
        sm2_get_choDir_btn->setText(QApplication::translate("sm2_get", "\351\200\211\346\213\251\344\277\235\345\255\230\350\267\257\345\276\204", Q_NULLPTR));
        sm2_get_getAndSave_btn->setText(QApplication::translate("sm2_get", "\347\224\237\346\210\220\345\205\254\347\247\201\351\222\245", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sm2_get: public Ui_sm2_get {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SM2_GET_H
