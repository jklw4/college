#include "sm3_sign.h"
#include "ui_sm3_sign.h"
#include "sm2_key_manage.h"
#include "filesigner.h"
#include <qdebug.h>
#include <qstring.h>
#include "tool.h"

sm3_sign::sm3_sign(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sm3_sign)
{
    ui->setupUi(this);
}

sm3_sign::~sm3_sign()
{
    delete ui;
}

/*//功能验证测试函数
void sm3_sign::on_pushButton_clicked()
{
    // 创建一个KeyManager类的对象
    KeyManager *key_manager = new KeyManager();

    // 定义一个私钥文件和一个公钥文件的路径，假设文件已经存在
    QString priv_file = "C:/Users/jklw4/Desktop/毕业设计/试验区/sm2_key/20230428095047-sm2-priv.key";
    QString pub_file = "C:/Users/jklw4/Desktop/毕业设计/试验区/sm2_key/20230428095047-sm2-pub.key";
    QString veri_file = "C:/Users/jklw4/Desktop/毕业设计/试验区/sm2_key/20230428095047-sm2-veri.veri";

//    // 定义一个私钥文件和一个公钥文件的路径，假设文件已经存在
//    QString priv_file = "C:/Users/jklw4/Desktop/毕业设计/试验区/standard_key/privkey.pem";
//    QString pub_file = "C:/Users/jklw4/Desktop/毕业设计/试验区/standard_key/pubkey.pem";
//    QString veri_file = "C:/Users/jklw4/Desktop/毕业设计/试验区/standard_key/cert.pem";


    key_manager->set_sm2_private_key_file(priv_file);
    key_manager->set_sm2_public_key_file(pub_file);
    key_manager->set_sm2_verification_veri_file(veri_file);

    // 创建一个FileSigner类的对象，传入KeyManager类的对象指针
    FileSigner *file_signer = new FileSigner(key_manager);

    // 定义一个源文件和一个目标文件的路径，假设源文件已经存在
    QString src_file = "C:/Users/jklw4/Desktop/毕业设计/试验区/important_file/secret1.txt";
    QString dst_file = "C:/Users/jklw4/Desktop/毕业设计/试验区/signed_file/secret2.sig";

    // 定义一个签名者的身份标识，假设是"123hello#@"
    QByteArray id = "123hello#@";

    // 调用sign_file函数，对源文件进行签名，并将结果保存到目标文件中，传入签名者的身份标识
    bool sign_result = file_signer->sign_file(src_file, dst_file, id);

    // 检查sign_file函数的返回值，如果为true，表示签名成功，否则表示签名失败
    if (sign_result) {
        qDebug() << "Sign file success";
    } else {
        qDebug() << "Sign file fail";
    }

    // 调用verify_file函数，对目标文件进行验证，并返回验证结果，传入签名者的身份标识
    bool verify_result = file_signer->verify_file(dst_file, id);

    // 检查verify_file函数的返回值，如果为true，表示验证成功，否则表示验证失败
    if (verify_result) {
        qDebug() << "Verify file success";
    } else {
        qDebug() << "Verify file fail";
    }

    // 释放FileSigner类和KeyManager类的对象
    delete file_signer;
    delete key_manager;

}*/

//选择文件路径
void sm3_sign::on_btn_sm3sign_cho_raw_file_clicked()
{
    // 获取要签名的文件的路径
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "C:/", "All Files(*.*)");
    // 设置标签的文本为文件的路径
    ui->lineEdit_dir_raw_file->setText(fileName);
}

void sm3_sign::on_btn_sm3sign_cho_pri_file_clicked()
{
    // 获取sm2私钥文件的路径
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "C:/", "All Files(*.*)");
    // 设置标签的文本为文件的路径
    ui->lineEdit_dir_pri_file->setText(fileName);
}

void sm3_sign::on_btn_sm3sign_cho_signed_dir_clicked()
{
    // 获取选择文件夹的路径
    QString dirName = QFileDialog::getExistingDirectory(this, "选择文件夹", QDir::homePath(), QFileDialog::ShowDirsOnly);
    // 设置标签的文本为文件夹的路径
    ui->lineEdit_dir_signed_file->setText(dirName);
}

//签名
void sm3_sign::on_btn_sm3sign_sign_clicked()
{
    // 创建一个KeyManager类的对象
    KeyManager *key_manager = new KeyManager();

    // 传入文件路径
    QString priv_file = ui->lineEdit_dir_pri_file->text();
    qDebug()<<"sm3_sign.cpp::btn_sm3sign_sign_clicked: priv_file:"<<priv_file;
    QString raw_file = ui->lineEdit_dir_raw_file->text();
    QString dir_signed_file = ui->lineEdit_dir_signed_file->text();

    QString signedFile = generateNewFilePath(raw_file,dir_signed_file,"sig");

    //传入签名者的身份标识
    QByteArray id = ui->lineEdit_signer_id->text().toUtf8();

    key_manager->set_sm2_private_key_file(priv_file);

    // 创建一个FileSigner类的对象，传入KeyManager类的对象指针
    FileSigner *file_signer = new FileSigner(key_manager);

    // 调用sign_file函数，对源文件raw_file进行签名，并将结果保存到目标文件signedFile中，传入签名者的身份标识
    bool sign_result = file_signer->sign_file(raw_file, signedFile, id);
    // 检查sign_file函数的返回值，如果为true，表示验证成功，否则表示验证失败
    if (sign_result) {
        qDebug() << "Sign file success";
    } else {
        qDebug() << "Sign file fail";
    }

//    // 调用verify_file函数，对目标文件进行验证，并返回验证结果，传入签名者的身份标识
//    bool verify_result = file_signer->verify_file(dst_file, id);

//    // 检查verify_file函数的返回值，如果为true，表示验证成功，否则表示验证失败
//    if (verify_result) {
//        qDebug() << "Verify file success";
//    } else {
//        qDebug() << "Verify file fail";
//    }

    // 释放FileSigner类和KeyManager类的对象
    delete file_signer;
    delete key_manager;
}



