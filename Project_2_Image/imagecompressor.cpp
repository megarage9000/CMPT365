#include "imagecompressor.h"


imageCompressor::imageCompressor(BMPFile file){
    convertToYCov(file);
}

void imageCompressor::convertToYCov(BMPFile file) {
    Y = std::vector<std::vector<int>>();
    Co = std::vector<std::vector<int>>();
    Cg = std::vector<std::vector<int>>();

    int width = file.getRgbWidth();
    int height = file.getRgbHeight();

    std::vector<int> YRow;
    std::vector<int> CoRow;
    std::vector<int> CgRow;

    for(int row = 0; row < height; row++){
        YRow = std::vector<int>();
        if(row % 2 == 0) {
            CoRow = std::vector<int>();
            CgRow = std::vector<int>();
        }
        for(int col = 0; col < width; col++){
            QRgb rgb = file.getRgbs()[row][col];
            int red = qRed(rgb);
            int green = qGreen(rgb);
            int blue = qBlue(rgb);


        }
    }



}


