#include "sm4_crypto.h"
#include "ui_sm4_crypto.h"
#include "filecrypt.h"
#include "tool.h"
#include <qdebug.h>
#include <QTime>
#include <QFileInfo>

sm4_crypto::sm4_crypto(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sm4_crypto)
{
    ui->setupUi(this);
}

sm4_crypto::~sm4_crypto()
{
    delete ui;
}

void sm4_crypto::on_btn_sm4_crypto_cho_raw_file_clicked()
{
    // 获取原文件
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "C:/", "All Files(*.*)");
    // 设置标签的文本为文件的路径
    ui->lineEdit_sm4_crypto_dir_raw_file->setText(fileName);
}

void sm4_crypto::on_btn_sm4_crypto_cho_shared_key_file_clicked()
{
    // 获取共享密钥文件
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "C:/", "All Files(*.*)");
    // 设置标签的文本为文件的路径
    ui->lineEdit_sm4_crypto_dir_shared_key_file->setText(fileName);
}


void sm4_crypto::on_btn_sm4_crypto_encryption_clicked()
{
    // 创建一个FileCrypt对象，用来进行文件加密和解密
    FileCrypt fc;
    QString file_save_sharedKey=ui->lineEdit_sm4_crypto_dir_shared_key_file->text();
    QString file_sm4_raw_file=ui->lineEdit_sm4_crypto_dir_raw_file->text();

    // 获取用户选择的目录
    QString dir = QFileDialog::getExistingDirectory(NULL, "选择文件保存目录", ".");

    // 如果用户没有选择，就退出
    if (dir.isEmpty()) {
       return ;
    }

    QString file_sm4_encrypted_file = generateNewFilePath(file_sm4_raw_file,dir,"enc");

    // 从共享密钥文件中读取共享密钥
    if (!fc.load_shared_secret(file_save_sharedKey)) {
        qDebug()<<"Load shared secret fail!";
        QMessageBox::critical(nullptr, "失败", "共享密钥文件读取失败!");
        return;
    }else{
        qDebug()<<"Load shared secret success!";
    }

    QFileInfo info(file_sm4_raw_file);
    if (info.exists()) {
      if (info.isFile()) {// 处理文件的情况
          // 记录开始时间
          QTime start = QTime::currentTime();

          // 对一个文件进行加密，并输出到另一个文件中
          if (!fc.sm4_crypt_file(file_sm4_raw_file, file_sm4_encrypted_file, true)) {
              qDebug()<<"sm4_crypt_file encryption failed";
              QMessageBox::critical(nullptr, "失败", "文件加密失败!");
              return;
          }else{
              // 记录结束时间
              QTime end = QTime::currentTime();
              // 计算执行时间
              int elapsed = start.msecsTo(end);
              // 显示执行时间
              QMessageBox::information(nullptr, "成功", QString("文件加密成功，耗时%1毫秒").arg(elapsed));
              qDebug()<<"sm4_crypt_file encryption success";
          }
      } else {// 处理文件夹的情况
          // 记录开始时间
          QTime start = QTime::currentTime();

          // 对一个文件进行加密，并输出到另一个文件中
          if (!fc.sm4_crypt_folder(file_sm4_raw_file, file_sm4_encrypted_file, true)) {
              qDebug()<<"sm4_crypt_file encryption failed";
              QMessageBox::critical(nullptr, "失败", "文件加密失败!");
              return;
          }else{
              // 记录结束时间
              QTime end = QTime::currentTime();
              // 计算执行时间
              int elapsed = start.msecsTo(end);
              // 显示执行时间
              QMessageBox::information(nullptr, "成功", QString("文件加密成功，耗时%1毫秒").arg(elapsed));
              qDebug()<<"sm4_crypt_file encryption success";
          }
      }
    } else {
      // 处理不存在的情况
        QMessageBox::critical(nullptr, "失败", "原文件路径错误!");
    }
}



void sm4_crypto::on_btn_sm4_crypto_decryption_clicked()
{
    // 创建一个FileCrypt对象，用来进行文件加密和解密
    FileCrypt fc;
    QString file_save_sharedKey=ui->lineEdit_sm4_crypto_dir_shared_key_file->text();
    qDebug()<<"sm4_crypto.cpp:decryption_clicked:file_save_sharedKey:"<<file_save_sharedKey;
    QString file_sm4_raw_file=ui->lineEdit_sm4_crypto_dir_raw_file->text();

    // 获取用户选择的目录
    QString dir = QFileDialog::getExistingDirectory(NULL, "选择文件保存目录", ".");

    // 如果用户没有选择，就退出
    if (dir.isEmpty()) {
       return ;
    }

    QString file_sm4_decrypted_file = generateNewFilePath(file_sm4_raw_file,dir,"dec");

    // 从共享密钥文件中读取共享密钥
    if (!fc.load_shared_secret(file_save_sharedKey)) {
        qDebug()<<"Load shared secret fail!";
        QMessageBox::critical(nullptr, "失败", "共享密钥文件读取失败!");
        return;
    }else{
        qDebug()<<"Load shared secret success!";
    }

    QFileInfo info(file_sm4_raw_file);
    if (info.exists()) {
      if (info.isFile()) {// 处理文件的情况
          // 记录开始时间
          QTime start = QTime::currentTime();

          // 对一个文件进行加密，并输出到另一个文件中
          if (!fc.sm4_crypt_file(file_sm4_raw_file, file_sm4_decrypted_file, false)) {
              qDebug()<<"sm4_crypt_file decryption failed";
              QMessageBox::critical(nullptr, "失败", "文件解密失败!");
              return;
          }else{
              // 记录结束时间
              QTime end = QTime::currentTime();
              // 计算执行时间
              int elapsed = start.msecsTo(end);
              // 显示执行时间
              QMessageBox::information(nullptr, "成功", QString("文件解密成功，耗时%1毫秒").arg(elapsed));
              qDebug()<<"sm4_crypt_file encryption success";
          }
      } else {// 处理文件夹的情况
          // 记录开始时间
          QTime start = QTime::currentTime();

          // 对一个文件进行加密，并输出到另一个文件中
          if (!fc.sm4_crypt_folder(file_sm4_raw_file, file_sm4_decrypted_file, false)) {
              qDebug()<<"sm4_crypt_file decryption failed";
              QMessageBox::critical(nullptr, "失败", "文件解密失败!");
              return;
          }else{
              // 记录结束时间
              QTime end = QTime::currentTime();
              // 计算执行时间
              int elapsed = start.msecsTo(end);
              // 显示执行时间
              QMessageBox::information(nullptr, "成功", QString("文件解密成功，耗时%1毫秒").arg(elapsed));
              qDebug()<<"sm4_crypt_file decryption success";
          }
      }
    } else {
      // 处理不存在的情况
        QMessageBox::critical(nullptr, "失败", "原文件路径错误!");
    }
}
