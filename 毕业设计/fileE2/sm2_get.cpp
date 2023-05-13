#include "sm2_get.h"
#include "ui_sm2_get.h"
#include "sm2_key_manage.h"
#include <QFileSystemModel>
#include <QMessageBox>
#include <QDateTime>
#include <QListView>
#include <QDir>

sm2_get::sm2_get(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::sm2_get)
{
    ui->setupUi(this);
}

sm2_get::~sm2_get()
{
    delete ui;
}


void sm2_get::on_sm2_get_getAndSave_btn_clicked()
{
    // 获取当前的时间戳
    QDateTime timestamp = QDateTime::currentDateTime();
    // 格式化时间戳为字符串
    QString timestamp_str = timestamp.toString("yyyyMMddhhmmss");

    // 拼接文件名
    QString priv_file = timestamp_str + "-sm2-priv.key";
    QString pub_file = timestamp_str + "-sm2-pub.key";

    // 获取用户选择的目录
    QString dir = QFileDialog::getExistingDirectory(NULL, "Select Directory", ".");

    // 如果用户没有选择，就使用默认的目录
    if (dir.isEmpty()) {
        dir="C:/" ;
    }

    // 拼接完整的文件路径
    priv_file = dir + "/" + priv_file;
    pub_file = dir + "/" + pub_file;


    // 创建一个密钥管理对象
    KeyManager *key_manager = new KeyManager();

    // 生成公私钥，并保存到指定的文件中
    if (!key_manager->generate_sm2_keypair(priv_file, pub_file)) {
        QMessageBox::critical(this, "错误", "未生成sm2公私钥文件");
    }else{
        QMessageBox::information(this, "成功", "sm2公私钥文件已保存到指定路径");
    }
}
