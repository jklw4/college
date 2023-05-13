#include "keyexchange.h"
#include <qdebug.h>
#include <openssl/err.h>

// 实现KeyExchange类的构造函数
KeyExchange::KeyExchange()
{
    // 初始化本地和远程的密钥管理类对象为NULL
    local_km = NULL;
    remote_km = NULL;
    // 初始化共享密钥和共享密钥长度为0
    shared_secret = NULL;
    shared_secret_len = 0;
}

// 实现KeyExchange类的析构函数
KeyExchange::~KeyExchange()
{
    // 释放共享密钥
    if (shared_secret != NULL) {
        free(shared_secret);
    }
}

// 实现KeyExchange类的set_local_key_manager函数
void KeyExchange::set_local_key_manager(KeyManager *local_km)
{
    // 设置本地的密钥管理类对象
    this->local_km = local_km;
}

// 实现KeyExchange类的set_remote_key_manager函数
void KeyExchange::set_remote_key_manager(KeyManager *remote_km)
{
    // 设置远程的密钥管理类对象
    this->remote_km = remote_km;
}

// 实现KeyExchange类的do_key_exchange函数
bool KeyExchange::do_key_exchange()
{
    // 检查本地和远程的密钥管理类对象是否有效
    if (local_km == NULL || remote_km == NULL)
    {
        return false; // 无效，返回失败
    }
    // 获取本地的SM2私钥
    EC_KEY *local_privkey = local_km->get_sm2_private_key();
    // 获取远程的SM2公钥
    EC_KEY *remote_pubkey = remote_km->get_sm2_public_key();

    // 创建一个空的EVP_PKEY对象
    EVP_PKEY *local_pkey = EVP_PKEY_new();
    // 将EC_KEY对象赋值给EVP_PKEY对象
    EVP_PKEY_assign_EC_KEY(local_pkey, local_privkey);

    // 使用EVP_PKEY对象创建一个EVP_PKEY_CTX对象，用来进行ECDH运算
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(local_pkey, NULL);
    // 初始化EVP_PKEY_CTX对象
    EVP_PKEY_derive_init(ctx);

    // 创建一个空的EVP_PKEY对象
    EVP_PKEY *remote_pkey = EVP_PKEY_new();
    // 将EC_KEY对象赋值给EVP_PKEY对象
    EVP_PKEY_assign_EC_KEY(remote_pkey, remote_pubkey);

    // 设置EVP_PKEY_CTX对象使用远程的SM2公钥
    EVP_PKEY_derive_set_peer(ctx, remote_pkey);

    // 计算共享密钥的长度，并分配内存空间
    EVP_PKEY_derive(ctx, NULL, &shared_secret_len);
    shared_secret = (unsigned char *)malloc(shared_secret_len);
    // 计算共享密钥，并存储到内存中
    if (!EVP_PKEY_derive(ctx, shared_secret, &shared_secret_len))
    {
        return false; // 计算失败，返回失败
    }
    // 释放EVP_PKEY_CTX对象和EVP_PKEY对象
    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(local_pkey);
    EVP_PKEY_free(remote_pkey);
    // 返回成功
    return true;
}

// 实现KeyExchange类的save_shared_secret函数
bool KeyExchange::save_shared_secret(const QString &file_name)
{
   // 检查共享密钥和长度是否有效
   if (shared_secret == NULL || shared_secret_len == 0) {
      qDebug()<<"keyexchange:save_shared_secret:invalid shared secret";
      return false; // 无效的共享密钥
   }
   qDebug()<<"keyexchange.cpp::save_shared_secret: shared_secret is:";
   for (int i = 0; i < 32; i++) {
       qDebug("%02x ", shared_secret[i]);
   }

   // 创建一个文件BIO
   BIO *fp = BIO_new_file(file_name.toStdString().c_str(), "wb");
   if (fp == NULL) {
      qDebug()<<"keyexchange:save_shared_secret:open failed";
      return false; // 打开文件失败
   }
   // 将共享密钥写入到文件中
   int written = BIO_write(fp, shared_secret, shared_secret_len);
   if (written <= 0) {
      // 写入错误，获取错误信息
      unsigned long err = ERR_get_error();
      char *err_msg = ERR_error_string(err, NULL);
      qDebug()<<"keyexchange:save_shared_secret:write error"<<"\n err_msg:"<<err_msg;
      BIO_free(fp); // 关闭文件
      return false;
   }
   if (written != shared_secret_len) {
      // 写入不完整，获取错误信息
      unsigned long err = ERR_get_error();
      char *err_msg = ERR_error_string(err, NULL);
      qDebug()<<"keyexchange:save_shared_secret:write incomplete"<<"\n err_msg:"<<err_msg;
      BIO_free(fp); // 关闭文件
      return false;
   }
   // 写入成功，关闭文件
   BIO_free(fp);
   return true; // 保存成功
}

// 实现KeyExchange类的get_ec_pubkey_coordinates函数
void KeyExchange::get_ec_pubkey_coordinates(EC_KEY *ec_key, BIGNUM **x, BIGNUM **y)
{
    // 获取EC_KEY对象中的椭圆曲线参数
    const EC_GROUP *group = EC_KEY_get0_group(ec_key);
    // 获取EC_KEY对象中的公钥点
    const EC_POINT *point = EC_KEY_get0_public_key(ec_key);
    // 创建两个BIGNUM对象，用来存储X坐标和Y坐标
    *x = BN_new();
    *y = BN_new();
    // 从公钥点中获取X坐标和Y坐标，并存储到BIGNUM对象中
    EC_POINT_get_affine_coordinates_GFp(group, point, *x, *y, NULL);
}

// 实现KeyExchange类的create_ec_pubkey_from_coordinates函数
EC_KEY *KeyExchange::create_ec_pubkey_from_coordinates(BIGNUM *x, BIGNUM *y)
{
    // 创建一个EC_KEY对象
    EC_KEY *ec_key = EC_KEY_new();
    // 设置EC_KEY对象使用SM2曲线参数
    EC_KEY_set_group(ec_key, EC_GROUP_new_by_curve_name(NID_sm2));
    // 创建一个EC_POINT对象，用来存储公钥点
    EC_POINT *point = EC_POINT_new(EC_KEY_get0_group(ec_key));
    // 从X坐标和Y坐标设置公钥点
    EC_POINT_set_affine_coordinates_GFp(EC_KEY_get0_group(ec_key), point, x, y, NULL);
    // 设置EC_KEY对象的公钥点
    EC_KEY_set_public_key(ec_key, point);
    // 释放EC_POINT对象
    EC_POINT_free(point);
    // 返回EC_KEY对象
    return ec_key;
}
