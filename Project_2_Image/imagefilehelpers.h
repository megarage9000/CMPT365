#ifndef IMAGEFILEHELPERS_H
#define IMAGEFILEHELPERS_H

#include <iostream>
#include <vector>
#include <QString>
#include <QImage>
#include <QFile>

namespace ImageHelpers {

    void saveImage(QString path, std::vector<std::vector<QRgb>> rgbs);
    QImage getImage(QString path);
}

#endif // IMAGEFILEHELPERS_H
