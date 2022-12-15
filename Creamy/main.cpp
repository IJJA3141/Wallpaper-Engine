#include "mainwindow.h"
#include <iostream>
#include <QApplication>

int* ptr = new int(10);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    std::cout << *ptr << std::endl;
    return a.exec();
}
