#include "bmpfile.h"

BMPFile::BMPFile(QString fileLocation)
{
    imageFile = QImage(fileLocation).convertToFormat(QImage::Format_RGB32);
    if(imageFile.isNull()) {
        printf("Unable to to get image\n");
    }
    else {
        printf("Got an image!\n");
    }
    getGrayScale();
}

// --- Grayscale ---
QImage BMPFile::getGrayScale() {
    int width = imageFile.width();
    int height = imageFile.height();

    imageFileGrayScale = imageFile.copy();
    for(int y = 0; y < height; y++) {
        QRgb * rgbVal = (QRgb * )imageFileGrayScale.scanLine(y);
        for(int x = 0; x < width; x++) {

            // Using the YUV color space weights to get grayscale value
            // Source: https://www.kdnuggets.com/2019/12/convert-rgb-image-grayscale.html (Linear Approximation),
            // and Lecture notes

            int red = qRed(rgbVal[x]) * 0.299;
            int green = qGreen(rgbVal[x]) * 0.587;
            int blue = qBlue(rgbVal[x]) * 0.114;
            int grayScaleValue = red + green + blue;

            rgbVal[x] = qRgb(grayScaleValue, grayScaleValue, grayScaleValue);
        }
    }

    QString fileName("/home/megarage9000/repos/CMPT365/Project_1/bmpTestFiles/grayScale.bmp");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        if(imageFileGrayScale.save(&file) == true) {
            std::cout << "finished image manipulation" << std::endl;
            return imageFileGrayScale;
        }
        else {
            std::cout << "unable to save new image" << std::endl;
        }
    }
    return imageFileGrayScale;
}

// --- GrayscaleDither ---
QImage BMPFile::getGrayScaleDither() {
    int width = imageFileGrayScale.width();
    int height = imageFileGrayScale.height();

    QImage ditheredImage = imageFileGrayScale.copy();
    for(int y = 0; y < height; y++) {
        QRgb * rgbVal = (QRgb *)ditheredImage.scanLine(y);
        for(int x = 0; x < width; x++) {
            int ditherRow = y % 4;
            int ditherCol = x % 4;
            int normalizedValue = qRed(rgbVal[x]) / 17;
            int ditherValue = getDitherValue(ditherRow, ditherCol);
            if(normalizedValue > ditherValue){
                rgbVal[x] = qRgb(255, 255, 255);
            }
            else{
                rgbVal[x] = qRgb(0, 0, 0);
            }
        }
    }

    QString fileName("/home/megarage9000/repos/CMPT365/Project_1/bmpTestFiles/grayScaleDither.bmp");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        if(ditheredImage.save(&file) == true) {
            std::cout << "finished image manipulation" << std::endl;
            return ditheredImage;
        }
        else {
            std::cout << "unable to save new image" << std::endl;
        }
    }
    return ditheredImage;


}

// --- Autolevel ---
struct rgbPdfCdf {
    int numPixels;
    float pdf;
    int newRgbVal;
};



QImage BMPFile::getAutoLevel() {
    // Auto color level is done via histogram equalization
    // Source: https://www.tutorialspoint.com/dip/histogram_equalization.htm

    int width = imageFile.width();
    int height = imageFile.height();
    int size = width * height;
    struct rgbPdfCdf imageRgbs [3][256];

    // Intializing values to calculate new RGB values
    for(int j = 0; j < 256; j++) {
        imageRgbs[0][j].numPixels = 0;
        imageRgbs[0][j].pdf = 0;
        imageRgbs[0][j].newRgbVal = 0;

        imageRgbs[1][j].numPixels = 0;
        imageRgbs[1][j].pdf = 0;
        imageRgbs[1][j].newRgbVal = 0;

        imageRgbs[2][j].numPixels = 0;
        imageRgbs[2][j].pdf = 0;
        imageRgbs[2][j].newRgbVal = 0;
    }

    // Gather number of pixels per channel at respective intensities
    for(int y = 0; y < height; y++) {
        QRgb *rgbVal = (QRgb *)imageFile.constScanLine(y);
        for(int x = 0; x < width; x++) {
            imageRgbs[0][qRed(rgbVal[x])].numPixels++;
            imageRgbs[1][qGreen(rgbVal[x])].numPixels++;
            imageRgbs[2][qBlue(rgbVal[x])].numPixels++;
        }
    }

    // Calculate new RGB values using Histogram Equalization
    float prevCdfRed = 0, prevCdfGreen = 0, prevCdfBlue = 0;
    for(int j = 0; j < 256; j++) {

        imageRgbs[0][j].pdf = (float)imageRgbs[0][j].numPixels / size;
        prevCdfRed += imageRgbs[0][j].pdf;
        imageRgbs[0][j].newRgbVal = prevCdfRed * (255);

        imageRgbs[1][j].pdf = (float)imageRgbs[1][j].numPixels / size;
        prevCdfGreen += imageRgbs[1][j].pdf;
        imageRgbs[1][j].newRgbVal = prevCdfGreen * (255);

        imageRgbs[2][j].pdf = (float)imageRgbs[2][j].numPixels / size;
        prevCdfBlue += imageRgbs[2][j].pdf;
        imageRgbs[2][j].newRgbVal = prevCdfBlue * (255);
    }

    // Create new image with auto-corrected colors
    QImage newImage = imageFile.copy();
    int newRed, newGreen, newBlue, prevRed, prevGreen, prevBlue;
    for(int y = 0; y < height; ++y) {
        QRgb * newRgbVal = (QRgb *)newImage.scanLine(y);
        for(int x = 0; x < width; ++x) {

            prevRed = qRed(newRgbVal[x]);
            prevGreen = qGreen(newRgbVal[x]);
            prevBlue = qBlue(newRgbVal[x]);

            newRed = imageRgbs[0][prevRed].newRgbVal;
            newGreen = imageRgbs[1][prevGreen].newRgbVal;
            newBlue = imageRgbs[2][prevBlue].newRgbVal;

            newRgbVal[x] = qRgb(newRed, newGreen, newBlue);
        }
    }
    // Saving (Not needed for the project)
    QString fileName("/home/megarage9000/repos/CMPT365/Project_1/bmpTestFiles/autoCorrect.bmp");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        if(newImage.save(&file) == true) {
            std::cout << "finished image manipulation" << std::endl;
            return newImage;
        }
        else {
            std::cout << "unable to save new image" << std::endl;
        }
    }
    return newImage;
}



