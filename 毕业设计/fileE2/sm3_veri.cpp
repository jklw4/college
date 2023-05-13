#include "sm3_veri.h"
#include "ui_sm3_veri.h"
#include "filesigner.h"
#include "sm2_key_manage.h"
#include <qdebug.h>

sm3_veri::sm3_veri(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sm3_veri)
{
    ui->setupUi(this);
}

sm3_veri::~sm3_veri()
{
    delete ui;
}

void sm3_veri::on_btn_sm3veri_cho_raw_file_clicked()
{
    // 获取原文件的路径
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "C:/", "All Files(*.*)");
    // 设置标签的文本为文件的路径
    ui->lineEdit_dir_raw_file->setText(fileName);
}

void sm3_veri::on_btn_sm3veri_cho_sig_file_clicked()
{
    // 获取要签名的文件的路径
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "C:/", "All Files(*.*)");
    // 设置标签的文本为文件的路径
    ui->lineEdit_dir_sig_file->setText(fileName);
}

void sm3_veri::on_btn_sm3veri_cho_pub_file_clicked()
{
    // 获取sm2公钥文件的路径
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "C:/", "All Files(*.*)");
    // 设置标签的文本为文件的路径
    ui->lineEdit_dir_pub_file->setText(fileName);
}

void sm3_veri::on_btn_sm3veri_verification_clicked()
{
    // 创建一个KeyManager类的对象
    KeyManager *key_manager = new KeyManager();

    // 传入文件路径
    QString pub_file = ui->lineEdit_dir_pub_file->text();
    qDebug()<<"sm3_sign.cpp::btn_sm3sign_sign_clicked: priv_file:"<<pub_file;
    QString raw_file = ui->lineEdit_dir_raw_file->text();
    QString sig_file = ui->lineEdit_dir_sig_file->text();

    //传入签名者的身份标识
    QByteArray id = ui->lineEdit_signer_id->text().toUtf8();

    key_manager->set_sm2_public_key_file(pub_file);

    // 创建一个FileSigner类的对象，传入KeyManager类的对象指针
    FileSigner *file_signer = new FileSigner(key_manager);

    // 调用verify_file函数，对目标文件进行验证，并返回验证结果，传入签名者的身份标识
    bool verify_result = file_signer->verify_file(sig_file,raw_file,id);

    // 检查verify_file函数的返回值，如果为true，表示验证成功，否则表示验证失败
    if (verify_result) {
        qDebug() << "Verify file success";
    } else {
        qDebug() << "Verify file fail";
    }

    // 释放FileSigner类和KeyManager类的对象
    delete file_signer;
    delete key_manager;
}
