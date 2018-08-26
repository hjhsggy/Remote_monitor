#include "dialog.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置程序风格
    //QApplication::setStyle(QStyleFactory::create("Fusion"));

    Dialog w;
    w.show();

    return a.exec();
}
