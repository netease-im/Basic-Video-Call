#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<uint32_t>("uint32_t");
    qRegisterMetaType<std::vector<unsigned char>>("std::vector<unsigned char>");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
