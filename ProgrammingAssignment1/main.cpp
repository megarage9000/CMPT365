#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include "matrixlift.h"

void printRgb(int rgbVals[], int size);
void printYCgCo(int yCgCoVals[], int size);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int rgbVals[3] = {
        12, 40, 32
    };

    int matrixTransform[3];
    int matrixLifting[3];

    std::cout << "Original RGB values";
    printRgb(rgbVals, sizeof (rgbVals) / sizeof (rgbVals[0]));

    std::cout << "Matrix transformation:" << std::endl;
    MatrixLift::YCoCgMuliplication(rgbVals, matrixTransform, sizeof(rgbVals) / sizeof(rgbVals[0]), 3);
    printYCgCo(matrixTransform, sizeof(matrixTransform) / sizeof(matrixTransform[0]));

    std::cout << "Matrix lifting:" << std::endl;
    MatrixLift::YCoCgLifitng(rgbVals, matrixLifting, sizeof(rgbVals) / sizeof(rgbVals[0]), 3);
    printYCgCo(matrixLifting, sizeof(matrixLifting) / sizeof(matrixLifting[0]));
    return a.exec();
}

void printRgb(int rgbVals[], int size) {
    if(size != 3){
        return;
    }
    std::cout << "RGB values :" << std::endl <<
                 "G = " << rgbVals[0] << std::endl <<
                 "B = " << rgbVals[1] << std::endl <<
                 "R = " << rgbVals[2] << std::endl;
}

void printYCgCo(int yCgCoVals[], int size) {
    if(size != 3){
        return;
    }
    std::cout << "YCgCo values :" << std::endl <<
                 "Cg = " << yCgCoVals[0] << std::endl <<
                 "Y = " << yCgCoVals[1] << std::endl <<
                 "Co = " << yCgCoVals[2] << std::endl;
}
