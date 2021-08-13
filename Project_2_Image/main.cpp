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

    BMPFile file = BMPFile("/home/megarage9000/repos/CMPT365/Project_2_test_files/Project2/bmp-sample-3.bmp");

    YCoCgConversion::RGBToYCoCg conversionA = YCoCgConversion::RGBToYCoCg(file.getRgbs());
    dctTransform transformY = dctTransform(conversionA.Y, false);
    dctTransform transformCo = dctTransform(conversionA.Co, false);
    dctTransform transformCg = dctTransform(conversionA.Cg, false);

    YCoCgConversion::YCoCgToRGB conversionBA = YCoCgConversion::YCoCgToRGB(
                    dctTransform(transformY.result, true).result,
                    dctTransform(transformCo.result, true).result,
                    dctTransform(transformCg.result, true).result
                );

    YCoCgConversion::YCoCgToRGB conversionBB = YCoCgConversion::YCoCgToRGB(
                    conversionA.Y,
                    conversionA.Co,
                    conversionA.Cg
                );


    ImageHelpers::saveImage("/home/megarage9000/repos/CMPT365/Project_2_test_files/Project2/bmp-sample-converteddct.bmp", conversionBA.rgbs);
    ImageHelpers::saveImage("/home/megarage9000/repos/CMPT365/Project_2_test_files/Project2/bmp-sample-converted.bmp", conversionBB.rgbs);
    w.show();
    return a.exec();
}
