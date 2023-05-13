#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sm2_key_manage.h"
#include <QFileSystemModel>
#include <QMessageBox>
#include <QDateTime>
#include <QListView>
#include <QDir>
#include <qdebug.h>
QApplication *MainWindow::a = nullptr;//定义并初始化静态的QApplication指针

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//生成sm2公私钥文件到指定目录
void MainWindow::on_btn_to_SM2_get_clicked()
{
    // 获取当前的时间戳
    QDateTime timestamp = QDateTime::currentDateTime();

    // 格式化时间戳为字符串
    QString timestamp_str = timestamp.toString("yyyyMMddhhmmss");

    // 拼接文件名
    QString priv_file = timestamp_str + "-sm2-priv.key";
    QString pub_file = timestamp_str + "-sm2-pub.key";
    QString veri_file = timestamp_str + "-sm2-veri.veri";

    // 获取用户选择的目录
    QString dir = QFileDialog::getExistingDirectory(NULL, "选择文件保存目录", ".");

    // 如果用户没有选择，就退出
    if (dir.isEmpty()) {
       return ;
    }

    // 拼接完整的文件路径
    priv_file = dir + "/" + priv_file;
    pub_file = dir + "/" + pub_file;
    veri_file = dir + "/" +veri_file;


    // 创建一个密钥管理对象
    KeyManager *key_manager = new KeyManager();

    // 生成公私钥，并保存到指定的文件中
    if (!key_manager->generate_sm2_keypair(priv_file, pub_file)) {
        QMessageBox::critical(this, "错误", "未生成sm2公私钥文件");
    }else{
        QMessageBox::information(this, "成功", "sm2公私钥文件已保存到指定路径");
    }

    // 生成证书，并保存到指定的文件中
    if (!key_manager->save_sm2_cert(veri_file)) {
        QMessageBox::critical(this, "错误", "未生成sm2公私钥的证书");
    }else{
        QMessageBox::information(this, "成功", "sm2公私钥的证书已保存到指定路径");
    }

}

//转到密钥交换协议生成共享密钥的界面
void MainWindow::on_btn_to_key_change_clicked()
{
    keyChange=new key_change(this);
    keyChange->show();
}

//转到sm2——sm3签名界面
void MainWindow::on_btn_to_sm3_sign_clicked()
{
    sm3Sign=new sm3_sign(this);
    sm3Sign->show();
}

//转到sm2——sm3验签界面
void MainWindow::on_btn_to_sm3_veri_clicked()
{
    sm3Veri=new sm3_veri(this);
    sm3Veri->show();
}

void MainWindow::on_btn_to_sm4_crypto_clicked()
{
    sm4Crypto=new sm4_crypto(this);
    sm4Crypto->show();
}

//切换主题
void MainWindow::on_actiongravira_triggered()
{
    // 读取qss文件的内容
    QFile file(":/style/Gravira/Gravira.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    qDebug()<<"change theme to Gravira";
    // 设置应用程序的样式
    a->setStyleSheet(styleSheet);
}

void MainWindow::on_actionintegrid_triggered()
{
    // 读取qss文件的内容
    QFile file(":/style/Integrid/Integrid.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    qDebug()<<"change theme to Integrid";
    // 设置应用程序的样式
    a->setStyleSheet(styleSheet);
}

void MainWindow::on_actionobit_triggered()
{
    // 读取qss文件的内容
    QFile file(":/style/Obit/Obit.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    qDebug()<<"change theme to Obit";
    // 设置应用程序的样式
    a->setStyleSheet(styleSheet);
}

void MainWindow::on_actionspybot_triggered()
{
    // 读取qss文件的内容
    QFile file(":/style/SpyBot/SpyBot.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    qDebug()<<"change theme to SpyBot";
    // 设置应用程序的样式
    a->setStyleSheet(styleSheet);
}

void MainWindow::on_actionwordoffice_triggered()
{
    // 读取qss文件的内容
    QFile file(":/style/WordOffice/WordOffice.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    qDebug()<<"change theme to WordOffice";
    // 设置应用程序的样式
    a->setStyleSheet(styleSheet);
}

void MainWindow::on_actionwstarpage_triggered()
{
    // 读取qss文件的内容
    QFile file(":/style/Wstartpage/Wstartpage.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    qDebug()<<"change theme to Wstartpage";
    // 设置应用程序的样式
    a->setStyleSheet(styleSheet);
}
