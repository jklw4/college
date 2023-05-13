#include <QApplication>
#ifndef SM2_KEY_MANAGE_H
#define SM2_KEY_MANAGE_H

#include <QFileDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/ec.h>
#include <mutex>

// 密钥管理类，用来封装公私钥的生成、保存、读取、加密、解密等操作
class KeyManager : public QObject
{
    Q_OBJECT
public:
    KeyManager();
    ~KeyManager();

    // 生成SM2公私钥对，并保存到指定的文件中
    bool generate_sm2_keypair(const QString &priv_file, const QString &pub_file);

    // 从指定的文件中读取SM2公私钥对
    bool load_sm2_keypair(const QString &priv_file, const QString &pub_file);

    // 获取SM2公钥
    EC_KEY* get_sm2_public_key();

    // 获取SM2私钥
    EC_KEY* get_sm2_private_key();

    //设置KeyManger对象的公钥路径属性
    void set_sm2_public_key_file(const QString &pub_file);

    //设置KeyManger对象的私钥路径属性
    void set_sm2_private_key_file(const QString &priv_file);

    //设置KeyManger对象的证书路径属性
    void set_sm2_verification_veri_file(const QString &veri_file);

    //根据sm2公私钥返回自签名证书
    X509* get_sign_cert();

    // 从pem格式文件中读取证书内容并返回一个x509对象
    X509* read_sm2_cert();

    // 根据sm2公私钥生成证书并保存为pem格式的文件
    bool save_sm2_cert(const QString &pem_file);

public:
    EVP_PKEY *sm2key; // SM2公私钥对

    EC_KEY *sm2_public_key; // SM2公钥

    EC_KEY *sm2_private_key; // SM2私钥

    QString sm2_public_key_file; //存储公钥的文件的路径

    QString sm2_private_key_file; //存储私钥的文件的路径

    QString sm2_verification_veri_file; //存储证书的文件的路径

    std::mutex sm2key_mutex; // 用来保护sm2key的互斥锁

};

#endif // SM2_KEY_MANAGE_H

