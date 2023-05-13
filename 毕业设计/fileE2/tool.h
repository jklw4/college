#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

// 定义一个函数，传入一个原文件的路径，一个新文件夹的路径和一个新后缀名，返回一个新文件的路径
QString generateNewFilePath(const QString &originalFile, const QString &newDirPath, const QString &newSuffix);

// 定义一个填充函数，使用PKCS#7或PKCS#5标准
int padding(unsigned char *data, int len);

// 定义一个去除填充函数，使用PKCS#7或PKCS#5标准
int unpadding(unsigned char *data, int len);
