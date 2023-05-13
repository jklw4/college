#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sm2_get.h>
#include <key_change.h>
#include <sm3_sign.h>
#include <sm4_crypto.h>
#include <sm3_veri.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static QApplication *a; //声明一个静态的QApplication指针

private slots:
    void on_btn_to_SM2_get_clicked();

    void on_btn_to_key_change_clicked();

    void on_btn_to_sm4_crypto_clicked();

    void on_btn_to_sm3_sign_clicked();

    void on_btn_to_sm3_veri_clicked();

    void on_actiongravira_triggered();

    void on_actionintegrid_triggered();

    void on_actionobit_triggered();

    void on_actionspybot_triggered();

    void on_actionwordoffice_triggered();

    void on_actionwstarpage_triggered();

private:
    Ui::MainWindow *ui;
private:
    sm2_get *sm2Get;
    key_change *keyChange;
    sm3_sign *sm3Sign;
    sm3_veri *sm3Veri;
    sm4_crypto *sm4Crypto;
};

#endif // MAINWINDOW_H
