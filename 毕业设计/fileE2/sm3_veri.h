#ifndef SM3_VERI_H
#define SM3_VERI_H

#include <QMainWindow>

namespace Ui {
class sm3_veri;
}

class sm3_veri : public QMainWindow
{
    Q_OBJECT

public:
    explicit sm3_veri(QWidget *parent = 0);
    ~sm3_veri();

private slots:
    void on_btn_sm3veri_cho_raw_file_clicked();

    void on_btn_sm3veri_cho_sig_file_clicked();

    void on_btn_sm3veri_cho_pub_file_clicked();

    void on_btn_sm3veri_verification_clicked();

private:
    Ui::sm3_veri *ui;
};

#endif // SM3_VERI_H
