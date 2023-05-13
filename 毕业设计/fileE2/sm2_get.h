#ifndef SM2_GET_H
#define SM2_GET_H

#include <QMainWindow>

namespace Ui {
class sm2_get;
}

class sm2_get : public QMainWindow
{
    Q_OBJECT

public:
    explicit sm2_get(QMainWindow *parent = 0);
    ~sm2_get();

private slots:
    void on_sm2_get_getAndSave_btn_clicked();

private:
    Ui::sm2_get *ui;
};

#endif // SM2_GET_H
