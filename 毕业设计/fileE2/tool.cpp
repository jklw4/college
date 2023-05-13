#include "tool.h"
#include <qfileinfo.h>

// 定义一个函数，传入一个原文件的路径，一个新文件夹的路径和一个新文件名备注后缀newTip，返回一个新文件的路径
QString generateNewFilePath(const QString &originalFile, const QString &newDirPath, const QString &newTip) {
    // 获取原文件的后缀名
    QString originalSuffix = QFileInfo(originalFile).suffix();
    qInfo() << "Original suffix:" << originalSuffix;

    // 获取不带后缀名的文件名
    QString baseName = QFileInfo(originalFile).baseName();
    qInfo() << "Base name:" << baseName;

    // 生成xin文件的名字，添加新后缀名
    QString newFile = baseName.append("_").append(newTip).append(".").append(originalSuffix);
    qInfo() << "new file:" << newFile;

    // 生成加密文件的完整路径，添加新文件夹前缀
    QString newFilePath = newDirPath;
    newFilePath.append("/").append(newFile);
    qInfo() << "new file path:" << newFilePath;

    // 返回加密文件的路径
    return newFilePath;
}


// 定义一个填充函数，使用PKCS#7或PKCS#5标准
int padding(unsigned char *data, int len)
{
    // 计算需要填充的字节数
    int pad = 16 - (len % 16);

    // 在数据末尾添加填充字节，每个字节的值等于填充字节数
    for (int i = 0; i < pad; i++)
    {
        data[len + i] = pad;
    }

    // 返回填充后的数据长度
    return len + pad;
}

// 定义一个去除填充函数，使用PKCS#7或PKCS#5标准
int unpadding(unsigned char *data, int len)
{
    // 检查数据长度是否是16字节的倍数
    if (len % 16 != 0)
    {
        return -1; // 数据长度不正确，返回错误
    }

    // 获取最后一个字节的值，即填充字节数
    int pad = data[len - 1];

    // 检查填充字节数是否在合理范围内
    if (pad < 1 || pad > 16)
    {
        return -1; // 填充字节数不正确，返回错误
    }

    // 检查数据末尾是否都是填充字节，每个字节的值等于填充字节数
    for (int i = 0; i < pad; i++)
    {
        if (data[len - 1 - i] != pad)
        {
            return -1; // 填充字节不正确，返回错误
        }
    }

    // 返回去除填充后的数据长度
    return len - pad;
}

