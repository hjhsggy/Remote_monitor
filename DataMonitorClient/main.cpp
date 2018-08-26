#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;

    //注意屏幕的坐标
    w.move(-8,0);
    w.show();

    return a.exec();
}
