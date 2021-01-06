#include <QApplication>

#include "mainwindow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    w.setWindowTitle(QString::fromLocal8Bit("比索汇率转换"));
    w.show();

    return a.exec();
}
