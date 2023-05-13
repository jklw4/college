// 文件签名模块类，用来封装文件签名和验证的操作
#include "FileSigner.h"
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QTime>
#include <openssl/pkcs7.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <qdebug.h>
#include <openssl/pkcs7.h>
#include <openssl/ec.h>

FileSigner::FileSigner(KeyManager *key_manager)
{
    this->key_manager = key_manager; // 保存密钥管理类的指针
}

FileSigner::~FileSigner()
{

}

// 对指定的文件进行签名，并保存到指定的文件中
// 参数id表示签名者的身份标识
bool FileSigner::sign_file(const QString &src_file, const QString &dst_file, const QByteArray &id)
{
    QTime timer; // 计时器，用来记录函数处理的时间
    timer.start(); // 开始计时

    // 检查源文件是否存在
    if (!QFile::exists(src_file)) {
        QMessageBox::critical(nullptr, "错误", "源文件不存在");
        return false;
    }

    // 检查目标文件是否已存在，如果存在则删除
    if (QFile::exists(dst_file)) {
        QFile::remove(dst_file);
    }

    // 使用SM3算法对源文件生成摘要
    QByteArray hash = sm3_hash_file(src_file);
    if (hash.isEmpty()) {
        QMessageBox::critical(nullptr, "错误", "生成摘要失败");
        return false;
    }
    qDebug() << "Hash:" << hash.toHex(); // 打印摘要结果

    // 使用SM2私钥对摘要进行签名
    QByteArray sig = sm2_sign_hash(hash, id); // 传入签名者的身份标识
    if (sig.isEmpty()) {
        QMessageBox::critical(nullptr, "错误", "生成签名失败");
        return false;
    }
    qDebug() << "Signature:" << sig.toHex(); // 打印签名结果

//    // 使用PKCS#7语法封装签名结果和原文件数据
//    QByteArray pkcs7 = pkcs7_wrap(sig, hash);
//    if (pkcs7.isEmpty()) {
//        QMessageBox::critical(nullptr, "错误", "生成PKCS#7结构失败");
//        return false;
//    }

//    // 将PKCS#7结构保存到目标文件中
//    QFile file(dst_file);
//    if (!file.open(QIODevice::WriteOnly)) {
//        QMessageBox::critical(nullptr, "错误", "打开目标文件失败");
//        return false;
//    }
//    file.write(pkcs7);
//    file.close();

    EC_KEY *pri_key = key_manager->get_sm2_private_key();
    // 根据私钥得到公钥
    const EC_POINT *pub_key = EC_KEY_get0_public_key(pri_key);
    if (pub_key == NULL) {
        printf("获取公钥失败\n");
        return -1;
    }
    // 转换为字节数组
    const EC_GROUP *group = EC_KEY_get0_group(pri_key);
    size_t len = EC_POINT_point2oct(group, pub_key, POINT_CONVERSION_UNCOMPRESSED, NULL, 0, NULL);
    unsigned char *buf = (unsigned char *)malloc(len);
    if (buf == NULL) {
        printf("分配内存失败\n");
        return -1;
    }
    EC_POINT_point2oct(group, pub_key, POINT_CONVERSION_UNCOMPRESSED, buf, len, NULL);
    // 存入QByteArray变量
    QByteArray pub_data((char *)buf, len);
    free(buf);

    // 使用自定义语法封装签名结果和公钥
    QByteArray pk = wrap(sig, pub_data);
    if (pk.isEmpty()) {
        QMessageBox::critical(nullptr, "错误", "生成自定义语法结构失败");
        return false;
    }

    // 将自定义语法结构保存到目标文件中
    QFile file(dst_file);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(nullptr, "错误", "打开目标文件失败");
        return false;
    }
    file.write(pk);
    file.close();

    int elapsed = timer.elapsed(); // 记录结束时间
    QMessageBox::information(nullptr, "成功", QString("文件签名成功，耗时%1毫秒").arg(elapsed));
    return true;
}


// 对指定的文件进行验证，并返回验证结果
// 参数id表示签名者的身份标识
bool FileSigner::verify_file(const QString &signature_file, const QString &raw_file, const QByteArray &id)
{
    QTime timer; // 计时器，用来记录函数处理的时间
    timer.start(); // 开始计时

    // 检查文件是否存在
    if (!QFile::exists(signature_file)) {
        QMessageBox::critical(nullptr, "错误", "签名文件不存在");
        return false;
    }
    // 检查文件是否存在
    if (!QFile::exists(raw_file)) {
        QMessageBox::critical(nullptr, "错误", "待验证的原文件不存在");
        return false;
    }

//    // 读取文件内容
//    QFile file(signature_file);
//    if (!file.open(QIODevice::ReadOnly)) {
//        QMessageBox::critical(nullptr, "错误", "打开文件失败");
//        return false;
//    }
//    QByteArray pkcs7 = file.readAll();
//    file.close();

//    // 使用PKCS#7语法解析签名结果和原文件数据
//    QByteArray sig, hash;
//    if (!pkcs7_unwrap(pkcs7, sig, hash)) {
//        QMessageBox::critical(nullptr, "错误", "解析PKCS#7结构失败");
//        return false;
//    }

    // 读取文件内容
    QFile file(signature_file);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "错误", "打开文件失败");
        return false;
    }
    QByteArray pk = file.readAll();
    file.close();

    // 使用自定义语法解析签名结果和签名者公钥
    QByteArray sig;//存签名结果
    QByteArray pub_data;//存签名者公钥
    QByteArray hash;//存对原文件进行sm3摘要得到hash值
    if (!unwrap(pk, sig, pub_data)) {
        QMessageBox::critical(nullptr, "错误", "解析自定义语法结构失败");
        return false;
    }
    hash=sm3_hash_file(raw_file);
    // 使用SM2公钥对摘要进行验证
    if (!sm2_verify_hash(hash, sig, id)) { // 传入签名者的身份标识
        QMessageBox::critical(nullptr, "提示", "签名和身份标识与原文件不匹配!");
        return false;
    }

    int elapsed = timer.elapsed(); // 记录结束时间
    QMessageBox::information(nullptr, "成功", QString("文件验签成功，耗时%1毫秒").arg(elapsed));
    return true;
}


// 使用SM3算法对文件生成摘要，包含大文件处理。
QByteArray FileSigner::sm3_hash_file(const QString &raw_file)
{
    // 打开文件
    QFile file(raw_file);
    if (!file.open(QIODevice::ReadOnly)) {
        return QByteArray();
    }

    // 创建SM3上下文
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) {
        return QByteArray();
    }

    // 初始化SM3上下文
    if (!EVP_DigestInit_ex(ctx, EVP_sm3(), nullptr)) {
        EVP_MD_CTX_free(ctx);
        return QByteArray();
    }

    // 读取文件数据并更新摘要
    const int buffer_size = 4096; // 缓冲区大小
    char buffer[buffer_size]; // 缓冲区数组
    int bytes_read; // 每次读取的字节数
    while ((bytes_read = file.read(buffer, buffer_size)) > 0) {
        if (!EVP_DigestUpdate(ctx, buffer, bytes_read)) {
            EVP_MD_CTX_free(ctx);
            return QByteArray();
        }
    }
    file.close();

    // 获取摘要结果
    unsigned char hash[EVP_MAX_MD_SIZE]; // 摘要数组
    unsigned int hash_len; // 摘要长度
    if (!EVP_DigestFinal_ex(ctx, hash, &hash_len)) {
        EVP_MD_CTX_free(ctx);
        return QByteArray();
    }

    // 释放SM3上下文
    EVP_MD_CTX_free(ctx);

    // 返回摘要结果
    return QByteArray((char *)hash, hash_len);
}

// 使用SM2算法对摘要进行签名
// 参数id表示签名者的身份标识
QByteArray FileSigner::sm2_sign_hash(const QByteArray &hash, const QByteArray &id)
{
    // 获取SM2私钥
    EC_KEY *key = key_manager->get_sm2_private_key();
    if (!key) {
        return QByteArray();
    }

    // 创建一个空的EVP_PKEY结构体
    EVP_PKEY *pkey = EVP_PKEY_new();
    if (!pkey) {
        return QByteArray();
    }

    // 将EC_KEY密钥赋值给EVP_PKEY结构体
    if (EVP_PKEY_assign_EC_KEY(pkey, key) <= 0) {
        EVP_PKEY_free(pkey);
        return QByteArray();
    }

    // 设置密钥的别名类型为EVP_PKEY_SM2
    if (EVP_PKEY_set_alias_type(pkey, EVP_PKEY_SM2) <= 0) {
        EVP_PKEY_free(pkey);
        return QByteArray();
    }

    // 创建SM2签名上下文
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    if (!ctx) {
        EVP_PKEY_free(pkey);
        return QByteArray();
    }

    // 初始化SM2签名上下文
    if (EVP_PKEY_sign_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return QByteArray();
    }

    // 设置签名者的身份标识
    if (EVP_PKEY_CTX_set1_id(ctx, id.data(), id.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return QByteArray();
    }

    // 计算签名结果所需的缓冲区大小
    size_t sig_len;
    if (EVP_PKEY_sign(ctx, nullptr, &sig_len, (unsigned char *)hash.data(), hash.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return QByteArray();
    }

    // 分配签名结果缓冲区
    unsigned char *sig = (unsigned char *)OPENSSL_malloc(sig_len);
    if (!sig) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return QByteArray();
    }

    // 获取签名结果
    if (EVP_PKEY_sign(ctx, sig, &sig_len, (unsigned char *)hash.data(), hash.size()) <= 0) {
        OPENSSL_free(sig);
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return QByteArray();
    }

    // 释放SM2签名上下文和EVP_PKEY结构体
    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(pkey);

    // 返回签名结果
    return QByteArray((char *)sig, sig_len);
}



// 使用SM2算法对摘要进行验证
// 参数id表示签名者的身份标识
bool FileSigner::sm2_verify_hash(const QByteArray &hash, const QByteArray &sig, const QByteArray &id)
{
    // 获取SM2公钥
    EC_KEY *key = key_manager->get_sm2_public_key();
    if (!key) {
        return false;
    }

    // 创建一个空的EVP_PKEY结构体
    EVP_PKEY *pkey = EVP_PKEY_new();
    if (!pkey) {
        return false;
    }

    // 将EC_KEY密钥赋值给EVP_PKEY结构体
    if (EVP_PKEY_assign_EC_KEY(pkey, key) <= 0) {
        EVP_PKEY_free(pkey);
        return false;
    }

    // 设置密钥的别名类型为EVP_PKEY_SM2
    if (EVP_PKEY_set_alias_type(pkey, EVP_PKEY_SM2) <= 0) {
        EVP_PKEY_free(pkey);
        return false;
    }

    // 创建SM2验证上下文
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    if (!ctx) {
        EVP_PKEY_free(pkey);
        return false;
    }

    // 初始化SM2验证上下文
    if (EVP_PKEY_verify_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return false;
    }

    // 设置签名者的身份标识
    if (EVP_PKEY_CTX_set1_id(ctx, id.data(), id.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return false;
    }

    // 验证签名结果
    int ret = EVP_PKEY_verify(ctx, (unsigned char *)sig.data(), sig.size(), (unsigned char *)hash.data(), hash.size());

    // 释放SM2验证上下文和EVP_PKEY结构体
    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(pkey);

    // 返回验证结果
    return ret == 1;
}

// 使用PKCS#7语法封装签名结果和原文件数据
// 参数：sig - 签名结果，data - 原文件数据
QByteArray FileSigner::pkcs7_wrap(const QByteArray &sig, const QByteArray &data)
{
    // 创建一个PKCS#7 SignedData结构
    PKCS7 *p7 = PKCS7_new();
    if (!p7) {
        return QByteArray();
    }

    // 设置PKCS#7结构的类型为NID_pkcs7_signed，表示是一个SignedData结构
    if (!PKCS7_set_type(p7, NID_pkcs7_signed)) {
        PKCS7_free(p7);
        return QByteArray();
    }

    // 获取PKCS#7结构的SignedData部分
    PKCS7_SIGNED *p7s = p7->d.sign;
    if (!p7s) {
        PKCS7_free(p7);
        return QByteArray();
    }

    // 设置PKCS#7结构的内容类型为NID_pkcs7_data，表示是一个原始数据
    if (!PKCS7_content_new(p7, NID_pkcs7_data)) {
        PKCS7_free(p7);
        qDebug()<<"pkcs7_wrap:PKCS7_content_new erro!";
        return QByteArray();
    }

    // 设置PKCS#7结构的内容数据为原文件数据
    if (!ASN1_STRING_set(p7->d.sign->contents->d.data, data.data(), data.size())) {
        PKCS7_free(p7);
        qDebug()<<"pkcs7_wrap:ASN1_STRING_set erro! ";
        return QByteArray();
    }

    // 创建一个签名者信息结构
    PKCS7_SIGNER_INFO *si = PKCS7_SIGNER_INFO_new();
    if (!si) {
        PKCS7_free(p7);
        qDebug()<<"pkcs7_wrap:PKCS7_SIGNER_INFO_new erro!";
        return QByteArray();
    }

    // 设置签名者信息结构的版本为1
    if (!ASN1_INTEGER_set(si->version, 1)) {
        PKCS7_SIGNER_INFO_free(si);
        PKCS7_free(p7);
        qDebug()<<"pkcs7_wrap:ASN1_INTEGER_set erro!";
        return QByteArray();
    }

    // 获取SM2私钥
    EC_KEY *key = key_manager->get_sm2_private_key();
    if (!key) {
        return QByteArray();
    }

    // 创建一个空的EVP_PKEY结构体
    EVP_PKEY *pkey = EVP_PKEY_new();
    if (!pkey) {
        EC_KEY_free(key);
        return QByteArray();
    }

    // 将EC_KEY密钥赋值给EVP_PKEY结构体
    if (EVP_PKEY_assign_EC_KEY(pkey, key) <= 0) {
        EVP_PKEY_free(pkey);
        EC_KEY_free(key);
        return QByteArray();
    }

    /*在使用EVP_PKEY_assign_EC_KEY()函数时，没有指定SM2算法的NID。
     * 这个函数是用来将EC_KEY结构体赋值给EVP_PKEY结构体的，但是它不会自动检测EC_KEY结构体的算法类型，
     * 而是默认使用EVP_PKEY_EC（408）作为NID*/
    // **设置EVP_PKEY结构体的类型为EVP_PKEY_SM2**
    if (!EVP_PKEY_set_alias_type(pkey, EVP_PKEY_SM2)) {
        qDebug()<<"pkcs7_wrap:EVP_PKEY_set_alias_type error!";
        EVP_PKEY_free(pkey);
        return QByteArray();
    }

    // 创建一个空的EVP_PKEY_CTX结构体
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (!ctx) {
        return QByteArray();
    }
    // 设置签名者信息结构的签名证书和签名者证书
    // 检查参数是否有效
    if (key_manager->read_sm2_cert() == NULL) {
        qDebug()<<"pkcs7_wrap:sign_cert is NULL!";
        return QByteArray();
    }
    // 使用EVP_PKEY_CTX结构体检查私钥是否有效
    if (EVP_PKEY_check(ctx) <= 0) {
        qDebug()<<"pkcs7_wrap:pkey is invalid!";
        return QByteArray();
    }

    // 检查证书和私钥是否匹配
    if (X509_check_private_key(key_manager->read_sm2_cert(), pkey)<=0) {
        qDebug()<<"pkcs7_wrap:sign_cert and pkey do not match!";
        return QByteArray();
    }
    // 检查摘要算法是否存在
    const EVP_MD *md = EVP_sm3();
    if (md == NULL) {
        qDebug()<<"pkcs7_wrap:digest is NULL!";
        return QByteArray();
    }
    // 输出摘要算法的类型和名称
    qDebug()<<"pkcs7_wrap:digest type is "<<EVP_MD_type(md);
    qDebug()<<"pkcs7_wrap:digest name is "<<EVP_MD_name(md);

    // 检查证书是否存在
    X509 *cert = key_manager->read_sm2_cert();
    if (cert == NULL) {
        qDebug()<<"pkcs7_wrap:sign_cert is NULL!";
        return QByteArray();
    }
    // 输出证书的版本和主题
    qDebug()<<"pkcs7_wrap:sign_cert version is "<<X509_get_version(cert);
    qDebug()<<"pkcs7_wrap:sign_cert subject is "<<X509_NAME_oneline(X509_get_subject_name(cert), NULL, 0);

    // 检查pkey参数是否有效
    if (pkey == NULL) {
        qDebug()<<"pkcs7_wrap:pkey is NULL!";
        return QByteArray();
    }
    // 检查pkey参数是否支持SM2签名算法
    if (EVP_PKEY_id(pkey) != EVP_PKEY_SM2) {
        qDebug() << "EVP_PKEY_id(pkey) = " << EVP_PKEY_id(pkey);
        qDebug()<<"pkcs7_wrap:pkey is not SM2!";
        return QByteArray();
    }
    // 检查si参数是否有效
    if (si == NULL) {
        qDebug()<<"pkcs7_wrap:si is NULL!";
        return QByteArray();
    }

    // 调用PKCS7_SIGNER_INFO_set函数
    if (!PKCS7_SIGNER_INFO_set(si, key_manager->read_sm2_cert(), pkey, EVP_sm3())) {
        // 获取错误代码和信息
        unsigned long err = ERR_get_error();
        char *errstr = ERR_error_string(err, NULL);
        qDebug()<<"pkcs7_wrap:PKCS7_SIGNER_INFO_set error!";
        qDebug()<<"Error code: "<<err;
        qDebug()<<"Error string: "<<errstr;
        PKCS7_SIGNER_INFO_free(si);
        PKCS7_free(p7);
        EVP_PKEY_free(pkey);
        return QByteArray();
    }


    // 设置签名者信息结构的加密后的摘要为sig
    if (!ASN1_STRING_set(si->enc_digest, sig.data(), sig.size())) {
        PKCS7_SIGNER_INFO_free(si);
        PKCS7_free(p7);
        qDebug()<<"pkcs7_wrap:ASN1_STRING_set erro! ";
        return QByteArray();
    }

    // 将签名者信息结构添加到PKCS#7结构中
    if (!PKCS7_add_signer(p7, si)) {
        PKCS7_SIGNER_INFO_free(si);
        PKCS7_free(p7);
        qDebug()<<"pkcs7_wrap:PKCS7_add_signer erro! ";
        return QByteArray();
    }

    // 将PKCS#7结构编码为DER格式
    unsigned char *der = nullptr;
    int der_len = i2d_PKCS7(p7, &der);
    if (der_len <= 0) {
        PKCS7_free(p7);
        qDebug()<<"pkcs7_wrap:i2d_PKCS7 failed!";
        return QByteArray();
    }

    // 释放PKCS#7结构
    PKCS7_free(p7);

    //释放evp_pkey结构
    EVP_PKEY_free(pkey);

    // 释放EVP_PKEY_CTX结构
    EVP_PKEY_CTX_free(ctx);

    // 返回DER格式的数据
    return QByteArray((char *)der, der_len);
}


// 使用PKCS#7语法解析签名结果和原文件数据
bool FileSigner::pkcs7_unwrap(const QByteArray &pkcs7, QByteArray &sig, QByteArray &data)
{
    // 将DER格式的数据解码为PKCS#7结构
    const unsigned char *der = (unsigned char *)pkcs7.data();
    PKCS7 *p7 = d2i_PKCS7(nullptr, &der, pkcs7.size());
    if (!p7) {
        qDebug()<<"pkcs7_unwrap:DER to pkcs#7 erro!";
        return false;
    }

    // 检查PKCS#7结构的类型是否为NID_pkcs7_signed，表示是一个SignedData结构
    if (!PKCS7_type_is_signed(p7)) {
        PKCS7_free(p7);
        qDebug()<<"pkcs7_unwrap:pkcs#7 is not NID_pkcs7_signed, erro!";
        return false;
    }

    // 获取PKCS#7结构的SignedData部分
    PKCS7_SIGNED *p7s = p7->d.sign;
    if (!p7s) {
        PKCS7_free(p7);
        qDebug()<<"pkcs7_unwrap:get the signed part of pkcs#7 erro!";
        return false;
    }

    // 检查PKCS#7结构的内容类型是否为NID_pkcs7_data，表示是一个原始数据
    if (!PKCS7_type_is_data(p7s->contents)) {
        PKCS7_free(p7);
        qDebug()<<"pkcs7_unwrap:PKCS7_type_is_data is not NID_pkcs7_data, erro!";
        return false;
    }

    // 获取PKCS#7结构的内容数据，即原文件数据
    data = QByteArray((char *)p7s->contents->d.data->data, p7s->contents->d.data->length);

    // 检查PKCS#7结构的签名者信息列表是否只有一个元素，表示只有一个签名者信息结构
    if (sk_PKCS7_SIGNER_INFO_num(p7s->signer_info) != 1) {
        PKCS7_free(p7);
        qDebug()<<"pkcs7_unwrap:pkcs7 signer_info number is not 1, erro!";
        return false;
    }

    // 获取PKCS#7结构的签名者信息列表中的第一个元素，即签名者信息结构
    PKCS7_SIGNER_INFO *si = sk_PKCS7_SIGNER_INFO_value(p7s->signer_info, 0);
    if (!si) {
        PKCS7_free(p7);
        qDebug()<<"pkcs7_unwrap:sk_PKCS7_SIGNER_INFO_value erro!";
        return false;
    }

    // 检查签名者信息结构的摘要算法是否为SM3，这里使用OBJ_txt2obj函数根据字符串来获取算法对象
    if (OBJ_cmp(si->digest_alg->algorithm, OBJ_txt2obj("SM3", 0)) != 0) {
        PKCS7_free(p7);
        qDebug()<<"pkcs7_unwrap:digest_alg->algorithm is not sm3, erro!";
        return false;
    }

    // 获取签名者信息结构的签名结果，即SM2对摘要的加密结果
    sig = QByteArray((char *)si->enc_digest->data, si->enc_digest->length);

    // 释放PKCS#7结构
    PKCS7_free(p7);

    // 返回成功
    return true;
}



// 使用自定义语法封装签名结果和原文件数据
// 语法规则为：[4字节签名长度][签名值][公钥内容]
QByteArray FileSigner::wrap(const QByteArray &sig, const QByteArray &data) {
    QByteArray pk; // 用来存储封装后的结果
    QDataStream stream(&pk, QIODevice::WriteOnly); // 用来写入二进制数据
    stream.setByteOrder(QDataStream::BigEndian); // 设置字节序为大端模式
    quint32 sig_len = sig.size(); // 获取签名值的长度
    stream << sig_len; // 写入4字节的签名长度
    stream.writeRawData(sig.data(), sig_len); // 写入签名值
    stream.writeRawData(data.data(), data.size()); // 写入原文件数据
    return pk; // 返回封装后的结果
}

// 使用自定义语法解析签名结果和原文件数据
// 语法规则为：[4字节签名长度][签名值][公钥内容]
bool FileSigner::unwrap(const QByteArray &pk, QByteArray &sig, QByteArray &data) {
    QDataStream stream(pk); // 用来读取二进制数据
    stream.setByteOrder(QDataStream::BigEndian); // 设置字节序为大端模式
    quint32 sig_len; // 用来存储签名长度
    stream >> sig_len; // 读取4字节的签名长度
    if (sig_len > static_cast<quint32>(pk.size()) - 4) { // 检查签名长度是否合法，把pk.size()转换成quint32类型
        QMessageBox::critical(nullptr, "错误", "解析PK结构失败");
        return false;
    }
    sig.resize(sig_len); // 调整签名值的大小
    stream.readRawData(sig.data(), sig_len); // 读取签名值
    data = pk.mid(4 + sig_len); // 获取原文件数据
    return true; // 返回解析成功
}
