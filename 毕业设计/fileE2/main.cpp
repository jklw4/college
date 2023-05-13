#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow::a = &a; //将a的地址赋给MainWindow类的静态指针
    // 读取qss文件的内容
    QFile file(":/style/Obit/Obit.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    // 设置应用程序的样式
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
