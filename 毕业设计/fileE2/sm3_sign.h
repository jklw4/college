#ifndef SM3_SIGN_H
#define SM3_SIGN_H

#include <QMainWindow>

namespace Ui {
class sm3_sign;
}

class sm3_sign : public QMainWindow
{
    Q_OBJECT

public:
    explicit sm3_sign(QWidget *parent = 0);
    ~sm3_sign();

private slots:
//    void on_pushButton_clicked();

    void on_btn_sm3sign_cho_raw_file_clicked();

    void on_btn_sm3sign_cho_pri_file_clicked();

    void on_btn_sm3sign_cho_signed_dir_clicked();

    void on_btn_sm3sign_sign_clicked();

private:
    Ui::sm3_sign *ui;
};

#endif // SM3_SIGN_H
