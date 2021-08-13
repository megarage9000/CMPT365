#include "imagefilehelpers.h"

namespace ImageHelpers {
    void saveImage(QString path, std::vector<std::vector<QRgb>> rgbs)
    {
        int width = rgbs[0].size();
        int height = rgbs.size();

        QImage image = QImage(width, height, QImage::Format_RGB32);
        for(int row = 0; row < height; row++) {
            QRgb * rgbVals = (QRgb *)image.scanLine(row);
            for(int col = 0; col < width; col++){
                rgbVals[col] = rgbs[row][col];
            }
        }

        QFile fileToSave(path);
        if(fileToSave.open(QIODevice::WriteOnly | QIODevice::Truncate)){
            image.save(&fileToSave, "bmp");
        }
    }

    QImage getImage(QString path)
    {
        return QImage(path).convertToFormat(QImage::Format_RGB32);
    }
}
