#include "mainwindow.h"

#include <QApplication>
#include <bmpfile.h>
#include "ycocgconversion.h"
#include "imagefilehelpers.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    BMPFile file = BMPFile("/home/megarage9000/repos/CMPT365/Project_2_test_files/Project2/bmp-sample-3.bmp");

    YCoCgConversion::RGBToYCoCg conversionA = YCoCgConversion::RGBToYCoCg(file.getRgbs());
    YCoCgConversion::YCoCgToRGB conversionB = YCoCgConversion::YCoCgToRGB(
                    conversionA.Y,
                    conversionA.Co,
                    conversionA.Cg
                );

    ImageHelpers::saveImage("/home/megarage9000/repos/CMPT365/Project_2_test_files/Project2/bmp-sample-converted.bmp", conversionB.rgbs);
    w.show();
    return a.exec();
}
