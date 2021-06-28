#ifndef BMPFILE_H
#define BMPFILE_H


#include <string>
#include <QString>
#include <QImage>
#include <iostream>

class BMPFile
{
public:
    BMPFile(QString fileLocation);
    QImage getAutoLevel();

private:
    QImage imageFile;
};

#endif // BMPFILE_H
