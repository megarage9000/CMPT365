#include "mainwindow.h"

#include <QApplication>
#include <bmpfile.h>
#include "ycocgconversion.h"
#include "dcttransform.h"
#include "imagefilehelpers.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    BMPFile file = BMPFile("/home/megarage9000/repos/CMPT365/Project_2_test_files/Project2/bmp-sample-2.bmp");

//    YCoCgConversion::RGBToYCoCg conversionA = YCoCgConversion::RGBToYCoCg(file.getRgbs());
//    YCoCgConversion::YCoCgToRGB conversionB = YCoCgConversion::YCoCgToRGB(
//                    conversionA.Y,
//                    conversionA.Co,
//                    conversionA.Cg
//                );

//    ImageHelpers::saveImage("/home/megarage9000/repos/CMPT365/Project_2_test_files/Project2/bmp-sample-converted.bmp", conversionB.rgbs);

    std::vector<std::vector<int>> values = {
        {10, 10, 10, 10, 10, 10, 10, 10, 13},
        {11, 11, 11, 11, 11, 11, 11, 11, 13},
        {12, 12, 12, 12, 12, 12, 12, 12, 13},
        {10, 10, 10, 10, 10, 10, 10, 10, 13},
        {11, 11, 11, 11, 11, 11, 11, 11, 13},
        {12, 12, 12, 12, 12, 12, 12, 12, 13},
        {10, 10, 10, 10, 10, 10, 10, 10, 13},
        {11, 11, 11, 11, 11, 11, 11, 11, 14},
        {11, 11, 11, 11, 11, 11, 11, 11, 13},
        {11, 11, 11, 11, 11, 11, 11, 11, 13},
    };

    std::vector<std::vector<int>> values2 = {
        {12, 10, 11, 20, 23, 25, 12, 12, 42},
        {12, 10, 11, 20, 23, 25, 12, 12, 42},
        {12, 10, 11, 20, 23, 25, 12, 12, 42},
        {12, 10, 11, 20, 23, 25, 12, 12, 42},
        {12, 10, 11, 20, 23, 25, 12, 12, 42},
        {12, 10, 11, 20, 23, 25, 12, 12, 42},
        {12, 10, 11, 20, 23, 25, 12, 12, 42},
        {12, 10, 11, 20, 23, 25, 12, 12, 42},
    };

    std::vector<std::vector<double>> subMatrix =
            createSubMatrix(values, 2, 2, 6, 6);

    mapMatrixValues(&values2, &subMatrix, 1, 1, 5, 5);

    int width = subMatrix[0].size();
    int height = subMatrix.size();

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            std::cout << subMatrix[i][j] << "|";
        }
        std::cout << "\n";
    }
    std::cout << "-------------------------------------\n";
    int width2 = values2[0].size();
    int height2 = values2.size();

    for(int i = 0; i < height2; i++){
        for(int j = 0; j < width2; j++){
            std::cout << values2[i][j] << "|";
        }
        std::cout << "\n";
    }
    std::cout << "-------------------------------------\n";

    w.show();
    return a.exec();
}
