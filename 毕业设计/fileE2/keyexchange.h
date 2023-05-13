#ifndef KEYEXCHANGE_H
#define KEYEXCHANGE_H


// 导入openssl库头文件
#include <openssl/ec.h>
#include <openssl/ecdh.h>
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <sm2_key_manage.h>

// 定义一个类，用来封装密钥交换的功能
class KeyExchange : public QObject
{
    Q_OBJECT
public:
    KeyExchange();
    ~KeyExchange();

    // 设置本地的密钥管理类对象
    void set_local_key_manager(KeyManager *local_km);

    // 设置远程的密钥管理类对象
    void set_remote_key_manager(KeyManager *remote_km);

    // 进行密钥交换，并获取共享密钥
    bool do_key_exchange();

    // 保存共享密钥到一个文件中
    bool save_shared_secret(const QString &file_name);

private:
    // 从EC_KEY对象中获取公钥的X坐标和Y坐标
    void get_ec_pubkey_coordinates(EC_KEY *ec_key, BIGNUM **x, BIGNUM **y);

    // 从X坐标和Y坐标创建一个EC_KEY对象
    EC_KEY *create_ec_pubkey_from_coordinates(BIGNUM *x, BIGNUM *y);

    KeyManager *local_km; // 本地的密钥管理类对象
    KeyManager *remote_km; // 远程的密钥管理类对象
    unsigned char *shared_secret; // 共享密钥
    size_t shared_secret_len; // 共享密钥的长度
};


#endif // KEYEXCHANGE_H
