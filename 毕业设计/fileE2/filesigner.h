#ifndef FILESIGNER_H
#define FILESIGNER_H

#include "sm2_key_manage.h"

// 文件签名模块类，用来封装文件签名和验证的操作
class FileSigner : public QObject {
    Q_OBJECT
public:
    FileSigner(KeyManager *key_manager); // 构造函数，需要传入一个密钥管理类的指针
    ~FileSigner();
    // 对指定的文件进行签名，并保存到指定的文件中
    bool sign_file(const QString &src_file, const QString &dst_file, const QByteArray &id);
    // 对指定的文件进行验证，并返回验证结果
    bool verify_file(const QString &sig_file,const QString &raw_file,const QByteArray &id);
private:
    KeyManager *key_manager; // 密钥管理类的指针
    // 使用SM3算法对文件生成摘要
    QByteArray sm3_hash_file(const QString &file);
    // 使用SM2算法对摘要进行签名
    QByteArray sm2_sign_hash(const QByteArray &hash,const QByteArray &id);
    // 使用SM2算法对摘要进行验证
    bool sm2_verify_hash(const QByteArray &hash, const QByteArray &sig, const QByteArray &id);
    // 使用PKCS#7语法封装签名结果和原文件数据
    QByteArray pkcs7_wrap(const QByteArray &sig, const QByteArray &data);
    // 使用PKCS#7语法解析签名结果和原文件数据
    bool pkcs7_unwrap(const QByteArray &pkcs7, QByteArray &sig, QByteArray &data);
    // 使用自定义语法封装签名结果和原文件数据
    QByteArray wrap(const QByteArray &sig, const QByteArray &data);
    // 使用自定义语法解析签名结果和原文件数据
    bool unwrap(const QByteArray &pk, QByteArray &sig, QByteArray &data);
};

#endif // FILESIGNER_H
