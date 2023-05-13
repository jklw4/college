#include "filecrypt.h"
#include <qdebug.h>
#include <error.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <QFile>
#include "tool.h"
#include <sys/stat.h> // struct stat
#include <string>
#include <QtCore/qtextcodec.h>


// 实现FileCrypt类的构造函数
FileCrypt::FileCrypt()
{
    // 初始化共享密钥为NULL
    shared_secret = NULL;
}

// 实现FileCrypt类的析构函数
FileCrypt::~FileCrypt()
{
    // 释放共享密钥
    if (shared_secret != NULL) {
        free(shared_secret);
    }
}

//从二进制文件file_name中读取二进制内容并存入到unsigned char*类型的shared_secret类变量中
bool FileCrypt::load_shared_secret(const QString &file_name)
{
    //避免中文路径无法得到file_size的问题！
    QTextCodec* codec = QTextCodec:: codecForName ( "gbk" );
    std::string file_name_gbk = codec-> fromUnicode ( file_name ). toStdString ();

   // 创建一个文件BIO
//   BIO *file = BIO_new_file(file_name.toStdString().c_str(), "rb");
   BIO *file = BIO_new_file(file_name_gbk.c_str(), "rb");
   if (file == NULL) {
       qDebug()<<"filecrypt.cpp:load_shared_secret:file erro!";
      return false; // 创建文件失败
   }
   qDebug()<<"filecrypt.cpp:load_shared_secret: file_name.toStdString().c_str()  is是:";
   qDebug()<<file_name.toStdString().c_str();
   // 获取文件的大小
   size_t file_size;
   // 这是一个存储文件(夹)信息的结构体，其中有文件大小和创建时间、访问时间、修改时间等
   struct stat statbuf;
   // 提供文件名字符串，获得文件属性结构体
//   stat(file_name.toStdString().c_str(), &statbuf);
   stat(file_name_gbk.c_str(), &statbuf);
   // 获取文件大小
   file_size = statbuf.st_size;

   qDebug()<<"filecrypt.cpp:load_shared_secret: file_size is:"<<file_size;
   // 分配内存空间，用来存储共享密钥
   shared_secret = (unsigned char *)malloc(file_size);
   if (shared_secret == NULL) {
      BIO_free(file); // 释放文件
      qDebug()<<"filecrypt.cpp:load_shared_secret:shared_secret == NULL error!";
      return false; // 分配内存失败
   }
   // 将文件中的数据读取到共享密钥中
   size_t read = BIO_read(file, shared_secret, file_size);
   if (read != file_size) {
      // 读取失败，释放内存，释放文件，获取错误信息
      free(shared_secret);
      BIO_free(file);
      unsigned long err = ERR_get_error();
      char *err_msg = ERR_error_string(err, NULL);
      qDebug()<<"filecrypt.cpp:load_shared_secret:read open error,file_name:"<<file_name<<"\n err_msg:"<<err_msg;
      return false;
   }
   // 读取成功，关闭文件
   BIO_free(file);
   return true;
}


// 实现FileCrypt类的sm4_crypt_file函数,encrypt为true表示加密，为false表示解密
bool FileCrypt::sm4_crypt_file(const QString &in_file_name, const QString &out_file_name, bool encrypt)
{
    // 创建BIO对象，用于文件读写
    BIO *in_bio = BIO_new_file(in_file_name.toStdString().c_str(), "rb");
    if (!in_bio)
    {
        qWarning() << "filecrypt.cpp::sm4_cbc:Cannot open input file" << in_file_name;
        return false;
    }

    BIO *out_bio = BIO_new_file(out_file_name.toStdString().c_str(), "wb");
    if (!out_bio)
    {
        qWarning() << "filecrypt.cpp::sm4_cbc:Cannot open output file" << out_file_name;
        BIO_free(in_bio);
        return false;
    }

    // 创建EVP_CIPHER_CTX对象
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
    {
        qWarning() << "filecrypt.cpp::sm4_cbc:Cannot create EVP_CIPHER_CTX object";
        ERR_print_errors_fp(stderr);
        BIO_free_all(in_bio);
        BIO_free_all(out_bio);
        return false;
    }
    memcpy(iv, shared_secret, 16); // 将shared_secret的前16字节复制到iv中
    qDebug()<<"filecrypt.cpp::sm4_cbc: shared_secret is:";
    for (int i = 0; i < 32; i++) {
        qDebug("%02x ", shared_secret[i]);
    }
    qDebug()<<"filecrypt.cpp::sm4_cbc: iv is:"<<iv;
    qDebug()<<"iv 2 is:";
    for (int i = 0; i < 16; i++) {
        qDebug("%02x ", iv[i]);
    }

    // 初始化EVP_CIPHER_CTX对象，设置加密算法为SM4，模式为CBC，密钥和随机向量
    if (!EVP_CipherInit_ex(ctx, EVP_sm4_cbc(), NULL, shared_secret, iv, encrypt))
    {
        qWarning() << "filecrypt.cpp::sm4_cbc:Cannot initialize EVP_CIPHER_CTX object";
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        BIO_free_all(in_bio);
        BIO_free_all(out_bio);
        return false;
    }

    // 设置填充模式为PKCS#7
    if (!EVP_CIPHER_CTX_set_padding(ctx, 1))
    {
        qWarning() << "filecrypt.cpp::sm4_cbc:Cannot set padding mode to PKCS#7";
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        BIO_free_all(in_bio);
        BIO_free_all(out_bio);
        return false;
    }

    // 定义缓冲区大小为16KB，输入缓冲区和输出缓冲区
    const int buffer_size = 16 * 1024;
    unsigned char in_buffer[buffer_size];
    unsigned char out_buffer[buffer_size + EVP_MAX_BLOCK_LENGTH];

    // 循环读取输入文件，加密或解密，并写入输出文件
    int in_len = 0; // 输入缓冲区的长度
    int out_len = 0; // 输出缓冲区的长度
    while ((in_len = BIO_read(in_bio, in_buffer, buffer_size)) > 0)
    {
        if (!EVP_CipherUpdate(ctx, out_buffer, &out_len, in_buffer, in_len))
        {
            qWarning() << "filecrypt.cpp::sm4_cbc:Cannot encrypt or decrypt data";
            ERR_print_errors_fp(stderr);
            EVP_CIPHER_CTX_free(ctx);
            BIO_free_all(in_bio);
            BIO_free_all(out_bio);
            return false;
        }
        if (BIO_write(out_bio, out_buffer, out_len) != out_len)
        {
            qWarning() << "filecrypt.cpp::sm4_cbc:Cannot write to output file";
            EVP_CIPHER_CTX_free(ctx);
            BIO_free_all(in_bio);
            BIO_free_all(out_bio);
            return false;
        }
    }

    // 检查是否有读取错误
    if (in_len < 0)
    {
        qWarning() << "filecrypt.cpp::sm4_cbc:Cannot read from input file";
        EVP_CIPHER_CTX_free(ctx);
        BIO_free_all(in_bio);
        BIO_free_all(out_bio);
        return false;
    }

    // 处理最后一块数据，并写入输出文件
    if (!EVP_CipherFinal_ex(ctx, out_buffer, &out_len))
    {
        qWarning() << "filecrypt.cpp::sm4_cbc:The last piece of data cannot be processed error";
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        BIO_free_all(in_bio);
        BIO_free_all(out_bio);
        return false;
    }
    if (BIO_write(out_bio, out_buffer, out_len) != out_len)
    {
        qWarning() << "filecrypt.cpp::sm4_cbc:Cannot write to output file";
        EVP_CIPHER_CTX_free(ctx);
        BIO_free_all(in_bio);
        BIO_free_all(out_bio);
        return false;
    }

    // 释放EVP_CIPHER_CTX对象和BIO对象
    EVP_CIPHER_CTX_free(ctx);
    BIO_free_all(in_bio);
    BIO_free_all(out_bio);

    // 返回成功
    return true;
}



// 实现FileCrypt类的sm4_crypt_folder函数
bool FileCrypt::sm4_crypt_folder(const QString &in_folder_name, const QString &out_folder_name, bool encrypt)
{
    // 检查共享密钥是否有效
    if (shared_secret == NULL) {
        return false; // 无效，返回失败
    }
    // 获取输入文件夹中的所有文件名
    QDir in_dir(in_folder_name);
    QStringList in_file_names = in_dir.entryList(QDir::Files);
    // 创建输出文件夹，如果不存在的话
    QDir out_dir(out_folder_name);
    if (!out_dir.exists()) {
        out_dir.mkpath(out_folder_name);
    }
    // 遍历输入文件夹中的所有文件
    for (int i = 0; i < in_file_names.size(); i++) {
        // 获取输入文件的完整路径
        QString in_file_path = in_dir.filePath(in_file_names[i]);
        // 获取输出文件的完整路径，使用相同的文件名
        QString out_file_path = out_dir.filePath(in_file_names[i]);
        // 对输入文件进行SM4加密或解密，并输出到输出文件中
        if (!sm4_crypt_file(in_file_path, out_file_path, encrypt)) {
            return false; // 加密或解密失败，返回失败
        }
    }
    return true; // 加密或解密成功，返回成功
}
