#include "mainwindow.h"

#include <QApplication>
#include <bmpfile.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    BMPFile file = BMPFile("/home/megarage9000/repos/CMPT365/Project_2_test_files/Project2/bmp-sample-3.bmp");
    file.outputRgbValues();
    w.show();
    return a.exec();
}
