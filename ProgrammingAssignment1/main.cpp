#include "mainwindow.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    float test = 2.2f;
    std::cout << "Test val before shift " << test << std::endl;
    test = (int)test << 1;
    std::cout << "Test value after shift " << test << std::endl;
    return a.exec();
}
