#include "siae.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SIAE w;
    w.show();
    return a.exec();
}
