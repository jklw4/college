#ifndef SM4_CRYPTO_H
#define SM4_CRYPTO_H

#include <QMainWindow>

namespace Ui {
class sm4_crypto;
}

class sm4_crypto : public QMainWindow
{
    Q_OBJECT

public:
    explicit sm4_crypto(QWidget *parent = 0);
    ~sm4_crypto();

private slots:
    void on_btn_sm4_crypto_cho_raw_file_clicked();

    void on_btn_sm4_crypto_cho_shared_key_file_clicked();

    void on_btn_sm4_crypto_encryption_clicked();

    void on_btn_sm4_crypto_decryption_clicked();

private:
    Ui::sm4_crypto *ui;
};

#endif // SM4_CRYPTO_H
