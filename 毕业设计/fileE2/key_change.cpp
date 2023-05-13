#include "key_change.h"
#include "ui_key_change.h"
#include "filecrypt.h"
#include "keyexchange.h"
#include <qdebug.h>
#include <qmessagebox.h>
#include <QDateTime>
key_change::key_change(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::key_change)
{
    ui->setupUi(this);
}

key_change::~key_change()
{
    delete ui;
}



// 定义一个测试函数，用来测试KeyExchange类和FileCrypt类的功能
void test()
{
    // 创建两个KeyManager对象，分别代表本地和远程的密钥管理类
    KeyManager local_km;
    KeyManager remote_km;
    
    QString file_local_generated_sm2_prikey="C:/Users/jklw4/Desktop/毕业设计/试验区/intact/user1/local_pri.key";
    QString file_local_generated_sm2_pubkey="C:/Users/jklw4/Desktop/毕业设计/试验区/intact/user1/local_pub.key";
    QString file_remote_generated_sm2_prikey="C:/Users/jklw4/Desktop/毕业设计/试验区/intact/user2/remote_priv.key";
    QString file_remote_generated_sm2_pubkey="C:/Users/jklw4/Desktop/毕业设计/试验区/intact/user2/remote_pub.key";
    
    QString file_local_sm2_prikey="C:/Users/jklw4/Desktop/毕业设计/试验区/intact/user1/local_pri.key";
    QString file_local_sm2_pubkey="C:/Users/jklw4/Desktop/毕业设计/试验区/intact/user1/local_pub.key";
    QString file_remote_sm2_prikey="C:/Users/jklw4/Desktop/毕业设计/试验区/intact/user2/remote_priv.key";
    QString file_remote_sm2_pubkey="C:/Users/jklw4/Desktop/毕业设计/试验区/intact/user2/remote_pub.key";

    QString file_save_sharedKey="C:/Users/jklw4/Desktop/毕业设计/试验区/intact/sharedKey/shared_secret.skey";
    QString file_sm4_raw_file="C:/Users/jklw4/Desktop/毕业设计/试验区/intact/sm4_raw_file/plain.txt";
    QString file_sm4_encrypted_file="C:/Users/jklw4/Desktop/毕业设计/试验区/intact/sm4_encrypted_file/cipher.sec";
    QString file_sm4_decrypted_file="C:/Users/jklw4/Desktop/毕业设计/试验区/intact/sm4_decrypted_file/plain2.txt";

    local_km.set_sm2_private_key_file(file_local_sm2_prikey);
    local_km.set_sm2_public_key_file(file_local_sm2_pubkey);
    remote_km.set_sm2_private_key_file(file_remote_sm2_prikey);
    remote_km.set_sm2_public_key_file(file_remote_sm2_pubkey);

    // 生成两对SM2公私钥，并保存到指定的文件中
    bool local_generate_result=local_km.generate_sm2_keypair(file_local_generated_sm2_prikey, file_local_generated_sm2_pubkey);
    bool remote_generate_result=remote_km.generate_sm2_keypair(file_remote_generated_sm2_prikey, file_remote_generated_sm2_pubkey);
    if(local_generate_result){
        qDebug()<<"local_km.generate_sm2_keypair success!";
    }else{
        qDebug()<<"local_km.generate_sm2_keypair failed!";
    }
    if(remote_generate_result){
        qDebug()<<"remote_km.generate_sm2_keypair success!";
    }else{
        qDebug()<<"remote_km.generate_sm2_keypair failed!";
    }
    // 从指定的文件中读取SM2公私钥对
    bool local_load_result=local_km.load_sm2_keypair(file_local_sm2_prikey, file_local_sm2_pubkey);
    bool remote_load_result=remote_km.load_sm2_keypair(file_remote_sm2_prikey, file_remote_sm2_pubkey);
    if(local_load_result){
        qDebug()<<"local_km.load_sm2_keypair success!";
    }else{
        qDebug()<<"local_km.load_sm2_keypair failed!";
    }
    if(remote_load_result){
        qDebug()<<"remote_km.load_sm2_keypair success!";
    }else{
        qDebug()<<"remote_km.load_sm2_keypair failed!";
    }

    // 创建一个KeyExchange对象，用来进行密钥交换
    KeyExchange ke;
    // 设置本地和远程的密钥管理类对象
    ke.set_local_key_manager(&local_km);
    ke.set_remote_key_manager(&remote_km);
    // 进行密钥交换，并获取共享密钥
    if (!ke.do_key_exchange()) {
        qDebug()<<"Key exchange fail!";
        return;
    }
    // 保存共享密钥到一个文件中
    if (!ke.save_shared_secret(file_save_sharedKey)) {
        qDebug()<<"Save shared secret fail!";
        return;
    }else{
        qDebug()<<"Save shared secret success!";
    }

    // 创建一个FileCrypt对象，用来进行文件加密和解密
    FileCrypt fc;
    // 从共享密钥文件中读取共享密钥
    if (!fc.load_shared_secret(file_save_sharedKey)) {
        qDebug()<<"Load shared secret fail!";
        return;
    }else{
        qDebug()<<"Load shared secret success!";
    }
    // 对一个文件进行加密，并输出到另一个文件中
    if (!fc.sm4_crypt_file(file_sm4_raw_file,file_sm4_encrypted_file, true)) {
        qDebug()<<"sm4_crypt_file encryption failed";
        return;
    }else{
        qDebug()<<"sm4_crypt_file encryption success";
    }
    // 对一个文件进行解密，并输出到另一个文件中
    if (!fc.sm4_crypt_file(file_sm4_encrypted_file, file_sm4_decrypted_file, false)) {
        qDebug()<<"Decryption fail!";
        return;
    }else{
        // 打印解密成功的信息
        qDebug()<<"Decryption success!";
        return;
    }
}

void key_change::on_pushButton_clicked()
{
    test();
}

void key_change::on_btn_key_change_cho_pri_file_1_clicked()
{
    // 获取用户1的私钥文件路径
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "C:/", "All Files(*.*)");
    // 设置标签的文本为文件的路径
    ui->lineEdit_key_change_dir_pri_file_1->setText(fileName);
}

void key_change::on_btn_key_change_cho_pub_file_1_clicked()
{
    // 获取用户1的公钥文件路径
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "C:/", "All Files(*.*)");
    // 设置标签的文本为文件的路径
    ui->lineEdit_key_change_dir_pub_file_1->setText(fileName);
}

void key_change::on_btn_key_change_cho_pri_file_2_clicked()
{
    // 获取用户2的私钥文件路径
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "C:/", "All Files(*.*)");
    // 设置标签的文本为文件的路径
    ui->lineEdit_key_change_dir_pri_file_2->setText(fileName);
}

void key_change::on_btn_key_change_cho_pub_file_2_clicked()
{
    // 获取用户2的公钥文件路径
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "C:/", "All Files(*.*)");
    // 设置标签的文本为文件的路径
    ui->lineEdit_key_change_dir_pub_file_2->setText(fileName);
}

void key_change::on_btn_key_change_get_shared_key_clicked()
{
    // 创建两个KeyManager对象，分别代表本地和远程的密钥管理类
    KeyManager local_km;
    KeyManager remote_km;

    QString file_local_sm2_prikey=ui->lineEdit_key_change_dir_pri_file_1->text();
    QString file_local_sm2_pubkey=ui->lineEdit_key_change_dir_pub_file_1->text();
    QString file_remote_sm2_prikey=ui->lineEdit_key_change_dir_pri_file_2->text();
    QString file_remote_sm2_pubkey=ui->lineEdit_key_change_dir_pub_file_2->text();

    local_km.set_sm2_private_key_file(file_local_sm2_prikey);
    local_km.set_sm2_public_key_file(file_local_sm2_pubkey);
    remote_km.set_sm2_private_key_file(file_remote_sm2_prikey);
    remote_km.set_sm2_public_key_file(file_remote_sm2_pubkey);

    // 从指定的文件中读取SM2公私钥对
    bool local_load_result=local_km.load_sm2_keypair(file_local_sm2_prikey, file_local_sm2_pubkey);
    bool remote_load_result=remote_km.load_sm2_keypair(file_remote_sm2_prikey, file_remote_sm2_pubkey);
    if(local_load_result){
        qDebug()<<"local_km.load_sm2_keypair success!";
    }else{
        qDebug()<<"local_km.load_sm2_keypair failed!";
    }
    if(remote_load_result){
        qDebug()<<"remote_km.load_sm2_keypair success!";
    }else{
        qDebug()<<"remote_km.load_sm2_keypair failed!";
    }

    // 创建一个KeyExchange对象，用来进行密钥交换
    KeyExchange ke;
    // 设置本地和远程的密钥管理类对象
    ke.set_local_key_manager(&local_km);
    ke.set_remote_key_manager(&remote_km);
    // 进行密钥交换，并获取共享密钥
    if (!ke.do_key_exchange()) {
        qDebug()<<"Key exchange fail!";
        return;
    }

    // 获取当前的时间戳
    QDateTime timestamp = QDateTime::currentDateTime();

    // 格式化时间戳为字符串
    QString timestamp_str = timestamp.toString("yyyyMMddhhmmss");

    // 拼接文件名
    QString file_save_sharedKey = timestamp_str + "_shared_key.skey";

    // 获取用户选择的目录
    QString dir = QFileDialog::getExistingDirectory(NULL, "选择文件保存目录", ".");

    // 如果用户没有选择，就退出
    if (dir.isEmpty()) {
       return ;
    }

    // 拼接完整的文件路径
    file_save_sharedKey = dir + "/" + file_save_sharedKey;

    // 保存共享密钥到一个文件中
    if (!ke.save_shared_secret(file_save_sharedKey)) {
        qDebug()<<"Save shared secret fail!";
        QMessageBox::critical(nullptr, "失败", "生成共享密钥文件失败!");
        return;
    }else{
        QMessageBox::information(nullptr, "成功", "生成共享密钥文件成功!");
        qDebug()<<"Save shared secret success!";
        return;
    }
}
