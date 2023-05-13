#include "sm2_key_manage.h"
#include <QApplication>
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
#include <qdebug.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h> // 包含X509_EXTENSION相关的头文件
#include <openssl/objects.h>
#include <openssl/err.h>
#include <mutex>

// 构造函数，初始化公私钥为NULL
KeyManager::KeyManager()
{
    sm2key = NULL;
    sm2_public_key_file = "";
    sm2_private_key_file = "";
}

// 析构函数，释放公私钥资源
KeyManager::~KeyManager()
{
    if (sm2key != NULL) {
        EVP_PKEY_free(sm2key);
        sm2key = NULL;
    }
}

//设置公钥文件的路径
void KeyManager::set_sm2_public_key_file(const QString &pub_file) {
    sm2_public_key_file = pub_file;
}

//设置私钥文件的路径
void KeyManager::set_sm2_private_key_file(const QString &priv_file) {
    sm2_private_key_file = priv_file;
}
//设置证书文件的路径
void KeyManager::set_sm2_verification_veri_file(const QString &veri_file){
    sm2_verification_veri_file = veri_file;
}

//从已设置好的路径中得到sm2公钥对象
EC_KEY* KeyManager::get_sm2_public_key() {
    // 定义一个变量保存公钥
    EC_KEY* sm2_public_key = nullptr;

    // 创建BIO对象读取公钥文件
    BIO *pub_bio = BIO_new_file(sm2_public_key_file .toStdString().c_str(), "r");
    if (pub_bio == nullptr) {
        qDebug("Failed to open public key file!");
    }

    // 读取公钥
    sm2_public_key = PEM_read_bio_EC_PUBKEY(pub_bio, &sm2_public_key, nullptr, nullptr);
    if (sm2_public_key == nullptr) {
        BIO_free(pub_bio);
        qDebug("Failed to read public key!");
    }

    BIO_free(pub_bio); //释放内存

    return sm2_public_key;
}

//从已设置好的路径中得到sm2私钥对象
EC_KEY* KeyManager::get_sm2_private_key() {
    // 定义一个变量保存公钥
    EC_KEY* sm2_private_key = nullptr;

    // 创建BIO对象读取私钥文件
    BIO *priv_bio = BIO_new_file(sm2_private_key_file.toStdString().c_str(), "r");
    if (priv_bio == nullptr) {
        qDebug("Failed to open private key file!");
    }

    // 读取私钥
    sm2_private_key = PEM_read_bio_ECPrivateKey(priv_bio, &sm2_private_key, nullptr, nullptr);
    if (sm2_private_key == nullptr) {
        BIO_free(priv_bio);
        qDebug("Failed to read private key!");
    }

    BIO_free(priv_bio);//释放内存

    return sm2_private_key;

}

//根据sm2公私钥文件生成一个证书,用于后续签名后文件的pkcs#7语法结构的封装
X509* KeyManager::get_sign_cert() {
    // 如果公私钥未加载,先加载公私钥
    if (!sm2key) {
       if (!load_sm2_keypair(sm2_private_key_file, sm2_public_key_file)) {
           qDebug()<<"KeyManager::get_sign_cert: load_sm2_keypair failed!";
           return nullptr;
       }
    }
    // 检查sm2key是否为空指针
    if (!sm2key) {
        qDebug()<<"KeyManager::get_sign_cert: sm2key is null!";
        return nullptr;
    }
    // 创建一个X509证书对象
    X509* cert = X509_new();
    if (!cert) {
       qDebug()<<"KeyManager::get_sign_cert: X509_new failed!";
       return nullptr;
    }
    // 设置证书的版本号为3
    if (!X509_set_version(cert, 2)) {
        qDebug()<<"KeyManager::get_sign_cert: X509_set_version failed!";
        X509_free(cert);
        return nullptr;
    }
    // 设置证书的序列号为1
    if (!ASN1_INTEGER_set(X509_get_serialNumber(cert), 1)) {
        qDebug()<<"KeyManager::get_sign_cert: ASN1_INTEGER_set failed!";
        X509_free(cert);
        return nullptr;
    }
    // 设置证书的有效期为十年
    if (!X509_gmtime_adj(X509_get_notBefore(cert), 0)) {
        qDebug()<<"KeyManager::get_sign_cert: X509_gmtime_adj failed!";
        X509_free(cert);
        return nullptr;
    }
    if (!X509_gmtime_adj(X509_get_notAfter(cert), 315360000L)) {
        qDebug()<<"KeyManager::get_sign_cert: X509_gmtime_adj failed!";
        X509_free(cert);
        return nullptr;
    }
    // 设置证书的主题和颁发者为自己
    X509_NAME* name = X509_get_subject_name(cert);
    if (!name) {
        qDebug()<<"KeyManager::get_sign_cert: X509_get_subject_name failed!";
        X509_free(cert);
        return nullptr;
    }

    if (!X509_NAME_add_entry_by_txt(name, "C", MBSTRING_ASC, (unsigned char*)"CN", -1, -1, 0)) {
        qDebug()<<"KeyManager::get_sign_cert: X509_NAME_add_entry_by_txt failed!";
        X509_free(cert);
        return nullptr;
    }

    if (!X509_NAME_add_entry_by_txt(name, "O", MBSTRING_ASC, (unsigned char*)"KeyManager", -1, -1, 0)) {
        qDebug()<<"KeyManager::get_sign_cert: X509_NAME_add_entry_by_txt failed!";
        X509_free(cert);
        return nullptr;
    }

    if (!X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (unsigned char*)"KeyManager", -1, -1, 0)) {
        qDebug()<<"KeyManager::get_sign_cert: X509_NAME_add_entry_by_txt failed!";
        X509_free(cert);
        return nullptr;
    }

    if (!X509_set_issuer_name(cert, name)) {
        qDebug()<<"KeyManager::get_sign_cert: X509_set_issuer_name failed!";
        X509_free(cert);
        return nullptr;
    }

    //设置证书公钥为sm2key的公钥
    if (!X509_set_pubkey(cert, sm2key)) {
        qDebug()<<"KeyManager::get_sign_cert: X509_set_pubkey failed!";
        X509_free(cert);
        return nullptr;
    }

    //使用sm2key的私钥对证书进行签名
    if (X509_sign(cert, sm2key, EVP_sha256()) == 0) {
        qDebug()<<"KeyManager::get_sign_cert: X509_sign failed!";
        //获取错误代码和信息
        unsigned long err = ERR_get_error();
        char *errstr = ERR_error_string(err, NULL);
        qDebug()<<"Error code: "<<err;
        qDebug()<<"Error string: "<<errstr;
        X509_free(cert);
        return NULL;
    }

    //返回生成的证书
    return cert;
}


// 根据sm2公私钥生成证书并保存为pem格式的文件
bool KeyManager::save_sm2_cert(const QString &pem_file)
{
    // 获取sm2公私钥生成的签名证书
    X509 *sign_cert = get_sign_cert();
    if (!sign_cert) {
        qDebug()<<"KeyManager::save_sm2_cert: get_sign_cert failed!";
        return false;
    }

    // 创建BIO对象，用来写入文件
    BIO *bio = BIO_new_file(pem_file.toStdString().c_str(), "w");
    if (!bio) {
        qDebug()<<"KeyManager::save_sm2_cert: BIO_new_file failed!";
        X509_free(sign_cert);
        return false;
    }

    // 使用PEM格式和SM2算法标识写入证书
    if (!PEM_write_bio_X509(bio, sign_cert)) {
        qDebug()<<"KeyManager::save_sm2_cert: PEM_write_bio_X509 failed!";
        BIO_free(bio);
        X509_free(sign_cert);
        return false;
    }

    // 释放BIO对象和证书
    BIO_free(bio);
    X509_free(sign_cert);
    return true;
}


// 从pem格式文件中读取证书内容并返回一个x509对象
X509* KeyManager::read_sm2_cert()
{
    QString pem_file =sm2_verification_veri_file;
    // 创建BIO对象读取证书文件
    BIO *cert_bio = BIO_new_file(pem_file.toStdString().c_str(), "r");
    if (cert_bio == nullptr) {
        qDebug()<<"KeyManager::read_sm2_cert: BIO_new_file failed!";
        return nullptr;
    }

    // 从BIO对象中读取证书内容
    X509 *sign_cert = PEM_read_bio_X509(cert_bio, NULL, NULL, NULL);
    if (sign_cert == nullptr) {
        BIO_free(cert_bio);
        qDebug()<<"KeyManager::read_sm2_cert: PEM_read_bio_X509 failed!";
        return nullptr;
    }

    // 释放BIO对象并返回证书对象
    BIO_free(cert_bio);
    return sign_cert;
}


// 生成SM2公私钥对，并保存到指定的文件中
bool KeyManager::generate_sm2_keypair(const QString &priv_file, const QString &pub_file)
{
    // 创建EC_KEY对象
    EC_KEY *ec_key = EC_KEY_new();
    if (ec_key == NULL) {
        return false;
    }

    // 获取国密推荐曲线
    EC_GROUP *ec_group = EC_GROUP_new_by_curve_name(NID_sm2);
    if (ec_group == NULL) {
        EC_KEY_free(ec_key);
        return false;
    }

    // 设置EC_KEY的曲线
    if (EC_KEY_set_group(ec_key, ec_group) != 1) {
        EC_GROUP_free(ec_group);
        EC_KEY_free(ec_key);
        return false;
    }

    // 生成EC_KEY的公私钥对
    if (EC_KEY_generate_key(ec_key) != 1) {
        EC_GROUP_free(ec_group);
        EC_KEY_free(ec_key);
        return false;
    }

    // 创建EVP_PKEY对象
    EVP_PKEY *evp_key = EVP_PKEY_new();
    if (evp_key == NULL) {
        EC_GROUP_free(ec_group);
        EC_KEY_free(ec_key);
        return false;
    }

    // 设置EVP_PKEY的类型和值为EC_KEY
    if (EVP_PKEY_assign_EC_KEY(evp_key, ec_key) != 1) {
        EVP_PKEY_free(evp_key);
        EC_GROUP_free(ec_group);
        EC_KEY_free(ec_key);
        return false;
    }

    // 释放EC_GROUP对象，因为它已经被EVP_PKEY引用
    EC_GROUP_free(ec_group);

    // 创建BIO对象，用来写入文件
    BIO *bio = NULL;

    // 写入私钥到文件
    bio = BIO_new_file(priv_file.toStdString().c_str(), "w");
    if (bio == NULL) {
        EVP_PKEY_free(evp_key);
        return false;
    }

    // 使用PEM格式和SM2算法标识写入私钥
    if (PEM_write_bio_PrivateKey(bio, evp_key, NULL, NULL, 0, NULL, NULL) != 1) {
        BIO_free(bio);
        EVP_PKEY_free(evp_key);
        return false;
    }

    // 释放BIO对象
    BIO_free(bio);

    // 写入公钥到文件
    bio = BIO_new_file(pub_file.toStdString().c_str(), "w");
    if (bio == NULL) {
        EVP_PKEY_free(evp_key);
        return false;
    }

    // 使用PEM格式和SM2算法标识写入公钥
    if (PEM_write_bio_PUBKEY(bio, evp_key) != 1) {
        BIO_free(bio);
        EVP_PKEY_free(evp_key);
        return false;
    }

    // 释放BIO对象
    BIO_free(bio);

    // 如果之前已经有公私钥，就释放它们
    if (sm2key != NULL) {
        EVP_PKEY_free(sm2key);
        sm2key = NULL;
    }

    // 将新生成的公私钥赋值给sm2key
    sm2key = evp_key;

//    EVP_PKEY_free(evp_key); // 释放EVP_PKEY对象，同时也会释放EC_KEY对象
    // 返回成功
    return true;
}

/*函数是可以成功读取公私钥文件的，不会被文件里的-----BEGIN PUBLIC KEY-----干扰。因为这些标记是PEM格式的一部分，
用来表示公钥或者私钥的开始和结束。PEM_read_bio_PrivateKey和PEM_read_bio_PUBKEY函数可以识别这些标记，
并且从中解析出公钥或者私钥的内容*/
// 从指定的文件中读取SM2公私钥对
bool KeyManager::load_sm2_keypair(const QString &priv_file, const QString &pub_file)
{
     // 创建EVP_PKEY对象，用来存储公私钥对
     EVP_PKEY *evp_key = EVP_PKEY_new();
     if (evp_key == NULL) {
         return false;
      }
     // 创建BIO对象，用来读取文件
     BIO *bio = NULL;

     // 从文件中读取私钥
     bio = BIO_new_file(priv_file.toStdString().c_str(), "r");
     if (bio == NULL) {
         EVP_PKEY_free(evp_key);
         return false;
     }

     // 使用PEM格式和SM2算法标识读取私钥
     if (PEM_read_bio_PrivateKey(bio, &evp_key, NULL, NULL) != evp_key) {
         BIO_free(bio);
         EVP_PKEY_free(evp_key);
         return false;
     }

     // 释放BIO对象
     BIO_free(bio);

     // 从文件中读取公钥
     bio = BIO_new_file(pub_file.toStdString().c_str(), "r");
     if (bio == NULL) {
         EVP_PKEY_free(evp_key);
         return false;
     }

     // 使用PEM格式和SM2算法标识读取公钥
     if (PEM_read_bio_PUBKEY(bio, &evp_key, NULL, NULL) != evp_key) {
         BIO_free(bio);
         EVP_PKEY_free(evp_key);
         return false;
     }

     // 释放BIO对象
     BIO_free(bio);

     // 如果之前已经有公私钥，就释放它们
     if (sm2key != NULL) {
         EVP_PKEY_free(sm2key);
         sm2key = NULL;
     }

     // 将新读取的公私钥赋值给sm2key
     sm2key = evp_key;

//     //释放指针
//     EVP_PKEY_free(evp_key);

     // 返回成功
     return true;
}
