#include "stdafx.h"
#include "Creamy.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Creamy w;
    w.show();
    return a.exec();
}
