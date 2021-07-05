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


int getHistEqualVal(int numPixels, int totalNumPixels, int * prevCdf) {
    int pdf = numPixels / totalNumPixels;
    *prevCdf = *prevCdf + pdf;
    return *prevCdf * 255;
}

QImage BMPFile::getAutoLevel() {
    QImage newImage = imageFile.convertToFormat(QImage::Format_RGB32);
    QRgb * bits = (QRgb*)imageFile.constBits();

    int size = newImage.width() * newImage.height();
    int imageRgbs [3][256];

    std::cout << "getting old image bits" << std::endl;
    for(int i = size; i < size; i++) {
        imageRgbs[0][qRed(bits[i])]++;
        imageRgbs[1][qGreen(bits[i])]++;
        imageRgbs[2][qBlue(bits[i])]++;
    }

    std::cout << "making new image" << std::endl;
    QRgb * newBits = (QRgb*)newImage.bits();
    int rCdf = 0, gCdf = 0, bCdf = 0;
    for(int j = 0; j < size; j++) {

        newBits[j] = QColor(
                    getHistEqualVal(imageRgbs[0][qRed(newBits[j])], size, &rCdf),
                    getHistEqualVal(imageRgbs[1][qGreen(newBits[j])], size, &gCdf),
                    getHistEqualVal(imageRgbs[2][qBlue(newBits[j])], size, &bCdf)
                    ).rgba();
    }

    if(newImage.save("/home/NewImage") == true) {
        std::cout << "finished image manipulation" << std::endl;
    }
    else {
        std::cout << "unable to save new image" << std::endl;
    }
}



