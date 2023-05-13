#ifndef KEY_CHANGE_H
#define KEY_CHANGE_H

#include <QMainWindow>

namespace Ui {
class key_change;
}

class key_change : public QMainWindow
{
    Q_OBJECT

public:
    explicit key_change(QWidget *parent = 0);
    ~key_change();

private slots:
    void on_pushButton_clicked();
    
    void on_btn_key_change_cho_pri_file_1_clicked();

    void on_btn_key_change_cho_pri_file_2_clicked();

    void on_btn_key_change_cho_pub_file_1_clicked();

    void on_btn_key_change_cho_pub_file_2_clicked();

    void on_btn_key_change_get_shared_key_clicked();

private:
    Ui::key_change *ui;
};

#endif // KEY_CHANGE_H
