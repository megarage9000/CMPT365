#ifndef FROMLITTLEENDIAN_H
#define FROMLITTLEENDIAN_H

#include <QFile>
#include <iostream>
#include <QtEndian>

template<class convertedType>
convertedType fromLittleEndian(QFile * file, int numBytes) {
    char * bits = new char[numBytes];
    file->read(bits, numBytes);
    convertedType result = qFromLittleEndian<convertedType>((uchar*)bits);
    delete[] bits;
    return result;
}

#endif // FROMLITTLEENDIAN_H
