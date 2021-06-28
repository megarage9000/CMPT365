#include "bmpfile.h"

BMPFile::BMPFile(QString fileLocation)
{
    imageFile = QImage(fileLocation);
    if(imageFile.isNull()) {
        printf("Unable to to get image\n");
    }
    else {
        printf("Got an image!\n");
    }
}

QImage BMPFile::getAutoLevel() {
    QImage newImage = imageFile.convertToFormat(QImage::Format_RGB32);
    QRgb * bits = (QRgb*)newImage.constBits();
    int size = newImage.width() * newImage.height();
    for(int i = 0; i <= size; i++) {
        std::cout << "i = " << i << std::endl;
        std::cout << "Color R = "
                << qRed(bits[size + i]) << ", G = "
                << qGreen(bits[size + i]) << ", B = "
                << qBlue(bits[size + i]) << std::endl;
    }
    std::cout <<" Finished!" << std::endl;



    return QImage();
}

struct colorIntensityInfo {
    int numPixels;
    int intensity;
    int newIntensity;
};
