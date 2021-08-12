#ifndef BMPFILE_H
#define BMPFILE_H


#include <string>
#include <QString>
#include <QImage>
#include <iostream>
#include <QVector>
#include <vector>
#include <QFile>

class BMPFile
{
public:
    BMPFile();
    BMPFile(QString fileLocation);
    void calculateImages(QString fileLocation);
    QImage getOriginal();
    QImage getAutoLevel();
    QImage getGrayScale();
    QImage getGrayScaleDither();

    void outputRgbValues();
    void freeRgbValues();

private:
    void calculateAutoLevel();
    void calculateGrayScale();
    void calculateDither();

    void getRGBData();

    QImage imageFile;
    QImage imageFileGrayScale;
    QImage imageFileDither;
    QImage imageAutoLevel;
    int ditherMatrix[4][4] = {
        {7, 9, 0, 4},
        {8, 10, 1, 2},
        {7, 11, 12, 14},
        {15, 7, 5, 4}
    };
    int getDitherValue(int row, int col) {
        return ditherMatrix[row][col];
    }

    QRgb * values = NULL;
    int imageWidth;
    int imageHeight;
    QRgb getValueAt(int row, int col);
    void setValueAt(int row, int col, QRgb value);

};

#endif // BMPFILE_H
