#include <QApplication>
#include <QFont>
#include "join_widget.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication a(argc, argv);
    QFont font;
    font.setFamily("Microsoft YaHei");
    a.setFont(font);

    JoinWidget demo;
    demo.show();

    return a.exec();
}
