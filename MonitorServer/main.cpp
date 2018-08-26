#include "dialog.h"
#include <QApplication>
//#include <QStyleFactory>

int main(int argc, char *argv[])
{
    //QApplication::setStyle(QStyleFactory::create("fusion"));

    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
